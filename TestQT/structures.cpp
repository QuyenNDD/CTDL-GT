#include "structures.h"
#include <cstdio>
#include <cstring>

void GhiMonHoc_LNR(treeMH t, FILE* f, int& count) {
    if (t == nullptr) return;
    GhiMonHoc_LNR(t->left, f, count);

    fprintf(f, "%s|%s|%d|%d\n", t->mh.MAMH, t->mh.TENMH, t->mh.STCLT, t->mh.STCTH);
    count++;

    GhiMonHoc_LNR(t->right, f, count);
}

void GhiDanhSachMonHoc(treeMH t, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Không thể mở file để ghi.\n");
        return;
    }

    int count = 0;
    // Ghi tạm số lượng = 0
    fprintf(f, "%d\n", count);

    // Ghi danh sách môn học
    GhiMonHoc_LNR(t, f, count);

    // Ghi lại số lượng ở đầu file
    rewind(f);
    fprintf(f, "%d\n", count);

    fclose(f);
}

void ThemMonHocVaoCay(treeMH& t, const MonHoc& mh) {
    if (t == nullptr) {
        t = new nodeMH{mh, nullptr, nullptr};
        return;
    }
    if (strcmp(mh.MAMH, t->mh.MAMH) < 0)
        ThemMonHocVaoCay(t->left, mh);
    else if (strcmp(mh.MAMH, t->mh.MAMH) > 0)
        ThemMonHocVaoCay(t->right, mh);
    // Trùng mã thì không thêm
}

void DocDanhSachMonHoc(treeMH& t, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Không thể mở file để đọc.\n");
        return;
    }

    int n;
    fscanf(f, "%d\n", &n);

    for (int i = 0; i < n; ++i) {
        MonHoc mh;
        char line[256];
        fgets(line, sizeof(line), f);
        sscanf(line, "%[^|]|%[^|]|%d|%d", mh.MAMH, mh.TENMH, &mh.STCLT, &mh.STCTH);

        ThemMonHocVaoCay(t, mh);
    }

    fclose(f);
}

void GhiDanhSachLopSV(const DS_LOPSV& dsLop, const char* filename) {
    FILE* f = fopen(filename, "w");
    if (!f) {
        printf("Không thể mở file để ghi.\n");
        return;
    }

    fprintf(f, "%d\n", dsLop.n);  // ghi số lớp

    for (int i = 0; i < dsLop.n; ++i) {
        const LopSV& lop = dsLop.nodes[i];
        fprintf(f, "%s|%s\n", lop.MALOP, lop.TENLOP);

        // Đếm số sinh viên trong danh sách liên kết
        int slsv = 0;
        PTRSV p = lop.FirstSV;
        while (p != nullptr) {
            ++slsv;
            p = p->next;
        }

        fprintf(f, "\t%d\n", slsv);

        // Ghi danh sách sinh viên
        p = lop.FirstSV;
        while (p != nullptr) {
            const SinhVien& sv = p->sv;
            fprintf(f, "\t%s|%s|%s|%s|%s|%s\n",
                    sv.MASV, sv.HO, sv.TEN, sv.PHAI, sv.SODT, sv.Email);
            p = p->next;
        }
    }

    fclose(f);
}

