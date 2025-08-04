#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "structures.h"
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
    LoadTableMonHoc(dsMH);
}

void MainWindow::ghiDuLieuTuFile() {
    GhiDanhSachMonHoc(dsMH, "DSMH.txt");
    GhiDanhSachLopSV(dsLop, "DS_LSV_SV.txt");
    GhiDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");

    QMessageBox::information(this, "Thông báo", "Ghi dữ liệu ra file thành công!");
}
void MainWindow::on_lineMaMH_textChanged(const QString &arg1)
{
    QString upperText = arg1.toUpper();
    if (arg1 != upperText) {
        int cursorPos = ui->lineMaMH->cursorPosition();
        ui->lineMaMH->setText(upperText);
        ui->lineMaMH->setCursorPosition(cursorPos);
    }
}
void MainWindow::on_lineTenMH_textChanged(const QString &arg1)
{
    QString upperText = arg1.toUpper();
    if (arg1 != upperText) {
        int cursorPos = ui->lineTenMH->cursorPosition();
        ui->lineTenMH->setText(upperText);
        ui->lineTenMH->setCursorPosition(cursorPos);
    }
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


void Duyet_MonHoc_InOrder(treeMH root, const std::function<void(const MonHoc&)>& callback) {
    if (root == nullptr) return;

    Duyet_MonHoc_InOrder(root->left, callback);
    callback(root->mh);
    qDebug() << "[MonHoc]" << root->mh.MAMH << root->mh.TENMH;
    Duyet_MonHoc_InOrder(root->right, callback);
}

void MainWindow::LoadTableMonHoc(treeMH root)
{
    ui->tblMH->setRowCount(0);
    ui->tblMH->setColumnCount(4);
    QStringList header = {"Mã MH", "Tên môn học", "STCLT", "STCTH"};
    ui->tblMH->setHorizontalHeaderLabels(header);
    ui->tblMH->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int row = 0;

    Duyet_MonHoc_InOrder(root, [&](const MonHoc& mh) {
        ui->tblMH->insertRow(row);
        ui->tblMH->setItem(row, 0, new QTableWidgetItem(mh.MAMH));
        ui->tblMH->setItem(row, 1, new QTableWidgetItem(mh.TENMH));
        ui->tblMH->setItem(row, 2, new QTableWidgetItem(QString::number(mh.STCLT)));
        ui->tblMH->setItem(row, 3, new QTableWidgetItem(QString::number(mh.STCTH)));
        row++;
    });

}

void MainWindow::on_btnThemMH_clicked()
{
    QString ma = ui->lineMaMH->text().trimmed().toUpper();
    QString ten = ui->lineTenMH->text().trimmed();
    int stclt = ui->spinBox_STCLT->value();
    int stcth = ui->spinBox_STCTH->value();

    if (ma.isEmpty() || ten.isEmpty()) {
        QMessageBox::warning(this, "Thiếu dữ liệu", "Vui lòng nhập đầy đủ Mã và Tên môn học!");
        return;
    }

    // Kiểm tra trùng mã
    if (SearchTree(dsMH, ma.toStdString().c_str()) != nullptr) {
        QMessageBox::warning(this, "Trùng mã", "Mã môn học đã tồn tại!");
        return;
    }

    MonHoc mh;
    strncpy(mh.MAMH, ma.toStdString().c_str(), 10); mh.MAMH[10] = '\0';
    strncpy(mh.TENMH, ten.toStdString().c_str(), 50); mh.TENMH[50] = '\0';
    mh.STCLT = stclt;
    mh.STCTH = stcth;

    Insert_MonHoc(dsMH, mh);
    GhiDanhSachMonHoc(dsMH, "DSMH.txt");
    LoadTableMonHoc(dsMH);

    QMessageBox::information(this, "Thành công", "Đã thêm môn học!");
    ui->lineMaMH->clear();
    ui->lineTenMH->clear();
    ui->spinBox_STCLT->setValue(0);
    ui->spinBox_STCTH->setValue(0);
}


void MainWindow::on_btnSuaMH_clicked()
{
    QString ma = ui->lineMaMH->text().trimmed().toUpper();
    QString ten = ui->lineTenMH->text().trimmed();
    int stclt = ui->spinBox_STCLT->value();
    int stcth = ui->spinBox_STCTH->value();

    if (ma.isEmpty()) {
        QMessageBox::warning(this, "Thiếu mã", "Vui lòng nhập mã môn học cần sửa!");
        return;
    }

    MonHoc mhMoi;
    strncpy(mhMoi.MAMH, ma.toStdString().c_str(), 10); mhMoi.MAMH[10] = '\0';
    strncpy(mhMoi.TENMH, ten.toStdString().c_str(), 50); mhMoi.TENMH[50] = '\0';
    mhMoi.STCLT = stclt;
    mhMoi.STCTH = stcth;

    if (SuaMonHoc(dsMH, mhMoi)) {
        GhiDanhSachMonHoc(dsMH, "DSMH.txt");
        LoadTableMonHoc(dsMH);
        QMessageBox::information(this, "Thành công", "Đã cập nhật thông tin môn học!");
    } else {
        QMessageBox::warning(this, "Không tìm thấy", "Không tìm thấy mã môn học cần sửa!");
    }
}


void MainWindow::on_btnXoaMH_clicked()
{
    QString ma = ui->lineMaMH->text().trimmed().toUpper();

    if (ma.isEmpty()) {
        QMessageBox::warning(this, "Thiếu dữ liệu", "Vui lòng nhập mã môn học cần xóa!");
        return;
    }

    if (SearchTree(dsMH, ma.toStdString().c_str()) == nullptr) {
        QMessageBox::warning(this, "Không tìm thấy", "Không tìm thấy mã môn học cần xóa!");
        return;
    }

    if (MonHocDaDuocDangKy(dsLTC, ma.toStdString().c_str())) {
        QMessageBox::warning(this, "Không thể xoá", "Môn học này đã được đăng ký trong lớp tín chỉ!");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Xác nhận", "Bạn có chắc chắn muốn xóa môn học này?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (RemoveTreeMH(dsMH, ma.toStdString().c_str()) == 1) {
            GhiDanhSachMonHoc(dsMH, "DSMH.txt");
            LoadTableMonHoc(dsMH);
            QMessageBox::information(this, "Thành công", "Đã xóa môn học!");
        } else {
            QMessageBox::warning(this, "Thất bại", "Xóa thất bại!");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    const int MAX_MH = 1000;
    nodeMH* ds[MAX_MH];
    int n = 0;
    LuuMonHocVaoMang(dsMH, ds, n);

    SapXepTangTheoTenMH(ds, n);

    ui->tblMH->setRowCount(0);
    ui->tblMH->setColumnCount(4);
    QStringList header = {"Mã MH", "Tên môn học", "STCLT", "STCTH"};
    ui->tblMH->setHorizontalHeaderLabels(header);
    ui->tblMH->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int i = 0; i < n; ++i) {
        MonHoc mh = ds[i]->mh;
        int row = ui->tblMH->rowCount();
        ui->tblMH->insertRow(row);
        ui->tblMH->setItem(row, 0, new QTableWidgetItem(mh.MAMH));
        ui->tblMH->setItem(row, 1, new QTableWidgetItem(mh.TENMH));
        ui->tblMH->setItem(row, 2, new QTableWidgetItem(QString::number(mh.STCLT)));
        ui->tblMH->setItem(row, 3, new QTableWidgetItem(QString::number(mh.STCTH)));
    }
}

