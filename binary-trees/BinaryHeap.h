//
// Created by oereor on 2026-03-21.
//

#ifndef BINARY_TREES_BINARYHEAP_H
#define BINARY_TREES_BINARYHEAP_H

/**
 * Represents a min-heap based on binary tree.
 */
class BinaryHeap {
public:
    BinaryHeap();
    explicit BinaryHeap(int capacity);
    ~BinaryHeap();
    void push(int item);
    int pop();
    [[nodiscard]] int size() const;
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] int peek() const;
    void clear();
private:
    static constexpr int DEFAULT_CAPACITY = 8;
    /**
     * m_Heap[0] will store the capacity.
     */
    int* m_Heap;
    int m_Size;
    int m_Capacity;
    void heapifyUp(int index) const;
    void heapifyDown(int index) const;
    void resize(int targetCapacity);
    [[nodiscard]] static int parent(int index);
    [[nodiscard]] static int leftChild(int index);
    [[nodiscard]] static int rightChild(int index);
};


#endif //BINARY_TREES_BINARYHEAP_H