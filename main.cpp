#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include "BinTree.h"

using namespace std;

void third_level_menu(int *choose)
{
    while ((*choose) < 1 || (*choose) > 2)
    {
        system("cls");
        cout << "Choose first or second tree? (1-fisrt, 2-second)" << endl;
        cout << "---> ";
        cin >> (*choose);
    }
}

template <class T>
int node_count(Node<T> *root)
{
    if (root->left == NULL && root->right == NULL)
        return 1;
    int left, right;
    if (root->left != NULL)
        left = node_count(root->left);
    else
        left = 0;
    if (root->right != NULL)
        right = node_count(root->right);
    else
        right = 0;
    return left + right + 1;
}

template <class T>
void insert_root(BinTree<T> *obj, T data)
{
    obj->insert(data);
}

template <class T>
void random_fill(BinTree<T> *first_obj, BinTree<T> *second_obj)
{
    srand(time(NULL));
    int num_of_cells = rand() % 10 + 3;
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    for (int i = 0; i < num_of_cells; i++)
    {
        insert_root(first_obj, (T)(rand() % 10 * timeinfo->tm_sec));
        insert_root(second_obj, (T)(rand() % 10 * timeinfo->tm_sec));
    }
}

template <class T>
void add_to_set(Node<T> *root, T *set, int &index)
{
    if (root)
    {
        add_to_set<T>(root->left, set, index);
        set[index] = root->data;
        index++;
        add_to_set<T>(root->right, set, index);
    }
    else
        return;
}

template <class T>
void help_add(BinTree<T> *obj, T *first_set, int first_size, T *second_set, int second_size)
{
    for (int i = 0; i < first_size; i++)
    {
        obj->insert(first_set[i]);
    }
    for (int i = 0; i < second_size; i++)
    {
        obj->insert(second_set[i]);
    }
}

template <class T>
void doing_task(BinTree<T> *first_obj, BinTree<T> *second_obj, BinTree<T> *result_obj, int num_of_task)
{
    int first_size = node_count(&first_obj->get_root()), second_size = node_count(&second_obj->get_root());
    T *first_set, *second_set;
    if (first_size)
    {
        int index = 0;
        first_set = new T[first_size];
        add_to_set<T>(&first_obj->get_root(), first_set, index);
    }
    if (second_size)
    {
        int index = 0;
        second_set = new T[second_size];
        add_to_set<T>(&second_obj->get_root(), second_set, index);
    }
    if (num_of_task == 1)
    {
        BinTree<T> help_obj;
        help_add(&help_obj, first_set, first_size, second_set, second_size);
        (*result_obj) = help_obj;
        return;
    }
    else
    {
        int help_index = 0, res_index = 0;
        BinTree<T> help_obj;
        help_add(&help_obj, first_set, first_size, second_set, second_size);
        T *res_set = new T[node_count(&help_obj.get_root())];
        T *help_set = new T[node_count(&help_obj.get_root())];
        add_to_set(&help_obj.get_root(), res_set, res_index);

        for (int i = 0; i < res_index; i++)
            cout << res_set[i] << endl;
        cout << "=====" << endl;

        help_index = 0;
        for (int i = 0; i < first_size; i++)
        {
            for (int j = 0; j < second_size; j++)
            {
                if (first_set[i] == second_set[j])
                {
                    help_set[help_index] = first_set[i];
                    help_index++;
                }
            }
        }
        for (int i = 0; i < help_index; i++)
        {
            cout << help_set[i] << endl;
            for (int j = 0; j < res_index; j++)
            {
                if (help_set[i] == res_set[j])
                {
                    res_set[j] = (T)999999999;
                }
            }
        }
        cout << "=====" << endl;
        for (int i = 0; i < res_index; i++)
        {
            if (res_set[i] != (T)999999999)
                result_obj->insert(res_set[i]);
        }
    }
}

template <class T>
void input_data(T *data)
{
    while ((*data) == T(0))
    {
        cout << "Input data -> ";
        cin >> (*data);
    }
}

template <class T>
void second_level_menu()
{
    BinTree<T> first_tree;
    BinTree<T> second_tree;
    T input = (T)0;
    int choose = 0;
    while (true)
    {
        system("cls");
        BinTree<T> result_tree;
        cout << endl
             << "=======FIRST TREE=======" << endl;
        first_tree.print(&first_tree.get_root(), 0, 0);

        cout << endl
             << "=======SECOND TREE=======" << endl;
        second_tree.print(&second_tree.get_root(), 0, 0);

        cout << endl
             << "Key Button || FUNCTION" << endl;
        cout << "=======================" << endl;
        cout << "    [Q]    ||   INSERT ROOT" << endl;
        cout << "    [W]    ||   FILL WITH RANDOM NUMBER" << endl;
        if (&first_tree.get_root() || &second_tree.get_root())
            cout << "    [E]    ||   ERASE 1 ROOT " << endl;
        if (&first_tree.get_root() || &second_tree.get_root())
            cout << "    [A]    ||   CLEAR FULL TREE" << endl;
        if (&first_tree.get_root() || &second_tree.get_root())
            cout << "    [S]    ||   DOING TASK" << endl;
        if (&first_tree.get_root() || &second_tree.get_root())
            cout << "    [D]    ||   START ALL TEST" << endl;
        cout << "   [Esc]   || I don't wanna " << endl;
        int key = _getch();
        // cout << key;
        // system("pause");
        Node<T> *help_root;
        switch (key)
        {
        case 113: // q
            third_level_menu(&choose);
            input_data<T>(&input);
            if (choose == 1)
                insert_root<T>(&first_tree, input);
            else
                insert_root<T>(&second_tree, input);
            break;
        case 119: // w
            random_fill(&first_tree, &second_tree);
            break;
        case 101:
            break;
        case 115: // s
            cout << endl;
            system("cls");
            doing_task<T>(&first_tree, &second_tree, &result_tree, 1);
            result_tree.print(&result_tree.get_root(), 0, 0);
            system("pause");
            help_root = &result_tree.get_root();
            result_tree.clear(&help_root);
            result_tree.set_root(help_root);
            doing_task<T>(&first_tree, &second_tree, &result_tree, 2);
            result_tree.print(&result_tree.get_root(), 0, 0);
            system("pause");
            break;
        case 27: // esc
            help_root = &first_tree.get_root();
            first_tree.clear(&help_root);
            first_tree.set_root(help_root);
            help_root = &second_tree.get_root();
            second_tree.clear(&help_root);
            second_tree.set_root(help_root);
            return;
        }
        input = T(0);
        choose = 0;
    }
}

int main()
{
    while (true)
    {
        system("cls");
        cout << "Chosse type of data" << endl
             << endl;
        cout << "Key Button || DATA TYPE" << endl;
        cout << "=======================" << endl;
        cout << "    [Q]    ||   INT    " << endl;
        cout << "    [W]    ||   FLOAT  " << endl;
        cout << "    [E]    ||   DOUBLE " << endl;
        cout << "   [Esc]   || I don't wanna " << endl;
        int key = _getch();
        switch (key)
        {
        case 113:
            second_level_menu<int>();
            return 0;
        case 119:
            second_level_menu<float>();
            return 0;
        case 101:
            second_level_menu<double>();
            return 0;
        case 27:
            system("cls");
            return 0;
        }
    }
}