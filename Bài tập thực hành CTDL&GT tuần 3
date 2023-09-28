#include <stdio.h>

struct Node { // 1
    int data;
    Node *pNext;
};
struct List { // 2
    Node *pHead;
    Node *pTail;
};
Node* createNode(int data) { // 3
    Node *node = new Node;
    if(node == NULL) {
        printf("Full Memory!!");
        return NULL;
    }

    node->data = data;
    node->pNext = NULL;
    return node;
}
void init(List &L) { L.pHead = L.pTail = NULL; } // 4
void push_front(List &L, int data) { // 5
    Node* node = createNode(data);
    if(node == NULL) return;

    if(L.pHead == NULL) L.pHead = L.pTail = node;
    else {
        node->pNext = L.pHead;
        L.pHead = node;
    }
}
void createList(List &L) { // 6
    int n;
    do {
        printf("\nNhap so luong phan tu cua List n = ");
        scanf("%d", &n);
    } while (n < 0);

    for(int i = 0, data; i < n; i++) {
        scanf("%d", &data);
        push_front(L, data);
    }
}
void eraseNode(List &L, int data) { // 7
    Node* p = L.pHead;
    if(p->data == data) {
        L.pHead = p->pNext;
        delete p;
        if(L.pHead == NULL) L.pTail == NULL;
        return;
    }

    while(p != L.pTail) {
        if(p->pNext->data == data) {
            Node* node = p->pNext->pNext;
            delete p->pNext;
            p->pNext = node;
            return;
        }
        p = p->pNext;
    }
}
bool isEmpty(List L) { // 8
    return L.pHead == NULL; // True if empty
}
void displayList(FILE* f, List L) {
    Node* p = L.pHead;
    while(p != NULL) {
        fprintf(f, "%d ", p->data);
        p = p->pNext;
    }
    fprintf(f, "\n");
}
void Separating_List(List &L, int x) { // 9
    List L1; init(L1);
    
    Node* p = L.pHead;
    while(p != NULL) {
        int data = p->data;
        if(data > x) {
            push_front(L1, data);
            p = p->pNext;
            eraseNode(L, data);
            continue;
        } else if(data == x) {
            p = p->pNext;
            eraseNode(L, data);
            continue;
        }
        
        p = p->pNext;
    }

    FILE* f = fopen("data.txt", "w");
    if(f == NULL) printf("\nKhong mo duoc file");
    else displayList(f, L), displayList(f, L1);

    fclose(f);
}
void Separating_List1(List L, int x) { // 10  
    List L1, L2; init(L1), init(L2);
    Node* p = L.pHead;
    while(p != NULL) {
        int data = p->data;
        if(data > x) push_front(L1, data);
        else if(data < x) push_front(L2, data);

        p = p->pNext;
    }

    FILE* f = fopen("data.txt", "w");
    if(f == NULL) printf("\nKhong mo duoc file");
    else displayList(f, L), displayList(f, L1), displayList(f, L2);
    
    fclose(f);
}
void menu() {
    printf("\n1. Tao danh sach");
    printf("\n2. Chen mot node vao dau List");
    printf("\n3. Xoa node co gia tri K");
    printf("\n4. Kiem tra Empty cua List");
    printf("\n5. Tao danh sach theo yeu cau a");
    printf("\n6. Tao danh sach theo yeu cau b");
}
int input() {
    int k;
    printf("\nNhap gia tri k = ");
    scanf("%d", &k);
    return k;
}

int main() {
    List L; init(L);
    int running = 1, choice, data;
    menu();
    while(running) {
        printf("\nLua chon cua ban: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                createList(L);
                break;
            case 2:
                data = input();
                push_front(L, data);
                break;
            case 3:
                data = input();
                eraseNode(L, data);
                break;
            case 4:
                if(isEmpty(L)) printf("\nDanh sach rong");
                else printf("\nDanh sach khong rong");
                break;
            case 5:
                data = input();
                Separating_List(L, data);
                break;
            case 6:
                data = input();
                Separating_List1(L, data);
                break;
            default:
                running = 0;
                break;
        }
    }

    return 0;
}
