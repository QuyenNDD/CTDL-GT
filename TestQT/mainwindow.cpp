 #include "mainwindow.h"
#include "ui_mainwindow.h"
#include "structures.h"
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
    ui->tblMH->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblND->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblSV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblLopSV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblKQ->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tblDiemTK->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->lineMaMH, &QLineEdit::textChanged,
            this, &MainWindow::on_lineMaMH_textChanged);
    connect(ui->lineMaMH, &QLineEdit::textChanged,
            this, &MainWindow::on_lineMaMH_textChanged);
    connect(ui->tblMH, &QTableWidget::itemSelectionChanged, this, [=]() {
        bool coDongDuocChon = !ui->tblMH->selectedItems().isEmpty();
        ui->btnSuaMH->setEnabled(coDongDuocChon);
        ui->btnXoaMH->setEnabled(coDongDuocChon);
    });
    connect(ui->tblSV, &QTableWidget::cellClicked,
            this, &MainWindow::on_tblSV_cellClicked);
    docDuLieuTuFile();
    connect(ui->tblLopSV, &QTableWidget::cellClicked,
            this, &MainWindow::on_tblLopSV_cellClicked);
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
    ui->txtMaSV->setEnabled(false);
    ui->txtHo->setEnabled(false);
    ui->txtTen->setEnabled(false);
    ui->cbPhai->setEnabled(false);
    ui->txtSoDT->setEnabled(false);
    ui->txtEmail->setEnabled(false);
    ui->btnThemSV->setEnabled(false);
    ui->btnXoaSV->setEnabled(false);
    ui->btnSuaSV->setEnabled(false);
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
    hienThiDanhSachLopSV(dsLop);
    hienThiDanhSachSV(dsLop);
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

