#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
const int MAX = 50;

struct Student {
	int mssv;
	char fullName[MAX];
	char gender[MAX];
	char Address[MAX];
	double diemTB;
};
void swap(Student &a, Student &b) {
	Student t = a;
	a = b;
	b = t;
}
void Nhap(Student &u) {
	printf("\nNhap mssv: ");
	scanf("%d", &u.mssv);
	fflush(stdin);
	printf("\nNhap Ho va Ten: ");
	gets(u.fullName);
	fflush(stdin);
	printf("\nNhap gioi tinh: ");
	gets(u.gender);
	fflush(stdin);
	printf("\nNhap dia chi: ");
	gets(u.Address);
	printf("\nNhap diem trung binh: ");
	scanf("%lf", &u.diemTB);
}
void Xuat(Student u) {
	printf("\n%-10d %-30s %-10s %-30s %10.2f", u.mssv, u.fullName, u.gender, u.Address, u.diemTB);
}
void NhapMang(Student *student, int &n) {
	do {
		printf("\nSo luong can nhap: ");
		scanf("%d", &n);
	} while(n <= 0 || n >= MAX);
	
	for(int i = 0; i < n; i++) Nhap(student[i]);
}
void XuatMang(Student *student, int n) {
	printf("\n%-10s %-30s %-10s %-30s %10s", "MSSV", "Ho va Ten", "Gioi tinh", "Dia chi", "Diem TB");
	for(int i = 0; i < n; i++) Xuat(student[i]);
}
void SapxepdiemTB(Student *student, int n) {
	for(int i = 0; i < n - 1; i++) 
		for(int j = i + 1; j < n; j++) 
			if(student[i].diemTB > student[j].diemTB)
				swap(student[i], student[j]);
}
void SapxepName(Student *student, int n) {
	for(int i = 0; i < n - 1; i++) 
		for(int j = i + 1; j < n; j++) 
			if(strcmp(student[i].fullName, student[j].fullName) > 0)
				swap(student[i], student[j]);
}
int searchMSSV(Student *student, int mssv, int n) {
	int i = 0;
	while(i < n && student[i].mssv != mssv) i++;
	return (i < n ? i : -1);
}
void SearchThongtin(Student *student, int mssv, int n) {
	int id = searchMSSV(student, mssv, n);
	if(id == -1) printf("\nKhong tim thay sinh vien co MSSV %d!");
	else Xuat(student[id]);
}
FILE *openfile(char *filename, char *option) {
	FILE *f = fopen(filename, option);
	if(f == NULL) {
		printf("\nKhong mo dc file!!");
		exit(1);
	}
	return f;
}
double maximumDiemTB(FILE *f) {
	double maximum = 0;
	
	Student st;
	while(fread(&st, sizeof(Student), 1, f) > 0) {
		if(st.diemTB > maximum) maximum = st.diemTB;
	}

	rewind(f);
	return maximum;
}
void XuatMaximumDiemTB(char *filename) {
	FILE *f = openfile(filename, "rb");
	if(f == NULL) return;
	
	double max_value = maximumDiemTB(f);
	Student st;
	while(fread(&st, sizeof(Student), 1, f) > 0) {
		if(st.diemTB == max_value) Xuat(st);
	}

	fclose(f);
}
void writeFile(char *filename, Student *student, int n) {
	FILE *f = openfile(filename, "wb");
	if(f == NULL) return;
	
	for(int i = 0; i < n; i++) fwrite(student + i, sizeof(Student), 1, f);
	fclose(f);
}
void readFile(char *filename, Student *student, int &n) {
	FILE *f = openfile(filename, "rb");
	if(f == NULL) return;
	
	int i = 0;
	while(fread(student + i, sizeof(Student), 1, f) > 0 && i < MAX) i++;
	n = i;

    fclose(f);
}
void fix(char *filename) {
	FILE *f = openfile(filename, "rb+");
	if(f == NULL) return;

    Student student;
	char choose;
    int mssv;
	while(1) {
		// system("cls");
        rewind(f);
        printf("\nco muon sua? (C/K): ");
        fflush(stdin);
        scanf("%c", &choose);
        if(choose == 'K') break;
		
        printf("\nMSSV can sua?:");
		scanf("%d", &mssv);

		while(fread(&student, sizeof(Student), 1, f) > 0) {
            if(student.mssv == mssv) {
                Xuat(student);
                fflush(stdin);
                Nhap(student);

                fseek(f, -sizeof(Student), SEEK_CUR);
                fwrite(&student, sizeof(Student), 1, f);
                fseek(f, sizeof(Student), SEEK_CUR);
            }
        }
	}

    fclose(f);
}
void removeStudent(char *filename, int mssv) {
    FILE *f = openfile(filename, "rb+");
    if (f == NULL) return;

	Student st;
    int found = 0;

    while (fread(&st, sizeof(Student), 1, f) > 0) {
        if (st.mssv == mssv) {
            found = 1;
            break;
        }
    }

	if(found == 0) {
		printf("\nKhong tim thay sinh vien co MSSV %d", mssv);
	} else {
		while (fread(&st, sizeof(Student), 1, f) > 0) {
			fseek(f, -2 * sizeof(Student), SEEK_CUR);
			fwrite(&st, sizeof(Student), 1, f);
			fseek(f, 2 * sizeof(Student), SEEK_CUR);
		}
		rewind(f);
		fseek(f, 0, SEEK_END);
		// Truncate (cắt đuôi) tệp để xóa bản ghi cuối cùng
		int newSize = ftell(f);
		ftruncate(fileno(f), newSize - sizeof(Student));

		printf("\nDa xoa sinh vien co MSSV %d", mssv);
	}
	
    fclose(f);
}
void menu() {
	printf("---------------------MENU---------------------");
	printf("\n1.Nhap cac sinh vien vao danh sach");
	printf("\n2.In danh sach sinh vien");
	printf("\n3.Xuat thong tin cua sinh vien co ma so X");
	printf("\n4.Sap xep danh sach sinh vien theo thu tu tang dan cua diem trung binh");
	printf("\n5.Sap xep danh sach sinh vien theo thu tu tang dan cua ho va ten");
	printf("\n6.Ghi danh sach sinh vien vao FILE");
	printf("\n7.Doc danh sach sinh vien tu FILE");
	printf("\n8.Sua thong tin cua mot sinh vien co ma X");
	printf("\n9.Xoa sinh vien co ma X");
	printf("\n10.Xuat ra cac sinh vien co diem trung binh cao nhat");
	printf("\n11.Exit");
}

