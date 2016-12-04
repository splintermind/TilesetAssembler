/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_Base_Image;
    QAction *actionLoad_Optional_Tile_Images;
    QAction *actionSave_As;
    QAction *actionQuit;
    QAction *actionReset;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QLabel *lblImage;
    QVBoxLayout *verticalLayout;
    QLabel *lblLayerInfo;
    QListWidget *listWidget;
    QPushButton *btnClearOptional;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(906, 628);
        actionLoad_Base_Image = new QAction(MainWindow);
        actionLoad_Base_Image->setObjectName(QStringLiteral("actionLoad_Base_Image"));
        actionLoad_Optional_Tile_Images = new QAction(MainWindow);
        actionLoad_Optional_Tile_Images->setObjectName(QStringLiteral("actionLoad_Optional_Tile_Images"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QStringLiteral("actionReset"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setMinimumSize(QSize(545, 545));
        scrollArea->setFrameShape(QFrame::StyledPanel);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 543, 543));
        horizontalLayout = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lblImage = new QLabel(scrollAreaWidgetContents);
        lblImage->setObjectName(QStringLiteral("lblImage"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblImage->sizePolicy().hasHeightForWidth());
        lblImage->setSizePolicy(sizePolicy1);
        lblImage->setFrameShape(QFrame::NoFrame);
        lblImage->setLineWidth(1);
        lblImage->setScaledContents(false);
        lblImage->setAlignment(Qt::AlignCenter);
        lblImage->setMargin(0);
        lblImage->setIndent(-1);

        horizontalLayout->addWidget(lblImage);

        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_2->addWidget(scrollArea);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(4);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lblLayerInfo = new QLabel(centralWidget);
        lblLayerInfo->setObjectName(QStringLiteral("lblLayerInfo"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lblLayerInfo->sizePolicy().hasHeightForWidth());
        lblLayerInfo->setSizePolicy(sizePolicy2);
        lblLayerInfo->setMinimumSize(QSize(0, 0));
        lblLayerInfo->setMaximumSize(QSize(16777215, 16777215));
        lblLayerInfo->setAlignment(Qt::AlignCenter);
        lblLayerInfo->setWordWrap(true);

        verticalLayout->addWidget(lblLayerInfo);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setDragDropMode(QAbstractItemView::InternalMove);
        listWidget->setDefaultDropAction(Qt::TargetMoveAction);
        listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        listWidget->setIconSize(QSize(32, 32));
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setUniformItemSizes(true);
        listWidget->setSelectionRectVisible(false);
        listWidget->setSortingEnabled(false);

        verticalLayout->addWidget(listWidget);

        btnClearOptional = new QPushButton(centralWidget);
        btnClearOptional->setObjectName(QStringLiteral("btnClearOptional"));

        verticalLayout->addWidget(btnClearOptional);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 906, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        mainToolBar->addAction(actionLoad_Base_Image);
        mainToolBar->addAction(actionLoad_Optional_Tile_Images);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionReset);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSave_As);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionQuit);

        retranslateUi(MainWindow);
        QObject::connect(actionLoad_Base_Image, SIGNAL(triggered()), MainWindow, SLOT(loadTilesetBase()));
        QObject::connect(actionLoad_Optional_Tile_Images, SIGNAL(triggered()), MainWindow, SLOT(loadTilesetVariations()));
        QObject::connect(actionReset, SIGNAL(triggered()), MainWindow, SLOT(reset()));
        QObject::connect(actionSave_As, SIGNAL(triggered()), MainWindow, SLOT(saveAs()));
        QObject::connect(btnClearOptional, SIGNAL(clicked()), MainWindow, SLOT(clearList()));
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(quit()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Tileset Assembler", 0));
        actionLoad_Base_Image->setText(QApplication::translate("MainWindow", "Load Tileset", 0));
#ifndef QT_NO_TOOLTIP
        actionLoad_Base_Image->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Browse for the base tileset image to load.</p><p>This should be the tileset without variations.</p><p><span style=\" color:#006fa7;\">Additionally this will find and load any images of the same type in the directory or sub-directories.</span></p></body></html>", 0));
#endif // QT_NO_TOOLTIP
        actionLoad_Optional_Tile_Images->setText(QApplication::translate("MainWindow", "Load Variations", 0));
#ifndef QT_NO_TOOLTIP
        actionLoad_Optional_Tile_Images->setToolTip(QApplication::translate("MainWindow", "Browse for tileset images which contain variations to overlay.", 0));
#endif // QT_NO_TOOLTIP
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As...", 0));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0));
        actionReset->setText(QApplication::translate("MainWindow", "Reset", 0));
#ifndef QT_NO_TOOLTIP
        actionReset->setToolTip(QApplication::translate("MainWindow", "Reset the tileset back to it's original state.", 0));
#endif // QT_NO_TOOLTIP
        lblImage->setText(QString());
        lblLayerInfo->setText(QApplication::translate("MainWindow", "Images are applied top to bottom.\n"
"Drag and drop to change the order.", 0));
        btnClearOptional->setText(QApplication::translate("MainWindow", "Clear List", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
