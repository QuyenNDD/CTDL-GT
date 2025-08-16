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
    void setButtonState(bool state);
    void clearForm();
    void hienThiDK_DSLTC(List_LTC &ds, int hk, const QString nienkhoa);
private slots:

    void on_btnThem_clicked();

    void on_btnXoa_clicked();

    void on_btnSua_clicked();

    void on_tblDSLTC_cellClicked(int row, int column);

    void on_btnInDSSV_clicked();

    void on_btnGhiFile_clicked();

    void on_lineMSV_returnPressed();

    void on_lineDK_NK_returnPressed();

    void on_tblDK_DSLTC_cellClicked(int row, int column);

    void on_btnDK_clicked();

private:
    Ui::MainWindow *ui;
    DS_LOPSV dsLop;
    List_LTC dsLTC;
    treeMH dsMH = nullptr;
    int maLTCDangChon = -1;
    LopTinChi* ltcDangChon = NULL;
};
#endif // MAINWINDOW_H
