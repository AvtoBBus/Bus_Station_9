#include <iostream>
#include <conio.h>
#include <string>
#include "interface.h"
#include "graph.h"

#define FUNC_SIZE 6

using namespace std;

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

int main()
{
    Graph graph;
    string func_mas[FUNC_SIZE] = {"ADD VERTEX", "DELETE VERTEX", "ADD EDGE", "DELETE EDGE", "CLEAR ALL", "WALK IN GRAPH"};
    Interface fl_menu(func_mas, FUNC_SIZE);
    while (true)
    {
        // string name1 = "1";
        // string name2 = "2";
        // string name3 = "3";
        // string name4 = "4";
        // string name5 = "5";
        // string name6 = "6";
        // string name7 = "7";
        // graph.add_vertex(name1);
        // graph.add_vertex(name2);
        // graph.add_vertex(name3);
        // graph.add_vertex(name4);
        // graph.add_vertex(name5);
        // graph.add_vertex(name6);
        // graph.add_vertex(name7);
        // graph.add_edge(name1, name2, 1.0);
        // graph.add_edge(name1, name3, 1.0);
        // graph.add_edge(name2, name4, 1.0);
        // graph.add_edge(name3, name7, 1.0);
        // graph.add_edge(name4, name6, 1.0);
        // graph.add_edge(name2, name5, 1.0);
        int input_weight = 0;
        string input_name;
        int flag = 0;
        if (graph.all_vertex())
            flag = fl_menu.print_menu(graph.print_graph());
        else
            flag = fl_menu.print_menu("");
        if (flag == 113) // q
        {
            system("cls");
            cout << "Input vertex name --->";
            getline(cin, input_name);
            graph.add_vertex(input_name);
            cout << endl;
        }
        if (flag == 119) // e
        {
            cout << endl;
        }
        if (flag == 27)
        {
            return 0;
        }
        system("pause");
    }
}