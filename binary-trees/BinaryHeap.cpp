//
// Created by oereor on 2026-03-21.
//

#include "BinaryHeap.h"

#include <stdexcept>
#include <variant>

BinaryHeap::BinaryHeap(const int capacity) {
    m_Heap = new int[capacity + 1];
    m_Capacity = capacity;
    m_Size = 0;
}

BinaryHeap::BinaryHeap() {
    m_Heap = new int[DEFAULT_CAPACITY + 1];
    m_Capacity = DEFAULT_CAPACITY;
    m_Size = 0;
}

int BinaryHeap::parent(const int index) {
    if (index == 1) {
        return -1;
    }
    return index / 2;
}

int BinaryHeap::leftChild(const int index) {
    return index * 2;
}

int BinaryHeap::rightChild(const int index) {
    return index * 2 + 1;
}

void BinaryHeap::clear() {
    const int* originalHeap = m_Heap;
    const int capacity = m_Capacity;
    m_Heap = new int[capacity + 1];
    m_Capacity = capacity;
    m_Size = 0;
    delete[] originalHeap;
}

int BinaryHeap::peek() const {
    if (isEmpty()) {
        throw;
    }

    return m_Heap[1];
}

bool BinaryHeap::isEmpty() const {
    return m_Size == 0;
}

int BinaryHeap::size() const {
    return m_Size;
}

void BinaryHeap::resize(const int targetCapacity) {
    const int* originalHeap = m_Heap;
    m_Heap = new int[targetCapacity + 1];
    m_Capacity = targetCapacity;
    for (int i = 1; i <= m_Size; i++) {
        m_Heap[i] = originalHeap[i];
    }
    delete[] originalHeap;
}

BinaryHeap::~BinaryHeap() {
    delete[] m_Heap;
}

void BinaryHeap::heapifyUp(const int index) const {
    int curr = index, par = parent(curr);
    while (par != -1 && m_Heap[curr] < m_Heap[par]) {
        std::swap(m_Heap[curr], m_Heap[par]);
        curr = par;
        par = parent(curr);
    }
}

void BinaryHeap::heapifyDown(const int index) const {
    int curr = index;
    int lc = leftChild(curr), rc = rightChild(curr);
    while (lc <= m_Size) {
        int minChild = lc;
        if (rc <= m_Size && m_Heap[rc] < m_Heap[minChild]) {
            minChild = rc;
        }
        if (m_Heap[minChild] < m_Heap[curr]) {
            std::swap(m_Heap[minChild], m_Heap[curr]);
            curr = minChild;
            lc = leftChild(curr);
            rc = rightChild(curr);
        }
        else {
            break;
        }
    }
}

void BinaryHeap::push(const int item) {
    if (m_Size >= m_Capacity) {
        resize(2 * m_Capacity);
    }
    m_Size++;
    m_Heap[m_Size] = item;
    heapifyUp(m_Size);
}

int BinaryHeap::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty.");
    }
    const int result = m_Heap[1];
    std::swap(m_Heap[1], m_Heap[m_Size]);
    m_Size--;
    heapifyDown(1);
    if (m_Size >= 2 * DEFAULT_CAPACITY && m_Size < m_Capacity / 4) {
        resize(m_Capacity / 2);
    }
    return result;
}
