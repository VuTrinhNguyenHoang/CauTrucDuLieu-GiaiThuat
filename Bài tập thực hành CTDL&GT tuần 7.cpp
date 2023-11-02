#include <stdio.h>
const int maxn = 100;
int edge[maxn][maxn], visited[maxn], n;

struct Node {
    int data;
    Node* pNext;
};
struct Queue {
    Node* first;
    Node* last;
};

void initQueue(Queue &q) { q.first = q.last = NULL; }
Node* getNode(int value) {
    Node* node = new Node;
    if(node == NULL) return NULL;

    node->data = value;
    node->pNext = NULL;
    return node;
}
void push(Queue &q, int value) {
    Node* node = getNode(value);
    if(node == NULL) return;

    if(q.first == NULL) q.first = q.last = node;
    else {
        q.last->pNext = node;
        q.last = node;
    }
}
bool empty(Queue &q) { return q.first == NULL; }
int top(Queue &q) { return q.first->data; }
void pop(Queue &q) {
    Node* node = q.first;
    q.first = q.first->pNext;
    delete node;
}

int bfs(int start, int end) {
    Queue q; initQueue(q);
    push(q, start);
    visited[start] = 1;
    while(!empty(q)) {
        int u = top(q); pop(q);
        for(int i = 1; i <= n; i++) if(edge[u][i] && !visited[i]) {
            push(q, i);
            visited[i] = 1;
        }
    }
    return visited[end];
}

int main() {
    printf("Nhap so luong dinh: ");
    scanf("%d", &n);
    printf("Nhap ma tran canh:\n");
    for(int i = 1; i <= n; i++)  
        for(int j = 1; j <= n; j++) 
            scanf("%d", &edge[i][j]);

    int start, end;
    while(true) {
        printf("Nhap start, end: ");
        scanf("%d%d", &start, &end);
        if(start == 0) break;

        for(int i = 1; i <= n; i++) visited[i] = 0;
        if(bfs(start, end)) printf("Co duong di tu %d den %d\n", start, end);
        else printf("Khong co duong di tu %d den %d\n", start, end);
    }

    return 0;
}