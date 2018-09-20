//
// Created by Michael chachamtzedek on 9/18/18.
//

#include "my_set.h"


template <class T>
my_set<T>::my_set()
{}
template <class T>
my_set<T>::my_set(my_set &&other) noexcept
{
    _size = other._size;
    _root = other._root;
    other._size = 0;
    other._root = nullptr;
}
template <class T>
my_set<T>::my_set(const my_set<T> &other)
{
//    for(mySetIterator<T, false> it = other.cbegin(); it != other.cend(); ++it){
//        insert(*it);
//    }
}
template <class T>
template<class InputIterator>
my_set<T>::my_set(InputIterator first, InputIterator last)
{
    insert(first, last);
}
template <class T>
my_set<T>::size_type my_set<T>::size() const
{
    return _size;
}
template <class T>
void my_set<T>::swap(my_set& x) noexcept {
    std::swap(_root, x._root);
    size_type tmp = _size;
    _size = x._size;
    x._size = tmp;
}

my_set &my_set::operator=(my_set &other)
{
    swap(other);
    return *this;
}

template <class T>
bool my_set::empty() const
{
    return size() == 0;
}
template <class T>
std::pair<typename my_set<T>::const_iterator, bool> my_set<T>::insert(const T &val)
{
    if(!_findHelper(val, _root)){
        node toInsert = std::make_shared<BstNode>(val);
        node &predecessor = _findNodeParent(val);
        _insertHelper(toInsert, predecessor);
//        return std::make_pair(mySetIterator<T, false>(_root, val), false);
    }
    return std::make_pair(mySetIterator<T, false>(_root, val), false);

}
template <class T>
std::pair<typename my_set<T>::const_iterator, bool> my_set<T>::insert(T &&val)
{
    return insert(val);
}
template <class T>
typename my_set<T>::const_iterator my_set<T>::insert(const_iterator position, const T &val)
{
    if(*position > val && val > position._it[position._curIndex]->right->_data){
        node toInsert = std::make_shared<BstNode>(val);
        _insertHelper(toInsert, position._it[position._curIndex]);
        return mySetIterator<T, false>(_root, val);
    }
    return insert(val).first;
}
template <class T>
my_set<T>::const_iterator my_set<T>::insert(const_iterator position, T &&val)
{
    return insert(position, val);
}

template <class T>
template<class InputIterator>
void my_set<T>::insert(InputIterator first, InputIterator last)
{
    while (*first < *last){
        insert(*first);
        ++first;
    }
}
template <class T>
my_set<T>::iterator my_set<T>::erase(const_iterator position)
{
    return my_set::iterator();
}
template <class T>
my_set<T>::size_type my_set<T>::erase(const T &val)
{
    if(!_findHelper(val, _root)){
        return 0;
    }
    node toDelete = nullptr;
    node parent = nullptr;
    if (_root->_data == val){
        toDelete = _root;
    }
    else{
        parent = _findNodeParent(val);
        toDelete = (parent->_data > val) ? parent->_left : parent->_right;
    }
    _eraseHelper(toDelete, parent);
    return 1;
}
template <class T>
my_set<T>::iterator my_set<T>::erase(const_iterator first, const_iterator last)
{
    return my_set::iterator();
}
template <class T>
void my_set<T>::clear()
{
    erase(cbegin(), cend());
}

template <class T>
typename my_set<T>::const_iterator my_set<T>::find(const T &val) const
{
    if(_findHelper(val, _root)){

        return my_set::const_iterator(_root ,val);
    }
    else {
        return my_set::const_iterator();
    }
}
template <class T>
bool my_set<T>::_findHelper(const T &val, node& cur) const{
    if (cur == nullptr || cur->_data == nullptr){
        return false;
    }
    else if (cur->_data == val){
        return true;
    }
    else if (cur->_data > val){
        return _findHelper(val, cur->_left);
    }
    else {
        return _findHelper(val, cur->_right);
    }
}
template <class T>
void my_set<T>::_insertHelper(node& toInsert, node& predecessor){
    if (_root == nullptr){
        _root = toInsert;
    }
    else if (predecessor->_data > toInsert->_data){
        if (predecessor->_right != nullptr){
            toInsert->_right = predecessor->_right;
        }
        predecessor->_right = toInsert;
    }
    else{
        if (predecessor->_left != nullptr){
            toInsert->_left = predecessor->_left;
        }
        predecessor->_left = toInsert;
    }
    ++_size;
}
template <class T>
typename my_set<T>::node& my_set<T>::_findNodeParent(const T &val)
{
    if (_root == nullptr){
        return _root;
    }
    node pos = nullptr;
    node cur = _root;
    while (pos == nullptr){
        if (cur->_data > val){
            if (cur ->_right == nullptr || cur ->_right ->_data < val){
                pos = cur;
            }
            else {
                cur = cur ->_right;
            }
        }
        else {
            if (cur->_left == nullptr || cur ->_left ->_data < val){
                pos = cur;
            }
            else {
                cur = cur ->_left;
            }
            
        }
    }
    
    return pos;
}
template <class T>
void my_set::_eraseHelper(node& toDelete, node& parent){
    // in case of the root
    if (parent == nullptr){

    }
}

template <class T, bool REVERSE>
T &mySetIterator::operator*() const
{
    return _it[_curIndex]->_data;
}
template <class T, bool REVERSE>
mySetIterator<T, REVERSE>::mySetIterator<T, REVERSE>(const my_set<T>::node &head)
{
    _initIterator(head);
}
template <class T, bool REVERSE>
mySetIterator<T, REVERSE>::mySetIterator<T, REVERSE>(const my_set<T>::node &head, const T& val){
    _initIterator(head);
    if(val != nullptr){
        while (_it[_size] != val){
            ++(*this);
        }
    }

};



template <class T, bool REVERSE>
T *mySetIterator::operator->() const
{
    return &_it[_curIndex]->_data;
}

template <class T, bool REVERSE>
mySetIterator &mySetIterator::operator++()
{
    if (REVERSE && _size > 0){
        --_size;
    }
    else if(!REVERSE && _size < _it.size()){
        ++_size;
    }
    return *this;
}
template <class T, bool REVERSE>
mySetIterator mySetIterator::operator++(int)
{
    mySetIterator temp(*this);
    operator++();
    return temp;
}
template <class T, bool REVERSE>
mySetIterator &mySetIterator::operator--()
{
    if (REVERSE && _size < _it.size()){
        ++_size;
    }
    else if(!REVERSE && _size > 0){
        ++_size;
    }
    return *this;
}

mySetIterator mySetIterator::operator--(int)
{
    mySetIterator temp(*this);
    operator--();
    return temp;
}

bool mySetIterator::operator==(mySetIterator& const rhs)
{
    return _it[_size] == rhs._it[rhs._size];
}

bool mySetIterator::operator!=(mySetIterator& const rhs)
{
    return _it[_size] != rhs._it[rhs._size];;
}

void mySetIterator::_inOrderTraversalToVec(const my_set::node& root)
{
    if (root == nullptr){
        return;
    }

    _inOrderTraversalToVec(root->_left);
    _it.push_back(root);
    _inOrderTraversalToVec(root->_right);
}

void mySetIterator::_initIterator(const my_set::node& root){
    _inOrderTraversalToVec(root);
    _size = _it.size();
}