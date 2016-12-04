#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QImageReader>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>
#include <QStandardPaths>
#include <QImageWriter>
#include <QListWidgetItem>
#include <QDirIterator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //disable actions until we have a main image
    ui->actionLoad_Optional_Tile_Images->setEnabled(false);

    //refresh the image when an item is checked
    connect(ui->listWidget,SIGNAL(itemChanged(QListWidgetItem*)),this,SLOT(itemChanged(QListWidgetItem*)));
    //refresh the image when items are re-ordered
    connect(ui->listWidget->model(),SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),this,SLOT(rowsMoved(QModelIndex,int,int,QModelIndex,int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        dialog.setDirectory(QCoreApplication::applicationDirPath());
    }

    //load a list of all the possible images formats
    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = (acceptMode == QFileDialog::AcceptOpen
                                               ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes());

    foreach (const QByteArray &mimeTypeName, supportedMimeTypes) {
        mimeTypeFilters.append(mimeTypeName);
    }
    mimeTypeFilters.sort();

    //filter the file dialog to only the supported image file types and default to png
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/png");
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setAcceptMode(acceptMode);
    if (acceptMode == QFileDialog::AcceptSave) {
        dialog.setDefaultSuffix("png");
    }
}

void MainWindow::loadTilesetBase()
{
    //ask for the base image
    QFileDialog dialog(this, tr("Select Base Tileset Image"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    if (dialog.exec() == QDialog::Accepted) {
        bool firstLoad = (m_baseImage.isNull());

        QString selectedFileName = dialog.selectedFiles().first();

        //try to load the image selected
        QImage baseImage = loadFile(selectedFileName,false);
        if (!baseImage.isNull()) {
            setWindowFilePath(selectedFileName);
            //set our image before looking for optional ones as validation checks the size
            m_image = baseImage;
            m_baseImage = baseImage;

            //use the main image file to determine the type of file and set a filter
            QFileInfo fiBase(selectedFileName);
            m_baseImageFileName = fiBase.fileName();
            QString filter = "*." + fiBase.suffix();

            m_loadResults.clear();
            //use the filter to find all other images of this type in the main image's dir and subdirs
            //iterate through the files found and load them
            QDirIterator it(fiBase.dir().path(), QStringList() << filter, QDir::Files, QDirIterator::Subdirectories);
            while (it.hasNext()) {
                it.next();
                if (it.fileInfo().absoluteFilePath() != fiBase.absoluteFilePath()) { //skip the base file
                    loadFile(it.filePath());
                }
            }
            checkLoadErrors();

            //display the base image
            refreshImage();

            //check the optional images
            if (m_optionalImages.count() > 0) {
                if (!firstLoad) {
                    //if we've changed the base image, validate any optional files we have
                    checkLoadedImages();
                }
                loadImgList();
            }
            //finally enable any actions that require a base image
            ui->actionLoad_Optional_Tile_Images->setEnabled(true);
        }
    }
}

void MainWindow::checkLoadedImages() {
    //check if new base image matches optional image sizes, and if not, remove them
    QMutableHashIterator<QString,QImage> it(m_optionalImages);
    while(it.hasNext()) {
        it.next();
        if (!isValidImage(it.value(),it.key())) {
            it.remove();
        }
    }
}

bool MainWindow::isValidImage(const QImage &img, const QString &fileName) {
    return (!img.isNull() && img.size() == m_baseImage.size() && fileName != m_baseImageFileName);
}
bool MainWindow::isValidFile(const QFileInfo &fi,const QImage &img) {
    if (!isValidImage(img,fi.fileName())) {
        recordError(fi.filePath(),tr("Invalid image or image dimensions don't match."));
        return false;
    } else if (m_optionalImages.contains(fi.fileName())) {
        recordError(fi.filePath(),tr("A file with this name has already been loaded."));
        return false;
    } else {
        return true;
    }
}

void MainWindow::refreshImage() {
    ui->lblImage->setPixmap(QPixmap::fromImage(m_image));
    ui->lblImage->adjustSize();
}

void MainWindow::loadTilesetVariations() {
    QFileDialog dialog(this, tr("Select Optional Tileset Images"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);
    if (dialog.exec() == QDialog::Accepted) {
        m_loadResults.clear();
        foreach(QString filePath, dialog.selectedFiles()) {
            loadFile(filePath);
        }
        loadImgList();
        checkLoadErrors();
    }
}

void MainWindow::checkLoadErrors(){
    if (m_loadResults.count() > 0) {
        QMessageBox loadErrors;
        loadErrors.setText(tr("One or more images could not be loaded!"));
        loadErrors.setDetailedText(m_loadResults.join("\n"));
        loadErrors.setIcon(QMessageBox::Warning);

        //add a spacer to adjust the size of the dialog since setFixedSize is broken
        QSpacerItem* horizontalSpacer = new QSpacerItem(500, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
        QGridLayout* layout = (QGridLayout*)loadErrors.layout();
        layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());

        loadErrors.exec();
    }
}

void MainWindow::loadImgList() {
    ui->listWidget->clear();

    //ui->listWidget->setSortingEnabled(false);
    foreach(QString fileName, m_optionalImages.keys()) {
        QFileInfo fi(fileName);
        QListWidgetItem *newItem = new QListWidgetItem(QIcon(QPixmap::fromImage(m_optionalImages.value(fileName))),
                                                       fi.baseName(),
                                                       ui->listWidget);
        newItem->setFlags(newItem->flags() | Qt::ItemIsUserCheckable);
        newItem->setCheckState(Qt::Unchecked);
        newItem->setToolTip(fileName);
        newItem->setData(Qt::UserRole,fileName);
        ui->listWidget->addItem(newItem);
    }
    //ui->listWidget->setSortingEnabled(true);
    ui->listWidget->sortItems(Qt::AscendingOrder);
}

QImage MainWindow::loadFile(const QString &filePath, const bool &isBatch) {
    QImageReader reader(filePath);
    QString errMsg;
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        errMsg = reader.errorString();
        if (!isBatch) {
            QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(filePath), reader.errorString()));
        } else {
            recordError(filePath,errMsg);
        }
        return QImage();
    }

    if (isBatch) {
        QFileInfo fi(filePath);
        if (isValidFile(fi,newImage)) {
            m_optionalImages.insert(fi.fileName(),newImage);
            return newImage;
        } else {
            return QImage();
        }
    }
    return newImage;
}

