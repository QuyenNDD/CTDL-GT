#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <cstdio> // cho FILE*
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Working Directory:" << QDir::currentPath();
    docDuLieuTuFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::docDuLieuTuFile() {
    DocDanhSachMonHoc(dsMH, "DSMH.txt");
    DocDanhSachLopSV(dsLop, "DS_LSV_SV.txt");
    DocDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
    hienThiDSLTC(dsLTC);
}

void MainWindow::ghiDuLieuTuFile() {
    GhiDanhSachMonHoc(dsMH, "DSMH.txt");
    GhiDanhSachLopSV(dsLop, "DS_LSV_SV.txt");
    GhiDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");

    QMessageBox::information(this, "Thông báo", "Ghi dữ liệu ra file thành công!");
}

int MainWindow::demSoLuongSvDK(PTRDK head){
    int count = 0;
    while (head != NULL){
        count++;
        head = head->next;
    }
    return count;
}

void MainWindow::hienThiDSLTC(List_LTC &ds){
    ui->tblDSLTC->setRowCount(0);
    qDebug() << "So luong lop tin chi:" << dsLTC.n;

    for (int i = 0; i < ds.n; i++){
        LopTinChi* ltc = ds.nodes[i];

        if (ltc == NULL) continue;

        int soLuongDK = demSoLuongSvDK(ltc->dssvdk);
        int conTrong = ltc->sosvmax - soLuongDK;

        int row = ui->tblDSLTC->rowCount();
        ui->tblDSLTC->insertRow(row);

        ui->tblDSLTC->setItem(row, 0, new QTableWidgetItem(ltc->MAMH));
        ui->tblDSLTC->setItem(row, 1, new QTableWidgetItem(ltc->NienKhoa));
        ui->tblDSLTC->setItem(row, 2, new QTableWidgetItem(QString::number(ltc->Nhom)));
        ui->tblDSLTC->setItem(row, 3, new QTableWidgetItem(QString::number(ltc->sosvmin)));
        ui->tblDSLTC->setItem(row, 4, new QTableWidgetItem(QString::number(ltc->sosvmax)));
        ui->tblDSLTC->setItem(row, 5, new QTableWidgetItem(QString::number(conTrong)));
    }
}


