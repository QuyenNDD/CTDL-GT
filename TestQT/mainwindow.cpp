#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <cstdio> // cho FILE*
#include <QDir>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    docDuLieuTuFile();
    QRegularExpression rx("[A-Za-z]+");
    QValidator *validator = new QRegularExpressionValidator(rx, this);
    ui->lineMMH->setValidator(validator);

    // Tự chuyển thành chữ in hoa
    connect(ui->lineMMH, &QLineEdit::textChanged, this, [=](const QString &text){
        ui->lineMMH->setText(text.toUpper());
    });

    connect(ui->lineMSV, &QLineEdit::textChanged, this, [=](const QString &text){
        ui->lineMSV->setText(text.toUpper());
    });

    connect(ui->lineNK, &QLineEdit::textChanged, this, [=](QString text){
        // Chỉ cho số và tối đa 8 chữ số
        text.remove(QRegularExpression("[^0-9]"));
        if (text.length() > 8) {
            text = text.left(8);
        }

        // Chèn dấu '-'
        if (text.length() > 4) {
            text.insert(4, '-');
        }

        // Tránh lặp vô hạn
        if (text != ui->lineNK->text()) {
            ui->lineNK->setText(text);
        }
    });

    connect(ui->lineDK_NK, &QLineEdit::textChanged, this, [=](QString text){
        // Chỉ cho số và tối đa 8 chữ số
        text.remove(QRegularExpression("[^0-9]"));
        if (text.length() > 8) {
            text = text.left(8);
        }

        // Chèn dấu '-'
        if (text.length() > 4) {
            text.insert(4, '-');
        }

        // Tránh lặp vô hạn
        if (text != ui->lineDK_NK->text()) {
            ui->lineDK_NK->setText(text);
        }
    });
    connect(ui->lineQLDK_NK, &QLineEdit::textChanged, this, [=](QString text){
        // Chỉ cho số và tối đa 8 chữ số
        text.remove(QRegularExpression("[^0-9]"));
        if (text.length() > 8) {
            text = text.left(8);
        }

        // Chèn dấu '-'
        if (text.length() > 4) {
            text.insert(4, '-');
        }

        // Tránh lặp vô hạn
        if (text != ui->lineQLDK_NK->text()) {
            ui->lineQLDK_NK->setText(text);
        }
    });
    setButtonState(false);
    connect(ui->lineMSV, &QLineEdit::returnPressed, this, &MainWindow::on_lineMSV_returnPressed);
    ui->btnDK->setEnabled(false);
    ui->btnQLDK_Huy->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setButtonState(bool state){
    ui->btnSua->setEnabled(state);
    ui->btnXoa->setEnabled(state);
    ui->btnInDSSV->setEnabled(state);
    ui->ckHuy->setEnabled(state);
}

void MainWindow::clearForm(){
    ui->lineMMH->clear();
    ui->lineNK->clear();
    ui->spHK->setValue(0);
    ui->spMAXSV->setValue(0);
    ui->spMINSV->setValue(0);
    ui->spNHOM->setValue(0);
    ui->ckHuy->setChecked(false);
}

void MainWindow::docDuLieuTuFile() {
    DocDanhSachMonHoc(dsMH, "DSMH.txt");
    DocDanhSachLopSV(dsLop, "DS_LSV_SV.txt");
    DocDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
    hienThiDSLTC(dsLTC);
}

// void MainWindow::ghiDuLieuTuFile() {
//     GhiDanhSachMonHoc(dsMH, "DSMH.txt");
//     GhiDanhSachLopSV(dsLop, "DS_LSV_SV.txt");
//     GhiDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");

//     QMessageBox::information(this, "Thông báo", "Ghi dữ liệu ra file thành công!");
// }

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
    //Kiểm tra niên khóa
    if (nienKhoa.length() != 9){
        QMessageBox::warning(this, "Lỗi", "Nhập sai niên khóa. Nhập theo dạng yyyy-yyyy");
        return;
    }else {
        int nam1 = nienKhoa.left(4).toInt();
        int nam2 = nienKhoa.mid(5, 4).toInt();
        if (nam1 >= nam2){
            QMessageBox::warning(this, "Lỗi", "Niên khóa không hợp lệ. Năm sau phải lớn hơn năm trước");
            return;
        }
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
    clearForm();
    hienThiDSLTC(dsLTC);
    setButtonState(false);
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
    clearForm();
    setButtonState(false);
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
    clearForm();
    setButtonState(false);
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
    setButtonState(true);
}


