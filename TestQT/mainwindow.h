#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <structures.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void docDuLieuTuFile();
    void ghiDuLieuTuFile();
    int demSoLuongSvDK(PTRDK head);
    void hienThiDSLTC(List_LTC &ds);
    void LoadTableMonHoc(treeMH root);
    void hienThiDanhSachLopSV(const DS_LOPSV& dsLop);
    void hienThiDanhSachSV(const DS_LOPSV& dsLop);
    void hienThiSV_Lop(LopSV* lop);
    void themSinhVien(const QString &maLop, const SinhVien &sv);
    void suaSinhVien(const QString &maSV, const SinhVien &svMoi);
    void xoaSinhVien(const QString &maSV);

private slots:

    void on_btnThemMH_clicked();

    void on_btnSuaMH_clicked();

    void on_btnXoaMH_clicked();

    void on_lineMaMH_textChanged(const QString &arg1);

    void on_lineTenMH_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_btnThem_clicked();

    void on_btnXoa_clicked();

    void on_btnSua_clicked();

    void on_tblDSLTC_cellClicked(int row, int column);

    void on_btnNDSearch_clicked();

    void on_lineNDMH_textChanged(const QString &arg1);

    void on_btnNDSave_clicked();

    void on_tblMH_cellClicked(int row, int column);

    void on_tblLopSV_cellClicked(int row, int column);

    void on_tblSV_cellClicked(int row, int column);

    void on_ThemLSV_clicked();

    void on_SuaLSV_clicked();

    void on_XoaLSV_clicked();

    void on_LuuLSV_clicked();

    void on_btnMaLop_SV_clicked();

    void on_btnThemSV_clicked();

    void on_btnXoaSV_clicked();

    void on_btnSuaSV_clicked();

    void on_btnLuuSV_clicked();

    void on_btnDiemTB_clicked();

    void on_btnDiemTK_clicked();

private:
    Ui::MainWindow *ui;
    DS_LOPSV dsLop;
    List_LTC dsLTC;
    treeMH dsMH = nullptr;
    int maLTCDangChon = -1;
    LopSV* lopHienTai = nullptr;  // lớp hiện tại khi nhập SV
};
#endif // MAINWINDOW_H
