#include <iostream>
using namespace std;

// Linked list node
class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = NULL;
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

        if (left < size && heap[left]->data < heap[smallest]->data)
            smallest = left;

        if (right < size && heap[right]->data < heap[smallest]->data)
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
        if (node == NULL || size == capacity)
            return;

        int i = size;
        heap[size] = node;
        size++;

        while (i > 0 && heap[i]->data < heap[(i - 1) / 2]->data) {
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

    bool isEmpty() {
        return size == 0;
    }

    ~MinHeap() {
        delete[] heap;
    }
};

// Merge K sorted linked lists
Node* mergeKLists(Node* lists[], int k) {

    MinHeap heap(k);

    // Insert the first node of every list
    for (int i = 0; i < k; i++) {
        if (lists[i] != NULL)
            heap.insert(lists[i]);
    }

    Node* head = NULL;
    Node* tail = NULL;

    while (!heap.isEmpty()) {

        // Get the smallest node
        Node* minimum = heap.extractMin();

        // Save the next node before disconnecting
        Node* nextNode = minimum->next;

        // Add minimum to the result list
        minimum->next = NULL;

        if (head == NULL) {
            head = minimum;
            tail = minimum;
        }
        else {
            tail->next = minimum;
            tail = minimum;
        }

        // Insert the next node from the same list
        if (nextNode != NULL)
            heap.insert(nextNode);
    }

    return head;
}

// Print the merged linked list
void printList(Node* head) {

    Node* temp = head;

    while (temp != NULL) {
        cout << temp->data;

        if (temp->next != NULL)
            cout << " -> ";

        temp = temp->next;
    }

    cout << " -> NULL" << endl;
}

int main() {

    int k;

    cout << "Enter number of linked lists: ";
    cin >> k;

    if (k <= 0) {
        cout << "Invalid number of lists.";
        return 0;
    }

    Node** lists = new Node*[k];

    // Input all linked lists
    for (int i = 0; i < k; i++) {

        int n;

        cout << "Enter number of nodes in list " << i + 1 << ": ";
        cin >> n;

        lists[i] = NULL;
        Node* tail = NULL;

        cout << "Enter sorted elements: ";

        for (int j = 0; j < n; j++) {

            int value;
            cin >> value;

            Node* newNode = new Node(value);

            if (lists[i] == NULL) {
                lists[i] = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    Node* result = mergeKLists(lists, k);

    cout << "\nMerged linked list:\n";
    printList(result);

    // Free memory
    while (result != NULL) {
        Node* temp = result;
        result = result->next;
        delete temp;
    }

    delete[] lists;

    return 0;
}
