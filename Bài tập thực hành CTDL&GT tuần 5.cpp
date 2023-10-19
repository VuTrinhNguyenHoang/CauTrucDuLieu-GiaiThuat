#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 100;

// define struct
struct Book {
    char name[50];
    char authors[5][50];
    char producer[50];
    int numberOfAuthor;
    int publishingYear;
};
struct Author {
    char name[50];
    int numberOfBook;
};
struct NodeBook {
    Book book;
    NodeBook* pNext;
};
struct NodeAuthor {
    Author author;
    NodeAuthor* pNext;
};
struct Library {
    NodeBook* pHead;
    NodeBook* pTail;
};
struct AuthorList {
    NodeAuthor* pHead;
    NodeAuthor* pTail;
};

// init
void initAuthorList(AuthorList &L) { L.pHead = L.pTail = NULL; }
void initLibrary(Library &L) { L.pHead = L.pTail = NULL; }
NodeBook* createNodeBook(Book &book) {
    NodeBook* nodebook = new NodeBook;
    if(nodebook == NULL) return NULL;

    nodebook->book = book;
    nodebook->pNext = NULL;
    return nodebook;
}
void inputBook(Book &book) {
    printf("Nhap ten sach: ");
    gets(book.name);
    do {
        printf("Nhap so luong tac gia: ");
        scanf("%d", &book.numberOfAuthor);
        if(book.numberOfAuthor <= 0 || book.numberOfAuthor > 5) 
            printf("So luong tac gia must be in [0, 5]!!\n");
    } while (book.numberOfAuthor <= 0 || book.numberOfAuthor > 5);

    for(int i = 0; i < book.numberOfAuthor; i++) {
        fflush(stdin);
        printf("Nhap ten tac gia thu %d: ", i + 1);
        gets(book.authors[i]);
    }

    printf("Nhap ten nha san xuat: ");
    gets(book.producer);

    printf("Nhap nam san xuat: "); 
    scanf("%d", &book.publishingYear);
}

// display
void display_Book(Book book) {
    printf("Ten sach: %s\n", book.name);
    printf("Danh sach tac gia:\n");
    for(int i = 0; i < book.numberOfAuthor; i++) 
        printf("\t%d. %s\n", i + 1, book.authors[i]);
    printf("Nha san xuat: %s\n", book.producer);
    printf("Nam san xuat: %d\n", book.publishingYear);
}
void display_Library(Library L) {
    NodeBook* p = L.pHead;
    int i = 0;
    while(p != NULL) {
        printf("----Thong tin danh sach thu %d----\n", ++i);
        display_Book(p->book);
        p = p->pNext;
    }
}
void display_AuthorList(AuthorList L) {
    NodeAuthor* nodeauthor = L.pHead;
    while(nodeauthor != NULL) {
        printf("Ten tac gia: %s\n", nodeauthor->author.name);
        printf("So luong sach: %d\n", nodeauthor->author.numberOfBook);
        nodeauthor = nodeauthor->pNext;
    }
}

// add
void addBook(Library &L, Book book) {
    NodeBook* nodebook = createNodeBook(book);
    if(nodebook == NULL) return;

    if(L.pHead == NULL) L.pHead = L.pTail = nodebook;
    else {
        L.pTail->pNext = nodebook;
        L.pTail = nodebook;
    }
}
void addAuthor(AuthorList &L, char* author, int numberOfBook) {
    NodeAuthor* nodeauthor = new NodeAuthor;
    if(nodeauthor == NULL) return;

    strcpy(nodeauthor->author.name, author);
    nodeauthor->author.numberOfBook = numberOfBook;
    nodeauthor->pNext = NULL;
    
    if(L.pHead == NULL) L.pHead = L.pTail = nodeauthor;
    else {
        L.pTail->pNext = nodeauthor;
        L.pTail = nodeauthor;
    }
}
void createLibrary(Library &L) {
    initLibrary(L);
    printf("Nhap so luong sach: ");
    int n; scanf("%d", &n);

    Book book;
    for(int i = 0; i < n; i++) {
        fflush(stdin);
        inputBook(book);
        addBook(L, book);
    }
}

