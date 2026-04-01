//
// Created by unkn0 on 2026-04-01.
//

#include <iostream>

struct Node {
    int index;
    int left;
    int right;
};

Node* nodes;

bool* isRoot;

int n;
int rootIndex = 0;

void preOrder(Node root) {
    std::cout << root.index << ' ';
    if (root.left != 0) {
        preOrder(nodes[root.left]);
    }
    if (root.right != 0) {
        preOrder(nodes[root.right]);
    }
}

int main() {
    std::cin >> n;
    nodes = new Node[n + 1];
    isRoot = new bool[n + 1];
    isRoot[0] = false;
    for (int i = 1; i <= n; i++) {
        isRoot[i] = true;
    }
    for (int i = 1; i <= n; i++) {
        int left, right;
        std::cin >> nodes[i].index >> left >> right;
        nodes[i].left = left;
        nodes[i].right = right;
        isRoot[left] = false;
        isRoot[right] = false;
    }
    for (int i = 1; i <= n; i++) {
        if (isRoot[i]) {
            rootIndex = i;
            break;
        }
    }
    preOrder(nodes[rootIndex]);
    delete[] nodes;
    delete[] isRoot;
}