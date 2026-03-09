//
// Created by Oereor on 2026/3/9.
//
#include "Stack.h"

template<class Type>
Stack<Type>::Stack() {
    this(DEFAULT_CAPACITY);
}

template<class Type>
Stack<Type>::Stack(const int capacity) {
    m_Items = new Type[capacity];
    m_Capacity = capacity;
    m_Size = 0;
}

template<class Type>
void Stack<Type>::push(const Type &item) {
    checkCapacity();
    m_Items[m_Size] = item;
    m_Size++;
}

template<class Type>
void Stack<Type>::resize(const int targetCapacity) {
    const Type* originalItems = m_Items;
    Type* newItems = new Type[targetCapacity];
    for (int i = 0; i < m_Size; i++) {
        newItems[i] = m_Items[i];
    }
    m_Items = newItems;
    m_Capacity = targetCapacity;
    delete[] originalItems;
}

template<class Type>
Type Stack<Type>::peek() const {
    if (m_Size == 0) {
        throw;
    }
    return m_Items[m_Size - 1];
}

template<class Type>
Type Stack<Type>::pop() {
    if (m_Size == 0) {
        throw;
    }
    Type* resultPtr = &m_Items[m_Size - 1];
    m_Size--;
    checkCapacity();
    return *resultPtr;
}

template<class Type>
void Stack<Type>::checkCapacity() {
    if (m_Size >= m_Capacity) {
        resize(2 * m_Capacity);
    }
    else if (m_Size / static_cast<double>(m_Capacity) < SHRINK_THRESHOLD) {
        resize(m_Capacity / 2 + 1);
    }
}

template<class Type>
int Stack<Type>::size() const {
    return m_Size;
}

template<class Type>
void Stack<Type>::clear() {
    m_Size = 0;
    const Type* originalItems = m_Items;
    m_Items = new Type[m_Capacity];
    delete[] originalItems;
}

template<class Type>
Stack<Type>::~Stack() {
    delete[] m_Items;
}
