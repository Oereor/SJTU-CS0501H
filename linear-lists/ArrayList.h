//
// Created by AP3RTUR3 WH3ATL3Y on 2026/3/9.
//

#ifndef LINEAR_LISTS_ARRAY_LIST_H
#define LINEAR_LISTS_ARRAY_LIST_H

#include "List.h"

template <class Type>
class ArrayList : public List<Type> {
public:
    ArrayList();
    explicit ArrayList(int capacity);
    ~ArrayList() override;
    void clear() override;
    int size() const override;
    void insert(int index, const Type& item) override;
    Type removeAt(int index) override;
    bool remove(const Type& item) override;
    bool contains(const Type& item) const override;
    int find(const Type& item) const override;
    Type get(int index) const override;
private:
    static constexpr int DEFAULT_CAPACITY = 4;
    static constexpr double SHRINK_THRESHOLD = 0.25;
    Type* m_Items;
    int m_Size;
    int m_Capacity;
    void resize(int targetCapacity);
    void checkSize();
};

#endif //LINEAR_LISTS_ARRAY_LIST_H