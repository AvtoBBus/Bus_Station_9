#include <iostream>
#include <conio.h>
#include <string>
#include "interface.h"
#include "graph.h"

using namespace std;

int main()
{
    Graph graph;
    string func_mas[1] = {"none"};
    Interface fl_menu(func_mas, 1);
    string name1 = "1";
    graph.add_vertex(name1);
    string name2 = "2";
    graph.add_vertex(name2);
    graph.add_edge(name1, name2, 1.0);
    graph.print_graph();
    system("pause");
    fl_menu.print_menu();
}