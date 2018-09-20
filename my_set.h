//
// Created by Michael chachamtzedek on 9/18/18.
//

#ifndef CPP_EX3_MY_SET_H
#define CPP_EX3_MY_SET_H

#include <opencl-c.h>
#include <iostream>

template <class T> class my_set;
template <class T, bool REVERSE> class mySetIterator;

template <class T>
class my_set {

public:

    using const_iterator = mySetIterator<T, false>;
    using iterator = mySetIterator<T, false>;
    using node = std::shared_ptr<BstNode>;
    using const_reverse_iterator = mySetIterator<T, true>;
    typedef size_t size_type;
    friend mySetIterator<T, false>;
    friend mySetIterator<T, true>;


    size_type size() const noexcept;

    bool empty() const noexcept;

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
    const_iterator find (const T& val) const;

    const_iterator cbegin() const noexcept;

    const_iterator cend() const noexcept;

    const_reverse_iterator crbegin() const noexcept;

    const_reverse_iterator crend() const noexcept;



private:


    int _size = 0;
    node _root = nullptr;
    node _tail = nullptr;
    class BstNode{
    public:
        BstNode(const T& data): _data(data) {}
        T _data;
        node _right = nullptr;
        node _left = nullptr;
        node _predecessor = nullptr;
        node _successor = nullptr;
    };

};

template <class T, bool REVERSE>
class mySetIterator{
public:
    mySetIterator(const my_set::node &_cur) : _cur(_cur) {};

    friend class my_set<T>;


private:
    my_set::node _cur;

};


#endif //CPP_EX3_MY_SET_H