int main() {
	int running = 1, n, choose, mssv, id;
	char filename[MAX];
	Student student[MAX];

	menu();
	while(running) {
		printf("\nNhap lua chon cua ban: ");
		scanf("%d", &choose);

		switch(choose) {
			case 1:
				NhapMang(student, n);
				break;
			case 2:
				XuatMang(student, n);
				break;
			case 3:
				printf("\nNhap mssv can tim: ");
				scanf("%d", &mssv);
				id = searchMSSV(student, mssv, n);
				
				if(id == -1) printf("\nKhong tim thay sinh vien co MSSV %d", mssv);
				else Xuat(student[id]);
				break;
			case 4:
				SapxepdiemTB(student, n);
				break;
			case 5:
				SapxepName(student, n);
				break;
			case 6:
				printf("\nNhap ten file can ghi: "); fflush(stdin);
				gets(filename);
				writeFile(filename, student, n);
				break;
			case 7:
				printf("\nNhap ten file can doc: "); fflush(stdin);
				gets(filename);
				readFile(filename, student, n);
				break;
			case 8:
				printf("\nNhap ten file can sua: "); fflush(stdin);
				gets(filename);
				fix(filename);
				break;
			case 9:
				printf("\nNhap mssv can xoa: ");
				scanf("%d", &mssv);

				printf("\nNhap ten file: "); fflush(stdin);
				gets(filename);

				removeStudent(filename, mssv);
				break;
			case 10:
				printf("\nNhap ten file: "); fflush(stdin);
				gets(filename);
				
				XuatMaximumDiemTB(filename);
				break;
			default:
				running = 0;
				break;
		}
	}
	return 0;
}
