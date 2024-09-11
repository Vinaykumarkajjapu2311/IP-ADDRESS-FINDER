#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node {
    int ipAdd;
    int dataPacket;
    Node *left;
    Node *right;
    Node *parent;
};

struct SplayTree {
    Node *root;
};

Node* newNode(int ipAdd) {
    Node* n = new Node;
    n->ipAdd = ipAdd;
    n->parent = NULL;
    n->right = NULL;
    n->left = NULL;
    return n;
}

SplayTree* newSplayTree() {
    SplayTree* t = new SplayTree;
    t->root = NULL;
    return t;
}

Node* maximum(SplayTree* t, Node* x) {
    while (x->right != NULL) {
        x = x->right;
    }
    return x;
}

void leftRotate(SplayTree* t, Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        t->root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void rightRotate(SplayTree* t, Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        t->root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void splay(SplayTree* t, Node* n) {
    while (n->parent != NULL) {
        if (n->parent == t->root) {
            if (n == n->parent->left) {
                rightRotate(t, n->parent);
            } else {
                leftRotate(t, n->parent);
            }
        } else {
            Node* p = n->parent;
            Node* g = p->parent;
            if (n->parent->left == n && p->parent->left == p) {
                rightRotate(t, g);
                rightRotate(t, p);
            } else if (n->parent->right == n && p->parent->right == p) {
                leftRotate(t, g);
                leftRotate(t, p);
            } else if (n->parent->right == n && p->parent->left == p) {
                leftRotate(t, p);
                rightRotate(t, g);
            } else if (n->parent->left == n && p->parent->right == p) {
                rightRotate(t, p);
                leftRotate(t, g);
            }
        }
    }
}

void insert(SplayTree* t, Node* n) {
    Node* y = NULL;
    Node* temp = t->root;
    while (temp != NULL) {
        y = temp;
        if (n->ipAdd < temp->ipAdd) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }
    n->parent = y;
    if (y == NULL) {
        t->root = n;
    } else if (n->ipAdd < y->ipAdd) {
        y->left = n;
    } else {
        y->right = n;
    }
    splay(t, n);
}

Node* search(SplayTree* t, Node* n, int x) {
    if (x == n->ipAdd) {
        splay(t, n);
        return n;
    } else if (x < n->ipAdd) {
        return search(t, n->left, x);
    } else if (x > n->ipAdd) {
        return search(t, n->right, x);
    } else {
        return NULL;
    }
}

void inorder(SplayTree* t, Node* n, char* cmn) {
    if (n != NULL) {
        inorder(t, n->left, cmn);
        cout << cmn << n->ipAdd << " -> " << n->dataPacket << endl;
        inorder(t, n->right, cmn);
    }
}

int main() {
    char* cmn = "192.168.3.";
    SplayTree* t = newSplayTree();
    Node* a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *k, *l, *m;
    a = newNode(104);
    b = newNode(112);
    c = newNode(117);
    d = newNode(124);
    e = newNode(121);
    f = newNode(108);
    g = newNode(109);
    h = newNode(111);
    i = newNode(122);
    j = newNode(125);
    k = newNode(129);
    insert(t, a);
    insert(t, b);
    insert(t, c);
    insert(t, d);
    insert(t, e);
    insert(t, f);
    insert(t, g);
    insert(t, h);
    insert(t, i);
    insert(t, j);
    insert(t, k);
    int x;
    int find[11] = {104, 112, 117, 124, 121, 108, 109, 111, 122, 125, 129};
    Node* add[11] = {a, b, c, d, e, f, g, h, i, j, k};
    srand(time(0));
    for (x = 0; x < 11; x++) {
        int data = rand() % 200;
        Node* temp = search(t, add[x], find[x]);
        if (temp != NULL) {
            temp->dataPacket = data;
        }
    }
    cout << "IP ADDRESS -> DATA PACKET\n";
    inorder(t, t->root, cmn);
    return 0;
}
