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
    ui->tblMH->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblND->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->lineMaMH, &QLineEdit::textChanged,
            this, &MainWindow::on_lineMaMH_textChanged);
    connect(ui->tblMH, &QTableWidget::itemSelectionChanged, this, [=]() {
        bool coDongDuocChon = !ui->tblMH->selectedItems().isEmpty();
        ui->btnSuaMH->setEnabled(coDongDuocChon);
        ui->btnXoaMH->setEnabled(coDongDuocChon);
    });
    docDuLieuTuFile();
    connect(ui->lineNDNK, &QLineEdit::textChanged, this, [=](QString text){
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
        if (text != ui->lineNDNK->text()) {
            ui->lineNDNK->setText(text);
        }
    });
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
void MainWindow::on_lineMaMH_textChanged(const QString &text)
{
    std::string input = text.toStdString();
    std::string result;
    result.reserve(10);

    for (char c : input) {
        if (c == ' ') continue;
        if (!isalnum((unsigned char)c)) continue;
        c = std::toupper((unsigned char)c);
        if (result.size() < 10) result.push_back(c);
    }

    QString filtered = QString::fromStdString(result);

    // tránh vòng lặp vô hạn: chỉ setText nếu khác
    if (ui->lineMaMH->text() != filtered) {
        ui->lineMaMH->setText(filtered);
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
void MainWindow::on_lineNDMH_textChanged(const QString &text)
{
    std::string input = text.toStdString();
    std::string result;
    result.reserve(10);

    for (char c : input) {
        if (c == ' ') continue;
        if (!isalnum((unsigned char)c)) continue;
        c = std::toupper((unsigned char)c);
        if (result.size() < 10) result.push_back(c);
    }

    QString filtered = QString::fromStdString(result);

    // tránh vòng lặp vô hạn: chỉ setText nếu khác
    if (ui->lineNDMH->text() != filtered) {
        ui->lineNDMH->setText(filtered);
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

    if (ma.isEmpty()) {
        QMessageBox::warning(this, "Thiếu dữ liệu", "Vui lòng nhập Mã môn học!");
        return;
    }
    if (ten.isEmpty()) {
        QMessageBox::warning(this, "Thiếu dữ liệu", "Vui lòng nhập Tên môn học!");
        return;
    }
    if (stclt <= 0) {
        QMessageBox::warning(this, "Sai dữ liệu", "Số tín chỉ lý thuyết không hợp lệ(<=0)!");
        return;
    }
    if (stcth <= 0) {
        QMessageBox::warning(this, "Sai dữ liệu", "Số tín chỉ thực hành không hợp lệ(<=0)!");
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
        ui->lineMaMH->setText("");
        ui->lineTenMH->setText("");
        ui->spinBox_STCLT->setValue(0);
        ui->spinBox_STCTH->setValue(0);
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
            ui->lineMaMH->setText("");
            ui->lineTenMH->setText("");
            ui->spinBox_STCLT->setValue(0);
            ui->spinBox_STCTH->setValue(0);
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
    for(int i = 0; i<n; i++){
        MonHoc mh = ds[i]->mh;
        qDebug() << mh.TENMH;
    }
    SapXepTangTheoTenMH(ds, n);

    ui->tblMH->setRowCount(0);
    ui->tblMH->setColumnCount(4);
    QStringList header = {"Mã MH", "Tên môn học", "STCLT", "STCTH"};
    ui->tblMH->setHorizontalHeaderLabels(header);

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


void MainWindow::on_btnNDSearch_clicked()
{

    ui->tblND->clear();
    ui->tblND->setRowCount(0);
    ui->tblND->setColumnCount(5);
    QStringList headers = {"STT", "MASV", "HỌ", "TÊN", "ĐIỂM"};
    ui->tblND->setHorizontalHeaderLabels(headers);

    QString mamh = ui->lineNDMH->text().trimmed().toUpper();
    QString nienkhoa = ui->lineNDNK->text().trimmed();
    int hocky = ui->spinBoxNDHK->value();
    int nhom = ui->spinBoxNDNhom->value();
    if (mamh.isEmpty()) {
        QMessageBox::warning(this, "Thiếu dữ liệu", "Mã môn học không được trống!");
        return;
    }
    if (nienkhoa.isEmpty()) {
        QMessageBox::warning(this, "Thiếu dữ liệu", "Niên khóa không được trống!");
        return;
    }
    if (hocky <= 0) {
        QMessageBox::warning(this, "Sai dữ liệu", "Học kỳ không hợp lệ(<=0)!");
        return;
    }
    if (nhom <= 0) {
        QMessageBox::warning(this, "Sai dữ liệu", "Nhóm không hợp lệ(<=0)!");
        return;
    }
    LopTinChi* ltc = TimLopTinChi(dsLTC, mamh.toStdString().c_str(), nienkhoa.toStdString().c_str(), hocky, nhom);

    if (ltc == nullptr) {
        QMessageBox::warning(this, "Thông báo", "Không tìm thấy lớp tín chỉ phù hợp.");
        return;
    }
    treeMH mhNode = SearchTree(dsMH, mamh.toStdString().c_str());
    ui->lineEditNDMonHoc->setText(mhNode->mh.TENMH);
    ui->lineEditNDNienKhoa->setText(nienkhoa);
    ui->lineEditNDHocKy->setText(QString::number(hocky));
    ui->lineEditNDNhom->setText(QString::number(nhom));
    int row = 0;
    int stt = 1;
    PTRDK p = ltc->dssvdk;
    while (p != nullptr) {
        SinhVien* sv = TimSinhVien(dsLop, p->dk.MASV);

        ui->tblND->insertRow(row);

        ui->tblND->setItem(row, 0, new QTableWidgetItem(QString::number(stt++)));
        ui->tblND->setItem(row, 1, new QTableWidgetItem(p->dk.MASV));

        if (sv != nullptr) {
            ui->tblND->setItem(row, 2, new QTableWidgetItem(QString(sv->HO)));
            ui->tblND->setItem(row, 3, new QTableWidgetItem(QString(sv->TEN)));
        } else {
            ui->tblND->setItem(row, 2, new QTableWidgetItem("[Không có]"));
            ui->tblND->setItem(row, 3, new QTableWidgetItem("[Không có]"));
        }

        QTableWidgetItem* diemItem = new QTableWidgetItem(QString::number(p->dk.DIEM, 'f', 2));
        diemItem->setTextAlignment(Qt::AlignCenter);
        diemItem->setFlags(diemItem->flags() | Qt::ItemIsEditable);
        ui->tblND->setItem(row, 4, diemItem);

        ++row;
        p = p->next;
    }

}

void MainWindow::on_btnNDSave_clicked()
{
    QString mamh = ui->lineNDMH->text().trimmed().toUpper();
    QString nienkhoa = ui->lineNDNK->text().trimmed();
    int hocky = ui->spinBoxNDHK->value();
    int nhom = ui->spinBoxNDNhom->value();

    LopTinChi* ltc = TimLopTinChi(dsLTC, mamh.toStdString().c_str(), nienkhoa.toStdString().c_str(), hocky, nhom);
    if (ltc == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp tín chỉ.");
        return;
    }

    int rowCount = ui->tblND->rowCount();
    int soLuu = 0;
    for (int row = 0; row < rowCount; row++) {
        QString masv = ui->tblND->item(row, 1)->text();
        QString diemStr = ui->tblND->item(row, 4)->text();

        bool ok;
        float diem = diemStr.toFloat(&ok);
        if (!ok || diem < 0 || diem > 10) {
            QMessageBox::warning(this, "Lỗi", QString("Điểm không hợp lệ tại dòng %1. Nhập điểm từ 0 đến 10.").arg(row + 1));
            return;
        }

        PTRDK p = ltc->dssvdk;
        while (p != nullptr) {
            if (QString(p->dk.MASV) == masv) {
                if (p->dk.DIEM != diem) {
                    p->dk.DIEM = diem;
                    ++soLuu;
                }
                break;
            }
            p = p->next;
        }
    }
    GhiDanhSachLopTinChi(dsLTC, "DS_LTC_DK.txt");
    if(soLuu > 0 )
    {
        QMessageBox::information(this, "Thành công", QString("Cập nhật thành công"));
    } else {
        QMessageBox::information(this, "Thông báo", QString("Chưa có thay đổi nào!"));
    }
}


void MainWindow::on_tblMH_cellClicked(int row, int column)
{
    QString maMH = ui->tblMH->item(row, 0)->text();
    QString tenMH = ui->tblMH->item(row, 1)->text();
    int STCLT = ui->tblMH->item(row, 2)->text().toInt();
    int STCTH = ui->tblMH->item(row, 3)->text().toInt();

    ui->lineMaMH->setText(maMH);
    ui->lineTenMH->setText(tenMH);
    ui->spinBox_STCLT->setValue(STCLT);
    ui->spinBox_STCTH->setValue(STCTH);
}

