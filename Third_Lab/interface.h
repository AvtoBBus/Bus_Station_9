#pragma once
#include <iostream>
#include <conio.h>
#include <string>
using namespace std;

class Interface
{
private:
    string *func_mas;
    int size;
    struct Buttons
    {
        int func_key[10] = {
            113,
            119,
            101,
            114,
            97,
            115,
            100,
            122,
            120,
            99};
        const char *func_button[10] = {"[Q]", "[W]", "[E]", "[R]", "[A]", "[S]", "[D]", "[Z]", "[X]", "[C]"};
    };
    bool check_key(int key);

public:
    Interface(string *func_mas, int size);

    int print_menu(string str_to_append);
};