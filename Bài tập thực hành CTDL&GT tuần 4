#include <stdio.h>
#include <stdlib.h>
struct DonThuc {
    float heSo;
    int soMu;
};
struct Node {
    DonThuc data;
    Node* pNext;
};
struct DaThuc {
    Node* pHead;
    Node* pTail;
};
DonThuc createDonThuc(float heSo, int soMu) {
    DonThuc donThuc;
    donThuc.heSo = heSo;
    donThuc.soMu = soMu;
    return donThuc;
}
Node* createNode(float heSo, int soMu) {
    DonThuc donThuc = createDonThuc(heSo, soMu);
    Node* node = new Node;
    node->data = donThuc;
    node->pNext = NULL;
    return node;
}
void init(DaThuc &daThuc) { daThuc.pHead = daThuc.pTail = NULL; }
void push_back(DaThuc &daThuc, float heSo, int soMu) {
    Node* node = createNode(heSo, soMu);
    if(daThuc.pHead == NULL) daThuc.pHead = daThuc.pTail = node;
    else {
        daThuc.pTail->pNext = node;
        daThuc.pTail = node; 
    }
}
void nhapDaThuc(DaThuc &daThuc) {
	float heSo;
	int soMu;
	printf("\nBat  dau  nhap  da  thuc  (nhap  he  so  0  de ket thuc): ");
	do {
		printf("\nNhap he so: "); 
		scanf("%f", &heSo);
		
        if (heSo == 0) break; 
		
        printf("\nNhap so mu: "); 
		scanf("%d", &soMu);
		
        push_back(daThuc, heSo, soMu);
	} while (heSo);

    system("cls");
}
void removeNode(DaThuc &daThuc) {
    Node* p = daThuc.pHead;
    Node* prev = NULL;

    while(p != NULL) {
        if(p->data.heSo == 0) {
            if(prev == NULL) daThuc.pHead = p->pNext;
            else prev->pNext = p->pNext;

            if(p == daThuc.pTail) {
                daThuc.pTail = prev;
                daThuc.pTail->pNext = NULL;
            }
            Node* t = p;
            p = p->pNext;

            delete t;
        } else {
            prev = p;
            p = p->pNext;
        }
    }
}
void sortDaThuc(DaThuc &daThuc) {
    for(Node* p = daThuc.pHead; p != daThuc.pTail; p = p->pNext)
        for(Node* q = p->pNext; q != NULL; q = q->pNext) {
            if(p->data.soMu < q->data.soMu) {
                DonThuc t = p->data;
                p->data = q->data;
                q->data = t;
            } else if (p->data.soMu == q->data.soMu) {
                p->data.heSo += q->data.heSo;
                q->data.heSo = 0;
            }
        }
    removeNode(daThuc);
}
DaThuc plusDaThuc(DaThuc a, DaThuc b) {
    Node* p = a.pHead;
    Node* q = b.pHead;

    DaThuc daThuc; init(daThuc);
    while(p != NULL && q != NULL) {
        if(p->data.soMu == q->data.soMu) {
            float heSo = p->data.heSo + q->data.heSo;
            if(heSo) push_back(daThuc, heSo, p->data.soMu);

            p = p->pNext;
            q = q->pNext;
        } else if (p->data.soMu > q->data.soMu) {
            push_back(daThuc, p->data.heSo, p->data.soMu);
            p = p->pNext;
        } else {
            push_back(daThuc, q->data.heSo, q->data.soMu);
            q = q->pNext;
        }
    }

    while(p != NULL) {
        push_back(daThuc, p->data.heSo, p->data.soMu);
        p = p->pNext;
    }
    while(q != NULL) {
        push_back(daThuc, q->data.heSo, q->data.soMu);
        q = q->pNext;
    }

    sortDaThuc(daThuc);
    return daThuc;
}
DaThuc minusDaThuc(DaThuc a, DaThuc b) {
    Node* p = a.pHead;
    Node* q = b.pHead;

    DaThuc daThuc; init(daThuc);
    while(p != NULL && q != NULL) {
        if(p->data.soMu == q->data.soMu) {
            float heSo = p->data.heSo - q->data.heSo;
            if(heSo) push_back(daThuc, heSo, p->data.soMu);

            p = p->pNext;
            q = q->pNext;
        } else if (p->data.soMu > q->data.soMu) {
            push_back(daThuc, p->data.heSo, p->data.soMu);
            p = p->pNext;
        } else {
            push_back(daThuc, -q->data.heSo, q->data.soMu);
            q = q->pNext;
        }
    }

    while(p != NULL) {
        push_back(daThuc, p->data.heSo, p->data.soMu);
        p = p->pNext;
    }
    while(q != NULL) {
        push_back(daThuc, -q->data.heSo, q->data.soMu);
        q = q->pNext;
    }

    sortDaThuc(daThuc);
    return daThuc;
}
DaThuc multiDaThuc(DaThuc a, DaThuc b) {
    DaThuc daThuc; init(daThuc);
    for(Node* p = a.pHead; p != NULL; p = p->pNext)
        for(Node* q = b.pHead; q != NULL; q = q->pNext)
            push_back(  daThuc, 
                        p->data.heSo * q->data.heSo, 
                        p->data.soMu + q->data.soMu);
    sortDaThuc(daThuc);
    return daThuc;
}
DaThuc divideDaThuc(DaThuc a, DaThuc b, DaThuc &c) {
    DaThuc daThuc; init(daThuc);
    
    Node* q = b.pHead;
    while(q != NULL) {
        if(q->data.heSo != 0) break;
        q = q->pNext;
    }

    if(q == NULL) {
        printf("da thuc b bang 0\n");
        exit(1);
    }

    while(a.pHead != NULL && a.pHead->data.soMu >= b.pHead->data.soMu) {
        DonThuc tmp = createDonThuc(a.pHead->data.heSo / b.pHead->data.heSo, 
                                    a.pHead->data.soMu - b.pHead->data.soMu);

        push_back(daThuc, tmp.heSo, tmp.soMu);

        DaThuc tmpDivisor; init(tmpDivisor);
        for(Node* p = b.pHead; p != NULL; p = p->pNext) {
            DonThuc tmpTerm = createDonThuc(tmp.heSo * p->data.heSo,
                                            tmp.soMu + p->data.soMu);
            push_back(tmpDivisor, tmpTerm.heSo, tmpTerm.soMu);
        }

        DaThuc tmpResult = minusDaThuc(a, tmpDivisor);
        removeNode(tmpResult);
        a = tmpResult;
    }

    c = a;
    return daThuc;
}
void display(DaThuc a) {
    Node* p = a.pHead;
    if(p == NULL) {
        printf("0\n");
        return;
    }

    while(p != NULL) {
        float heSo = p->data.heSo;
        int soMu = p->data.soMu;

        if(p == a.pHead) {
            if(soMu == 0) {
                printf("%.0f ", heSo);
            } else if(soMu == 1) {
                if(abs(heSo) == 1) printf("%sx ", (heSo == 1.0 ? "" : "-"));
                else printf("%.0fx ", heSo);
            } else if(abs(heSo) == 1) {
                printf("%sx^%d ", (heSo == 1.0 ? "" : "-"), soMu);
            } else printf("%.0fx^%d ", heSo, soMu);
        } else {
            if(soMu == 0) {
                printf("%s %.0f ", (heSo > 0 ? "+" : "-"), abs(heSo));
            } else if(soMu == 1) {
                if(abs(heSo) == 1) printf("%s x ", (heSo == 1.0 ? "+" : "-"));
                else printf("%s %.0fx ", (heSo > 0 ? "+" : "-"), abs(heSo));
            } else if(abs(heSo) == 1) {
                printf("%s x^%d ", (heSo == 1.0 ? "+" : "-"), soMu);
            } else printf("%s %.0fx^%d ", (heSo > 0 ? "+" : "-"), abs(heSo), soMu);
        }
        p = p->pNext;
    }
    printf("\n");
}

int main() {
    DaThuc a, b, c; init(a), init(b), init(c);
    printf("\nNhap Da Thuc A"); nhapDaThuc(a); 
    printf("\nNhap Da Thuc B"); nhapDaThuc(b);

    // sắp xếp lại các phần tử trong Đa Thức theo thứ tự đúng
    sortDaThuc(a), sortDaThuc(b);

    printf("A = "); display(a);
    printf("B = "); display(b);

    // Phép cộng
    printf("A + B = "); display(plusDaThuc(a, b));
    
    // Phép trừ
    printf("A - B = "); display(minusDaThuc(a, b));
    
    // Phép nhân
    printf("A * B = "); display(multiDaThuc(a, b));
    
    // Phép chia
    printf("A / B = "); display(divideDaThuc(a, b, c));
    printf("A / B Du C = "); display(c);
    return 0;
}
