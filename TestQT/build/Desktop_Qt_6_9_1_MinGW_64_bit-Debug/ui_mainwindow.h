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
    QWidget *widget_3;
    QLineEdit *lineMaMH;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineTenMH;
    QPushButton *btnThemMH;
    QPushButton *btnSuaMH;
    QPushButton *btnXoaMH;
    QSpinBox *spinBox_STCLT;
    QSpinBox *spinBox_STCTH;
    QPushButton *pushButton;
    QWidget *widget_4;
    QTableWidget *tblMH;
    QWidget *tabQLSV;
    QWidget *tabQLLSV;
    QWidget *tabTongKet;
    QWidget *tabND;
    QWidget *widget_5;
    QLineEdit *lineNDNK;
    QLineEdit *lineNDMH;
    QLabel *label_10;
    QLabel *label_12;
    QLabel *label_13;
    QPushButton *btnNDSearch;
    QLabel *label_11;
    QSpinBox *spinBoxNDNhom;
    QSpinBox *spinBoxNDHK;
    QWidget *widget_6;
    QLabel *label_14;
    QLineEdit *lineEditNDMonHoc;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *lineEditNDNienKhoa;
    QLineEdit *lineEditNDHocKy;
    QLineEdit *lineEditNDNhom;
    QTableWidget *tblND;
    QPushButton *btnNDSave;
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
    QLabel *label_61;
    QSpinBox *spHK;
    QCheckBox *ckHuy;
    QWidget *widget_2;
    QTableWidget *tblDSLTC;
    QPushButton *btnGhiFile;
    QWidget *tabDK;
    QWidget *tabXBC;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 575);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(0, 0, 801, 591));
        tabQLMH = new QWidget();
        tabQLMH->setObjectName("tabQLMH");
        widget_3 = new QWidget(tabQLMH);
        widget_3->setObjectName("widget_3");
        widget_3->setGeometry(QRect(0, 0, 791, 151));
        lineMaMH = new QLineEdit(widget_3);
        lineMaMH->setObjectName("lineMaMH");
        lineMaMH->setGeometry(QRect(90, 20, 113, 26));
        label_6 = new QLabel(widget_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(10, 30, 63, 20));
        label_7 = new QLabel(widget_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(10, 70, 63, 20));
        label_8 = new QLabel(widget_3);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(260, 20, 63, 20));
        label_9 = new QLabel(widget_3);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(260, 70, 63, 20));
        lineTenMH = new QLineEdit(widget_3);
        lineTenMH->setObjectName("lineTenMH");
        lineTenMH->setGeometry(QRect(90, 60, 113, 26));
        btnThemMH = new QPushButton(widget_3);
        btnThemMH->setObjectName("btnThemMH");
        btnThemMH->setGeometry(QRect(530, 20, 93, 29));
        btnThemMH->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);\n"
"alternate-background-color: rgb(255, 170, 127);\n"
"selection-background-color: rgb(255, 0, 0);"));
        btnSuaMH = new QPushButton(widget_3);
        btnSuaMH->setObjectName("btnSuaMH");
        btnSuaMH->setEnabled(true);
        btnSuaMH->setGeometry(QRect(530, 60, 93, 29));
        btnSuaMH->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));
        btnXoaMH = new QPushButton(widget_3);
        btnXoaMH->setObjectName("btnXoaMH");
        btnXoaMH->setEnabled(true);
        btnXoaMH->setGeometry(QRect(660, 60, 93, 29));
        btnXoaMH->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));
        spinBox_STCLT = new QSpinBox(widget_3);
        spinBox_STCLT->setObjectName("spinBox_STCLT");
        spinBox_STCLT->setGeometry(QRect(320, 20, 91, 26));
        spinBox_STCTH = new QSpinBox(widget_3);
        spinBox_STCTH->setObjectName("spinBox_STCTH");
        spinBox_STCTH->setGeometry(QRect(320, 70, 91, 26));
        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(530, 110, 221, 29));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);\n"
