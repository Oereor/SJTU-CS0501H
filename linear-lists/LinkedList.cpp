//
// Created by AP3RTUR3 WH3ATL3Y on 2026/3/9.
//

#include "LinkedList.h"

template<class Type>
LinkedList<Type>::LinkedList() {
    m_Head = new Node(nullptr);
    m_Tail = new Node(nullptr);
    m_Size = 0;
    m_Head->next = m_Tail;
    m_Tail->prev = m_Head;
}

template<class Type>
LinkedList<Type>::~LinkedList() {
    Node* currNode = m_Head;
    while (currNode != nullptr) {
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

template<class Type>
void LinkedList<Type>::clear() {
    Node* currNode = m_Head->next;
    while (currNode != m_Tail) {
        Node* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
    m_Head->next = m_Tail;
    m_Tail->prev = m_Head;
    m_Size = 0;
}

template<class Type>
int LinkedList<Type>::size() const {
    return m_Size;
}

template<class Type>
LinkedList<Type>::Node *LinkedList<Type>::getNode(const int index) const {
    if (index < 0 || index >= m_Size) {
        return nullptr;
    }
    Node* curr = m_Head->next;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr;
}

template<class Type>
void LinkedList<Type>::insert(const Node *node, const Type& data) {
    Node* nextNode = node->next;
    Node* newNode = new Node(data, node, nextNode);
    node->next = newNode;
    nextNode->prev = newNode;
    m_Size++;
}

template<class Type>
void LinkedList<Type>::remove(const Node *node) {
    Node* prevNode = node->prev;
    Node* nextNode = node->next;
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete node;
    m_Size--;
}

template<class Type>
Type LinkedList<Type>::removeAt(const int index) {
    if (index < 0 || index >= m_Size) {
        throw;
    }
    Node* targetNode = getNode(index);
    Type* result = &targetNode->data;
    remove(targetNode);
    return *result;
}

template<class Type>
void LinkedList<Type>::insert(const int index, const Type &item) {
    if (index < 0 || index >= m_Size) {
        throw;
    }
    const Node* targetNode = getNode(index);
    insert(targetNode, item);
}

template<class Type>
Type LinkedList<Type>::get(int index) const {
    if (index < 0 || index >= m_Size) {
        throw;
    }
    return getNode(index)->data;
}
