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

    for (int i = 0; i < ds.n; i++){
        LopTinChi* ltc = ds.nodes[i];

        if (ltc == NULL) continue;

        int soLuongDK = demSoLuongSvDK(ltc->dssvdk);
        int conTrong = ltc->sosvmax - soLuongDK;

        int row = ui->tblDSLTC->rowCount();
        ui->tblDSLTC->insertRow(row);

        ui->tblDSLTC->setItem(row, 0, new QTableWidgetItem(QString::number(ltc->MALOPTC)));
        ui->tblDSLTC->setItem(row, 1, new QTableWidgetItem(ltc->MAMH));
        ui->tblDSLTC->setItem(row, 2, new QTableWidgetItem(ltc->NienKhoa));
        ui->tblDSLTC->setItem(row, 3, new QTableWidgetItem(QString::number(ltc->Hocky)));
        ui->tblDSLTC->setItem(row, 4, new QTableWidgetItem(QString::number(ltc->Nhom)));
        ui->tblDSLTC->setItem(row, 5, new QTableWidgetItem(QString::number(ltc->sosvmin)));
        ui->tblDSLTC->setItem(row, 6, new QTableWidgetItem(QString::number(ltc->sosvmax)));
        ui->tblDSLTC->setItem(row, 7, new QTableWidgetItem(QString::number(conTrong)));
        int huyLop = ltc->huylop ? 1 : 0;
        ui->tblDSLTC->setItem(row, 8, new QTableWidgetItem(QString::number(huyLop)));
    }
}



void MainWindow::on_btnThem_clicked()
{
    QString maMH = ui->lineMMH->text().trimmed();
    QString nienKhoa = ui->lineNK->text().trimmed();
    int hocKy = ui->spHK->value();
    int nhom = ui->spNHOM->value();
    int svMax = ui->spMAXSV->value();
    int svMin = ui->spMINSV->value();

    //Kiểm tra khoảng trắng
    if(maMH.contains(' ') || nienKhoa.contains(' ')){
        QMessageBox::warning(this, "Lỗi", "Mã môn học và niên khóa không được chứa khoảng trắng.");
        return;
    }
    //Kiểm tra học kì > 0
    if (hocKy <= 0){
        QMessageBox::warning(this, "Lỗi", "Học kỳ phải khác 0.");
        return;
    }
    //Kiểm tra nhóm > 0
    if (nhom <= 0){
        QMessageBox::warning(this, "Lỗi", "Nhóm phải khác 0.");
        return;
    }
    //Kiểm tra mã môn học đã tồn tại chưa
    if (!TimMaMonHoc(dsMH, maMH.toStdString().c_str())){
        QMessageBox::warning(this, "Lỗi", "Mã môn học không tồn tại.");
        return;
    }
    //Kiểm tra số svmin và max
    if (svMin == 0 || svMax == 0 || svMin >= svMax){
        QMessageBox::warning(this, "Lỗi", "Số SV tối thiểu không được lớn hơn số SV tối đa.");
        return;
    }
    //Kiểm tra có trùng lớp tín chỉ không ( maMH, nienKhoa, nhom, hocKy)
    for (int i = 0; i < dsLTC.n; i++){
        LopTinChi* ltc = dsLTC.nodes[i];
        if (strcmp(maMH.toStdString().c_str(), ltc->MAMH) == 0 &&
            strcmp(nienKhoa.toStdString().c_str(), ltc->NienKhoa) == 0 &&
            hocKy == ltc->Hocky &&
            nhom == ltc->Nhom){
            QMessageBox::warning(this, "Lỗi", "Lớp tín chỉ đã tồn tại (trùng NienKhoa, HocKy, MaMH, Nhom).");
            return;
        }
    }

    //Tạo lớp tín chỉ mới
    LopTinChi* ltc = new LopTinChi;
    strcpy(ltc->MAMH, maMH.toStdString().c_str());
    strcpy(ltc->NienKhoa, nienKhoa.toStdString().c_str());
    ltc->Hocky = hocKy;
    ltc->Nhom = nhom;
    ltc->sosvmin = svMin;
    ltc->sosvmax = svMax;
    ltc->huylop = false;
    ltc->dssvdk = NULL;
    ltc->MALOPTC = dsLTC.n + 1;

    dsLTC.nodes[dsLTC.n++] = ltc;
    QMessageBox::information(this, "Thành công", "Đã thêm lớp tín chỉ mới.");

    hienThiDSLTC(dsLTC);
}

void MainWindow::on_btnXoa_clicked()
{
    int row = ui->tblDSLTC->currentRow();

    if (row < 0){
        QMessageBox::warning(this, "Thông báo", "Vui lòng chọn lớp tín chỉ cần xóa.");
        return;
    }

    int maLtc = ui->tblDSLTC->item(row, 0)->text().toInt();

    //Mở hộp thoại xác nhận xóa
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Xác nhận xóa",
        QString("Bạn có chắc chắn muốn xóa lớp tín chỉ có mã %1 không?").arg(maLtc),
        QMessageBox::Yes | QMessageBox::No
        );
    if (reply != QMessageBox::Yes) return;

    int result = XoaLTC(dsLTC, maLtc);

    if (result == -1) {
        QMessageBox::warning(this, "Thông báo", "Đã có sinh viên đăng kí, không thể xóa.");
    } else if (result == 0) {
        QMessageBox::warning(this, "Thông báo", "Không tìm thấy lớp tín chỉ.");
    } else {
        QMessageBox::information(this, "Thông báo", "Đã xóa thành công.");
        hienThiDSLTC(dsLTC);
    }
}


