#include "structures.h"
#include <cstdio>
#include <cstring>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
//Mon hoc

bool hasSpace(const QString &str) {
    QByteArray bytes = str.toUtf8();
    for (char c : bytes) {
        if ((int)c == 32) return true;
    }
    return false;
}
treeMH SearchTree(treeMH root,const char* mamh) {
    while (root != nullptr) {
        int cmp = strcmp(mamh, root->mh.MAMH);
        if (cmp == 0)
            return root;
        else if (cmp < 0)
            root = root->left;
        else
            root = root->right;
    }
    return nullptr;
}
int DemSoLuongMonHoc(treeMH root) {
    if (root == NULL) return 0;
    return 1 + DemSoLuongMonHoc(root->left) + DemSoLuongMonHoc(root->right);
}
void Insert_MonHoc(treeMH &root, MonHoc mh) {
    if (root == nullptr) {
        root = new nodeMH;
        root->mh = mh;
        root->left = root->right = nullptr;
    } else if (strcmp(mh.MAMH, root->mh.MAMH) < 0) {
        Insert_MonHoc(root->left, mh);
    } else if (strcmp(mh.MAMH, root->mh.MAMH) > 0) {
        Insert_MonHoc(root->right,mh);
    }
}
void SaveFileMonHoc(treeMH root, QTextStream &out) {
    if (root != NULL) {
        out << root->mh.MAMH << "|"
            << root->mh.TENMH << "|"
            << root->mh.STCLT << "|"
            << root->mh.STCTH << "\n";

        SaveFileMonHoc(root->left, out);
        SaveFileMonHoc(root->right, out);
    }
}

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
    fprintf(f, "%d\n", count);

    GhiMonHoc_LNR(t, f, count);

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

int DocDanhSachMonHoc(treeMH &root, const QString& tenfile) {
    QFile file(tenfile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Không mở được file:" << tenfile;
        return 0;
    }

    QTextStream in(&file);
    int soLuong;
    in >> soLuong;
    in.readLine();

    qDebug() << "Đang đọc" << soLuong << "môn học từ file:" << tenfile;

    for (int i = 0; i < soLuong; ++i) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList parts = line.split("|");
        if (parts.size() < 4) {
            qDebug() << "Dòng không hợp lệ:" << line;
            continue;
        }

        MonHoc mh;
        strncpy(mh.MAMH, parts[0].toStdString().c_str(), 10); mh.MAMH[10] = '\0';
        strncpy(mh.TENMH, parts[1].toStdString().c_str(), 50); mh.TENMH[50] = '\0';
        mh.STCLT = parts[2].toInt();
        mh.STCTH = parts[3].toInt();

        Insert_MonHoc(root, mh);
    }

    file.close();
    return 1;
}

bool SuaMonHoc(treeMH root, const MonHoc& monHocMoi) {
    treeMH node = SearchTree(root, monHocMoi.MAMH);
    if (node == nullptr) return false;

    strcpy(node->mh.TENMH, monHocMoi.TENMH);
    node->mh.STCLT = monHocMoi.STCLT;
    node->mh.STCTH = monHocMoi.STCTH;

    return true;
}
void remove_case_3 (treeMH &r, treeMH &rp )
{
    if (r->left != NULL)
        remove_case_3 (r->left, rp);
    else
    {
        rp->mh = r->mh;
        rp = r;
        r = rp->right;
    }
}
int RemoveTreeMH(treeMH &root,const char *mamh)
{
    if(root == NULL || SearchTree(root, mamh) == NULL) return 0;
    else
    {
        if(strcmp(root->mh.MAMH, mamh) < 0) RemoveTreeMH(root->right, mamh);
        else if(strcmp(root->mh.MAMH, mamh) > 0) RemoveTreeMH(root->left, mamh);
        else
        {
            treeMH rp;
            rp = root;
            if(rp->left == NULL) root = root->right;
            else if (rp->right==NULL) root=root->left;
            else remove_case_3(rp->right, rp);
            delete rp;
        }
    }
    return 1;
}
void LuuMonHocVaoMang(treeMH root, nodeMH* ds[], int &n)
{
    if (root == nullptr) return;
    LuuMonHocVaoMang(root->left, ds, n);
    ds[n++] = root;
    LuuMonHocVaoMang(root->right, ds, n);
}

