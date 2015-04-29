/********************************************************************************
** Form generated from reading UI file 'workspace.ui'
**
** Created: Mon Apr 22 15:10:49 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORKSPACE_H
#define UI_WORKSPACE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WorkSpaceClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionSave;
    QAction *actionAbout;
    QAction *actionGenData;
    QWidget *centralWidget;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QFrame *line;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *mOpen;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *mSave;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *mClear;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *mSearch;
    QSpacerItem *horizontalSpacer_4;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout_3;
    QWidget *thumbnailWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *thumbLayout_2;
    QScrollBar *scrollBar_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WorkSpaceClass)
    {
        if (WorkSpaceClass->objectName().isEmpty())
            WorkSpaceClass->setObjectName(QString::fromUtf8("WorkSpaceClass"));
        WorkSpaceClass->resize(1059, 602);
        actionOpen = new QAction(WorkSpaceClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/WorkSpace/Resources/icons/newScene.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionExit = new QAction(WorkSpaceClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionSave = new QAction(WorkSpaceClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/WorkSpace/Resources/icons/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon1);
        actionAbout = new QAction(WorkSpaceClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionGenData = new QAction(WorkSpaceClass);
        actionGenData->setObjectName(QString::fromUtf8("actionGenData"));
        centralWidget = new QWidget(WorkSpaceClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        formLayoutWidget = new QWidget(centralWidget);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 0, 501, 401));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 500, 400);
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 410, 501, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 470, 501, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        mOpen = new QPushButton(layoutWidget);
        mOpen->setObjectName(QString::fromUtf8("mOpen"));
        mOpen->setIcon(icon);

        horizontalLayout->addWidget(mOpen);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        mSave = new QPushButton(layoutWidget);
        mSave->setObjectName(QString::fromUtf8("mSave"));
        mSave->setIcon(icon1);

        horizontalLayout->addWidget(mSave);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        mClear = new QPushButton(layoutWidget);
        mClear->setObjectName(QString::fromUtf8("mClear"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/WorkSpace/Resources/icons/Eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        mClear->setIcon(icon2);

        horizontalLayout->addWidget(mClear);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        mSearch = new QPushButton(layoutWidget);
        mSearch->setObjectName(QString::fromUtf8("mSearch"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/WorkSpace/Resources/icons/Search-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        mSearch->setIcon(icon3);

        horizontalLayout->addWidget(mSearch);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(510, 0, 541, 541));
        gridLayout_3 = new QGridLayout(layoutWidget_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        thumbnailWidget_2 = new QWidget(layoutWidget_2);
        thumbnailWidget_2->setObjectName(QString::fromUtf8("thumbnailWidget_2"));
        thumbnailWidget_2->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_4 = new QHBoxLayout(thumbnailWidget_2);
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        thumbLayout_2 = new QGridLayout();
        thumbLayout_2->setSpacing(1);
        thumbLayout_2->setObjectName(QString::fromUtf8("thumbLayout_2"));

        horizontalLayout_4->addLayout(thumbLayout_2);

        scrollBar_2 = new QScrollBar(thumbnailWidget_2);
        scrollBar_2->setObjectName(QString::fromUtf8("scrollBar_2"));
        scrollBar_2->setOrientation(Qt::Vertical);

        horizontalLayout_4->addWidget(scrollBar_2);


        gridLayout_3->addWidget(thumbnailWidget_2, 0, 0, 1, 1);

        WorkSpaceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WorkSpaceClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1059, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WorkSpaceClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WorkSpaceClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        WorkSpaceClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WorkSpaceClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        WorkSpaceClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExit);
        menuFile->addAction(actionGenData);
        menuHelp->addAction(actionAbout);

        retranslateUi(WorkSpaceClass);

        QMetaObject::connectSlotsByName(WorkSpaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *WorkSpaceClass)
    {
        WorkSpaceClass->setWindowTitle(QApplication::translate("WorkSpaceClass", "WorkSpace", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("WorkSpaceClass", "Open", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("WorkSpaceClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("WorkSpaceClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionExit->setShortcut(QApplication::translate("WorkSpaceClass", "Esc", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("WorkSpaceClass", "Save", 0, QApplication::UnicodeUTF8));
        actionSave->setShortcut(QApplication::translate("WorkSpaceClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("WorkSpaceClass", "About", 0, QApplication::UnicodeUTF8));
        actionAbout->setShortcut(QApplication::translate("WorkSpaceClass", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionGenData->setText(QApplication::translate("WorkSpaceClass", "GenData", 0, QApplication::UnicodeUTF8));
        mOpen->setText(QApplication::translate("WorkSpaceClass", "Open", 0, QApplication::UnicodeUTF8));
        mSave->setText(QApplication::translate("WorkSpaceClass", "Save", 0, QApplication::UnicodeUTF8));
        mClear->setText(QApplication::translate("WorkSpaceClass", "Clear", 0, QApplication::UnicodeUTF8));
        mSearch->setText(QApplication::translate("WorkSpaceClass", "Search", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("WorkSpaceClass", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("WorkSpaceClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WorkSpaceClass: public Ui_WorkSpaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORKSPACE_H