void DocDanhSachLopSV(DS_LOPSV& dsLop, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Không thể mở file để đọc.\n");
        dsLop.n = 0;
        return;
    }

    fscanf(f, "%d\n", &dsLop.n);
    for (int i = 0; i < dsLop.n; ++i) {
        char line[256];
        fgets(line, sizeof(line), f);

        // Tách MALOP và TENLOP
        char* token = strtok(line, "|");
        strcpy(dsLop.nodes[i].MALOP, token);
        token = strtok(nullptr, "\n");
        if (token != nullptr) {
            // loại bỏ ký tự newline cuối dòng nếu có
            token[strcspn(token, "\r\n")] = '\0';
            strcpy(dsLop.nodes[i].TENLOP, token);
        }

        int slsv;
        fscanf(f, "\t%d\n", &slsv);
        dsLop.nodes[i].FirstSV = nullptr;
        PTRSV tail = nullptr;

        for (int j = 0; j < slsv; ++j) {
            fgets(line, sizeof(line), f);
            SinhVien sv;
            sscanf(line, "\t%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%s",
                   sv.MASV, sv.HO, sv.TEN, sv.PHAI, sv.SODT, sv.Email);

            PTRSV node = new nodeSV{sv, nullptr};
            if (dsLop.nodes[i].FirstSV == nullptr)
                dsLop.nodes[i].FirstSV = node;
            else
                tail->next = node;
            tail = node;
        }
    }

    fclose(f);
}



void GhiDanhSachLopTinChi(const List_LTC& dsLTC, const char* filename) {
    FILE* f = fopen(filename, "wt");
    if (!f) {
        printf("Không thể mở file để ghi.\n");
        return;
    }

    fprintf(f, "%d\n", dsLTC.n);
    for (int i = 0; i < dsLTC.n; ++i) {
        LopTinChi* ltc = dsLTC.nodes[i];

        fprintf(f, "%d|%s|%s|%d|%d|%d|%d|%d\n",
                ltc->MALOPTC, ltc->MAMH, ltc->NienKhoa,
                ltc->Hocky, ltc->Nhom, ltc->sosvmin, ltc->sosvmax, ltc->huylop ? 1 : 0);

        // Đếm số sinh viên đăng ký
        int count = 0;
        PTRDK p = ltc->dssvdk;
        while (p != nullptr) {
            ++count;
            p = p->next;
        }
        fprintf(f, "\t%d\n", count);

        // Ghi từng sinh viên
        p = ltc->dssvdk;
        while (p != nullptr) {
            fprintf(f, "\t%s|%.2f\n", p->dk.MASV, p->dk.DIEM);
            p = p->next;
        }
    }

    fclose(f);
}

void DocDanhSachLopTinChi(List_LTC& dsLTC, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Không thể mở file để đọc.\n");
        dsLTC.n = 0;
        return;
    }

    fscanf(f, "%d\n", &dsLTC.n);
    for (int i = 0; i < dsLTC.n; ++i) {
        LopTinChi* ltc = new LopTinChi;
        ltc->dssvdk = nullptr;

        // Đọc thông tin lớp tín chỉ
        fscanf(f, "%d|%10[^|]|%9[^|]|%d|%d|%d|%d|%d\n",
               &ltc->MALOPTC, ltc->MAMH, ltc->NienKhoa,
               &ltc->Hocky, &ltc->Nhom, &ltc->sosvmin,
               &ltc->sosvmax, (int*)&ltc->huylop);

        // Đọc số lượng sinh viên đăng ký (dòng có tab đầu dòng)
        int slDK;
        fscanf(f, "\t%d\n", &slDK);

        PTRDK tail = nullptr;
        for (int j = 0; j < slDK; ++j) {
            char line[256];
            fgets(line, sizeof(line), f);

            DangKy dk;
            sscanf(line, "\t%[^|]|%f", dk.MASV, &dk.DIEM);

            PTRDK node = new nodeDK{dk, nullptr};
            if (ltc->dssvdk == nullptr)
                ltc->dssvdk = node;
            else
                tail->next = node;
            tail = node;
        }

        dsLTC.nodes[i] = ltc;
    }

    fclose(f);
}

bool TimMaMonHoc(treeMH root, const char* maMH){
    while (root != NULL){
        int cmp = strcmp(maMH, root->mh.MAMH);
        if (cmp == 0) return true;
        else if (cmp > 0) {
            root = root->right;
        }else {
            root = root->left;
        }
    }
    return false;
}

