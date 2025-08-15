#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <cstring>
#include <QFile>

const int MAX_LTC = 10000;
const int MAX_LOPSV = 500;

struct MonHoc {
    char MAMH[11];
    char TENMH[51];
    int STCLT, STCTH;
};
struct nodeMH {
    MonHoc mh;
    nodeMH *left, *right;
};
typedef nodeMH* treeMH;

struct SinhVien {
    char MASV[16];
    char HO[51];
    char TEN[11];
    char PHAI[4];
    char SODT[16];
    char Email[50];
};
struct nodeSV {
    SinhVien sv;
    nodeSV *next;
};
typedef nodeSV* PTRSV;

struct LopSV {
    char MALOP[16];
    char TENLOP[51];
    PTRSV FirstSV;
};
struct DS_LOPSV {
    int n = 0;
    LopSV nodes[MAX_LOPSV];
};

struct DangKy {
    char MASV[16];
    float DIEM;
};

struct nodeDK {
    DangKy dk;
    nodeDK *next;
};
typedef nodeDK* PTRDK;

struct LopTinChi {
    int MALOPTC;
    char MAMH[11];
    char NienKhoa[10];
    int Hocky, Nhom, sosvmin, sosvmax;
    bool huylop = false;
    PTRDK dssvdk;
};
struct List_LTC {
    int n = 0;
    LopTinChi* nodes[MAX_LTC];
};

extern treeMH dsMH;

int DemSoLuongMonHoc(treeMH root);
treeMH SearchTree(treeMH root,const char* mamh);
void Insert_MonHoc(treeMH &root, MonHoc mh);
void SaveFileMonHoc(treeMH root, QTextStream &out);
void ThemMonHocVaoCay(treeMH& t, const MonHoc& mh);
void GhiDanhSachMonHoc(treeMH t, const char* filename);
int DocDanhSachMonHoc(treeMH &root, const QString& tenfile);
bool SuaMonHoc(treeMH root, const MonHoc& monHocMoi);
int RemoveTreeMH(treeMH &root,const char *mamh);
void LuuMonHocVaoMang(treeMH root, nodeMH* ds[], int &n);
void SapXepTangTheoTenMH(nodeMH* ds[], int n);
bool MonHocDaDuocDangKy(List_LTC &dsLTC, const char* mamh);

void GhiDanhSachLopSV(const DS_LOPSV& dsLop, const char* filename);
void DocDanhSachLopSV(DS_LOPSV& dsLop, const char* filename);
LopSV* TimLop(DS_LOPSV& dsLop, const char* MALOP);

void GhiDanhSachLopTinChi(const List_LTC& dsLTC, const char* filename);
void DocDanhSachLopTinChi(List_LTC& dsLTC, const char* filename);
bool TimMaMonHoc(treeMH root, const char* maMH);
int XoaLTC(List_LTC &ds, int maLtc);
int HieuChinhLTC(List_LTC &ds, int maLtc, const LopTinChi& ltcMoi);
LopTinChi* TimLopTinChi(const List_LTC& dsLTC, const char* mamh, const char* nienkhoa, int hocky, int nhom);
SinhVien* TimSinhVien(const DS_LOPSV& dsLop, const char* masv);

#endif // STRUCTURES_H
