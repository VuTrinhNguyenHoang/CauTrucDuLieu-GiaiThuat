#include<iostream>
#include<string.h>
#include<stdio.h>
using namespace std;

struct Word{
    char Vietnamese[50];
    char English[50];
    int height;
};

struct Node {
    Node* pLeft;
    Node* pRight;
    Word word;
};
typedef Node* Tree;
// Nguyen mau ham
void Init(Tree &T);
int NhapWord(Word &word); 
void XuatWord(Word word); 
Node* TaoNode(Word word); 
int ThemNodeVaoCay(Tree &T, Word word); 
void TaoCay(Tree &T); 
void XuatTree(Tree T);
void Search(Tree T, Word word);
void TraCuu(Tree T);
void Suatu(Tree &T);
void Fix(Tree &T, Word word);

//
int main() {
	Tree T;
	Init(T);
	TaoCay(T);
	XuatTree(T);
    TraCuu(T);
    Suatu(T);
    XuatTree(T);
}
//
int NhapWord(Word &word) {
	printf("\n Nhap tu tieng anh: ");
    fflush(stdin);
    gets(word.English);
    
    if(strlen(word.English)==0) return 0;
    	
    printf("\n Nhap nghia tieng viet: ");
    fflush(stdin);
    gets(word.Vietnamese);
    word.height = 1;
    return 1;
}
//

void XuatWord(Word word) {
	printf("\n%-20s: %-15s", word.English, word.Vietnamese);
}

// Khoi tao
void Init(Tree &T) { T = NULL; }
//
Node* TaoNode(Word word) {
	Node* p = new Node;
    if(p == NULL) return NULL;

    p->pLeft = p->pRight = NULL;
    p->word = word;
    return p;
}
// 
int Sosanh(Word sv1, Word sv2) {
	if(strlen(sv1.English) > strlen(sv2.English)) return 1;
	else if(strlen(sv1.English) < strlen(sv2.English)) return -1;
	return strcmp(sv1.English,sv2.English);
}
//
int ThemNodeVaoCay(Tree &T, Word word) {
	if (T) {
		if(Sosanh(T->word ,word) == 0) return 0; 
		if(Sosanh(T->word ,word) > 0) return ThemNodeVaoCay(T->pLeft, word);
		return ThemNodeVaoCay(T->pRight, word);
	}
	
	T = TaoNode(word);
	if (T == NULL) return -1; 
	
	return 1;
}
//
void TaoCay(Tree &T) {
	Init(T);
	Word word;
	int flag = NhapWord(word);	
	int kq;

	while(flag) {
		kq = ThemNodeVaoCay(T, word);
		if(kq == 0) printf("\n Da co word");
		else if(kq == -1) printf("\n Ko du bo nho");
		else printf("\n Chen thanh cong");
		flag = NhapWord(word);
	}
}
//
void XuatTree(Tree T) {
    if(T == NULL) return;
    XuatTree(T->pLeft);
    XuatWord(T->word);
    XuatTree(T->pRight);
}
//
void Search(Tree T, Word word) {
    if(T == NULL) {
        printf("\n Khong co tu can tim");
        return;
    }

    if(Sosanh(T->word, word) == 0) XuatWord(T->word);
    else if(Sosanh(T->word, word) > 0) Search(T->pLeft, word);
    else Search(T->pRight, word); 
}
//
void TraCuu(Tree T) {
    Word word;
    printf("\nNhap tu tieng anh can tim can tim: ");
    gets(word.English);

    Search(T, word);
}
//
void Suatu(Tree &T) {
    Word word;
    printf("\n Nhap tu tieng anh can sua: ");
    gets(word.English);

    printf("\n Nhap nghia tieng viet moi: ");
    gets(word.Vietnamese);

    Fix(T, word);
} 
//
void Fix(Tree &T, Word word) {
    if(T == NULL) {
        printf("\n Khong co tu can sua");
        return;
    }

    if(Sosanh(T->word, word) == 0) T->word = word;
    else if(Sosanh(T->word, word) > 0) Fix(T->pLeft, word);
    else Fix(T->pRight, word);
}
//
void LeftRotation(Tree &T, Word word) {
    
}