MonHoc* TimMonHocTheoMa(treeMH root, const char* maMH){
    while (root != NULL) {
        int cmp = strcmp(maMH, root->mh.MAMH);
        if (cmp == 0) return &root->mh;
        else if (cmp < 0) root = root->left;
        else root = root->right;
    }
    return NULL;
}

int XoaLTC(List_LTC &ds, int maLtc){
    for (int i = 0; i < ds.n; i++){
        LopTinChi* ltc = ds.nodes[i];
        if (ltc->MALOPTC == maLtc){
            if (ltc->dssvdk != NULL){
                return -1; // Lớp đã có sinh viên đăng kí
            }
            delete ltc;
            for (int j = i; j < ds.n - 1; j++){
                ds.nodes[j] = ds.nodes[j + 1];
            }
            ds.n--;
            return 1; // Đã xóa
        }
    }
    return 0; // Không tìm thấy;
}

int HieuChinhLTC(List_LTC &ds, int maLtc, const LopTinChi& ltcMoi){
    for (int i = 0; i < ds.n; i++){
        LopTinChi* ltc = ds.nodes[i];
        if (ltc->MALOPTC == maLtc){
            strcpy(ltc->MAMH, ltcMoi.MAMH);
            strcpy(ltc->NienKhoa, ltcMoi.NienKhoa);
            ltc->Hocky = ltcMoi.Hocky;
            ltc->Nhom = ltcMoi.Nhom;
            ltc->sosvmin = ltcMoi.sosvmin;
            ltc->sosvmax = ltcMoi.sosvmax;
            ltc->huylop = ltcMoi.huylop;
            return 1; //Đã sửa
        }
    }
    return 0; // Không tìm thấy
}

SinhVien* TimSinhVienTheoMa(const DS_LOPSV &ds, const char* maSv, char* outMaLop){
    for (int i = 0; i < ds.n; i++){
        PTRSV p = ds.nodes[i].FirstSV;
        while (p != NULL){
            if (strcmp(p->sv.MASV, maSv) == 0){
                if (outMaLop != NULL){
                    strcpy(outMaLop, ds.nodes[i].MALOP);
                    return &p->sv;
                }
            }
            p = p->next;
        }
    }
    return NULL;
}

LopTinChi* TimLTCTheo4DK(List_LTC &ds, const char* nienkhoa, int hocky, const char* maMh, int nhom){
    for (int i = 0; i < ds.n; i++){
        LopTinChi* ltc = ds.nodes[i];
        if (strcmp(ltc->NienKhoa, nienkhoa) == 0 &&
            ltc->Hocky == hocky &&
            strcmp(ltc->MAMH, maMh) == 0 &&
            ltc->Nhom == nhom){
            return ltc;
        }
    }
    return NULL;
}

int ThemSVVaoLTC(LopTinChi* ltc, const char* maSv){
    if (!ltc) return 0; //Không có lớp tín chỉ

    //Kiểm tra sinh viên đã đăng kí chưa
    PTRDK p = ltc->dssvdk;
    int count = 0;
    while(p){
        if (strcmp(p->dk.MASV, maSv) == 0) return 1; // Sinh viên đã đăng kí
        count++;
        p = p->next;
    }

    if (count >= ltc->sosvmax) return 2; // Đã đầy sinh viên

    PTRDK newNode = new nodeDK;
    strcpy(newNode->dk.MASV, maSv);
    newNode->dk.DIEM = 0;
    newNode->next = NULL;

    if (!ltc->dssvdk) {
        ltc->dssvdk = newNode;
    }else {
        p = ltc->dssvdk;
        while(p->next){
            p = p->next;
        }
        p->next = newNode;
    }
    return 3; // Thêm thành công
}

void HuyLTC(List_LTC& ds, int maLtc){
    LopTinChi* ltc = NULL;
    for (int i = 0; i < ds.n; i++){
        if (ds.nodes[i]->MALOPTC == maLtc){
            ltc = ds.nodes[i];
            break;
        }
    }

    if(ltc != NULL) {
        ltc->huylop = true;
    }
}
