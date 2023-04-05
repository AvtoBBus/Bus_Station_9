#include <iostream>
#include <conio.h>
#include <time.h>
#include "BinTree.h"

using namespace std;

template <class T>
void insert_root(BinTree<T> &obj, T data)
{
    obj.insert(data);
}

int third_level_menu()
{
    int choose = 0;
    while (choose < 1 && choose > 2)
    {
        system("cls");
        cout << "Choose first or second tree? (1-fisrt, 2-second)" << endl;
        cout << "---> ";
        cin >> choose;
    }
    return choose;
}

template <class T>
T input_data()
{
    T data = T(0);
    while (data == T(0))
    {
        cout << "Input data -> ";
        cin >> data;
    }
    return data;
}

template <class T>
void second_level_menu()
{
    while (true)
    {
        BinTree<T> first_tree;
        BinTree<T> second_tree;
        cout << "       FIRST TREE     " << endl;
        first_tree.print(first_tree.get_root(), 0, 0);
        cout << "      SECOND TREE     " << endl;
        second_tree.print(second_tree.get_root(), 0, 0);
        system("cls");
        cout << "Key Button || FUNCTION" << endl;
        cout << "=======================" << endl;
        cout << "    [Q]    ||   INSERT ROOT" << endl;
        cout << "    [W]    ||   FILL WITH RANDOM NUMBER" << endl;
        if (first_tree.get_root() || second_tree.get_root())
            cout << "    [E]    ||   ERASE 1 ROOT " << endl;
        if (first_tree.get_root() || second_tree.get_root())
            cout << "    [A]    ||   CLEAR FULL TREE" << endl;
        cout << "   [Esc]   || I don't wanna " << endl;
        int key = _getch();
        T input = (T)0;
        int choose = 0;
        switch (key)
        {
        case 113:
            input = input_data<T>();
            choose = third_level_menu();
            if (choose == 1)
                insert_root<T>(first_tree, input);
            else
                insert_root<T>(second_tree, input);
            break;
        case 50:
            break;
        case 101:
            break;
        case 27:
            system("cls");
            first_tree.clear(first_tree.get_root());
            second_tree.clear(second_tree.get_root());
            return;
        }
    }
}

int main()
{
    while (true)
    {
        system("cls");
        cout << "Chosse your fig...type of data" << endl
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
        case 50:
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