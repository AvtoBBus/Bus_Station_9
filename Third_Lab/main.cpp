#include <iostream>
#include <conio.h>
#include <string>
#include "interface.h"
#include "graph.h"

#define FUNC_SIZE 9

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

bool check_str_input(string input_str)
{
    if (input_str.size() == 0 || input_str == " ")
        return false;
    return true;
}

int main()
{
    Graph graph;
    string func_mas[FUNC_SIZE] = {"ADD VERTEX", "DELETE VERTEX", "ADD EDGE", "DELETE EDGE", "CREATE RANDOM GRAPH", "CLEAR ALL", "WALK IN GRAPH", "FIND MIN PART", "FIND STORAGE"};
    Interface fl_menu(func_mas, FUNC_SIZE);
    while (true)
    {
        int input_weight = 0;
        string input_name;
        string input_name_to;
        int flag = 0;
        if (graph.all_vertex())
            flag = fl_menu.print_menu(graph.print_graph());
        else
            flag = fl_menu.print_menu("");
        if (flag == 113) // q
        {
            system("cls");
            cout << endl;
            cout << "Input vertex name ---> ";
            getline(cin, input_name);
            while (!check_str_input(input_name))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name);
            }
            try
            {
                graph.add_vertex(input_name);
            }
            catch (const char *error)
            {
                cout << error;
            }
            cout << endl;
        }
        if (flag == 119) // w
        {
            system("cls");
            cout << endl;
            cout << "Input vertex name ---> ";
            getline(cin, input_name);
            while (!check_str_input(input_name))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name);
            }
            try
            {
                graph.remove_vertex("vertex_1");
            }
            catch (const char *error)
            {
                cout << error;
            }
            cout << endl;
        }
        if (flag == 101) // e
        {
            system("cls");
            cout << endl;
            cout << "Input vertex name from  ---> ";
            getline(cin, input_name);
            while (!check_str_input(input_name))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name);
            }
            cout << "Input vertex name to ---> ";
            getline(cin, input_name_to);
            while (!check_str_input(input_name_to))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name_to);
            }
            cout << "Input weight ---> ";
            input_weight = check_input();
            try
            {
                graph.add_edge(input_name, input_name_to, input_weight);
            }
            catch (const char *error)
            {
                cout << error;
            }
            cout << endl;
        }
        if (flag == 114) // r
        {
            system("cls");
            cout << endl;
            cout << "Input vertex name from  ---> ";
            getline(cin, input_name);
            while (!check_str_input(input_name))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name);
            }
            cout << "Input vertex name to ---> ";
            getline(cin, input_name_to);
            while (!check_str_input(input_name_to))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name_to);
            }
            try
            {
                graph.remove_edge(input_name, input_name_to);
            }
            catch (const char *error)
            {
                cout << error;
            }
            cout << endl;
        }
        if (flag == 97) // a
        {
            if (graph.all_vertex())
            {
                string func[1] = {"Clear current Graph"};
                Interface sl_menu(func, 1);
                int key = sl_menu.print_menu("\nGraph is not empty!\n");
                if (key == 113)
                {
                    try
                    {
                        graph.clear_graph();
                    }
                    catch (const char *error)
                    {
                        cout << error << endl;
                    }
                    cout << "Graph clear" << endl;
                    cout << "Input vertex num ---> ";
                    int input_num = check_input();
                    graph.create_random_graph(input_num);
                }
                if (key == 27)
                    continue;
            }
            else
            {
                cout << "Input vertex num ---> ";
                int input_num = check_input();
                graph.create_random_graph(input_num);
            }
        }
        if (flag == 115) // s
        {
            try
            {
                graph.clear_graph();
            }
            catch (const char *error)
            {
                cout << error << endl;
            }
        }
        if (flag == 100) // d
        {
            cout << "Input start vertex name\n----> ";
            getline(cin, input_name);
            try
            {
                graph.walk(input_name);
                cout << endl;
            }
            catch (const char *error)
            {
                cout << error << endl;
            }
        }
        if (flag == 122) // z
        {
            cout << endl;
            cout << "Input vertex name from  ---> ";
            getline(cin, input_name);
            while (!check_str_input(input_name))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name);
            }
            cout << "Input vertex name to ---> ";
            getline(cin, input_name_to);
            while (!check_str_input(input_name_to))
            {
                cout << endl
                     << "Str is empty! Please repeat input ---> ";
                getline(cin, input_name_to);
            }
            try
            {
                vector<Graph::Edge> result = graph.shortest_path(input_name, input_name_to);
                double path_size = 0.0;
                cout << graph.find_vertex(input_name) + 1 << "->";
                for (auto iter = result.begin(); iter != result.end(); iter++)
                {
                    cout
                        << iter->id_destination + 1;
                    if (iter != result.end() - 1)
                        cout << "->";
                    path_size += iter->weight;
                }
                cout << endl
                     << "Path size = " << path_size;
            }
            catch (const char *error)
            {
                cout << error;
            }
            cout << endl;
        }
        if (flag == 120) // x
        {
            if (!graph.empty_graph())
            {
                try
                {
                    cout << graph.find_storage() << endl;
                }
                catch (const char *error)
                {
                    cout << error << endl;
                }
            }
        }
        if (flag == 27)
        {
            return 0;
        }
        system("pause");
    }
}