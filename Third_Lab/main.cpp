#include <iostream>
#include <conio.h>
#include <string>
#include "interface.h"
#include "graph.h"

using namespace std;

int main()
{
    while (true)
    {
        Graph graph;
        string func_mas[2] = {"walk1", "walk2"};
        Interface fl_menu(func_mas, 2);
        string name1 = "1";
        string name2 = "2";
        string name3 = "3";
        string name4 = "4";
        string name5 = "5";
        string name6 = "6";
        string name7 = "7";
        graph.add_vertex(name1);
        graph.add_vertex(name2);
        graph.add_vertex(name3);
        graph.add_vertex(name4);
        graph.add_vertex(name5);
        graph.add_vertex(name6);
        graph.add_vertex(name7);
        graph.add_edge(name1, name2, 1.0);
        graph.add_edge(name1, name3, 1.0);
        graph.add_edge(name2, name4, 1.0);
        graph.add_edge(name3, name7, 1.0);
        graph.add_edge(name4, name6, 1.0);
        graph.add_edge(name2, name5, 1.0);

        int flag = fl_menu.print_menu(graph.print_graph());

        if (flag == 113)
        {
            graph.walk(name1);
            cout << endl;
        }
        if (flag == 119)
        {
            graph.walk(name2);
            cout << endl;
        }
        if (flag == 27)
        {
            return 0;
        }
        system("pause");
    }
}