void MainWindow::on_btnInDSSV_clicked()
{
    QString maMH = ui->lineMMH->text().trimmed();
    QString nienKhoa = ui->lineNK->text().trimmed();
    int hocKy = ui->spHK->value();
    int nhom = ui->spNHOM->value();

    LopTinChi* ltc = NULL;
    for (int i = 0; i < dsLTC.n; i++){
        LopTinChi *lt = dsLTC.nodes[i];
        if (strcmp(lt->MAMH, maMH.toStdString().c_str()) == 0 &&
            strcmp(lt->NienKhoa, nienKhoa.toStdString().c_str()) == 0 &&
            lt->Hocky == hocKy &&
            lt->Nhom == nhom) {
            ltc = lt;
            break;
        }
    }
    if (!ltc) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp tín chỉ.");
        return;
    }

    QWidget* tab = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(tab);
    QTableWidget* table = new QTableWidget;
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels(QStringList() << "MASV" << "HỌ TÊN" << "LỚP");
    layout->addWidget(table);
    tab->setLayout(layout);

    PTRDK pdk = ltc->dssvdk;
    while (pdk != nullptr) {
        char maLop[16] = "";
        SinhVien* sv = TimSinhVienTheoMa(dsLop, pdk->dk.MASV, maLop);
        if (sv != nullptr) {
            int row = table->rowCount();
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(QString(sv->MASV)));
            QString hoTen = QString("%1 %2").arg(sv->HO).arg(sv->TEN);
            table->setItem(row, 1, new QTableWidgetItem(hoTen));
            table->setItem(row, 2, new QTableWidgetItem(QString(maLop)));
        }
        pdk = pdk->next;
    }

    // Giả sử bạn có tabWidget trong UI, nếu không có thì tạo thêm trong Qt Designer
    ui->tabWidget->addTab(tab, QString("DS DK %1-%2").arg(maMH).arg(nhom));
    ui->tabWidget->setCurrentWidget(tab);
}


void MainWindow::on_btnGhiFile_clicked()
{
    GhiDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
    DocDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
    QMessageBox::information(this, "Thông báo", "Đã ghi vào file DS_LTC_DK.txt thành công!");
}


void MainWindow::on_lineMSV_returnPressed()
{
    QString masv = ui->lineMSV->text().trimmed();

    if(masv.contains(' ')){
        QMessageBox::warning(this, "Lỗi", "Mã sinh viên không được chứa khoảng trắng.");
        return;
    }

    char maLop[16] = "";
    SinhVien* sv = TimSinhVienTheoMa(dsLop, masv.toStdString().c_str(), maLop);

    if (sv != NULL){
        ui->lineHoTen->setText(QString(sv->HO) + " " + QString(sv->TEN));
        ui->lineLop->setText(QString(maLop));
    }else {
        ui->lineHoTen->setText("");
        ui->lineLop->setText("");
        QMessageBox::information(this, "Thông báo", "Không tìm thấy mã sinh viên.");
    }
}

void MainWindow::hienThiDK_DSLTC(List_LTC &ds, int hk, const QString nienkhoa){
    ui->tblDK_DSLTC->setRowCount(0);
    bool check = false;
    int svdk = 0;
    int controng = 0;
    for (int i = 0; i < ds.n; i++){
        LopTinChi* ltc = ds.nodes[i];

        if (ltc->Hocky == hk && strcmp(ltc->NienKhoa, nienkhoa.toStdString().c_str()) == 0 && !ltc->huylop){
            MonHoc* mh = TimMonHocTheoMa(dsMH, ltc->MAMH);
            svdk = demSoLuongSvDK(ltc->dssvdk);
            controng = ltc->sosvmax - svdk;
            check = true;

            int row = ui->tblDK_DSLTC->rowCount();
            ui->tblDK_DSLTC->insertRow(row);

            ui->tblDK_DSLTC->setItem(row, 0, new QTableWidgetItem(ltc->MAMH));
            ui->tblDK_DSLTC->setItem(row, 1, new QTableWidgetItem(mh->TENMH));
            ui->tblDK_DSLTC->setItem(row, 2, new QTableWidgetItem(QString::number(ltc->Nhom)));
            ui->tblDK_DSLTC->setItem(row, 3, new QTableWidgetItem(QString::number(svdk)));
            ui->tblDK_DSLTC->setItem(row, 4, new QTableWidgetItem(QString::number(controng)));

            if(ltc->huylop || controng == 0){
                for (int col = 0; col < 5; col++)
                    ui->tblDK_DSLTC->item(row, col)->setFlags(Qt::NoItemFlags);
            }
        }
    }

    if (!check){
        QMessageBox::information(this, "Thông báo", "Không có lớp tín chỉ nào ở trong hoc ki " + QString::number(hk) + " và niên khóa " + nienkhoa +"!");
        return;
    }
}