"border: 2px solid ;"));
        widget_4 = new QWidget(tabQLMH);
        widget_4->setObjectName("widget_4");
        widget_4->setGeometry(QRect(0, 160, 791, 351));
        tblMH = new QTableWidget(widget_4);
        if (tblMH->columnCount() < 4)
            tblMH->setColumnCount(4);
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(10);
        font.setBold(false);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tblMH->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(10);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font1);
        tblMH->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setFont(font1);
        tblMH->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setFont(font1);
        tblMH->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tblMH->setObjectName("tblMH");
        tblMH->setGeometry(QRect(0, 10, 791, 341));
        tblMH->setMaximumSize(QSize(791, 16777215));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Times New Roman")});
        tblMH->setFont(font2);
        tblMH->setStyleSheet(QString::fromUtf8("border: 2px solid black;       \n"
""));
        tblMH->verticalHeader()->setVisible(false);
        tabWidget->addTab(tabQLMH, QString());
        tabQLSV = new QWidget();
        tabQLSV->setObjectName("tabQLSV");
        tabWidget->addTab(tabQLSV, QString());
        tabQLLSV = new QWidget();
        tabQLLSV->setObjectName("tabQLLSV");
        tabWidget->addTab(tabQLLSV, QString());
        tabTongKet = new QWidget();
        tabTongKet->setObjectName("tabTongKet");
        tabWidget->addTab(tabTongKet, QString());
        tabND = new QWidget();
        tabND->setObjectName("tabND");
        widget_5 = new QWidget(tabND);
        widget_5->setObjectName("widget_5");
        widget_5->setGeometry(QRect(0, 0, 801, 111));
        lineNDNK = new QLineEdit(widget_5);
        lineNDNK->setObjectName("lineNDNK");
        lineNDNK->setGeometry(QRect(90, 10, 113, 26));
        lineNDMH = new QLineEdit(widget_5);
        lineNDMH->setObjectName("lineNDMH");
        lineNDMH->setGeometry(QRect(90, 70, 113, 26));
        label_10 = new QLabel(widget_5);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(10, 20, 71, 20));
        label_12 = new QLabel(widget_5);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(340, 10, 63, 20));
        label_13 = new QLabel(widget_5);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(10, 70, 63, 20));
        btnNDSearch = new QPushButton(widget_5);
        btnNDSearch->setObjectName("btnNDSearch");
        btnNDSearch->setGeometry(QRect(600, 70, 93, 29));
        btnNDSearch->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 127);"));
        label_11 = new QLabel(widget_5);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(340, 70, 63, 20));
        spinBoxNDNhom = new QSpinBox(widget_5);
        spinBoxNDNhom->setObjectName("spinBoxNDNhom");
        spinBoxNDNhom->setGeometry(QRect(400, 10, 101, 26));
        spinBoxNDHK = new QSpinBox(widget_5);
        spinBoxNDHK->setObjectName("spinBoxNDHK");
        spinBoxNDHK->setGeometry(QRect(400, 70, 101, 26));
        widget_6 = new QWidget(tabND);
        widget_6->setObjectName("widget_6");
        widget_6->setGeometry(QRect(-1, 129, 791, 401));
        widget_6->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        widget_6->setContextMenuPolicy(Qt::ContextMenuPolicy::DefaultContextMenu);
        widget_6->setStyleSheet(QString::fromUtf8("#widget_6 {\n"
"    border-top: 2px solid;   \n"
"}"));
        label_14 = new QLabel(widget_6);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(200, 20, 181, 31));
        label_14->setFont(font1);
        lineEditNDMonHoc = new QLineEdit(widget_6);
        lineEditNDMonHoc->setObjectName("lineEditNDMonHoc");
        lineEditNDMonHoc->setGeometry(QRect(380, 20, 231, 26));
        lineEditNDMonHoc->setReadOnly(true);
        label_15 = new QLabel(widget_6);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(162, 60, 81, 20));
        label_15->setFont(font1);
        label_16 = new QLabel(widget_6);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(370, 60, 63, 20));
        label_16->setFont(font1);
        label_17 = new QLabel(widget_6);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(510, 60, 51, 20));
        label_17->setFont(font1);
        lineEditNDNienKhoa = new QLineEdit(widget_6);
        lineEditNDNienKhoa->setObjectName("lineEditNDNienKhoa");
        lineEditNDNienKhoa->setGeometry(QRect(240, 60, 113, 26));
        lineEditNDNienKhoa->setReadOnly(true);
        lineEditNDHocKy = new QLineEdit(widget_6);
        lineEditNDHocKy->setObjectName("lineEditNDHocKy");
        lineEditNDHocKy->setGeometry(QRect(430, 60, 61, 26));
        lineEditNDHocKy->setReadOnly(true);
        lineEditNDNhom = new QLineEdit(widget_6);
        lineEditNDNhom->setObjectName("lineEditNDNhom");
        lineEditNDNhom->setGeometry(QRect(560, 60, 61, 26));
        lineEditNDNhom->setReadOnly(true);
        tblND = new QTableWidget(widget_6);
        if (tblND->columnCount() < 5)
            tblND->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tblND->setHorizontalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tblND->setHorizontalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tblND->setHorizontalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tblND->setHorizontalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tblND->setHorizontalHeaderItem(4, __qtablewidgetitem8);
        tblND->setObjectName("tblND");
        tblND->setGeometry(QRect(0, 100, 791, 261));
        tblND->setFont(font2);
        tblND->setStyleSheet(QString::fromUtf8("border: 2px solid;"));
        tblND->verticalHeader()->setVisible(false);
        btnNDSave = new QPushButton(widget_6);
        btnNDSave->setObjectName("btnNDSave");
        btnNDSave->setGeometry(QRect(620, 370, 93, 29));
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
        spNHOM->setGeometry(QRect(100, 110, 111, 25));
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
        spMINSV->setGeometry(QRect(370, 10, 61, 25));
        spMAXSV = new QSpinBox(widget);
        spMAXSV->setObjectName("spMAXSV");
        spMAXSV->setGeometry(QRect(370, 50, 61, 25));
        btnThem = new QPushButton(widget);
        btnThem->setObjectName("btnThem");
        btnThem->setGeometry(QRect(580, 10, 80, 24));
        btnXoa = new QPushButton(widget);
        btnXoa->setObjectName("btnXoa");
        btnXoa->setGeometry(QRect(580, 50, 80, 24));
        btnSua = new QPushButton(widget);
        btnSua->setObjectName("btnSua");
        btnSua->setGeometry(QRect(580, 90, 80, 24));
        label_61 = new QLabel(widget);
        label_61->setObjectName("label_61");
        label_61->setGeometry(QRect(240, 110, 71, 16));
        spHK = new QSpinBox(widget);
        spHK->setObjectName("spHK");
        spHK->setGeometry(QRect(370, 110, 61, 25));
        ckHuy = new QCheckBox(widget);
        ckHuy->setObjectName("ckHuy");
        ckHuy->setGeometry(QRect(450, 20, 77, 21));
        widget_2 = new QWidget(tabLTC);
        widget_2->setObjectName("widget_2");
        widget_2->setGeometry(QRect(0, 160, 791, 411));
        tblDSLTC = new QTableWidget(widget_2);
        if (tblDSLTC->columnCount() < 9)
            tblDSLTC->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(1, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(2, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(3, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(4, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(5, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(6, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(7, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        tblDSLTC->setHorizontalHeaderItem(8, __qtablewidgetitem17);
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

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineMaMH->setInputMask(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "Ma MH", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "T\303\252n MH", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "STCLT", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "STCTH", nullptr));
        btnThemMH->setText(QCoreApplication::translate("MainWindow", "Th\303\252m", nullptr));
        btnSuaMH->setText(QCoreApplication::translate("MainWindow", "S\306\260\314\211a", nullptr));
        btnXoaMH->setText(QCoreApplication::translate("MainWindow", "Xo\314\201a", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "S\304\203\314\201p x\303\252\314\201p t\304\203ng d\303\242\314\200n theo t\303\252n", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tblMH->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "MaMH", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tblMH->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "TenMH", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tblMH->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "STCLT", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tblMH->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "STCTH", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabQLMH), QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 m\303\264n h\341\273\215c", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabQLSV), QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 sinh vi\303\252n", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabQLLSV), QCoreApplication::translate("MainWindow", "Qu\341\272\243n l\303\275 l\341\273\233p sinh vi\303\252n", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabTongKet), QCoreApplication::translate("MainWindow", "T\303\264\314\211ng k\303\252\314\201t ", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Ni\303\252n kho\314\201a:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Nho\314\201m:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "M\303\264n ho\314\243c:", nullptr));
        btnNDSearch->setText(QCoreApplication::translate("MainWindow", "Ti\314\200m ki\303\252\314\201m", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Ho\314\243c ky\314\200:", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "BA\314\211NG \304\220I\303\212\314\211M M\303\224N HO\314\243C", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Ni\303\252n kho\314\201a:", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Ho\314\243c ky\314\200:", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Nho\314\201m:", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tblND->horizontalHeaderItem(0);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "STT", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tblND->horizontalHeaderItem(1);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "MSSV", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tblND->horizontalHeaderItem(2);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "HO", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tblND->horizontalHeaderItem(3);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "TEN", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tblND->horizontalHeaderItem(4);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "DIEM", nullptr));
        btnNDSave->setText(QCoreApplication::translate("MainWindow", "L\306\260u", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabND), QCoreApplication::translate("MainWindow", "Nh\341\272\255p \304\221i\341\273\203m", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "M\303\243 m\303\264n h\341\273\215c:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ni\303\252n kh\303\263a:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Nh\303\263m:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i thi\341\273\203u: ", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i \304\221a: ", nullptr));
        btnThem->setText(QCoreApplication::translate("MainWindow", "Th\303\252m", nullptr));
        btnXoa->setText(QCoreApplication::translate("MainWindow", "X\303\263a", nullptr));
        btnSua->setText(QCoreApplication::translate("MainWindow", "Hi\341\273\207u ch\341\273\211nh", nullptr));
        label_61->setText(QCoreApplication::translate("MainWindow", "H\341\273\215c k\341\273\263:", nullptr));
        ckHuy->setText(QCoreApplication::translate("MainWindow", "H\341\273\247y l\341\273\233p", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tblDSLTC->horizontalHeaderItem(0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "M\303\243 l\341\273\233p t\303\255n ch\341\273\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tblDSLTC->horizontalHeaderItem(1);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "M\303\243 MH", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tblDSLTC->horizontalHeaderItem(2);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("MainWindow", "Ni\303\252n kh\303\263a", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tblDSLTC->horizontalHeaderItem(3);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("MainWindow", "H\341\273\215c k\341\273\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tblDSLTC->horizontalHeaderItem(4);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("MainWindow", "Nh\303\263m", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = tblDSLTC->horizontalHeaderItem(5);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i thi\341\273\203u", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = tblDSLTC->horizontalHeaderItem(6);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("MainWindow", "S\341\273\221 sinh vi\303\252n t\341\273\221i \304\221a", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = tblDSLTC->horizontalHeaderItem(7);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("MainWindow", "C\303\262n tr\341\273\221ng", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = tblDSLTC->horizontalHeaderItem(8);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("MainWindow", "H\341\273\247y l\341\273\233p", nullptr));
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
