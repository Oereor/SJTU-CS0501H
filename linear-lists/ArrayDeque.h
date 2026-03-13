//
// Created by unkn0 on 2026-03-13.
//

#ifndef LINEAR_LISTS_ARRAYDEQUE_H
#define LINEAR_LISTS_ARRAYDEQUE_H

template <typename Object>
class ArrayDeque {
public:
    ArrayDeque();
    explicit ArrayDeque(int capacity);
    ~ArrayDeque();
    [[nodiscard]] int size() const;
    bool isEmpty() const;
    void addFirst(const Object& item);
    void addLast(const Object& item);
    const Object& removeFirst();
    const Object& removeLast();
    const Object& getFirst() const;
    const Object& getLast() const;
    void clear();
private:
    static constexpr int DEFAULT_CAPACITY = 4;
    int m_Size;
    int m_Capacity;
    Object* m_Items;
    void checkCapacity();
    void resize(int targetCapacity);
    void increasePointer(int& pointer) const;
    void decreasePointer(int& pointer) const;
    int m_Head;
    int m_Tail;
};


#endif //LINEAR_LISTS_ARRAYDEQUE_H