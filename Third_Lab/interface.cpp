#include <iostream>
#include <conio.h>
#include <string>
#include "interface.h"
#include "graph.h"
using namespace std;

bool Interface::check_key(int key)
{
    Buttons needed_buttons;
    for (int i = 0; i < this->size; i++)
    {
        if (key == needed_buttons.func_key[i])
            return true;
    }
    if (key == 27)
        return true;
    return false;
}

Interface::Interface(string *func_mas, int size)
{
    this->func_mas = func_mas;
    this->size = size;
}

int Interface::print_menu()
{
    Buttons buttons;
    while (true)
    {
        system("cls");
        cout << endl
             << "Key Button || FUNCTION" << endl;
        cout << "=======================" << endl;
        for (int i = 0; i < this->size; i++)
            cout << "    " << buttons.func_button[i] << "    ||    " << func_mas[i] << endl;
        cout << "   [Esc]   ||   Exit" << endl;
        int key = _getch();
        if (check_key(key))
            return key;
    }
}