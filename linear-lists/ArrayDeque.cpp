//
// Created by unkn0 on 2026-03-13.
//

#include "ArrayDeque.h"

template<typename Object>
ArrayDeque<Object>::ArrayDeque(const int capacity) {
    m_Capacity = capacity;
    m_Items = new Object[m_Capacity];
    m_Head = 0;
    m_Tail = 0;
    m_Size = 0;
}

template<typename Object>
ArrayDeque<Object>::ArrayDeque() {
    this(DEFAULT_CAPACITY);
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
    delete m_Items;
}

template<typename Object>
void ArrayDeque<Object>::addFirst(const Object &item) {
    checkCapacity();
    increasePointer(m_Head);
    m_Items[m_Head] = item;
    m_Size++;
}

template<typename Object>
void ArrayDeque<Object>::increasePointer(int &pointer) const {
    pointer = (pointer + 1) % m_Capacity;
}

template<typename Object>
void ArrayDeque<Object>::decreasePointer(int &pointer) const {
    pointer = (pointer - 1) % m_Capacity;
}


