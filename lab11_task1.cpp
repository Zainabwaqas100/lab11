#include <iostream>
using namespace std;

// Represents a node in the Huffman tree
class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = NULL;
        right = NULL;
    }
};

// Binary Min Heap
class MinHeap {
private:
    Node** heap;
    int size;
    int capacity;

    void heapifyDown(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && heap[left]->freq < heap[smallest]->freq)
            smallest = left;

        if (right < size && heap[right]->freq < heap[smallest]->freq)
            smallest = right;

        if (smallest != i) {
            Node* temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;

            heapifyDown(smallest);
        }
    }

public:
    MinHeap(int cap) {
        capacity = cap;
        size = 0;
        heap = new Node*[capacity];
    }

    void insert(Node* node) {
        int i = size;
        heap[size] = node;
        size++;

        while (i > 0 && heap[(i - 1) / 2]->freq > heap[i]->freq) {
            Node* temp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = temp;

            i = (i - 1) / 2;
        }
    }

    Node* extractMin() {
        if (size == 0)
            return NULL;

        Node* minimum = heap[0];

        heap[0] = heap[size - 1];
        size--;

        if (size > 0)
            heapifyDown(0);

        return minimum;
    }

    int getSize() {
        return size;
    }

    ~MinHeap() {
        delete[] heap;
    }
};

// Builds the Huffman tree
Node* buildHuffmanTree(char characters[], int frequencies[], int n) {

    MinHeap heap(n);

    // Insert all characters into the min heap
    for (int i = 0; i < n; i++) {
        Node* newNode = new Node(characters[i], frequencies[i]);
        heap.insert(newNode);
    }

    // Keep combining the two smallest nodes
    while (heap.getSize() > 1) {

        Node* left = heap.extractMin();
        Node* right = heap.extractMin();

        // Create a new internal node
        Node* parent = new Node('\0', left->freq + right->freq);

        parent->left = left;
        parent->right = right;

        heap.insert(parent);
    }

    return heap.extractMin();
}

// Prints Huffman codes in preorder
void printCodes(Node* root, char code[], int depth) {

    if (root == NULL)
        return;

    // Leaf node: print character and its code
    if (root->left == NULL && root->right == NULL) {

        if (depth == 0) {
            code[depth++] = '0';
        }

        code[depth] = '\0';

        cout << root->ch << ": " << code << endl;
        return;
    }

    // Left = 0
    code[depth] = '0';
    printCodes(root->left, code, depth + 1);

    // Right = 1
    code[depth] = '1';
    printCodes(root->right, code, depth + 1);
}

// Frees the tree memory
void deleteTree(Node* root) {
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    int n;

    cout << "Enter number of characters: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid number of characters.";
        return 0;
    }

    char* characters = new char[n];
    int* frequencies = new int[n];

    cout << "Enter characters and their frequencies:\n";

    for (int i = 0; i < n; i++) {
        cin >> characters[i] >> frequencies[i];
    }

    Node* root = buildHuffmanTree(characters, frequencies, n);

    char* code = new char[n + 1];

    cout << "\nHuffman Codes (Preorder):\n";
    printCodes(root, code, 0);

    deleteTree(root);
    delete[] characters;
    delete[] frequencies;
    delete[] code;

    return 0;
}