void MainWindow::recordError(const QString &filePath, const QString &error){
    m_loadResults << tr("%1\n  Error: %2\n").arg(filePath).arg(error);
}

void MainWindow::saveAs()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

bool MainWindow::saveFile(const QString &fileName)
{
    QImageWriter writer(fileName);

    if (!writer.write(m_image)) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot write %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName)), writer.errorString());
        return false;
    }
    const QString message = tr("Saved \"%1\"").arg(QDir::toNativeSeparators(fileName));
    statusBar()->showMessage(message);
    return true;
}

void MainWindow::apply() {
    //create a new image from the base image
    m_image = QImage(m_baseImage.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&m_image);

    //paint background
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(m_image.rect(), Qt::transparent);
    //paint base image
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, m_baseImage);

    //paint overlays
    for(int idx = 0; idx < ui->listWidget->count(); ++idx)
    {
        QListWidgetItem* item = ui->listWidget->item(idx);
        if (item->checkState() == Qt::Checked) {
            QString fileName = item->data(Qt::UserRole).toString();
            painter.drawImage(0, 0,m_optionalImages.value(fileName));
        }
    }

    //    painter.setCompositionMode(QPainter::CompositionMode_Overlay);
    //    painter.fillRect(m_image.rect(), Qt::red);
    painter.end();

    refreshImage();
}

void MainWindow::reset() {
    m_image = m_baseImage;
    refreshImage();
}

void MainWindow::clearList() {
    m_optionalImages.clear();
    ui->listWidget->clear();
}

void MainWindow::quit() {
    QCoreApplication::quit();
}

void MainWindow::itemChanged(QListWidgetItem *item) {
    Q_UNUSED(item);
    apply();
}
void MainWindow::rowsMoved(const QModelIndex &parent, int start, int end, const QModelIndex &destination, int row) {
    Q_UNUSED(parent);
    Q_UNUSED(start);
    Q_UNUSED(end);
    Q_UNUSED(destination);
    Q_UNUSED(row);
    apply();
}
