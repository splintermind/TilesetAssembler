#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QListWidgetItem>
#include <QDir>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QImage m_baseImage; //original base image chosen
    QString m_baseImageFileName; //base image file name
    QImage m_image; //current image being modified
    QHash<QString,QImage> m_optionalImages; //other images that may be combined with the base
    QStringList m_loadResults; //store load error information

    QImage loadFile(const QString &filePath, const bool &isOptional = true);
    bool saveFile(const QString &fileName);

    void refreshImage();

    bool isValidImage(const QImage &img, const QString &fileName);
    bool isValidFile(const QFileInfo &fi, const QImage &img);
    void loadImgList();
    void recordError(const QString &filePath, const QString &error);

    void checkLoadedImages();
    void checkLoadErrors();

private slots:
    void loadTilesetBase();
    void loadTilesetVariations();

    void saveAs();
    void apply();
    void reset();
    void clearList();
    void quit();

    void itemChanged(QListWidgetItem *item);
    void rowsMoved(const QModelIndex & parent, int start, int end, const QModelIndex & destination, int row);

};

#endif // MAINWINDOW_H
