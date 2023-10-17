/*
Thông tin của một quyển sách trong thư viện gồm các thông tin: 
- Tên sách (chuỗi) 
- Tác giả (chuỗi, tối đa 5 tác giả) 
- Nhà xuất bản (chuỗi)
- Năm xuất bản (số nguyên)
1.  Hãy tạo danh sách liên kết (đơn hoặc kép) chứa thông tin các quyển sách có trong thư viện (được nhập từ bàn phím). 
    Ghi danh sách liên kết vào File
2.  Cho biết số lượng các quyển sách của một tác giả bất kỳ (nhập từ bàn phím). 
3.  Trong năm YYYY (nhập từ bàn phím), nhà xuất bản ABC (nhập từ bàn phím) đã phát hành những quyển sách nào. 
4.  Xóa tất cả các quyển sách của tác giả X (X: tham số của hàm). Ghi kết quả sách liên kết vào File (khác File trong câu 1)
5.  Thống kê số lượng sách của mỗi tác giả và ghi kết quả thống kê lên tệp. 
6.  Đọc dữ liệu thống kê trong câu 5. Xuất lên màn hình.
7.  Đọc dữ liệu từ tệp trong câu a và đưa vào danh sách liên kết đơn.
8.  Đọc dữ liệu thống kê trong câu 5 và đưa vào một danh sách mới có lưu trữ thông tin gồm: tên tác giả và số lượng sách
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 100;

struct Book {
    char name[30];
    char Author[5][50];
    char nhaXuatBan[30];
    int numberOfAuthor;
    int publishingYear;
};
struct Node {
    Book data;
    Node *pNext;
};
struct ThuVien {
    Node *pHead;
    Node *pTail;
    int size;
};
struct Author {
    char Author[30];
    int soLuongSach;
};
struct NodeAuthor {
    Author data;
    NodeAuthor *pNext;
};
struct ListAuthor {
    NodeAuthor *Head;
    NodeAuthor *Tail;
};

// Init
void InitAuthor(Author &X) { X.soLuongSach = 0; }
void InitListAuthor(ListAuthor &TG) { TG.Head = TG.Tail = NULL; }
void InitList(ThuVien &L) { L.pHead = L.pTail = NULL, L.size = 0; }
void Input(Book &A) {
    fflush(stdin);
    printf("Nhap ten sach : ");
    gets(A.name);
    do {
        printf("Nhap so luong tac gia : ");
        scanf("%d", &A.numberOfAuthor);
        if (A.numberOfAuthor > 5) printf("So luong tac gia khong hop le !!\n");
    } while (A.numberOfAuthor > 5);
    
    fflush(stdin);
    for (int i = 0; i < A.numberOfAuthor; ++i) {
        printf("Nhap tac gia thu %d : ", i + 1);
        gets(A.Author[i]);
        fflush(stdin);
    }
    
    printf("Nhap ten nha xuat ban : ");
    gets(A.nhaXuatBan);
    printf("Nhap nam xuat ban sach : ");
    scanf("%d", &A.publishingYear);
    fflush(stdin);
}
Node *createNode(Book A) {
    Node *p = new Node;
    p->data = A;
    p->pNext = NULL;
    return p;
}

// add
void add_Author(ListAuthor &TG, char *Author, int soLuongSach) {
    NodeAuthor *p = new NodeAuthor;
    if (p == NULL) return;

    strcpy(p->data.Author, Author);
    p->data.soLuongSach = soLuongSach;
    p->pNext = NULL;
    
    if (TG.Head == NULL) TG.Head = TG.Tail = p;
    else {
        TG.Tail->pNext = p;
        TG.Tail = p;
    }
}
void add_Book(ThuVien &L, Book A) {
    Node *p = createNode(A);
    if (p == NULL) return;
    
    if (L.pHead == NULL) L.pHead = L.pTail = p;
    else {
        L.pTail->pNext = p;
        L.pTail = p;
    }
}
void create_ThuVien(ThuVien &L) {
    printf("Nhap so luong sach : ");
    scanf("%d", &L.size);
    
    Book temp;
    for (int i = 0; i < L.size; ++i) {
        Input(temp);
        add_Book(L, temp);
    }
}

// display
void Output(Book A) {
    printf("Ten sach : %s\n", A.name);
    printf("Danh sach tac gia \n");
    for (int i = 0; i < A.numberOfAuthor; ++i) printf("Tac gia thu %d : %s\n", i + 1, A.Author[i]);
    printf("Nha xuat ban : %s\n", A.nhaXuatBan);
    printf("Nam xuat ban : %d\n", A.publishingYear);
}
void display(ThuVien L) {
    Node *p = L.pHead;
    int i = 0;
    while (p != NULL) {
        printf("----Thong Tin Sach Thu %d------\n", ++i);
        Output(p->data);
        p = p->pNext;
    }
}
void display2(ListAuthor TG) {
    NodeAuthor *p = TG.Head;
    while (p != NULL) {
        printf("Ten tac gia : %s\n", p->data.Author);
        printf("So luong Sach : %d\n", p->data.soLuongSach);
        p = p->pNext;
    }
}

// methods
int findAuthor(ListAuthor &TG, char *name) {
    NodeAuthor *p = TG.Head;
    while (p != NULL) {
        if (strcmp(p->data.Author, name) == 0) {
            p->data.soLuongSach++;
            return 1;
        }
        p = p->pNext;
    }
    return 0;
}
int count_SoSach_of_Tacgia(ThuVien TV, char *name) {
    int cnt = 0;
    Node *p = TV.pHead;
    Book tmp;
    while (p != NULL) {
        tmp = p->data;
        for (int i = 0; i < tmp.numberOfAuthor; ++i) if (!strcmp(name, tmp.Author[i])) ++cnt;
        p = p->pNext;
    }
    return cnt;
}
void soSach_xuatBan_trongNam(ThuVien TV, char *tenNhaXB, int namXB) {
    int check = 0, cnt = 0;
    Book a[maxn];
    Node *p = TV.pHead;
    while (p != NULL) {
        Book temp = p->data;
        if (temp.publishingYear == namXB && strcmp(temp.nhaXuatBan,tenNhaXB) == 0) a[cnt++] = temp, check = 1;
        p = p->pNext;
    }
    if (!check) printf("Nha xuat ban %s khong xuat ban sach nao trong nam %d\n", tenNhaXB, namXB);
    else {
        printf("---Danh sach nhung cuon sach nha xuat ban %s xuat ban trong nam %d---\n", tenNhaXB, namXB);
        for (int i = 0; i < cnt; ++i) printf("%d. %s\n", i + 1, a[i].name);
    }
}

// file
void read_Library_from_File(ThuVien &L, const char *fileName) {
    InitList(L);
    FILE *file = fopen(fileName, "rb");
    if (file == NULL) {
        printf("Khong mo duoc file!");
        return;
    }

    Book temp;
    while (fread(&temp, sizeof(Book), 1, file)) add_Book(L, temp);
    
    display(L);
    fclose(file);
    printf("\nDoc danh sach sach tu file thanh cong!\n");
}
void write_Library_to_File(ThuVien L, const char *fileName) {
    FILE *file = fopen(fileName, "wb");
    if (file == NULL) {
        printf("Khong mo duoc file!");
        return;
    }

    Node *p = L.pHead;
    while (p != NULL) {
        fwrite(&p->data, sizeof(Book), 1, file);
        p = p->pNext;
    }

    fclose(file);
    printf("\nGhi danh sach sach vao file thanh cong!\n");
}
void deleteBooks(ThuVien &TV, char *Author, const char *filename) {
    Node *p = TV.pHead;
    Node *prev = NULL;
    while (p != NULL) {
        int ok = 0;
        for (int i = 0; i < p->data.numberOfAuthor; ++i) 
            if (strcmp(Author, p->data.Author[i]) == 0) {
                if (prev == NULL) TV.pHead = p->pNext;
                else prev->pNext = p->pNext;
                
                if (p == TV.pTail) TV.pTail = prev;
                
                Node *temp = p;
                p = p->pNext;
                free(temp);
                ok = 1;
                
                break;
            }
        
        if (!ok) {
            prev = p;
            p = p->pNext;
        }
    }
    write_Library_to_File(TV, filename);
}
void ThongKeSach(ThuVien TV, ListAuthor &TG, const char *filename) {
    Node *p = TV.pHead;
    InitListAuthor(TG);
    while (p != NULL) {
        for (int i = 0; i < p->data.numberOfAuthor; ++i)
            if (!findAuthor(TG, p->data.Author[i]))
                add_Author(TG, p->data.Author[i], 1);
        
        p = p->pNext;
    }

    FILE *f = fopen(filename, "wb");
    NodeAuthor *q = TG.Head;
    while (q != NULL) {
        fwrite(&q->data, sizeof(Author), 1, f);
        q = q->pNext;
    }

    fclose(f);
}
void readThongKe1(ListAuthor &tmp, const char *filename) {
    FILE *f = fopen(filename, "rb");
    InitListAuthor(tmp);
    Author temp;
    while (fread(&temp, sizeof(Author), 1, f)) add_Author(tmp, temp.Author, temp.soLuongSach);
    
    fclose(f);
}
void readThongKe2(ListAuthor &tmp, const char *filename) {
    FILE *f = fopen(filename, "rb");
    InitListAuthor(tmp);
    Author temp;
    while (fread(&temp, sizeof(Author), 1, f)) add_Author(tmp, temp.Author, temp.soLuongSach);
    
    display2(tmp);
    fclose(f);
}

void Menu() {
    printf("----- MOI LUA CHON CHUC NANG -----\n");
    printf("1. Tao ThuVien Sach va ghi vao File\n");
    printf("2. Cho biet so luong sach cua mot tac gia bat ki\n");
    printf("3. Cho biet thong tin nhung quyen sach ma tac gia X xuat ban trong nam YYYY\n");
    printf("4. Xoa tat ca cac quyen sach cua tac gia X va ghi vao tep moi\n");
    printf("5. Thong ke so luong sach cua moi tac gia va ghi vao tep\n");
    printf("6. Doc du lieu thong ke tu cau 5 va xuat len man hinh\n");
    printf("7. Doc du lieu tu tep trong cau 1 va dua vao danh sach lien ket don\n");
    printf("8. Doc du lieu thong ke tu cau 5 va dua vao mot danh sach moi\n");
    printf("9. Doc du lieu tu tep trong cau 4\n");
    printf("10. Thoat chuong trinh\n");
}

int main() {
    ThuVien library1, library2, library3;
    ListAuthor TG, temp1, temp2;
    InitListAuthor(TG), InitListAuthor(temp1), InitListAuthor(temp2),
    InitList(library1), InitList(library2), InitList(library3);
    
    char filename1[] = "library1.bin"; // file luu yeu cau 1
    char filename2[] = "library2.bin"; // file luu yeu cau 4
    char filename3[] = "Author.bin"; // file luu yeu cau 5
    char authorName[50], nhaXuatBan[50];

    int running = 1, choose, count1, year;
    Menu();
    while (running) {
        printf("Moi nhap lua chon : ");
        scanf("%d", &choose);
        switch (choose) {
            case 1:
                create_ThuVien(library1);
                write_Library_to_File(library1, filename1);
                break;
            case 2:
                printf("Nhap ten tac gia can kiem tra : ");
                fflush(stdin);
                gets(authorName);
                count1 = count_SoSach_of_Tacgia(library1, authorName);
                printf("So luong sach cua tac gia %s : %d\n", authorName, count1);
                break;
            case 3:
                printf("Nhap ten nha xuat ban can kiem tra : ");
                fflush(stdin);
                gets(nhaXuatBan);
                printf("Nhap nam xuat ban : ");
                scanf("%d", &year);
                soSach_xuatBan_trongNam(library1, nhaXuatBan, year);
                break;
            case 4:
                printf("Nhap ten tac gia cua sach can xoa : ");
                fflush(stdin);
                gets(authorName);
                deleteBooks(library1, authorName, filename2);
                break;
            case 5:
                ThongKeSach(library1, TG, filename3);
                break;
            case 6:
                readThongKe2(temp1, filename3);
                break;
            case 7:
                read_Library_from_File(library2, filename1);
                break;
            case 8:
                readThongKe1(temp2, filename3);
                break;
            case 9:
                read_Library_from_File(library3, filename2);
                break;
            default:
                running = 0;
                break;
        }
    }
    return 0;
}