#include <iostream>
#include <map>
#include <queue>

class Encoder {
public:
    Encoder() {
        for (int i = 0; i < 26; i++) {
            constexpr int w[] = {120, 91, 81, 76, 73, 69, 62, 60, 59, 43, 39, 28, 27, 26, 23, 21, 20, 19, 18, 15, 11, 7, 4, 3, 2, 1};
            weights[letters[i]] = w[i];
        }
        huffmanRoot = nullptr;
        constructHuffmanTree();
    }

    ~Encoder() {
        deleteNode(huffmanRoot);
    }
private:
    struct Node {
        char ch;
        int weight;
        Node* left;
        Node* right;

        Node(char c, int w) : ch(c), weight(w), left(nullptr), right(nullptr) { }

        bool operator<(const Node &other) const {
            return this->weight > other.weight;  // To implement a min-priority queue
        }
    };

    Node* huffmanRoot;

    char letters[26] =
    {'E', 'T', 'A', 'O', 'I', 'N', 'R', 'S', 'H', 'D', 'L', 'F', 'C', 'M', 'U', 'G', 'Y', 'P', 'W', 'B', 'V', 'K', 'J', 'X', 'Z', 'Q'};

    std::map<char, int> weights;

    std::map<char, std::string> huffmanCode;

    void constructHuffmanTree() {
        std::priority_queue<Node*> pq;
        for (int i = 0; i < 26; i++) {
            Node* node = new Node(letters[i], weights[letters[i]]);
            pq.push(node);
        }
        while (pq.size() > 1) {
            Node* n1 = pq.top(); pq.pop();
            Node* n2 = pq.top(); pq.pop();
            Node* newNode = new Node(' ', n1->weight + n2->weight);
            newNode->left = n1;
            newNode->right = n2;
            pq.push(newNode);
        }
        huffmanRoot = pq.top();
    }

    void generateHuffmanCodeMap() {
        if (huffmanRoot == nullptr) {
            constructHuffmanTree();
        }
        generateHuffmanCode(huffmanRoot, "");
    }

    void generateHuffmanCode(const Node* node, const std::string& code) {
        if (node->left == nullptr && node->right == nullptr) {
            huffmanCode[node->ch] = code;
            return;
        }
        if (node->left != nullptr) {
            generateHuffmanCode(node->left, code + "0");
        }
        if (node->right != nullptr) {
            generateHuffmanCode(node->right, code + "1");
        }
    }

    static void deleteNode(const Node* node) {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return;
        }
        if (node->left != nullptr) {
            deleteNode(node->left);
        }
        if (node->right != nullptr) {
            deleteNode(node->right);
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}