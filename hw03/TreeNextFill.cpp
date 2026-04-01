#include <cmath>
#include <iostream>
#include <queue>

struct Node {
    int index;
    int left;
    int right;
    int next;
};

Node* nodes;

Node** fullBinaryTree;

bool* isRoot;

int n;
int rootIndex = 0;

int leftChild(int index) {
    return index * 2;
}

int rightChild(int index) {
    return index * 2 + 1;
}

bool isPowerOfTwo(int num) {
    if (num == 1) {
        return true;
    }
    int l = static_cast<int>(log(num)) + 1;
    for (int i = 1; i <= l; i++) {
        if (1 << i == num) {
            return true;
        }
    }
    return false;
}

int main() {
    std::cin >> n;
    nodes = new Node[n + 1];
    fullBinaryTree = new Node*[n + 1];
    isRoot = new bool[n + 1];
    isRoot[0] = false;
    for (int i = 1; i <= n; i++) {
        isRoot[i] = true;
    }
    for (int i = 1; i <= n; i++) {
        int val, left, right;
        std::cin >> val >> left >> right;
        nodes[i].index = i;
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
    std::queue<Node*> fringe;
    int curr = 1;
    fringe.push(&nodes[rootIndex]);
    while (!fringe.empty()) {
        Node* currNode = fringe.front();
        fringe.pop();
        if (currNode->left != 0) {
            fringe.push(&nodes[currNode->left]);
        }
        if (currNode->right != 0) {
            fringe.push(&nodes[currNode->right]);
        }
        fullBinaryTree[curr] = currNode;
        curr++;
    }
    for (int i = 1; i <= n; i++) {
        if (isPowerOfTwo(i + 1) || i == n) {
            fullBinaryTree[i]->next = 0;
        }
        else {
            fullBinaryTree[i]->next = fullBinaryTree[i + 1]->index;
        }
    }
    for (int i = 1; i <= n; i++) {
        std::cout << nodes[i].next << std::endl;
    }

    delete[] nodes;
    delete[] isRoot;
    delete[] fullBinaryTree;
}