void MainWindow::on_lineDK_NK_returnPressed()
{
    QString nienkhoa = ui->lineDK_NK->text().trimmed();
    int hk = ui->spDK_HK->value();

    if (nienkhoa.contains(' ')){
        QMessageBox::warning(this, "Lỗi", "Niên khóa không được chứa khoảng trắng.");
        return;
    }

    if (nienkhoa.length() != 9){
        QMessageBox::warning(this, "Lỗi", "Nhập sai niên khóa. Nhập theo dạng yyyy-yyyy");
        return;
    }else {
        int nam1 = nienkhoa.left(4).toInt();
        int nam2 = nienkhoa.mid(5, 4).toInt();
        if (nam1 >= nam2){
            QMessageBox::warning(this, "Lỗi", "Niên khóa không hợp lệ. Năm sau phải lớn hơn năm trước");
            return;
        }
    }
    if (hk <= 0) {
        QMessageBox::warning(this, "Lỗi", "Học kỳ phải lớn hơn 0.");
        return;
    }
    hienThiDK_DSLTC(dsLTC, hk, nienkhoa);
}


void MainWindow::on_tblDK_DSLTC_cellClicked(int row, int column)
{
    QString maMh = ui->tblDK_DSLTC->item(row, 0)->text();
    QString tenMh = ui->tblDK_DSLTC->item(row, 1)->text();
    int nhom = ui->tblDK_DSLTC->item(row, 2)->text().toInt();

    ui->lineDK_MMH->setText(maMh);
    ui->lineDK_MH->setText(tenMh);
    ui->lineDK_Nhom->setText(QString::number(nhom));
    ui->btnDK->setEnabled(true);

    QString nienkhoa = ui->lineDK_NK->text();
    int hocky = ui->spDK_HK->value();

    ltcDangChon = TimLTCTheo4DK(dsLTC, nienkhoa.toStdString().c_str(), hocky, maMh.toStdString().c_str(), nhom);
}


void MainWindow::on_btnDK_clicked()
{
    QString maSv = ui->lineMSV->text().trimmed();
    if(maSv.isEmpty()){
        QMessageBox::warning(this, "Lỗi", "Không được để trống mã sinh viên.");
        return;
    }
    char maLop[16] = "";
    SinhVien* sv = TimSinhVienTheoMa(dsLop, maSv.toStdString().c_str(), maLop);
    if (!sv){
        QMessageBox::warning(this, "Lỗi", "Sinh viên không tồn tại.");
        return;
    }

    QString maMh = ui->lineDK_MMH->text();
    if (maMh.isEmpty()){
        QMessageBox::warning(this, "Lỗi", "Chưa chọn lớp để đăng kí.");
        return;
    }

    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Xác nhận đăng kí",
        QString("Bạn có chắc chắn muốn đăng kí lớp tín chỉ không?"),
        QMessageBox::Yes | QMessageBox::No
        );
    if (reply != QMessageBox::Yes) return;

    int kq = ThemSVVaoLTC(ltcDangChon, maSv.toStdString().c_str());

    if(kq == 0){
        QMessageBox::information(this, "Thông báo", "Không tồn tại lớp tín chỉ.");
        return;
    } else if (kq == 1){
        QMessageBox::information(this, "Thông báo", "Sinh viên đã đăng kí lớp tín chỉ này.");
        return;
    } else if (kq == 2){
        QMessageBox::information(this, "Thông báo", "Không còn chỗ trống.");
        return;
    } else {
        QMessageBox::information(this, "Thành công", "Đăng kí thành công.");
        GhiDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
        DocDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
        int hk = ui->spDK_HK->value();
        QString nienkhoa = ui->lineDK_NK->text().trimmed();
        hienThiDK_DSLTC(dsLTC, hk, nienkhoa);
        hienThiDSLTC(dsLTC);
        return;
    }
}