void SapXepTangTheoTenMH(nodeMH* ds[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (strcmp(ds[i]->mh.TENMH, ds[j]->mh.TENMH) > 0) {
                nodeMH* temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
}
bool MonHocDaDuocDangKy(List_LTC &dsLTC, const char* mamh) {
    for (int i = 0; i < dsLTC.n; ++i) {
        if (strcmp(dsLTC.nodes[i]->MAMH, mamh) == 0) {
            return true;
        }
    }
    return false;
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
    FILE* f = fopen(filename, "w");
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
LopTinChi* TimLopTinChi(const List_LTC& dsLTC, const char* mamh, const char* nienkhoa, int hocky, int nhom) {
    for (int i = 0; i < dsLTC.n; ++i) {
        LopTinChi* ltc = dsLTC.nodes[i];
        if (strcmp(ltc->MAMH, mamh) == 0 &&
            strcmp(ltc->NienKhoa, nienkhoa) == 0 &&
            ltc->Hocky == hocky &&
            ltc->Nhom == nhom &&
            !ltc->huylop) {
            return ltc;
        }
    }
    return nullptr;
}
SinhVien* TimSinhVien(const DS_LOPSV& dsLop, const char* masv) {
    for (int i = 0; i < dsLop.n; ++i) {
        PTRSV sv = dsLop.nodes[i].FirstSV;
        while (sv != nullptr) {
            if (strcmp(sv->sv.MASV, masv) == 0) {
                return &sv->sv;
            }
            sv = sv->next;
        }
    }
    return nullptr;
}

//Lop sinh vien
LopSV* TimLop(DS_LOPSV& dsLop, const char* MALOP) {
    for (int i = 0; i < dsLop.n; ++i) {
        if (strcmp(dsLop.nodes[i].MALOP, MALOP) == 0) {
            return &dsLop.nodes[i];
        }
    }
    return nullptr;
}


// Tìm sinh viên theo mã
SinhVien* TimSinhVienTrongLop(PTRSV First, const char* maSV) {
    PTRSV p = First;
    while (p != nullptr) {
        if (strcmp(p->sv.MASV, maSV) == 0) return &p->sv;
        p = p->next;
    }
    return nullptr;
}


nodeMH* TimMonHoc(treeMH root, const char* maMH) {
    if (root == nullptr) return nullptr;
    int cmp = strcmp(maMH, root->mh.MAMH);
    if (cmp == 0) return root;
    if (cmp < 0) return TimMonHoc(root->left, maMH);
    return TimMonHoc(root->right, maMH);
}

float TinhDiemTrungBinhSV(const SinhVien &sv, const List_LTC &dsLTC, treeMH dsMH) {
    float tongDiem = 0;
    int tongTC = 0;

    for (int i = 0; i < dsLTC.n; i++) {
        LopTinChi* ltc = dsLTC.nodes[i];
        if (ltc == nullptr || ltc->huylop) continue;

        // duyệt danh sách đăng ký của lớp tín chỉ
        for (PTRDK dk = ltc->dssvdk; dk != nullptr; dk = dk->next) {
            if (strcmp(dk->dk.MASV, sv.MASV) == 0 && dk->dk.DIEM >= 0) {
                nodeMH* node = TimMonHoc(dsMH, ltc->MAMH);
                if (node != nullptr) {
                    int soTC = node->mh.STCLT + node->mh.STCTH;
                    tongDiem += dk->dk.DIEM * soTC;
                    tongTC += soTC;
                }
            }
        }
    }

    return (tongTC > 0) ? (tongDiem / tongTC) : 0;
}

SinhVien* TimSinhVienTrongLop(const LopSV& lop, const char* masv) {
    for (PTRSV p = lop.FirstSV; p != nullptr; p = p->next) {
        if (strcmp(p->sv.MASV, masv) == 0) {
            return &p->sv;
        }
    }
    return nullptr;
}

// So sánh theo Họ + Tên
int soSanhSV(const SinhVien& a, const SinhVien& b) {
    int cmpTen = strcmp(a.TEN, b.TEN);
    if (cmpTen == 0) {
        return strcmp(a.HO, b.HO);
    }
    return cmpTen;
}

// Selection Sort
void selectionSort(SinhVien arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (soSanhSV(arr[j], arr[minIdx]) < 0) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            SinhVien tmp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = tmp;
        }
    }
}

int TongTinChiCuaSV(const SinhVien &sv, List_LTC &dsLTC, treeMH dsMH) {
    int tongTC = 0;

    // Duyệt tất cả lớp tín chỉ
    for (int i = 0; i < dsLTC.n; i++) {
        LopTinChi* ltc = dsLTC.nodes[i];
        if (ltc == nullptr || ltc->huylop) continue;

        // Duyệt danh sách SV đăng ký trong lớp tín chỉ này
        for (PTRDK dk = ltc->dssvdk; dk != nullptr; dk = dk->next) {
            if (strcmp(dk->dk.MASV, sv.MASV) == 0) {
                // Tìm môn học
                nodeMH* node = TimMonHoc(dsMH, ltc->MAMH);
                if (node != nullptr) {
                    tongTC += node->mh.STCLT + node->mh.STCTH;
                }
            }
        }
    }

    return tongTC;
}

