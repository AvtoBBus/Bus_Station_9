#include "BinTree.h"
#include <iostream>

using namespace std;

template <class T>
void BinTree<T>::recursion_copy(Node<T> *obj)
{
    insert(obj->data);
    if (obj->left)
        recursion_copy(obj->left);
    if (obj->right)
        recursion_copy(obj->right);
}

template <class T>
Node<T> *BinTree<T>::find_min_in_right(Node<T> *obj)
{
    if (obj)
    {
        if (obj->right)
            return find_min_in_right(obj->right);
    }
    return obj;
}

template <class T>
BinTree<T>::BinTree()
{
    this->root = nullptr;
}

template <class T>
BinTree<T>::BinTree(const BinTree &obj)
{
    recursion_copy(obj.root);
}

template <class T>
Node<T> *BinTree<T>::get_root()
{
    return this->root;
}

template <class T>
void BinTree<T>::clear(Node<T> *root)
{
    if (root)
    {
        if (root->left)
            clear(root->left);
        if (root->right)
            clear(root->right);
        delete root;
    }
}

template <class T>
void BinTree<T>::insert(T data)
{
    if (!root)
    {
        root = new Node<T>(data);
        return;
    }
    Node<T> *tmp = root;
    tmp->prev = nullptr;

    while (tmp)
    {
        if (tmp->data == data)
            return;
        if (tmp->data < data)
        {
            if (tmp->right)
                tmp = tmp->right;
            else
            {
                tmp->right = new Node<T>(data, tmp);
                return;
            }
        }
        if (tmp->data > data)
        {
            if (tmp->left)
                tmp = tmp->left;
            else
            {
                tmp->left = new Node<T>(data, tmp);
                return;
            }
        }
    }
    throw "Error";
}

template <class T>
void BinTree<T>::print(Node<T> *root, int side, int level)
{
    if (root)
    {
        print(root->left, -1, level + 2);
        for (int i = 0; i < level; i++)
            cout << "   ";
        if (side == 0)
            cout << " -> " << root->data << "----------------------------------" << endl;
        if (side == 1)
            cout << " \\-> " << root->data << endl;
        if (side == -1)
            cout << " /-> " << root->data << endl;
        print(root->right, 1, level + 2);
    }
}

template <class T>
Node<T> *BinTree<T>::search(T data)
{
    if (!root)
        return nullptr;
    Node<T> *tmp = root;
    while (tmp)
    {
        if (tmp->data == data)
            return tmp;
        else if (tmp->data < data)
            tmp = tmp->right;
        else
            tmp = tmp->right;
    }
    return nullptr;
}

template <class T>
bool BinTree<T>::contains(const Node<T> *obj)
{
    return bool(search(obj->data));
}

template <class T>
void BinTree<T>::erase(T data)
{
    if (!root)
        throw "Error, empty tree";
    if (!search(data))
        throw "Error, incorrect index";

    Node<T> *node_to_delete = search(data);
    Node<T> *min_in_right_side = find_min_in_right(node_to_delete->right);
    if (node_to_delete->left && node_to_delete->right)
    {
        node_to_delete->data = min_in_right_side->data;
        min_in_right_side->prev->left = nullptr;
        delete min_in_right_side;
        min_in_right_side = nullptr;
        return;
    }
    else
    {
        if (node_to_delete->left || node_to_delete->right)
        {
            if (node_to_delete->left)
            {
                node_to_delete->data = node_to_delete->left->data;
                delete node_to_delete->left;
                node_to_delete->left = nullptr;
            }
            else
            {
                node_to_delete->data = node_to_delete->right->data;
                delete node_to_delete->right;
                node_to_delete->right = nullptr;
            }
            return;
        }
        else
        {
            if (!node_to_delete->prev)
            {
                delete node_to_delete;
                node_to_delete = nullptr;
                root = node_to_delete;
            }
            else
            {
                if (node_to_delete->prev->left == node_to_delete)
                    node_to_delete->prev->left = nullptr;
                else
                    node_to_delete->prev->right = nullptr;
                delete node_to_delete;
                node_to_delete = nullptr;
            }
            return;
        }
    }
}

template <class T>
BinTree<T> &BinTree<T>::operator=(const BinTree &obj)
{
    recursion_copy(obj.root);
    return *this;
}

template <class T>
BinTree<T>::~BinTree()
{
    if (root)
        clear(root);
}

template struct Node<int>;
template struct Node<float>;
template struct Node<double>;
template class BinTree<int>;
template class BinTree<float>;
template class BinTree<double>;