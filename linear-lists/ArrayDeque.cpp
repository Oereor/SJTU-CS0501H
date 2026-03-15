//
// Created by unkn0 on 2026-03-13.
//

#include "ArrayDeque.h"

template<typename Object>
ArrayDeque<Object>::ArrayDeque(const int capacity) {
    m_Capacity = capacity >= DEFAULT_CAPACITY ? capacity : DEFAULT_CAPACITY;
    m_Items = new Object[m_Capacity];
    m_Head = 0;
    m_Tail = 1;
    m_Size = 0;
}

template<typename Object>
ArrayDeque<Object>::ArrayDeque() {
    m_Capacity = DEFAULT_CAPACITY;
    m_Items = new Object[m_Capacity];
    m_Head = 0;
    m_Tail = 1;
    m_Size = 0;
}

template<typename Object>
int ArrayDeque<Object>::size() const {
    return m_Size;
}

template<typename Object>
bool ArrayDeque<Object>::isEmpty() const {
    return m_Size == 0;
}

template<typename Object>
ArrayDeque<Object>::~ArrayDeque() {
    m_Head = 0;
    m_Tail = 0;
    m_Size = 0;
    m_Capacity = 0;
    delete[] m_Items;
}

template<typename Object>
void ArrayDeque<Object>::addFirst(const Object &item) {
    checkCapacity();
    decreasePointer(m_Head);
    m_Items[queueIndex(m_Head)] = item;
    m_Size++;
}

template<typename Object>
void ArrayDeque<Object>::addLast(const Object &item) {
    checkCapacity();
    increasePointer(m_Tail);
    m_Items[queueIndex(m_Tail - 1)] = item;
    m_Size++;
}

template<typename Object>
const Object &ArrayDeque<Object>::getFirst() const {
    if (this->isEmpty()) {
        return nullptr;
    }

    return m_Items[queueIndex(m_Head)];
}

template<typename Object>
const Object &ArrayDeque<Object>::getLast() const {
    if (this->isEmpty()) {
        return nullptr;
    }

    return m_Items[queueIndex(m_Tail - 1)];
}

template<typename Object>
bool ArrayDeque<Object>::removeFirst() {
    if (this->isEmpty()) {
        return false;
    }

    increasePointer(m_Head);
    m_Size--;
    checkCapacity();
    return true;
}

template<typename Object>
bool ArrayDeque<Object>::removeLast() {
    if (this->isEmpty()) {
        return false;
    }

    decreasePointer(m_Tail);
    m_Size--;
    checkCapacity();
    return true;
}

template<typename Object>
void ArrayDeque<Object>::clear() {
    const Object* originalItems = m_Items;
    m_Items = new Object[m_Capacity];
    m_Head = 0;
    m_Tail = 1;
    m_Size = 0;
    delete[] originalItems;
}

template<typename Object>
void ArrayDeque<Object>::increasePointer(int &pointer) const {
    pointer = (pointer + 1) % m_Capacity;
}

template<typename Object>
void ArrayDeque<Object>::decreasePointer(int &pointer) const {
    pointer = (pointer - 1) % m_Capacity;
}

template<typename Object>
int ArrayDeque<Object>::queueIndex(const int index) const {
    return index % m_Capacity;
}

template<typename Object>
void ArrayDeque<Object>::resize(const int targetCapacity) {
    Object* originalItems = m_Items;
    m_Capacity = targetCapacity;
    m_Items = new Object[targetCapacity];
    for (int i = 0, p = m_Head; p != m_Tail; i++, increasePointer(p)) {
        m_Items[i] = originalItems[queueIndex(p)];
    }
    delete[] originalItems;
}

template<typename Object>
void ArrayDeque<Object>::checkCapacity() {
    if (m_Size >= m_Capacity - 1) {
        resize(m_Capacity * 2);
    }
    else if (m_Size / static_cast<double>(m_Capacity) < SHRINK_THRESHOLD && m_Capacity >= DEFAULT_CAPACITY * 2) {
        resize(m_Capacity / 2 + 1);
    }
}

