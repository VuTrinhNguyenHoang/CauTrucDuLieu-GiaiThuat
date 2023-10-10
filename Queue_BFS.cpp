#include <iostream>
using namespace std;
const int maxn = 1e2 + 2;
int Edge[maxn][maxn], used[maxn], n, m;
struct Node {
    int data;
    Node* pNext;

    Node (int val) : data(val), pNext(NULL) {}
};
struct Queue {
private:
    Node* pHead;
    Node* pTail;
public:
    Queue() : pHead(NULL), pTail(NULL) {}

    void push(int val) {
        Node* node = new Node(val);

        if(pHead == NULL) pHead = pTail = node;
        else {
            pTail->pNext = node;
            pTail = node;
        }
    }

    void pop() {
        Node* node = pHead;
        pHead = pHead->pNext;
        delete node; 
    }
    
    int top() { return pHead->data; }
    bool empty() { return pHead == NULL; }
};

void bfs(int x = 1) {
    Queue q;
    q.push(x);
    used[x] = 1;
    cout << 1 << ' ';
    while(!q.empty()) {
        int u = q.top(); q.pop();
        for(int i = 1; i <= n; i++) if(Edge[u][i] && !used[i]) {
            cout << i << ' ';
            q.push(i);
            used[i] = 1;
        }
    }
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        Edge[u][v] = Edge[v][u] = 1;
    }

    bfs();
    return 0;
}
