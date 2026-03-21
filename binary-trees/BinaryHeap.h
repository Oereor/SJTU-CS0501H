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
    bool push(int item);
    int pop();
};


#endif //BINARY_TREES_BINARYHEAP_H