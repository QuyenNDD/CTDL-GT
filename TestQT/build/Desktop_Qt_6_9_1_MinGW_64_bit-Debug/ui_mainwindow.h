/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tabQLMH;
    QTextEdit *txtKetQuaMonHoc;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *txtTenMH;
    QLabel *label_9;
    QLineEdit *txtSTCLT;
    QLabel *label_10;
    QLineEdit *txtSTCTH;
    QLineEdit *txtMaMH;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnThemMH;
    QPushButton *btnXoaMH;
    QPushButton *btnSuaMH;
    QPushButton *btnInDSMH;
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
    QSpinBox *spMAXSV;
    QPushButton *btnThem;
    QPushButton *btnXoa;
    QPushButton *btnSua;
    QLabel *label_6;
    QSpinBox *spHK;
    QCheckBox *ckHuy;
    QPushButton *btnInDSSV;
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
        txtKetQuaMonHoc = new QTextEdit(tabQLMH);
        txtKetQuaMonHoc->setObjectName("txtKetQuaMonHoc");
        txtKetQuaMonHoc->setGeometry(QRect(0, 210, 791, 321));
        formLayoutWidget = new QWidget(tabQLMH);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(30, 20, 471, 181));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(formLayoutWidget);
        label_7->setObjectName("label_7");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label_7);

        label_8 = new QLabel(formLayoutWidget);
        label_8->setObjectName("label_8");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_8);

        txtTenMH = new QLineEdit(formLayoutWidget);
        txtTenMH->setObjectName("txtTenMH");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, txtTenMH);

        label_9 = new QLabel(formLayoutWidget);
        label_9->setObjectName("label_9");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_9);

        txtSTCLT = new QLineEdit(formLayoutWidget);
        txtSTCLT->setObjectName("txtSTCLT");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, txtSTCLT);

        label_10 = new QLabel(formLayoutWidget);
        label_10->setObjectName("label_10");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_10);

        txtSTCTH = new QLineEdit(formLayoutWidget);
        txtSTCTH->setObjectName("txtSTCTH");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, txtSTCTH);

        txtMaMH = new QLineEdit(formLayoutWidget);
        txtMaMH->setObjectName("txtMaMH");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, txtMaMH);

        verticalLayoutWidget = new QWidget(tabQLMH);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(550, 10, 160, 139));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        btnThemMH = new QPushButton(verticalLayoutWidget);
        btnThemMH->setObjectName("btnThemMH");

        verticalLayout->addWidget(btnThemMH);

        btnXoaMH = new QPushButton(verticalLayoutWidget);
        btnXoaMH->setObjectName("btnXoaMH");

        verticalLayout->addWidget(btnXoaMH);

        btnSuaMH = new QPushButton(verticalLayoutWidget);
        btnSuaMH->setObjectName("btnSuaMH");

        verticalLayout->addWidget(btnSuaMH);

        btnInDSMH = new QPushButton(verticalLayoutWidget);
        btnInDSMH->setObjectName("btnInDSMH");

        verticalLayout->addWidget(btnInDSMH);

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
        label_4->setGeometry(QRect(240, 20, 121, 16));
        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(240, 60, 111, 16));
        spMINSV = new QSpinBox(widget);
        spMINSV->setObjectName("spMINSV");
        spMINSV->setGeometry(QRect(370, 10, 42, 25));
        spMAXSV = new QSpinBox(widget);
        spMAXSV->setObjectName("spMAXSV");
        spMAXSV->setGeometry(QRect(370, 50, 42, 25));
        btnThem = new QPushButton(widget);
        btnThem->setObjectName("btnThem");
        btnThem->setGeometry(QRect(580, 10, 80, 24));
        btnXoa = new QPushButton(widget);
        btnXoa->setObjectName("btnXoa");
        btnXoa->setGeometry(QRect(580, 50, 80, 24));
        btnSua = new QPushButton(widget);
        btnSua->setObjectName("btnSua");
        btnSua->setGeometry(QRect(580, 90, 80, 24));
        label_6 = new QLabel(widget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(240, 110, 71, 16));
        spHK = new QSpinBox(widget);
        spHK->setObjectName("spHK");
        spHK->setGeometry(QRect(370, 110, 42, 25));
        ckHuy = new QCheckBox(widget);
        ckHuy->setObjectName("ckHuy");
        ckHuy->setGeometry(QRect(450, 20, 77, 21));
        btnInDSSV = new QPushButton(widget);
        btnInDSSV->setObjectName("btnInDSSV");
        btnInDSSV->setGeometry(QRect(580, 130, 161, 24));
        widget_2 = new QWidget(tabLTC);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(0, 160, 791, 411));
        tblDSLTC = new QTableWidget(widget_2);
        if (tblDSLTC->columnCount() < 9)
            tblDSLTC->setColumnCount(9);
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
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        tblDSLTC->setObjectName("tblDSLTC");
        tblDSLTC->setEnabled(true);
        tblDSLTC->setGeometry(QRect(0, 0, 801, 331));
        tblDSLTC->setMaximumSize(QSize(801, 16777215));
        tblDSLTC->setRowCount(0);
        tblDSLTC->setColumnCount(9);
        tblDSLTC->horizontalHeader()->setMinimumSectionSize(23);
        tblDSLTC->horizontalHeader()->setDefaultSectionSize(88);
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

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        txtKetQuaMonHoc->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">K\341\272\277t qu\341\272\243 m\303\264n h\341\273\215c</p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "M\303\243 m\303\264n h\341\273\215c:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "T\303\252n m\303\264n h\341\273\215c:", nullptr));
        txtTenMH->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 t\303\255n ch\341\273\211 l\303\275 thuy\341\272\277t:", nullptr));
        txtSTCLT->setText(QString());
        label_10->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 t\303\255n ch\341\273\211 th\341\273\261c h\303\240nh:", nullptr));
        txtSTCTH->setText(QString());
        txtMaMH->setText(QString());
        btnThemMH->setText(QCoreApplication::translate("MainWindow", "ThemMH", nullptr));
        btnXoaMH->setText(QCoreApplication::translate("MainWindow", "XoaMH", nullptr));
        btnSuaMH->setText(QCoreApplication::translate("MainWindow", "SuaMH", nullptr));
        btnInDSMH->setText(QCoreApplication::translate("MainWindow", "InDSMH", nullptr));
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
        label_6->setText(QCoreApplication::translate("MainWindow", "H\341\273\215c k\341\273\263:", nullptr));
        ckHuy->setText(QCoreApplication::translate("MainWindow", "H\341\273\247y l\341\273\233p", nullptr));
        btnInDSSV->setText(QCoreApplication::translate("MainWindow", "Danh s\303\241ch sinh vi\303\252n \304\221\304\203ng k\303\255", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblDSLTC->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "M\303\243 l\341\273\233p t\303\255n ch\341\273\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblDSLTC->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "M\303\243 MH", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblDSLTC->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Ni\303\252n kh\303\263a", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblDSLTC->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "H\341\273\215c k\341\273\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblDSLTC->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Nh\303\263m", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tblDSLTC->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i thi\341\273\203u", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tblDSLTC->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i \304\221a", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tblDSLTC->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "C\303\262n tr\341\273\221ng", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tblDSLTC->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "H\341\273\247y l\341\273\233p", nullptr));
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