void MainWindow::hienThiDanhSachLopSV(const DS_LOPSV& dsLop) {
    // Xóa dữ liệu cũ trên bảng
    ui->tblLopSV->clearContents();
    ui->tblLopSV->setRowCount(0);

    // Đặt header cho bảng
    QStringList headers = {"Mã Lớp", "Tên Lớp"};
    ui->tblLopSV->setColumnCount(headers.size());
    ui->tblLopSV->setHorizontalHeaderLabels(headers);

    // Duyệt qua tất cả lớp
    for (int i = 0; i < dsLop.n; ++i) {
        const LopSV &lop = dsLop.nodes[i];  // dùng const ref tránh copy

        int row = ui->tblLopSV->rowCount();
        ui->tblLopSV->insertRow(row);

        ui->tblLopSV->setItem(row, 0, new QTableWidgetItem(QString::fromUtf8(lop.MALOP)));
        ui->tblLopSV->setItem(row, 1, new QTableWidgetItem(QString::fromUtf8(lop.TENLOP)));
    }
    ui->tblLopSV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::hienThiDanhSachSV(const DS_LOPSV& dsLop) {
    ui->tblSV->clearContents();
    ui->tblSV->setRowCount(0);

    QStringList headers = {"Mã SV", "Họ", "Tên", "Phái", "SĐT", "Email"};
    ui->tblSV->setColumnCount(headers.size());
    ui->tblSV->setHorizontalHeaderLabels(headers);

    for (int i = 0; i < dsLop.n; ++i) {
        LopSV lop = dsLop.nodes[i];

        // Gom SV vào mảng tạm
        int count = 0;
        PTRSV p = lop.FirstSV;
        while (p != nullptr) {
            count++;
            p = p->next;
        }

        if (count == 0) continue;

        SinhVien* arr = new SinhVien[count];
        p = lop.FirstSV;
        for (int k = 0; k < count; k++) {
            arr[k] = p->sv;
            p = p->next;
        }

        // Sắp xếp selection sort
        selectionSort(arr, count);

        // Hiển thị sau khi sort
        for (int k = 0; k < count; k++) {
            int row = ui->tblSV->rowCount();
            ui->tblSV->insertRow(row);

            ui->tblSV->setItem(row, 0, new QTableWidgetItem(arr[k].MASV));
            ui->tblSV->setItem(row, 1, new QTableWidgetItem(arr[k].HO));
            ui->tblSV->setItem(row, 2, new QTableWidgetItem(arr[k].TEN));
            ui->tblSV->setItem(row, 3, new QTableWidgetItem(arr[k].PHAI));
            ui->tblSV->setItem(row, 4, new QTableWidgetItem(arr[k].SODT));
            ui->tblSV->setItem(row, 5, new QTableWidgetItem(arr[k].Email));
        }

        delete[] arr;
    }

    ui->tblSV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::hienThiSV_Lop(LopSV* lop) {
    if (lop == nullptr) return;

    // Gom SV vào mảng
    int count = 0;
    PTRSV p = lop->FirstSV;
    while (p != nullptr) {
        count++;
        p = p->next;
    }

    ui->tblSV->clearContents();
    ui->tblSV->setRowCount(0);

    QStringList headers = {"Mã SV", "Họ", "Tên", "Phái", "SĐT", "Email"};
    ui->tblSV->setColumnCount(headers.size());
    ui->tblSV->setHorizontalHeaderLabels(headers);

    if (count == 0) return;

    SinhVien* arr = new SinhVien[count];
    p = lop->FirstSV;
    for (int i = 0; i < count; i++) {
        arr[i] = p->sv;
        p = p->next;
    }

    // Sắp xếp selection sort
    selectionSort(arr, count);

    // Đổ dữ liệu ra bảng
    for (int i = 0; i < count; i++) {
        int row = ui->tblSV->rowCount();
        ui->tblSV->insertRow(row);

        ui->tblSV->setItem(row, 0, new QTableWidgetItem(arr[i].MASV));
        ui->tblSV->setItem(row, 1, new QTableWidgetItem(arr[i].HO));
        ui->tblSV->setItem(row, 2, new QTableWidgetItem(arr[i].TEN));
        ui->tblSV->setItem(row, 3, new QTableWidgetItem(arr[i].PHAI));
        ui->tblSV->setItem(row, 4, new QTableWidgetItem(arr[i].SODT));
        ui->tblSV->setItem(row, 5, new QTableWidgetItem(arr[i].Email));
    }

    delete[] arr;
    ui->tblSV->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_tblLopSV_cellClicked(int row, int /*column*/) {
    if (row < 0) return;

    QString maLop = ui->tblLopSV->item(row, 0)->text();
    QString tenLop = ui->tblLopSV->item(row, 1)->text();

    ui->txtMaLop->setText(maLop);
    ui->txtTenLop->setText(tenLop);
}

void MainWindow::on_ThemLSV_clicked()
{
    QString ma = ui->txtMaLop->text().trimmed();
    QString ten = ui->txtTenLop->text().trimmed();

    if (ma.isEmpty() || ten.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Mã lớp và tên lớp không được rỗng!");
        return;
    }

    // kiểm tra trùng mã lớp
    for (int i = 0; i < dsLop.n; i++) {
        if (QString::fromUtf8(dsLop.nodes[i].MALOP) == ma) {
            QMessageBox::warning(this, "Lỗi", "Mã lớp đã tồn tại!");
            return;
        }
    }

    if (dsLop.n >= MAX_LOPSV) {
        QMessageBox::warning(this, "Lỗi", "Danh sách lớp đầy!");
        return;
    }

    LopSV lop;
    strcpy(lop.MALOP, ma.toUtf8().constData());
    strcpy(lop.TENLOP, ten.toUtf8().constData());
    lop.FirstSV = nullptr;

    dsLop.nodes[dsLop.n++] = lop;

    hienThiDanhSachLopSV(dsLop);

    QMessageBox::information(this, "Thành công",
                             "Đã thêm lớp: " + ma + " - " + ten);
}


void MainWindow::on_SuaLSV_clicked()
{
    int row = ui->tblLopSV->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Lỗi", "Hãy chọn lớp cần sửa!");
        return;
    }

    QString oldTen = QString::fromUtf8(dsLop.nodes[row].TENLOP);

    QString ten = ui->txtTenLop->text().trimmed();
    if (ten.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Tên lớp không được rỗng!");
        return;
    }

    strcpy(dsLop.nodes[row].TENLOP, ten.toUtf8().constData());

    hienThiDanhSachLopSV(dsLop);

    QMessageBox::information(this, "Thành công",
                             "Đã sửa lớp: " + QString::fromUtf8(dsLop.nodes[row].MALOP) +
                                 "\nTên cũ: " + oldTen +
                                 "\nTên mới: " + ten);
}


void MainWindow::on_XoaLSV_clicked()
{
    int row = ui->tblLopSV->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "Lỗi", "Hãy chọn lớp cần xóa!");
        return;
    }

    // giải phóng danh sách SV của lớp này
    PTRSV p = dsLop.nodes[row].FirstSV;
    while (p) {
        PTRSV tmp = p;
        p = p->next;
        delete tmp;
    }

    QString ma = QString::fromUtf8(dsLop.nodes[row].MALOP);
    QString ten = QString::fromUtf8(dsLop.nodes[row].TENLOP);

    // dịch trái mảng
    for (int i = row; i < dsLop.n - 1; i++) {
        dsLop.nodes[i] = dsLop.nodes[i + 1];
    }
    dsLop.n--;

    hienThiDanhSachLopSV(dsLop);

    QMessageBox::information(this, "Thành công",
                             "Đã xóa lớp: " + ma + " - " + ten);
}


