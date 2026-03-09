//
// Created by AP3RTUR3 WH3ATL3Y on 2026/3/9.
//

#ifndef LINEAR_LISTS_STACK_H
#define LINEAR_LISTS_STACK_H

template <class Type>
class Stack {
public:
    Stack();
    explicit Stack(int capacity);
    int size() const;
    void push(const Type& item);
    Type pop();
    Type peek() const;
    void clear();
    ~Stack();

private:
    static constexpr int DEFAULT_CAPACITY = 4;
    static constexpr double SHRINK_THRESHOLD = 0.25;
    int m_Size;
    int m_Capacity;
    Type* m_Items;

    void resize(int targetCapacity);
    void checkCapacity();
};

#endif //LINEAR_LISTS_STACK_H