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

private slots:

    void on_btnThemMH_clicked();

    void on_btnSuaMH_clicked();

    void on_btnXoaMH_clicked();

    void on_lineMaMH_textChanged(const QString &arg1);

    void on_lineTenMH_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    DS_LOPSV dsLop;
    List_LTC dsLTC;
    treeMH dsMH = nullptr;

};
#endif // MAINWINDOW_H
