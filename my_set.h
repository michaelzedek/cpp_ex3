//
// Created by Michael chachamtzedek on 9/18/18.
//

#ifndef CPP_EX3_MY_SET_H
#define CPP_EX3_MY_SET_H

#include <iostream>
#include <memory>
#include <vector>

template <class T> class my_set;
template <class T, bool REVERSE> class mySetIterator;

template <class T>
class my_set {

public:

    using const_iterator = mySetIterator<T, false>;
    using iterator = mySetIterator<T, false>;
    using const_reverse_iterator = mySetIterator<T, true>;
    typedef size_t size_type;
    friend mySetIterator<T, false>;
    friend mySetIterator<T, true>;
    my_set();
    my_set(my_set&& other) noexcept;
    my_set (const my_set& other);
    template <class InputIterator>
    my_set(InputIterator first, InputIterator last);

    size_type size() const noexcept {
        return _size;};

    bool empty() const noexcept {
        return size() == 0;};

    std::pair<const_iterator ,bool> insert(const T& val);

    std::pair<const_iterator ,bool> insert(T&& val);
    const_iterator insert(const_iterator position, const T& val);
    const_iterator insert(const_iterator position, T&& val);

    template <class InputIterator>
    void insert (InputIterator first, InputIterator last);

    iterator  erase (const_iterator position);
    size_type erase (const T& val);
    iterator  erase (const_iterator first, const_iterator last);
    void clear() noexcept;
    void swap(my_set& x);
    my_set&operator = (my_set & other);
    const_iterator find (const T& val) const;

    const_iterator cbegin() const noexcept{return mySetIterator<T, false>(_root);};

    const_iterator cend() const noexcept {return mySetIterator<T, false>();};

    const_reverse_iterator crbegin() const noexcept{return mySetIterator<T, true>(_root);};

    const_reverse_iterator crend() const noexcept{return nullptr;};




    class BstNode{
    public:
        using node = std::shared_ptr<BstNode>;
    public:
        BstNode(const T& data): _data(data) {}
        T _data;
        node _right = nullptr;
        node _left = nullptr;
        node _predecessor = nullptr;
    };
    using node = std::shared_ptr<BstNode>;

private:
    bool _findHelper(const T &val, node& cur) const;
    void _insertHelper(node& toInsert, node &position);
    node& _findNodeParent(const T &val);
    void _eraseHelper(node& toDelete, node& parent);
    size_type _size;
    node _root;
    node _tail;
};


template <class T, bool REVERSE>
class mySetIterator{
public:
    mySetIterator(typename my_set<T>::node &_cur);
    mySetIterator();
    mySetIterator<T, REVERSE>(typename my_set<T>::node &head, T& val);
    ~mySetIterator(){_it.clear();};
    T& operator*() const;
    T* operator->() const;
    mySetIterator& operator++();
    mySetIterator operator++(int);
    mySetIterator& operator--();
    mySetIterator operator--(int);
    bool operator==(mySetIterator& rhs);
    bool operator!=(mySetIterator& rhs);

    friend class my_set<T>;


private:
    typename my_set<T>::node _root;
    int _curIndex;
    unsigned long _size;
    std::vector<typename my_set<T>::node> _it;
    void _initIterator(typename my_set<T>::node& root);
    void _inOrderTraversalToVec(typename my_set<T>::node& root);
};


#endif //CPP_EX3_MY_SET_H
