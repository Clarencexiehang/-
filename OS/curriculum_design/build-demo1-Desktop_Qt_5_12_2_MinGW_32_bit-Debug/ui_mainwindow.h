/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *createprocess;
    QPushButton *deleteprocess;
    QPushButton *start;
    QPushButton *pause;
    QTableWidget *processtable;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(895, 642);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/tubiao.jpg!qt324new_nowater"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        createprocess = new QPushButton(centralWidget);
        createprocess->setObjectName(QString::fromUtf8("createprocess"));
        createprocess->setGeometry(QRect(30, 50, 121, 51));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        createprocess->setFont(font);
        deleteprocess = new QPushButton(centralWidget);
        deleteprocess->setObjectName(QString::fromUtf8("deleteprocess"));
        deleteprocess->setGeometry(QRect(30, 120, 121, 51));
        deleteprocess->setFont(font);
        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));
        start->setGeometry(QRect(30, 270, 121, 51));
        start->setFont(font);
        pause = new QPushButton(centralWidget);
        pause->setObjectName(QString::fromUtf8("pause"));
        pause->setGeometry(QRect(30, 340, 121, 51));
        pause->setFont(font);
        processtable = new QTableWidget(centralWidget);
        processtable->setObjectName(QString::fromUtf8("processtable"));
        processtable->setGeometry(QRect(180, 50, 631, 341));
        processtable->setFont(font);
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QBrush brush(QColor(255, 255, 127, 255));
        brush.setStyle(Qt::NoBrush);
        QFont font1;
        font1.setUnderline(true);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font1);
        __qtablewidgetitem->setBackground(QColor(85, 255, 0));
        __qtablewidgetitem->setForeground(brush);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font2;
        font2.setStrikeOut(false);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font2);
        __qtablewidgetitem1->setBackground(QColor(255, 170, 0));
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableWidget->rowCount() < 1)
            tableWidget->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setBackground(QColor(170, 255, 0));
        tableWidget->setVerticalHeaderItem(0, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(180, 400, 631, 192));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 895, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        createprocess->setText(QApplication::translate("MainWindow", "\345\210\233\345\273\272\350\277\233\347\250\213", nullptr));
        deleteprocess->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\277\233\347\250\213", nullptr));
        start->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", nullptr));
        pause->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\350\277\233\347\250\213\345\217\267", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\344\274\230\345\205\210\347\272\247", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\346\222\222\346\227\246\346\263\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