void MainWindow::on_LuuLSV_clicked()
{
    ghiDuLieuTuFile(); // gọi hàm đã viết sẵn
    QMessageBox::information(this, "Thông báo", "Đã lưu danh sách lớp thành công!");
}

void MainWindow::on_btnMaLop_SV_clicked()
{
    QString maLop = ui->txtMaLop_SV->text().trimmed();

    if (maLop.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập mã lớp!");
        return;
    }

    LopSV* lop = TimLop(dsLop, maLop.toStdString().c_str());

    if (lop == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy mã lớp: " + maLop);
        return;
    }

    lopHienTai = lop;

    // Gọi hàm hiển thị đã sort
    hienThiSV_Lop(lopHienTai);

    QMessageBox::information(this, "Thông báo",
                             "Đang nhập sinh viên cho lớp: " + maLop);
    ui->txtMaSV->setEnabled(true);
    ui->txtHo->setEnabled(true);
    ui->txtTen->setEnabled(true);
    ui->cbPhai->setEnabled(true);
    ui->txtSoDT->setEnabled(true);
    ui->txtEmail->setEnabled(true);
    ui->btnThemSV->setEnabled(true);
    ui->btnSuaSV->setEnabled(true);
    ui->btnXoaSV->setEnabled(true);
}

void MainWindow::on_tblSV_cellClicked(int row, int column)
{
    if (row < 0) return;

    // Lấy dữ liệu từ bảng
    QString maSV  = ui->tblSV->item(row, 0)->text();
    QString ho    = ui->tblSV->item(row, 1)->text();
    QString ten   = ui->tblSV->item(row, 2)->text();
    QString phai  = ui->tblSV->item(row, 3)->text();
    QString sdt   = ui->tblSV->item(row, 4)->text();
    QString email = ui->tblSV->item(row, 5)->text();

    // Hiển thị lên các ô nhập liệu
    ui->txtMaSV->setText(maSV);
    ui->txtHo->setText(ho);
    ui->txtTen->setText(ten);
    ui->txtSoDT->setText(sdt);
    ui->txtEmail->setText(email);

    // Nếu bạn đã đổi PHAI sang QComboBox (vd: ui->cmbPhai)
    int index = ui->cbPhai->findText(phai);
    if (index != -1)
        ui->cbPhai->setCurrentIndex(index);
}