void MainWindow::on_lineQLDK_NK_returnPressed()
{
    QString nienkhoa = ui->lineQLDK_NK->text().trimmed();
    int hk = ui->spQLDK_HK->value();

    if (nienkhoa.contains(' ')){
        QMessageBox::warning(this, "Lỗi", "Niên khóa không được chứa khoảng trắng.");
        return;
    }

    if (nienkhoa.length() != 9){
        QMessageBox::warning(this, "Lỗi", "Nhập sai niên khóa. Nhập theo dạng yyyy-yyyy");
        return;
    }else {
        int nam1 = nienkhoa.left(4).toInt();
        int nam2 = nienkhoa.mid(5, 4).toInt();
        if (nam1 >= nam2){
            QMessageBox::warning(this, "Lỗi", "Niên khóa không hợp lệ. Năm sau phải lớn hơn năm trước");
            return;
        }
    }
    if (hk <= 0) {
        QMessageBox::warning(this, "Lỗi", "Học kỳ phải lớn hơn 0.");
        return;
    }

    hienThiQLDK_LTC(dsLTC, hk, nienkhoa);
    ui->btnQLDK_Huy->setEnabled(true);
}

void MainWindow::hienThiQLDK_LTC(List_LTC &ds, int hk, const QString nienkhoa){
    ui->tblQLDK_LTC->setRowCount(0);
    bool check = false;
    int svdk = 0;
    int controng = 0;
    for (int i = 0; i < ds.n; i++){
        LopTinChi* ltc = ds.nodes[i];

        if (ltc->Hocky == hk && strcmp(ltc->NienKhoa, nienkhoa.toStdString().c_str()) == 0 && !ltc->huylop){
            svdk = demSoLuongSvDK(ltc->dssvdk);
            if (svdk < ltc->sosvmin){
                controng = ltc->sosvmax - svdk;
                check = true;

                int row = ui->tblQLDK_LTC->rowCount();
                ui->tblQLDK_LTC->insertRow(row);

                ui->tblQLDK_LTC->setItem(row, 0, new QTableWidgetItem(QString::number(ltc->MALOPTC)));
                ui->tblQLDK_LTC->setItem(row, 1, new QTableWidgetItem(ltc->MAMH));
                ui->tblQLDK_LTC->setItem(row, 2, new QTableWidgetItem(ltc->NienKhoa));
                ui->tblQLDK_LTC->setItem(row, 3, new QTableWidgetItem(QString::number(ltc->Hocky)));
                ui->tblQLDK_LTC->setItem(row, 4, new QTableWidgetItem(QString::number(ltc->Nhom)));
                ui->tblQLDK_LTC->setItem(row, 5, new QTableWidgetItem(QString::number(ltc->sosvmin)));
                ui->tblQLDK_LTC->setItem(row, 6, new QTableWidgetItem(QString::number(svdk)));
                ui->tblQLDK_LTC->setItem(row, 7, new QTableWidgetItem(QString::number(controng)));
            }
        }
    }

    if (!check){
        QMessageBox::information(this, "Thông báo", "Không có lớp tín chỉ nào ở trong hoc ki " + QString::number(hk) + " và niên khóa " + nienkhoa +"!");
        return;
    }
}

void MainWindow::on_btnQLDK_Huy_clicked()
{
    int row = ui->tblQLDK_LTC->rowCount();
    if (row == 0) {
        QMessageBox::information(nullptr, "Thông báo", "Không có lớp tín chỉ nào bị hủy (tất cả đều đủ sinh viên).");
        return;
    }

    for (int i = 0; i < row; i++){
        int maLtc = ui->tblQLDK_LTC->item(i, 0)->text().toInt();
        QMessageBox::StandardButton reply = QMessageBox::question(
            this,
            "Xác nhận xóa lớp tín chỉ",
            QString("Bạn có chắc chắn muốn hủy lớp tín chỉ" + QString::number(maLtc) + " không?"),
            QMessageBox::Yes | QMessageBox::No
            );
        if (reply != QMessageBox::Yes) return;
        HuyLTC(dsLTC, maLtc);
    }
    GhiDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
    DocDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
    hienThiDSLTC(dsLTC);
}

