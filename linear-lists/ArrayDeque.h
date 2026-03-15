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
    [[nodiscard]] bool isEmpty() const;
    void addFirst(const Object& item);
    void addLast(const Object& item);
    bool removeFirst();
    bool removeLast();
    const Object& getFirst() const;
    const Object& getLast() const;
    void clear();
private:
    static constexpr int DEFAULT_CAPACITY = 4;
    static constexpr double SHRINK_THRESHOLD = 0.25;
    int m_Size;
    int m_Capacity;
    Object* m_Items;
    void checkCapacity();
    void resize(int targetCapacity);
    void increasePointer(int& pointer) const;
    void decreasePointer(int& pointer) const;
    [[nodiscard]] int queueIndex(int index) const;
    int m_Head; // points to the start of items
    int m_Tail; // points to the place just after the last item
};


#endif //LINEAR_LISTS_ARRAYDEQUE_H