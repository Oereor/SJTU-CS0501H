//
// Created by Oereor on 2026/3/9.
//

#ifndef LINEAR_LISTS_LINKEDLIST_H
#define LINEAR_LISTS_LINKEDLIST_H
#include "List.h"

template <class Type>
class LinkedList : public List<Type> {
public:
    LinkedList();
    ~LinkedList() override;
    void clear() override;
    [[nodiscard]] int size() const override;
    void insert(int index, const Type& item) override;
    void insertFront(const Type& item);
    void insertBack(const Type& item);
    Type removeAt(int index) override;
    bool remove(const Type& item) override;
    bool contains(const Type& item) const override;
    int find(const Type& item) const override;
    Type get(int index) const override;
private:
    struct Node {
        Type data;
        Node* prev;
        Node* next;
        Node(const Type& data, const Node* prev, const Node* next) {
            this->data = data;
            this->prev = prev;
            this->next = next;
        }
        explicit Node(const Type& data) {
            this(data, nullptr, nullptr);
        }
    };
    Node* m_Head;
    Node* m_Tail;
    int m_Size;
    void insert(const Node* node, const Type& data);
    void remove(const Node* node);
    Node* getNode(int index) const;
};

#endif //LINEAR_LISTS_LINKEDLIST_H