void MainWindow::on_btnThemSV_clicked()
{
    if (lopHienTai == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Hãy chọn lớp trước khi thêm sinh viên!");
        return;
    }

    // Lấy dữ liệu từ giao diện
    SinhVien sv;
    strcpy(sv.MASV, ui->txtMaSV->text().trimmed().toStdString().c_str());
    strcpy(sv.HO, ui->txtHo->text().trimmed().toStdString().c_str());
    strcpy(sv.TEN, ui->txtTen->text().trimmed().toStdString().c_str());
    strcpy(sv.PHAI, ui->cbPhai->currentText().toStdString().c_str());
    strcpy(sv.SODT, ui->txtSoDT->text().trimmed().toStdString().c_str());
    strcpy(sv.Email, ui->txtEmail->text().trimmed().toStdString().c_str());

    if (strlen(sv.MASV) == 0) {
        QMessageBox::warning(this, "Lỗi", "Mã sinh viên không được để trống!");
        return;
    }

    // 🔎 Kiểm tra trùng MASV, SODT, Email
    for (PTRSV cur = lopHienTai->FirstSV; cur != nullptr; cur = cur->next) {
        if (strcmp(cur->sv.MASV, sv.MASV) == 0) {
            QMessageBox::warning(this, "Lỗi", "Mã sinh viên đã tồn tại!");
            return;
        }
        if (strlen(sv.SODT) > 0 && strcmp(cur->sv.SODT, sv.SODT) == 0) {
            QMessageBox::warning(this, "Lỗi", "Số điện thoại đã tồn tại!");
            return;
        }
        if (strlen(sv.Email) > 0 && strcmp(cur->sv.Email, sv.Email) == 0) {
            QMessageBox::warning(this, "Lỗi", "Email đã tồn tại!");
            return;
        }
    }

    // Kiểm tra số điện thoại chỉ chứa số
    QString sodt = ui->txtSoDT->text().trimmed();
    QRegularExpression regexSdt("^\\d+$");
    if (!sodt.isEmpty() && !regexSdt.match(sodt).hasMatch()) {
        QMessageBox::warning(this, "Lỗi", "Số điện thoại chỉ được chứa chữ số!");
        return;
    }

    // Kiểm tra email hợp lệ
    QString email = ui->txtEmail->text().trimmed();
    QRegularExpression regexEmail("^[\\w.%+-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");
    if (!email.isEmpty() && !regexEmail.match(email).hasMatch()) {
        QMessageBox::warning(this, "Lỗi", "Email không hợp lệ!");
        return;
    }

    // Thêm vào đầu danh sách
    PTRSV node = new nodeSV;
    node->sv = sv;
    node->next = lopHienTai->FirstSV;
    lopHienTai->FirstSV = node;

    hienThiSV_Lop(lopHienTai);

    QMessageBox::information(this, "Thành công",
                             "Đã thêm sinh viên: " + QString::fromUtf8(sv.MASV) +
                                 " - " + QString::fromUtf8(sv.HO) + " " + QString::fromUtf8(sv.TEN));
}


void MainWindow::on_btnXoaSV_clicked()
{
    if (lopHienTai == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Hãy chọn lớp trước khi xóa sinh viên!");
        return;
    }

    QString maSV = ui->txtMaSV->text().trimmed();
    if (maSV.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Nhập MASV để xóa!");
        return;
    }

    PTRSV prev = nullptr;
    PTRSV cur = lopHienTai->FirstSV;

    while (cur != nullptr && strcmp(cur->sv.MASV, maSV.toStdString().c_str()) != 0) {
        prev = cur;
        cur = cur->next;
    }

    if (cur == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy sinh viên!");
        return;
    }

    QString hoTen = QString::fromUtf8(cur->sv.HO) + " " + QString::fromUtf8(cur->sv.TEN);

    if (prev == nullptr) {
        lopHienTai->FirstSV = cur->next;
    } else {
        prev->next = cur->next;
    }
    delete cur;

    hienThiSV_Lop(lopHienTai);

    QMessageBox::information(this, "Thành công",
                             "Đã xóa sinh viên: " + maSV + " - " + hoTen);
}