void MainWindow::on_btnSua_clicked()
{
    if (maLTCDangChon == -1) {
        QMessageBox::warning(this, "Thông báo", "Vui lòng chọn lớp tín chỉ cần sửa.");
        return;
    }

    QString maMH = ui->lineMMH->text().trimmed();
    QString nienKhoa = ui->lineNK->text().trimmed();
    int hocKy = ui->spHK->value();
    int nhom = ui->spNHOM->value();
    int svMax = ui->spMAXSV->value();
    int svMin = ui->spMINSV->value();
    bool huyLop = ui->ckHuy->isChecked();

    //Kiểm tra khoảng trắng
    if(maMH.contains(' ') || nienKhoa.contains(' ')){
        QMessageBox::warning(this, "Lỗi", "Mã môn học và niên khóa không được chứa khoảng trắng.");
        return;
    }
    //Kiểm tra học kì > 0
    if (hocKy <= 0){
        QMessageBox::warning(this, "Lỗi", "Học kỳ phải khác 0.");
        return;
    }
    //Kiểm tra nhóm > 0
    if (nhom <= 0){
        QMessageBox::warning(this, "Lỗi", "Nhóm phải khác 0.");
        return;
    }
    //Kiểm tra mã môn học đã tồn tại chưa
    if (!TimMaMonHoc(dsMH, maMH.toStdString().c_str())){
        QMessageBox::warning(this, "Lỗi", "Mã môn học không tồn tại.");
        return;
    }
    //Kiểm tra số svmin và max
    if (svMin == 0 || svMax == 0 || svMin >= svMax){
        QMessageBox::warning(this, "Lỗi", "Số SV tối thiểu không được lớn hơn số SV tối đa.");
        return;
    }
    //Kiểm tra có trùng lớp tín chỉ không ( maMH, nienKhoa, nhom, hocKy)
    for (int i = 0; i < dsLTC.n; i++){
        LopTinChi* ltc = dsLTC.nodes[i];
        if (ltc->MALOPTC == maLTCDangChon) continue;
        if (strcmp(maMH.toStdString().c_str(), ltc->MAMH) == 0 &&
            strcmp(nienKhoa.toStdString().c_str(), ltc->NienKhoa) == 0 &&
            hocKy == ltc->Hocky &&
            nhom == ltc->Nhom){
            QMessageBox::warning(this, "Lỗi", "Lớp tín chỉ đã tồn tại (trùng NienKhoa, HocKy, MaMH, Nhom).");
            return;
        }
    }

    LopTinChi ltcMoi;
    strcpy(ltcMoi.MAMH, maMH.toStdString().c_str());
    strcpy(ltcMoi.NienKhoa, nienKhoa.toStdString().c_str());
    ltcMoi.Hocky = hocKy;
    ltcMoi.Nhom = nhom;
    ltcMoi.sosvmin = svMin;
    ltcMoi.sosvmax = svMax;
    ltcMoi.huylop = huyLop;

    int ketQua = HieuChinhLTC(dsLTC, maLTCDangChon, ltcMoi);

    if (ketQua == 1) {
        QMessageBox::information(this, "Thông báo", "Sửa thành công.");
        hienThiDSLTC(dsLTC);
    }else {
        QMessageBox::warning(this, "Thông báo", "Không tìm thấy lớp tín chỉ.");
    }
}


void MainWindow::on_tblDSLTC_cellClicked(int row, int column)
{
    maLTCDangChon = ui->tblDSLTC->item(row, 0)->text().toInt();

    QString maMH = ui->tblDSLTC->item(row, 1)->text();
    QString nienKhoa = ui->tblDSLTC->item(row, 2)->text();
    int hocKy = ui->tblDSLTC->item(row, 3)->text().toInt();
    int nhom = ui->tblDSLTC->item(row, 4)->text().toInt();
    int svMin = ui->tblDSLTC->item(row, 5)->text().toInt();
    int svMax = ui->tblDSLTC->item(row, 6)->text().toInt();
    int huyLop = ui->tblDSLTC->item(row, 8)->text().toInt();

    ui->lineMMH->setText(maMH);
    ui->lineNK->setText(nienKhoa);
    ui->spHK->setValue(hocKy);
    ui->spNHOM->setValue(nhom);
    ui->spMINSV->setValue(svMin);
    ui->spMAXSV->setValue(svMax);
    if (huyLop == 1) {
        ui->ckHuy->setChecked(true);
    }else {
        ui->ckHuy->setChecked(false);
    }
}

