#include <stdio.h>
#include <string.h>
#include <stdlib.h>
const int MAXN = 110;
char op[3][3] = {"r", "w", "a"};
struct WORD {
    char Name[256];
    char Meaning[512];
};
void swap(WORD &u, WORD &v) {
    WORD t = u;
    u = v;
    v = t;
}
void sortName(WORD *word, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(strcmp(word[i].Name, word[j].Name) > 0) {
                swap(word[i], word[j]);
            }
        }
    }
}
void Nhap(WORD &u) {
    printf("\nNhap ten word: ");
    scanf("%s", u.Name);
    fflush(stdin);
    printf("\nNhap nghia word: ");
    gets(u.Meaning);
}
void Xuat(WORD u) {
    printf("%s: %s\n", u.Name, u.Meaning);
}
int searchName(WORD *word, char *name, int n) {
    int lo = 0, hi = n - 1;
    while(lo <= hi) {
        int mid = (lo + hi) / 2;
        int flag = strcmp(word[mid].Name, name);
        if(flag == 0) return mid;

        if(flag > 0) hi = mid - 1;
        else lo = mid + 1;
    }
    return -1;
}
FILE *OPENFILE(char *filename, char *option) {
    FILE *file = fopen(filename, option);
    if(file == NULL) {
        perror("Khong the mo file");
        exit(1);
    }
    return file;
}
void writeOne(FILE *f, WORD word) {
    if(f == NULL) return;
    fprintf(f, "%s:%s\n", word.Name, word.Meaning);
}
void writeArray(WORD *word, char *filename, int n) {
    FILE *f = OPENFILE(filename, op[2]);
    if(f != NULL) for(int i = 0; i < n; i++) writeOne(f, word[i]);
    fclose(f);
}
int readFile(WORD *word, char *filename, int n) {
    FILE *f = OPENFILE(filename, op[0]);
    if(f == NULL) return 0;

    char Str[1024], delimiters[] = ":\n";
    int sz = 0;
    for (int i = 0; i < n; i++) {
        if (fgets(Str, sizeof(Str), f) != NULL) {
            char *name = strtok(Str, delimiters);
            char *meaning = strtok(NULL, delimiters);

            if (name != NULL && meaning != NULL) {
                strcpy(word[sz].Name, name);
                strcpy(word[sz++].Meaning, meaning);
            }
        } else {
            strcpy(word[i].Name, "");
            strcpy(word[i].Meaning, "");
        }
    }
    fclose(f);
    return sz;
}
void readOne(char *filename, char *Name) {
    FILE *f = OPENFILE(filename, op[0]);
    if(f == NULL) return;

    char Str[1024], delimiters[] = ":\n";
    WORD t;
    while (fgets(Str, sizeof(Str), f) != NULL) {
        char *name = strtok(Str, delimiters);
        char *meaning = strtok(NULL, delimiters);
        strcpy(t.Name, name);
        strcpy(t.Meaning, meaning);

        if(strcmp(t.Name, Name) == 0) Xuat(t);
    }
    fclose(f);
}
void updateMeaning(WORD word, char *filename, char *newMeaning) {
    char filetemp[] = "temp.txt";
    FILE *f = OPENFILE(filename, op[0]);
    FILE *t = OPENFILE(filetemp, op[2]);
    if(f == NULL || t == NULL) {
        fclose(f), fclose(t);
        return;
    }

    char Str[1024], delimiters[] = ":\n";

    while (fgets(Str, sizeof(Str), f) != NULL) {
        char *name = strtok(Str, delimiters);
        char *meaning = strtok(NULL, delimiters);

        WORD newword;
        strcpy(newword.Name, name);
        strcpy(newword.Meaning, meaning);
        
        if( strcmp(meaning, word.Meaning) == 0 && 
            strcmp(name, word.Name) == 0) strcpy(newword.Meaning, newMeaning);
        
        writeOne(t, newword);
    }

    fclose(f), fclose(t);

    remove(filename);

    rename(filetemp, filename);
}
void removeWord(WORD word, char *filename) {
    char filetemp[] = "temp.txt";
    FILE *f = OPENFILE(filename, op[0]);
    FILE *t = OPENFILE(filetemp, op[2]);
    if(f == NULL || t == NULL) {
        fclose(f), fclose(t);
        return;
    }

    char Str[1024], delimiters[] = ":\n";

    while (fgets(Str, sizeof(Str), f) != NULL) {
        char *name = strtok(Str, delimiters);
        char *meaning = strtok(NULL, delimiters);

        WORD newword;
        strcpy(newword.Name, name);
        strcpy(newword.Meaning, meaning);
        
        if( strcmp(newword.Name, word.Name) != 0 ||
            strcmp(newword.Meaning, word.Meaning) != 0) writeOne(t, newword);
    }

    fclose(f), fclose(t);

    remove(filename);

    rename(filetemp, filename);
}
void menu() {
    printf("------------------MENU------------------\n");
    printf("1.Nhap 1 tu\n");
    printf("2.Xuat 1 tu\n");
    printf("3.Sap xep theo Name tang dan\n");
    printf("4.Tim kiem 1 tu\n");
    printf("5.Ghi mot tu vao tep\n");
    printf("6.Ghi mot mang len tep\n");
    printf("7.Doc tep\n");
    printf("8.Doc mot tu trong tep\n");
    printf("9.Cap nhat Meaning cua mot tu trong tep\n");
    printf("10.Xoa mot tu trong tep\n");
    printf("11.Exit\n");
}

int main() {
    int running = 1, position = 0, choose, id;
    char filename[1024], name[256];
    WORD word[MAXN], w;
    
    menu();
    while(running) {
        printf("\nNhap lua chon: ");
        scanf("%d", &choose);
        fflush(stdin);
        switch(choose) {
            case 1:
                Nhap(word[position++]);
                fflush(stdin);
                break;
            case 2:
                do {
                    printf("\nNhap phan tu can xuat: ");
                    scanf("%d", &id);
                } while(id < 0 || id >= position);
                
                Xuat(word[id]);
                break;
            case 3:
                sortName(word, position);
                break;
            case 4:
                printf("\nNhap ten word can tim: ");
                scanf("%s", name);
                
                id = searchName(word, name, position);
                if(id == -1) printf("\nKhong tim thay ten word!!");
                else printf("\nVi tri cua %s la %d", name, id);
                break;
            case 5:
                Nhap(w);
                printf("\nNhap ten file can them: ");
                gets(filename);
                
                FILE *f;
                writeOne(f = OPENFILE(filename, op[2]), w);
                fclose(f);
                break;
            case 6:
                printf("\nNhap ten file can them: ");
                gets(filename);
                
                writeArray(word, filename, position);
                break;
            case 7:
                printf("\nNhap ten file can doc: ");
                gets(filename);
                position = readFile(word, filename, MAXN);
                break;
            case 8:
                fflush(stdin);
                printf("\nNhap ten can tim: ");
                gets(name); 
                
                fflush(stdin);
                printf("\nNhap ten file can doc: ");
                gets(filename);
                
                readOne(filename, name);
                break;
            case 9:
                char newMeaning[512];
                Nhap(w);
                printf("\nNhap Meaning moi can doi: ");
                gets(newMeaning);
                fflush(stdin);

                printf("\nNhap ten file can doi: ");
                gets(filename);
                
                updateMeaning(w, filename, newMeaning);
                break;
            case 10:
                Nhap(w);
                printf("\nNhap ten file can xoa: ");
                gets(filename);
                
                removeWord(w, filename);
                break;
            default: 
                running = 0;
                break;
        }
    }
    return 0;
}
