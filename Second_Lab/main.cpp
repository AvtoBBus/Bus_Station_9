#include <iostream>
#include <chrono>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <vector>
#include "sorts.h"

using namespace std;
using namespace chrono;

void write_in_file(const char *filename, int num_of_elem, double med_comparison, double med_copy)
{
    FILE *file = fopen(filename, "a");
    stringstream ss;
    ss << num_of_elem;
    ss << " ";
    ss << med_comparison;
    ss << " ";
    ss << med_copy;
    ss << "\n";
    string str_to_write = ss.str();
    fputs(str_to_write.c_str(), file);
    fclose(file);
}

int randomaizer(int last_x)
{
    int x = last_x;
    x = (1021 * x + 24631) % 116640 - 116640 / 2;
    return x;
}

void random_fill(vector<int> &mas, int size)
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    int x = (timeinfo->tm_sec + timeinfo->tm_hour + timeinfo->tm_min) / 3;

    for (int i = 0; i < size; i++)
    {
        x = randomaizer(x);
        mas.push_back(x);
    }
}

void fill_mass(vector<int> &mas, int size, bool reverse = false)
{
    if (!reverse)
    {
        for (int i = 0; i < size; i++)
            mas.push_back(i + 1);
    }
    else
    {
        for (int i = size; i > 0; i--)
            mas.push_back(i - 1);
    }
}

void beautiful_print(vector<int> &mas)
{
    int elem_to_print = 3;
    for (int i = 0; i < elem_to_print; i++)
        cout << mas[i] << " ";
    cout << "... ";
    for (int i = mas.size() - elem_to_print; i < mas.size(); i++)
        cout << mas[i] << " ";
}

void show_work(const char *type_of_mass)
{
    cout << "====PRESS ANY BUTTON====" << endl;
    cout << "==TO START CHANGE SORT==" << endl
         << endl;
    _getch();
    for (int i = 1000; i < 10001; i += 1000)
    {
        vector<int> mas;
        stats result;
        cout << endl
             << "===" << i << " ELEMENTS===";
        if (strcmp("random", type_of_mass) == 0)
            random_fill(mas, i);
        if (strcmp("sorted", type_of_mass) == 0)
            fill_mass(mas, i);
        if (strcmp("reversed", type_of_mass) == 0)
            fill_mass(mas, i, true);
        cout << endl;
        beautiful_print(mas);
        cout << endl;
        change_sort(&mas, result);
        beautiful_print(mas);
        cout << endl;
        cout << endl
             << "===COMPLETE===" << result.comparison_count << "=" << result.copy_count << endl;
    }
    for (int i = 25000; i < 100001; i *= 2)
    {
        vector<int> mas;
        stats result;
        cout << endl
             << "===" << i << " ELEMENTS===";
        if (strcmp("random", type_of_mass) == 0)
            random_fill(mas, i);
        if (strcmp("sorted", type_of_mass) == 0)
            fill_mass(mas, i);
        if (strcmp("reversed", type_of_mass) == 0)
            fill_mass(mas, i, true);
        cout << endl;
        beautiful_print(mas);
        cout << endl;
        change_sort(&mas, result);
        beautiful_print(mas);
        cout << endl;
        cout << endl
             << "===COMPLETE===" << result.comparison_count << "=" << result.copy_count << endl;
    }
    cout << endl;
    cout << "====PRESS ANY BUTTON====" << endl;
    cout << "==TO START SHELL SORT===" << endl
         << endl;
    _getch();
    for (int i = 1000; i < 10001; i += 1000)
    {
        vector<int> mas;
        stats result;
        cout << endl
             << "===" << i << " ELEMENTS===";
        if (strcmp("random", type_of_mass) == 0)
            random_fill(mas, i);
        if (strcmp("sorted", type_of_mass) == 0)
            fill_mass(mas, i);
        if (strcmp("reversed", type_of_mass) == 0)
            fill_mass(mas, i, true);
        cout << endl;
        beautiful_print(mas);
        cout << endl;
        shell_sort(&mas, result);
        beautiful_print(mas);
        cout << endl;
        cout << endl
             << "COMPLETE===" << result.comparison_count << "=" << result.copy_count << endl;
    }
    for (int i = 25000; i < 100001; i *= 2)
    {
        vector<int> mas;
        stats result;
        cout << endl
             << "===" << i << " ELEMENTS===";
        if (strcmp("random", type_of_mass) == 0)
            random_fill(mas, i);
        if (strcmp("sorted", type_of_mass) == 0)
            fill_mass(mas, i);
        if (strcmp("reversed", type_of_mass) == 0)
            fill_mass(mas, i, true);
        cout << endl;
        beautiful_print(mas);
        cout << endl;
        shell_sort(&mas, result);
        beautiful_print(mas);
        cout << endl;
        cout << endl
             << "COMPLETE===" << result.comparison_count << "=" << result.copy_count << endl;
    }
    system("pause");
}

