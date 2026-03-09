#include "ArrayList.h"
//
// Created by AP3RTUR3 WH3ATL3Y on 2026/3/9.
//
template<class Type>
ArrayList<Type>::ArrayList() {
    this(DEFAULT_CAPACITY);
}

template<class Type>
ArrayList<Type>::ArrayList(const int capacity) {
    m_Capacity = capacity;
    m_Items = new Type[m_Capacity];
    m_Size = 0;
}

template<class Type>
ArrayList<Type>::~ArrayList() {
    delete[] m_Items;
}

template<class Type>
int ArrayList<Type>::size() const {
    return m_Size;
}

template<class Type>
void ArrayList<Type>::clear() {
    const Type* originalItems = m_Items;
    m_Items = new Type[m_Capacity];
    m_Size = 0;
    delete[] originalItems;
}

template<class Type>
void ArrayList<Type>::resize(const int targetCapacity) {
    const Type* originalItems = m_Items;
    m_Items = new Type[targetCapacity];
    for (int i = 0; i < m_Size; i++) {
        m_Items[i] = originalItems[i];
    }
    m_Capacity = targetCapacity;
    delete[] originalItems;
}

template<class Type>
void ArrayList<Type>::checkSize() {
    if (m_Size >= m_Capacity) {
        resize(2 * m_Capacity);
    }
    else if (m_Size / static_cast<double>(m_Capacity) < SHRINK_THRESHOLD) {
        resize(m_Capacity / 2 + 1);
    }
}

template<class Type>
void ArrayList<Type>::insert(const int index, const Type &item) {
    if (index < 0 || index > m_Size) {
        throw;
    }
    checkSize();
    for (int i = m_Size; i > index; i--) {
        m_Items[i] = m_Items[i - 1];
    }
    m_Items[index] = item;
}

template<class Type>
bool ArrayList<Type>::remove(const Type &item) {
    for (int i = 0; i < m_Size; i++) {
        if (m_Items[i] == item) {
            removeAt(i);
            return true;
        }
    }
    return false;
}

template<class Type>
Type ArrayList<Type>::removeAt(const int index) {
    if (index < 0 || index >= m_Size) {
        throw;
    }
    Type* result = &m_Items[index];
    for (int i = index; i < m_Size - 1; i++) {
        m_Items[i] = m_Items[i + 1];
    }
    checkSize();
    return *result;
}

template<class Type>
bool ArrayList<Type>::contains(const Type &item) const {
    for (int i = 0; i < m_Size; i++) {
        if (m_Items[i] == item) {
            return true;
        }
    }
    return false;
}

template<class Type>
int ArrayList<Type>::find(const Type &item) const {
    for (int i = 0; i < m_Size; i++) {
        if (m_Items[i] == item) {
            return i;
        }
    }
    return -1;
}

template<class Type>
Type ArrayList<Type>::get(const int index) const {
    if (index < 0 || index >= m_Size) {
        throw;
    }
    return m_Items[index];
}
