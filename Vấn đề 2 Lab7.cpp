#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// define struct
struct Product {
    int productID;
    char productName[100];
};
struct NodeProduct {
    Product product;
    NodeProduct* pNext;
};
struct Queue {
    NodeProduct* first;
    NodeProduct* last;
};

// init
void initQueue(Queue &q) { q.first = q.last = NULL; }

// input
void inputOneProduct(Product &p) {
    printf("\nNhap ma san pham: ");
    scanf("%d", &p.productID);

    fflush(stdin);
    printf("\nNhap ten san pham: ");
    gets(p.productName);
}
NodeProduct* getNode() {
    NodeProduct* node = new NodeProduct;
    
    if(node == NULL) {
        printf("\nKho da day!");
        return NULL;
    }
    
    inputOneProduct(node->product);
    node->pNext = NULL;
    return node;
}
void push(Queue &q) {
    NodeProduct* node = getNode();
    if(node == NULL) return;

    if(q.first == NULL) q.first = q.last = node;
    else {
        q.last->pNext = node;
        q.last = node;
    }

    printf("\nNhap san pham thanh cong!");
}

// output
void outputOneProduct(Product p) {
    printf("\nMa san pham: %d, Ten san pham: %s", p.productID, p.productName);
}

// method
bool empty(Queue &q) {
    return q.first == NULL;
}
void exportProduct(Queue &q) {
    if(empty(q)) {
        printf("\nKho rong!");
        return;
    }
    NodeProduct* node = q.first;
    q.first = q.first->pNext;
    delete node;
    printf("Xuat san pham thanh cong!");
}
void display(Queue q, int choice) {
    if(empty(q)) {
        printf("\nKho rong!");
        return;
    }
    if(choice == 0) outputOneProduct(q.last->product);
    else outputOneProduct(q.first->product);
}
void displayAll(Queue q) {
    NodeProduct* node = q.first;
    while(node != NULL) {
        outputOneProduct(node->product);
        node = node->pNext;
    }
}

// menu
void menu() {
    printf("\n0. Lam sach giao dien");
    printf("\n1. Nhap mot san pham");
    printf("\n2. Xuat mot san pham");
    printf("\n3. Xem san pham chuan bi xuat");
    printf("\n4. Xem san pham moi nhap");
    printf("\n5. Xem cac san pham co trong kho");
    printf("\n6. Ket thuc chuong trinh");
}

int main() {
    int running = 1, choice;
    Queue q; initQueue(q);
    
    menu();
    while(running) {
        printf("\nNhap lua chon: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                push(q);
                break;
            case 2:
                exportProduct(q);
                break;
            case 3:
                display(q, 1);
                break;
            case 4:
                display(q, 0);
                break;
            case 5:
                displayAll(q);
                break;
            case 6:
                running = 0;
                break;
            default:
                system("cls");
                menu();
                break;
        }
    }
    return 0;
}