void sort(const char *type_of_mass)
{
    cout << "======CHANGE SORT=======" << endl;
    stats med_res;
    for (int j = 1000; j < 10001; j += 1000)
    {
        cout << endl
             << "====" << j << " ELEMENTS START====" << endl;
        duration<float> result;
        for (int i = 0; i < 100; i++)
        {
            stats help_res;
            vector<int> mas;
            if (strcmp("random", type_of_mass) == 0)
                random_fill(mas, j);
            if (strcmp("sorted", type_of_mass) == 0)
                fill_mass(mas, j);
            if (strcmp("reversed", type_of_mass) == 0)
                fill_mass(mas, j, true);

            auto start = high_resolution_clock::now();
            change_sort(&mas, help_res);
            auto end = high_resolution_clock::now();
            result += end - start;
            med_res.comparison_count += help_res.comparison_count;
            med_res.copy_count += help_res.copy_count;
            if (i % 4 == 0)
                cout << "=";
        }
        cout << "==" << med_res.comparison_count / 100;
        cout << "==" << med_res.copy_count / 100;
        cout << "==" << abs(result.count()) / 100 << "==" << endl;
        if (strcmp("random", type_of_mass) == 0)
            write_in_file("random_mass_change.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("sorted", type_of_mass) == 0)
            write_in_file("sorted_mass_change.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("reversed", type_of_mass) == 0)
            write_in_file("reversed_mass_change.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        med_res.comparison_count = 0;
        med_res.copy_count = 0;
    }
    for (int j = 25000; j < 100001; j *= 2)
    {
        cout << endl
             << "====" << j << " ELEMENTS START====" << endl;
        duration<float> result;
        for (int i = 0; i < 100; i++)
        {
            stats help_res;
            vector<int> mas;
            if (strcmp("random", type_of_mass) == 0)
                random_fill(mas, j);
            if (strcmp("sorted", type_of_mass) == 0)
                fill_mass(mas, j);
            if (strcmp("reversed", type_of_mass) == 0)
                fill_mass(mas, j, true);
            auto start = high_resolution_clock::now();
            change_sort(&mas, help_res);
            auto end = high_resolution_clock::now();
            result += end - start;
            med_res.comparison_count += help_res.comparison_count;
            med_res.copy_count += help_res.copy_count;
            if (i % 4 == 0)
                cout << "=";
        }
        cout << "==" << med_res.comparison_count / 100;
        cout << "==" << med_res.copy_count / 100;
        if (strcmp("random", type_of_mass) == 0)
            write_in_file("random_mass_change.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("sorted", type_of_mass) == 0)
            write_in_file("sorted_mass_change.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("reversed", type_of_mass) == 0)
            write_in_file("reversed_mass_change.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        cout << "==" << abs(result.count()) / 100 << "==" << endl;
        med_res.comparison_count = 0;
        med_res.copy_count = 0;
    }
    cout << endl
         << "======SHELL SORT=======" << endl;
    for (int j = 1000; j < 10001; j += 1000)
    {
        cout << endl
             << "====" << j << " ELEMENTS START====" << endl;
        duration<float> result;
        for (int i = 0; i < 100; i++)
        {
            stats help_res;
            vector<int> mas;
            if (strcmp("random", type_of_mass) == 0)
                random_fill(mas, j);
            if (strcmp("sorted", type_of_mass) == 0)
                fill_mass(mas, j);
            if (strcmp("reversed", type_of_mass) == 0)
                fill_mass(mas, j, true);
            auto start = high_resolution_clock::now();
            shell_sort(&mas, help_res);
            auto end = high_resolution_clock::now();
            result += end - start;
            med_res.comparison_count += help_res.comparison_count;
            med_res.copy_count += help_res.copy_count;
            if (i % 4 == 0)
                cout << "=";
        }
        cout << "==" << med_res.comparison_count / 100;
        cout << "==" << med_res.copy_count / 100;
        if (strcmp("random", type_of_mass) == 0)
            write_in_file("random_mass_shell.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("sorted", type_of_mass) == 0)
            write_in_file("sorted_mass_shell.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("reversed", type_of_mass) == 0)
            write_in_file("reversed_mass_shell.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        cout << "==" << abs(result.count()) / 100 << "==" << endl;
        med_res.comparison_count = 0;
        med_res.copy_count = 0;
    }
    for (int j = 25000; j < 100001; j *= 2)
    {
        cout << endl
             << "====" << j << " ELEMENTS START====" << endl;
        duration<float> result;
        for (int i = 0; i < 100; i++)
        {
            stats help_res;
            vector<int> mas;
            if (strcmp("random", type_of_mass) == 0)
                random_fill(mas, j);
            if (strcmp("sorted", type_of_mass) == 0)
                fill_mass(mas, j);
            if (strcmp("reversed", type_of_mass) == 0)
                fill_mass(mas, j, true);
            auto start = high_resolution_clock::now();
            shell_sort(&mas, help_res);
            auto end = high_resolution_clock::now();
            result += end - start;
            med_res.comparison_count += help_res.comparison_count;
            med_res.copy_count += help_res.copy_count;
            if (i % 4 == 0)
                cout << "=";
        }
        cout << "==" << med_res.comparison_count / 100;
        cout << "==" << med_res.copy_count / 100;
        if (strcmp("random", type_of_mass) == 0)
            write_in_file("random_mass_shell.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("sorted", type_of_mass) == 0)
            write_in_file("sorted_mass_shell.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        if (strcmp("reversed", type_of_mass) == 0)
            write_in_file("reversed_mass_shell.txt", j, med_res.comparison_count / 100, med_res.copy_count / 100);
        cout << "==" << abs(result.count()) / 100 << "==" << endl;
        med_res.comparison_count = 0;
        med_res.copy_count = 0;
    }
}

void start_all_test()
{
    cout << "======RANDOM MASS=======" << endl;
    duration<float> result;
    auto start = high_resolution_clock::now();
    sort("random");
    auto end = high_resolution_clock::now();
    result = end - start;
    cout << "===COMPLITED===TIME:" << abs(result.count()) << endl;

    cout << endl
         << "======SORTED MASS=======" << endl;
    start = high_resolution_clock::now();
    sort("sorted");
    end = high_resolution_clock::now();
    result = end - start;
    cout << "===COMPLITED===TIME:" << abs(result.count()) << endl;

    cout << endl
         << "=====REVERSED MASS======" << endl;
    start = high_resolution_clock::now();
    sort("reversed");
    end = high_resolution_clock::now();
    result = end - start;
    cout << "===COMPLITED===TIME:" << abs(result.count()) << endl;
    system("pause");
}

int check_input()
{
    int number;
    while (!(cin >> number) || (cin.peek() != '\n'))
    {
        cin.clear();
        while (cin.get() != '\n')
            ;
        cout << "Input error! Repeat please...\n";
        cout << "---> ";
    }
    return number;
}

void create_mass_menu()
{
    vector<int> mas;
    while (true)
    {
        vector<int> help_vec;
        stats result;
        duration<float> time_result;
        auto start = high_resolution_clock::now();
        auto end = high_resolution_clock::now();
        int input = 0;
        system("cls");
        cout << "MASS:" << endl;
        for (int i = 0; i < mas.size(); i++)
            cout << mas[i] << " ";
        cout << endl;
        cout << endl
             << "Key Button || FUNCTION" << endl;
        cout << "=======================" << endl;
        cout << "    [Q]    ||   ADD ELEMENT" << endl;
        if (mas.size() >= 2)
            cout << "    [W]    ||   START CHANGE SORT" << endl;
        if (mas.size() >= 2)
            cout << "    [E]    ||   START SHELL SORT" << endl;
        cout << "   [Esc]   ||   EXIT" << endl;
        int key = _getch();
        switch (key)
        {
        case 113: // q
            system("cls");
            cout << endl
                 << "=Input number=" << endl
                 << endl;
            input = check_input();
            mas.push_back(input);
            break;
        case 119: // w
            system("cls");
            cout << endl
                 << "======START CHANGE SORT=======" << endl
                 << endl;
            help_vec = mas;
            cout << "Before : ";
            for (int i = 0; i < help_vec.size(); i++)
                cout << help_vec[i] << " ";
            start = high_resolution_clock::now();
            change_sort(&help_vec, result);
            end = high_resolution_clock::now();
            time_result = end - start;
            cout << endl
                 << "After : ";
            for (int i = 0; i < help_vec.size(); i++)
                cout << help_vec[i] << " ";
            cout << endl
                 << "\n==Result==\nComprasion count = " << result.comparison_count << "\nCopy count = " << result.copy_count << "\nWork time = " << abs(time_result.count()) << endl;
            system("pause");
            break;
        case 101: // e
            system("cls");
            cout << endl
                 << "======START SHELL SORT=======" << endl
                 << endl;
            help_vec = mas;
            cout << "Before : ";
            for (int i = 0; i < help_vec.size(); i++)
                cout << help_vec[i] << " ";
            start = high_resolution_clock::now();
            shell_sort(&help_vec, result);
            end = high_resolution_clock::now();
            time_result = end - start;
            cout << endl
                 << "After : ";
            for (int i = 0; i < help_vec.size(); i++)
                cout << help_vec[i] << " ";
            cout << endl
                 << "\n==Result==\nComprasion count = " << result.comparison_count << "\nCopy count = " << result.copy_count << "\nWork time = " << abs(time_result.count()) << endl;
            system("pause");
            break;
        case 27:
            return;
        }
    }
}

int main()
{
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    while (true)
    {
        system("cls");
        cout << endl
             << "Key Button || FUNCTION" << endl;
        cout << "=======================" << endl;
        cout << "    [Q]    ||   RANDOM MASS" << endl;
        cout << "    [W]    ||   SORTED MASS" << endl;
        cout << "    [E]    ||   REVERSED MASS" << endl;
        cout << "    [R]    ||   CREATE MASS" << endl;
        cout << "    [A]    ||   START ALL TEST" << endl;
        cout << "   [Esc]   ||   EXIT" << endl;
        int key = _getch();
        switch (key)
        {
        case 113:
            system("cls");
            cout << "======RANDOM MASS=======" << endl
                 << endl;
            show_work("random");
            break;
        case 119:
            system("cls");
            cout << "======SORTED MASS=======" << endl
                 << endl;
            show_work("sorted");
            break;
        case 101:
            system("cls");
            cout << "=====REVERSED MASS======" << endl
                 << endl;
            show_work("reversed");
            break;
        case 114:
            create_mass_menu();
            break;
        case 97:
            system("cls");
            cout << "==START TIME " << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "==" << endl;
            start_all_test();
            cout << "==END TIME " << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec << "==" << endl;
            system("pause");
            break;
        case 27:
            return 0;
        }
    }
}