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

void GhiMonHoc_LNR(treeMH t, FILE* f, int& count);
void GhiDanhSachMonHoc(treeMH t, const char* filename);
void ThemMonHocVaoCay(treeMH& t, const MonHoc& mh);
void DocDanhSachMonHoc(treeMH& t, const char* filename);

void GhiDanhSachLopSV(const DS_LOPSV& dsLop, const char* filename);
void DocDanhSachLopSV(DS_LOPSV& dsLop, const char* filename);

void GhiDanhSachLopTinChi(const List_LTC& dsLTC, const char* filename);
void DocDanhSachLopTinChi(List_LTC& dsLTC, const char* filename);

#endif // STRUCTURES_H