// methods
int numberOfBookByAuthor(Library L, char* author) {
    int cnt = 0;
    NodeBook* p = L.pHead;
    while(p != NULL) {
        for(int i = 0; i < p->book.numberOfAuthor; i++) 
            if(strcmp(author, p->book.authors[i]) == 0)
                ++cnt;
        p = p->pNext;
    }
    return cnt;
}
void Book_Producer_inYear(Library L, char* producer, int year) {
    Book a[maxn];
    int cnt = 0;
    NodeBook* p = L.pHead;
    while(p != NULL) {
        if( strcmp(p->book.producer, producer) == 0 &&
            year == p->book.publishingYear) a[cnt++] = p->book;
        p = p->pNext;
    }

    if(cnt == 0) printf("Nha xuat ban %s khong xuat ban sach trong nam %d\n", producer, year);
    else {
        printf("---Danh sach nhung cuon sach nha xuat ban %s xuat ban trong nam %d---\n", producer, year);
        for(int i = 0; i < cnt; i++) printf("%d. %s\n", i + 1, a[i].name);
    }
}
int findAuthor(AuthorList L, char* author) {
    NodeAuthor* p = L.pHead;
    while(p != NULL) {
        if(strcmp(p->author.name, author) == 0) {
            p->author.numberOfBook++;
            return 1;
        }
        p = p->pNext;
    }
    return 0;
}
void statisticBook_Author(Library L, AuthorList &AL) {
    initAuthorList(AL);
    NodeBook* nodebook = L.pHead;
    while(nodebook != NULL) {
        for(int i = 0; i < nodebook->book.numberOfAuthor; i++)
            if(findAuthor(AL, nodebook->book.authors[i]) == 0) 
                addAuthor(AL, nodebook->book.authors[i], 1);
        nodebook = nodebook->pNext;
    }
}
void deleteBooks(Library &L, char* author) {
    NodeBook* p = L.pHead;
    NodeBook* prev = NULL;
    while(p != NULL) {
        int ok = 0;
        for(int i = 0; i < p->book.numberOfAuthor; i++)
            if(strcmp(author, p->book.authors[i]) == 0) {
                if(prev == NULL) L.pHead = p->pNext;
                else prev->pNext = p->pNext;

                if(p == L.pTail) L.pTail = prev;
                
                NodeBook* t = p;
                p = p->pNext;
                free(t);
                ok = 1;
                break;
            }
        
        if(ok == 0) {
            prev = p;
            p = p->pNext;
        }
    }
}

// file
void writeLibraryToFile(Library L, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if(file == NULL) {
        printf("Khong mo duoc file!!!\n");
        return;
    }

    NodeBook* nodebook = L.pHead;
    while(nodebook != NULL) {
        fwrite(&nodebook->book, sizeof(Book), 1, file);
        nodebook = nodebook->pNext;
    }
    printf("Ghi danh sach sach vao file thanh cong!\n");
    
    fclose(file);
}
void writeAuthorListToFile(AuthorList L, const char* filename) {
    FILE* file = fopen(filename, "wb");
    if(file == NULL) {
        printf("Khong mo duoc file!!!\n");
        return;
    }

    NodeAuthor* nodeauthor = L.pHead;
    while(nodeauthor != NULL) {
        fwrite(&nodeauthor->author, sizeof(Author), 1, file);
        nodeauthor = nodeauthor->pNext;
    }
    printf("Ghi danh sach tac gia vao file thanh cong!\n");

    fclose(file);
}
void readLibraryFromFile(Library &L, const char* filename) {
    initLibrary(L);
    FILE* file = fopen(filename, "rb");
    if(file == NULL) {
        printf("Khong mo duoc file!!!\n");
        return;
    }

    Book book;
    while(fread(&book, sizeof(Book), 1, file)) addBook(L, book);
    display_Library(L);
    printf("Doc danh sach sach tu file thanh cong!\n");

    fclose(file);
}
void readAuthorListFromFile(AuthorList &L, const char* filename) {
    initAuthorList(L);
    FILE* file = fopen(filename, "rb");
    if(file == NULL) {
        printf("Khong mo duoc file!!!\n");
        return;
    }

    Author author;
    while(fread(&author, sizeof(Author), 1, file)) addAuthor(L, author.name, author.numberOfBook);
    printf("Doc danh sach tac gia thanh cong!!!\n");

    fclose(file);
}

void menu() {
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
    printf("10. Lam sach giao dien\n");
    printf("11. Thoat chuong trinh\n");
}

int main() {
    Library Lib1, Lib2, Lib3;
    AuthorList auList1, auList2, auList3;

    char filename1[] = "library1.txt";
    char filename2[] = "library2.txt";
    char filename3[] = "author.txt";
    char author[50];

    int running = 1, choice, count, year;
    menu();
    while(running) {
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                createLibrary(Lib1);
                writeLibraryToFile(Lib1, filename1);
                break;
            case 2:
                fflush(stdin);
                printf("Nhap ten tac gia: ");
                gets(author);
                count = numberOfBookByAuthor(Lib1, author);
                printf("So luong sach cua tac gia %s: %d\n", author, count);
                break;
            case 3:
                fflush(stdin);
                printf("Nhap ten nha san xuat: ");
                gets(author);

                fflush(stdin);
                printf("Nhap nam xuat ban: ");
                scanf("%d", &year);
                Book_Producer_inYear(Lib1, author, year);
                break;
            case 4:
                fflush(stdin);
                printf("Nhap ten tac gia muon xoa: ");
                gets(author);
                deleteBooks(Lib1, author);
                writeLibraryToFile(Lib1, filename2);
                break;
            case 5:
                statisticBook_Author(Lib1, auList1);
                writeAuthorListToFile(auList1, filename3);
                break;
            case 6:
                readAuthorListFromFile(auList2, filename3);
                display_AuthorList(auList2);
                break;
            case 7:
                readLibraryFromFile(Lib2, filename1);
                break;
            case 8:
                readAuthorListFromFile(auList3, filename3);
                break;
            case 9:
                readLibraryFromFile(Lib3, filename2);
                break;
            case 10:
                system("cls");
                menu();
                break;
            default:
                running = 0;
                break;
        }
    }
    return 0;
}