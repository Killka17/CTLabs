#include <algorithm>
#include "avl.h"

bool exists(node *root, int key);

size_t GetHeight(node* n) {
    return n ? n->h : 0;
}

void UpdateHeight(node* n) {
    if (n) {
        n->h = std::max(GetHeight(n->l), GetHeight(n->r)) + 1;
    }
}

node* RotateRight(node* y) {
    node* x = y->l;
    node* T2 = x->r;

    x->r = y;
    y->l = T2;

    UpdateHeight(y);
    UpdateHeight(x);

    return x;
}

node* RotateLeft(node* x) {
    node* y = x->r;
    node* T2 = y->l;

    y->l = x;
    x->r = T2;

    UpdateHeight(x);
    UpdateHeight(y);

    return y;
}

long long BalanceFactor(node* n) {
    return n ? GetHeight(n->r) - GetHeight(n->l) : 0;
}

node* Balance(node* n) {
    UpdateHeight(n);

    if (BalanceFactor(n) > 1) {
        if (BalanceFactor(n->r) < 0) {
            n->r = RotateRight(n->r);
        }
        return RotateLeft(n);
    }
    if (BalanceFactor(n) < -1) {
        if (BalanceFactor(n->l) > 0) {
            n->l = RotateLeft(n->l);
        }
        return RotateRight(n);
    }

    return n;
}

node* insert(node* root, int key) {
    if (!root) {
        return new node{nullptr, nullptr, key, 1};
    }

    if (key < root->key) {
        root->l = insert(root->l, key);
    } else if (key > root->key) {
        root->r = insert(root->r, key);
    } else {
        return root;
    }

    return Balance(root);
}

node* findMin(node* n) {
    return n->l ? findMin(n->l) : n;
}

node* removeMin(node* n) {
    if (!n->l) {
        return n->r;
    }
    n->l = removeMin(n->l);
    return Balance(n);
}

node* remove(node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key) {
        root->l = remove(root->l, key);
    } else if (key > root->key) {
        root->r = remove(root->r, key);
    } else {
        node* l = root->l;
        node* r = root->r;
        delete root;
        if (!r) return l;
        node* min = findMin(r);
        min->r = removeMin(r);
        min->l = l;
        return Balance(min);
    }

    return Balance(root);
}

bool exists(node* root, int key) {
    if (!root) return false;

    if (key < root->key) {
        return exists(root->l, key);
    } else if (key > root->key) {
        return exists(root->r, key);
    } else {
        return true;
    }
}
