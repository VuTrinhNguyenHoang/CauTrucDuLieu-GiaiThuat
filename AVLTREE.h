#include <iostream>
using namespace std;

struct AVLNode {
public:
    int data;
    int height;
    int count;
    AVLNode* left;
    AVLNode* right;

    AVLNode(int value) : data(value), height(1), count(1), left(NULL), right(NULL) {}
    
    int compare(int value) {
        if(this->data > value) return 1;
        if(this->data < value) return -1;
        return 0;
    }

    friend ostream& operator << (ostream& os, const AVLNode& node) {
        os << "data: " << node.data << "; count: " << node.count << "; height: " << node.height << '\n';
        return os;
    }
};
struct AVLTree {
public:
    AVLTree() : size(0), root(NULL) {}
    
    void insert(int value) {
        this->root = insert(this->root, value);
    }

    void erase(int value) {
        this->root = erase(this->root, value);
    }

    void display() {
        cout << "Tree size: " << getSize() << endl;
        display(this->root);
    }

    int getMin() { return minValueNode(this->root)->data; }
    int getMax() { return maxValueNode(this->root)->data; }
    int getSize() { return size; }
    int getHeight(AVLNode* node) { return (node == NULL ? 0 : node->height); }
private:
    int size;
    AVLNode* root;

    AVLNode* insert(AVLNode* node, int value) {
        if(node == NULL) {
            size++;
            return new AVLNode(value);
        }

        if(node->compare(value) == 0) {
            node->count++;
            return node;
        }

        if(node->compare(value) == 1) node->left = insert(node->left, value);
        else if (node->compare(value) == -1) node->right = insert(node->right, value);
        
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);

        if(balance > 1) {
            if(node->left->compare(value) == -1) node->left = leftRotation(node->left);
            return rightRotation(node);
        } else if (balance < -1) {
            if(node->right->compare(value) == 1) node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    AVLNode* erase(AVLNode* node, int value) {
        if(node == NULL) return NULL;

        if(node->compare(value) == 1) node->left = erase(node->left, value);
        else if(node->compare(value) == -1) node->right = erase(node->right, value);
        else {
            node->count--;
            if(node->count != 0) return node;
            
            if((node->left == NULL) || (node->right == NULL)) {
                AVLNode* temp = ((node->left == NULL) ? node->right : node->left);

                delete(node);
                node = temp;
            } else {
                AVLNode* temp = minValueNode(node->right);

                node->data = temp->data;
                node->right = erase(node->right, node->data);
            }
        }

        if(node == NULL) return NULL;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalance(node);

        if(balance > 1) {
            if(getBalance(node->left) < 0) node->left = leftRotation(node->left);
            return rightRotation(node);
        } else if (balance < -1) {
            if(getBalance(node->right) > 0) node->right = rightRotation(node->right);
            return leftRotation(node);
        }

        return node;
    }

    AVLNode* leftRotation(AVLNode* node) {
        if(node == NULL) return NULL;

        AVLNode* returnNode = node->right;
        node->right = returnNode->left;
        returnNode->left = node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        returnNode->height = max(getHeight(returnNode->left), getHeight(returnNode->right)) + 1;

        return returnNode;
    }

    AVLNode* rightRotation(AVLNode* node) {
        if(node == NULL) return NULL;

        AVLNode* returnNode = node->left;
        node->left = returnNode->right;
        returnNode->right = node;

        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        returnNode->height = max(getHeight(returnNode->left), getHeight(returnNode->right)) + 1;

        return returnNode;
    }

    AVLNode* minValueNode(AVLNode* node) {
        if(node->left == NULL) return node;
        return minValueNode(node->left);
    }

    AVLNode* maxValueNode(AVLNode* node) {
        if(node->right == NULL) return node;
        return maxValueNode(node->right);
    }

    int getBalance(AVLNode* node) {
        if(node == NULL) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    void display(AVLNode* node) {
        if(node == NULL) return;

        cout << *node;
        display(node->left), display(node->right);
    }
};
