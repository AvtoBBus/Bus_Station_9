#pragma once
#include <iostream>

using namespace std;

template <class T>
struct Node
{
    T data;
    Node *left;
    Node *right;
    Node *prev;

    Node(T data = (T)0, Node *prev = nullptr, Node *left = nullptr, Node *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
        this->prev = prev;
    }
};

template <class T>
class BinTree
{
private:
    Node<T> *root;
    void recursion_copy(Node<T> *obj);
    Node<T> *find_min_in_right(Node<T> *obj);

public:
    BinTree();
    BinTree(const BinTree &obj);

    Node<T> &get_root();
    void set_root(Node<T> *root);
    void clear(Node<T> **root);
    void insert(T data);
    void print(Node<T> *root, int side, int level);
    Node<T> *search(T data);
    bool contains(const Node<T> *obj);
    void erase(T data);
    BinTree &operator=(const BinTree &obj);
    ~BinTree();
};