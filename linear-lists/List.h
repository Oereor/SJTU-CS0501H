//
// Created by AP3RTUR3 WH3ATL3Y on 2026/3/9.
//

#ifndef LINEAR_LISTS_LIST_H
#define LINEAR_LISTS_LIST_H

template <class Type>
class List {
public:
    virtual ~List() = default;
    virtual int size() const = 0;
    virtual void insert(int index, const Type& item) = 0;
    virtual Type removeAt(int index) = 0;
    virtual bool remove(const Type& item) = 0;
    virtual bool contains(const Type& item) const = 0;
    virtual int find(const Type& item) const = 0;
    virtual Type get(int index) const = 0;
    virtual void clear() = 0;
};


#endif //LINEAR_LISTS_LIST_H