void MainWindow::on_btnSuaSV_clicked()
{
    if (lopHienTai == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Hãy chọn lớp trước khi sửa!");
        return;
    }

    QString maSV = ui->txtMaSV->text().trimmed();
    if (maSV.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Nhập MASV để sửa!");
        return;
    }

    PTRSV cur = lopHienTai->FirstSV;
    while (cur != nullptr && strcmp(cur->sv.MASV, maSV.toStdString().c_str()) != 0) {
        cur = cur->next;
    }

    if (cur == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy sinh viên!");
        return;
    }

    QString oldHoTen = QString::fromUtf8(cur->sv.HO) + " " + QString::fromUtf8(cur->sv.TEN);

    // Lấy dữ liệu mới
    char ho[51], ten[11], sdt[16], email[51];
    strcpy(ho, ui->txtHo->text().trimmed().toStdString().c_str());
    strcpy(ten, ui->txtTen->text().trimmed().toStdString().c_str());
    QString phaiStr = ui->cbPhai->currentText();
    strcpy(cur->sv.PHAI, phaiStr.toStdString().c_str());
    strcpy(sdt, ui->txtSoDT->text().trimmed().toStdString().c_str());
    strcpy(email, ui->txtEmail->text().trimmed().toStdString().c_str());

    // 🔎 Kiểm tra trùng SDT, Email với sinh viên khác
    for (PTRSV p = lopHienTai->FirstSV; p != nullptr; p = p->next) {
        if (p == cur) continue; // bỏ qua chính nó
        if (strlen(sdt) > 0 && strcmp(p->sv.SODT, sdt) == 0) {
            QMessageBox::warning(this, "Lỗi", "Số điện thoại đã tồn tại!");
            return;
        }
        if (strlen(email) > 0 && strcmp(p->sv.Email, email) == 0) {
            QMessageBox::warning(this, "Lỗi", "Email đã tồn tại!");
            return;
        }
    }

    // Cập nhật thông tin
    strcpy(cur->sv.HO, ho);
    strcpy(cur->sv.TEN, ten);
    strcpy(cur->sv.SODT, sdt);
    strcpy(cur->sv.Email, email);

    hienThiSV_Lop(lopHienTai);

    QString newHoTen = QString::fromUtf8(cur->sv.HO) + " " + QString::fromUtf8(cur->sv.TEN);

    QMessageBox::information(this, "Thành công",
                             "Đã sửa sinh viên: " + maSV +
                                 "\nTên cũ: " + oldHoTen +
                                 "\nTên mới: " + newHoTen);
}


void MainWindow::on_btnLuuSV_clicked()
{
    ghiDuLieuTuFile();  // bạn đã có sẵn hàm này trong MainWindow
    QMessageBox::information(this, "Thông báo", "Đã lưu danh sách sinh viên ra file!");
}


void MainWindow::on_btnDiemTB_clicked()
{
    QString maLop = ui->txtDiemTB->text().trimmed();
    if (maLop.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập mã lớp!");
        return;
    }

    // Tìm lớp theo mã
    LopSV* lop = TimLop(dsLop, maLop.toUtf8().constData());
    if (!lop) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp!");
        return;
    }

    //Hiện thông tin lớp vào lineEdit
    ui->hienLopDTB->setText(QString::fromUtf8(lop->MALOP));

    //Tính tổng số tín chỉ của lớp
    int tongTinChi = 0;
    for (PTRSV p = lop->FirstSV; p != nullptr; p = p->next) {
        tongTinChi += TongTinChiCuaSV(p->sv, dsLTC, dsMH);
        // 👉 bạn cần viết hàm TongTinChiCuaSV(sv, dsLTC, dsMH)
    }
    ui->lineEditTinChiK->setText(QString::number(tongTinChi));

    // Hiển thị bảng điểm TB
    ui->tblKQ->clearContents();
    ui->tblKQ->setRowCount(0);

    QStringList headers = {"STT", "MASV", "Họ Tên", "Điểm TB"};
    ui->tblKQ->setColumnCount(headers.size());
    ui->tblKQ->setHorizontalHeaderLabels(headers);

    int stt = 1;
    for (PTRSV p = lop->FirstSV; p != nullptr; p = p->next) {
        const SinhVien &sv = p->sv;
        float diemTB = TinhDiemTrungBinhSV(sv, dsLTC, dsMH);

        int row = ui->tblKQ->rowCount();
        ui->tblKQ->insertRow(row);

        ui->tblKQ->setItem(row, 0, new QTableWidgetItem(QString::number(stt++)));
        ui->tblKQ->setItem(row, 1, new QTableWidgetItem(QString::fromUtf8(sv.MASV)));
        ui->tblKQ->setItem(row, 2, new QTableWidgetItem(QString::fromUtf8(sv.HO) + " " + QString::fromUtf8(sv.TEN)));
        ui->tblKQ->setItem(row, 3, new QTableWidgetItem(QString::number(diemTB, 'f', 2)));
    }

    ui->tblKQ->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}


