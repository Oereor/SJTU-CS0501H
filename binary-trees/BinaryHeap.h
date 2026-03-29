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
    bool push(int item);
    int pop();
    [[nodiscard]] int size() const;
    [[nodiscard]] int peek() const;
    void clear();
private:
    static constexpr int DEFAULT_CAPACITY = 8;
    static constexpr double SHRINK_THRESHOLD = 0.25;
    int* m_Heap;
    int m_Size;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize(int targetCapacity);
    [[nodiscard]] int parent(int index) const;
    [[nodiscard]] int leftChild(int index) const;
    [[nodiscard]] int rightChild(int index) const;
};


#endif //BINARY_TREES_BINARYHEAP_H