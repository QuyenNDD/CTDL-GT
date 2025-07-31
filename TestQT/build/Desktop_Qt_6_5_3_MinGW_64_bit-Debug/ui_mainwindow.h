/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabQLMH;
    QWidget *tabQLSV;
    QWidget *tabQLLSV;
    QWidget *tabND;
    QWidget *tabLTC;
    QWidget *widget;
    QLineEdit *lineMMH;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineNK;
    QSpinBox *spNHOM;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spMINSV;
    QSpinBox *sqMAXSV;
    QPushButton *btnThem;
    QPushButton *btnXoa;
    QPushButton *btnSua;
    QWidget *widget_2;
    QTableWidget *tblDSLTC;
    QPushButton *btnGhiFile;
    QWidget *tabDK;
    QWidget *tabXBC;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 801, 601));
        tabQLMH = new QWidget();
        tabQLMH->setObjectName("tabQLMH");
        tabWidget->addTab(tabQLMH, QString());
        tabQLSV = new QWidget();
        tabQLSV->setObjectName("tabQLSV");
        tabWidget->addTab(tabQLSV, QString());
        tabQLLSV = new QWidget();
        tabQLLSV->setObjectName("tabQLLSV");
        tabWidget->addTab(tabQLLSV, QString());
        tabND = new QWidget();
        tabND->setObjectName("tabND");
        tabWidget->addTab(tabND, QString());
        tabLTC = new QWidget();
        tabLTC->setObjectName("tabLTC");
        widget = new QWidget(tabLTC);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 801, 161));
        lineMMH = new QLineEdit(widget);
        lineMMH->setObjectName("lineMMH");
        lineMMH->setGeometry(QRect(100, 20, 113, 24));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 20, 71, 16));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 60, 71, 16));
        lineNK = new QLineEdit(widget);
        lineNK->setObjectName("lineNK");
        lineNK->setGeometry(QRect(100, 60, 113, 24));
        spNHOM = new QSpinBox(widget);
        spNHOM->setObjectName("spNHOM");
        spNHOM->setGeometry(QRect(100, 110, 42, 25));
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 110, 71, 16));
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(290, 20, 121, 16));
        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(290, 70, 111, 16));
        spMINSV = new QSpinBox(widget);
        spMINSV->setObjectName("spMINSV");
        spMINSV->setGeometry(QRect(420, 10, 42, 25));
        sqMAXSV = new QSpinBox(widget);
        sqMAXSV->setObjectName("sqMAXSV");
        sqMAXSV->setGeometry(QRect(420, 70, 42, 25));
        btnThem = new QPushButton(widget);
        btnThem->setObjectName("btnThem");
        btnThem->setGeometry(QRect(580, 10, 80, 24));
        btnXoa = new QPushButton(widget);
        btnXoa->setObjectName("btnXoa");
        btnXoa->setGeometry(QRect(580, 50, 80, 24));
        btnSua = new QPushButton(widget);
        btnSua->setObjectName("btnSua");
        btnSua->setGeometry(QRect(580, 90, 80, 24));
        widget_2 = new QWidget(tabLTC);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(-1, 159, 801, 411));
        tblDSLTC = new QTableWidget(widget_2);
        if (tblDSLTC->columnCount() < 6)
            tblDSLTC->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tblDSLTC->setObjectName("tblDSLTC");
        tblDSLTC->setEnabled(true);
        tblDSLTC->setGeometry(QRect(0, 10, 801, 331));
        tblDSLTC->setMaximumSize(QSize(801, 16777215));
        tblDSLTC->setColumnCount(6);
        tblDSLTC->horizontalHeader()->setMinimumSectionSize(23);
        tblDSLTC->horizontalHeader()->setDefaultSectionSize(133);
        btnGhiFile = new QPushButton(widget_2);
        btnGhiFile->setObjectName("btnGhiFile");
        btnGhiFile->setGeometry(QRect(680, 350, 91, 31));
        tabWidget->addTab(tabLTC, QString());
        tabDK = new QWidget();
        tabDK->setObjectName("tabDK");
        tabWidget->addTab(tabDK, QString());
        tabXBC = new QWidget();
        tabXBC->setObjectName("tabXBC");
        tabWidget->addTab(tabXBC, QString());
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabQLMH), QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 m\303\264n h\341\273\215c", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabQLSV), QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 sinh vi\303\252n", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabQLLSV), QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 l\341\273\233p sinh vi\303\252n", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabND), QCoreApplication::translate("MainWindow", "Nh\341\272\255p \304\221i\341\273\203m", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "M\303\243 m\303\264n h\341\273\215c:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ni\303\252n kh\303\263a:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Nh\303\263m:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i thi\341\273\203u: ", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i \304\221a: ", nullptr));
        btnThem->setText(QCoreApplication::translate("MainWindow", "Th\303\252m", nullptr));
        btnXoa->setText(QCoreApplication::translate("MainWindow", "X\303\263a", nullptr));
        btnSua->setText(QCoreApplication::translate("MainWindow", "Hi\341\273\207u ch\341\273\211nh", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblDSLTC->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "M\303\243 MH", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblDSLTC->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Ni\303\252n kh\303\263a", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblDSLTC->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Nh\303\263m", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblDSLTC->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i thi\341\273\203u", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblDSLTC->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i \304\221a", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tblDSLTC->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "C\303\262n tr\341\273\221ng", nullptr));
        btnGhiFile->setText(QCoreApplication::translate("MainWindow", "Ghi file", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabLTC), QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 l\341\273\233p t\303\255n ch\341\273\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabDK), QCoreApplication::translate("MainWindow", "\304\220\304\203ng k\303\255 t\303\255n ch\341\273\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabXBC), QCoreApplication::translate("MainWindow", "Xu\341\272\245t b\303\241o c\303\241o", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