void MainWindow::on_btnDiemTK_clicked()
{
    QString maLop = ui->txtDiemTK->text().trimmed();
    if (maLop.isEmpty()) {
        QMessageBox::warning(this, "Lỗi", "Vui lòng nhập mã lớp!");
        return;
    }

    // 1. Tìm lớp
    LopSV* lop = TimLop(dsLop, maLop.toUtf8().constData());
    if (lop == nullptr) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy lớp!");
        return;
    }

    // 2. Thu thập tất cả mã môn học có SV lớp này tham gia
    QStringList dsMonHoc;
    for (int i = 0; i < dsLTC.n; i++) {
        LopTinChi* ltc = dsLTC.nodes[i];
        for (PTRDK p = ltc->dssvdk; p != nullptr; p = p->next) {
            // kiểm tra SV này có thuộc lớp đang xét không
            if (TimSinhVienTrongLop(*lop, p->dk.MASV) != nullptr) {
                QString mamh = QString::fromUtf8(ltc->MAMH);
                if (!dsMonHoc.contains(mamh)) {
                    dsMonHoc << mamh;
                }
            }
        }
    }
    dsMonHoc.sort();

    // 3. Setup bảng
    QStringList headers;
    headers << "STT" << "Mã SV" << "Họ Tên";
    headers << dsMonHoc;

    ui->tblDiemTK->clearContents();
    ui->tblDiemTK->setRowCount(0);
    ui->tblDiemTK->setColumnCount(headers.size());
    ui->tblDiemTK->setHorizontalHeaderLabels(headers);

    // 4. Hiển thị từng SV trong lớp
    int stt = 1;
    for (PTRSV sv = lop->FirstSV; sv != nullptr; sv = sv->next) {
        int row = ui->tblDiemTK->rowCount();
        ui->tblDiemTK->insertRow(row);

        ui->tblDiemTK->setItem(row, 0, new QTableWidgetItem(QString::number(stt++)));
        ui->tblDiemTK->setItem(row, 1, new QTableWidgetItem(QString::fromUtf8(sv->sv.MASV)));
        ui->tblDiemTK->setItem(row, 2, new QTableWidgetItem(
                                           QString("%1 %2").arg(sv->sv.HO).arg(sv->sv.TEN)
                                           ));

        // Với từng môn học -> tìm điểm cao nhất của SV này
        for (int j = 0; j < dsMonHoc.size(); j++) {
            QString mamh = dsMonHoc[j];
            float diemMax = -1;

            for (int k = 0; k < dsLTC.n; k++) {
                LopTinChi* ltc = dsLTC.nodes[k];
                if (mamh == QString::fromUtf8(ltc->MAMH)) {
                    for (PTRDK p = ltc->dssvdk; p != nullptr; p = p->next) {
                        if (strcmp(p->dk.MASV, sv->sv.MASV) == 0) {
                            if (p->dk.DIEM > diemMax) {
                                diemMax = p->dk.DIEM;
                            }
                        }
                    }
                }
            }

            if (diemMax >= 0) {
                ui->tblDiemTK->setItem(row, 3 + j, new QTableWidgetItem(QString::number(diemMax)));
            } else {
                ui->tblDiemTK->setItem(row, 3 + j, new QTableWidgetItem("-"));
            }
        }
    }

    ui->tblDiemTK->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
