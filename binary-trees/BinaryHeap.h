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
    ~BinaryHeap();
    bool push(int item);
    int pop();
    [[nodiscard]] int size() const;
    [[nodiscard]] int peek() const;
    void clear();
private:
    int* heap;
    int m_Size;
    void heapifyUp(int index);
    void heapifyDown(int index);
    void resize(int targetCapacity);
};


#endif //BINARY_TREES_BINARYHEAP_H