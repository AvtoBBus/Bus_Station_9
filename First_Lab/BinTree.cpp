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
Node<T> &BinTree<T>::get_root()
{
    return *(this->root);
}

template <class T>
void BinTree<T>::set_root(Node<T> *root)
{
    this->root = root;
}

template <class T>
void BinTree<T>::clear(Node<T> **root)
{
    if ((*root)->left != nullptr)
        clear(&((*root)->left));
    if ((*root)->right != nullptr)
        clear(&((*root)->right));
    delete (*root);
    (*root) = nullptr;
}

template <class T>
bool BinTree<T>::insert(T data)
{
    if (!root)
    {
        root = new Node<T>(data);
        return true;
    }
    Node<T> *tmp = root;
    tmp->prev = nullptr;

    while (tmp)
    {
        if (tmp->data == data)
            return false;
        if (tmp->data < data)
        {
            if (tmp->right)
                tmp = tmp->right;
            else
            {
                tmp->right = new Node<T>(data, tmp);
                return true;
            }
        }
        if (tmp->data > data)
        {
            if (tmp->left)
                tmp = tmp->left;
            else
            {
                tmp->left = new Node<T>(data, tmp);
                return true;
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

        else
        {
            if (tmp->data < data)
                tmp = tmp->right;
            else
            {
                if (tmp->data > data)
                    tmp = tmp->left;
            }
        }
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
        return;
    Node<T> *erase_root = search(data);
    if (erase_root == nullptr)
        return;
    if (erase_root == root)
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            root = nullptr;
            return;
        }
        if (erase_root->left != nullptr && erase_root->right == nullptr)
        {
            root = root->left;
            delete erase_root;
            return;
        }
        if (erase_root->left == nullptr && erase_root->right != nullptr)
            root = root->right;
        delete erase_root;
        return;
    }

    if (erase_root->left == nullptr && erase_root->right == nullptr)
    {
        Node<T> *parent_erase = erase_root->prev;
        if (parent_erase->left == erase_root)
            parent_erase->left = nullptr;
        else
            parent_erase->right = nullptr;
        delete erase_root;
        return;
    }

    if (erase_root->left != nullptr && erase_root->right == nullptr)
    {
        Node<T> *parent_erase = erase_root->prev;
        if (parent_erase->left == erase_root)
            parent_erase->left = erase_root->left;
        else
            parent_erase->right = erase_root->left;
        delete erase_root;
        return;
    }
    if (erase_root->left == nullptr && erase_root->right != nullptr)
    {
        Node<T> *parent_erase = erase_root->prev;
        if (parent_erase->left == erase_root)
            parent_erase->left = erase_root->right;
        else
            parent_erase->right = erase_root->right;
        delete erase_root;
        return;
    }
    if (erase_root->left != nullptr && erase_root->right != nullptr)
    {
        Node<T> *min_node = find_min_in_right(erase_root->right);
        Node<T> *parent_min_node = min_node->prev;
        if (min_node->right == nullptr)
        {
            erase_root->data = min_node->data;
            if (parent_min_node->right == min_node)
                parent_min_node->right = nullptr;
            else
                parent_min_node->left = nullptr;
            delete min_node;
            return;
        }
        else
        {
            erase_root->data = min_node->data;
            if (parent_min_node->right == min_node)
                parent_min_node->right = min_node->right;
            else
                parent_min_node->left = min_node->right;

            delete min_node;
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
        clear(&root);
}

template struct Node<int>;
template struct Node<float>;
template struct Node<double>;
template class BinTree<int>;
template class BinTree<float>;
template class BinTree<double>;