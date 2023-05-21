#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>
#include "graph.h"
using namespace std;

int Graph::find_vertex(string name) const
{
    for (int i = 0; i < vertex.size(); i++)
    {
        if (vertex[i].name == name)
            return i;
    }
    return -1;
}
int Graph::find_edge(string name_from, string name_to) const
{
    int id_from = find_vertex(name_from);
    int id_to = find_vertex(name_to);
    for (int i = 0; i < vertex[id_from].edges.size(); i++)
    {
        if (vertex[id_from].edges[i].id_destination == id_to)
            return i;
    }
    return -1;
}
void Graph::set_color(int index, int new_color)
{
    vertex[index].color = new_color;
}
bool Graph::check_color()
{
    bool all_black = true;
    int black = 2;
    for (auto iter_v = vertex.begin(); iter_v != vertex.end(); iter_v++)
    {
        if (iter_v->color != black)
            all_black = false;
    }
    return all_black;
}

void Graph::clear_color()
{
    int white = 0;
    for (auto iter_v = vertex.begin(); iter_v != vertex.end(); iter_v++)
        set_color(find_vertex(iter_v->name), white);
}

string Graph::print_graph()
{
    if (!vertex.size())
        cout << "Graph is empty";
    else
    {
        stringstream ss;
        for (auto iter_v = vertex.begin(); iter_v != vertex.end(); iter_v++)
        {
            ss << iter_v->name << "=> ";
            for (auto iter_e = iter_v->edges.begin(); iter_e != iter_v->edges.end(); iter_e++)
                ss << vertex[iter_e->id_destination].name << ", ";
            ss << "\n";
        }
        cout << ss.str() << endl;
        return ss.str();
    }
}

void Graph::add_vertex(string name)
{
    if (!has_vertex(name))
    {
        Vertex tmp(name);
        vertex.push_back(tmp);
    }
    else
        throw "Error, such a vertex has already been created!";
}
void Graph::remove_vertex(string name)
{
    if (has_vertex(name))
    {
        int id_erase = find_vertex(name);
        vector<Vertex>::iterator it = vertex.begin() + id_erase;
        vertex.erase(it);
    }
    else
        throw "Error, not found vertex";
}
bool Graph::has_vertex(string name) const
{
    if (find_vertex(name) != -1)
        return true;
    return false;
}

bool Graph::all_vertex() const
{
    if (!vertex.size())
        return false;
    cout << "All vertex:" << endl;
    for (auto iter_v = vertex.begin(); iter_v != vertex.end(); iter_v++)
        cout << "(" << iter_v->name << ")" << endl;
    return true;
}

void Graph::add_edge(string name_from, string name_to, double weight)
{
    if (!has_vertex(name_from))
        throw "Error, not found vertex from";
    if (!has_vertex(name_to))
        throw "Error, not found vertex to";
    int id_from = find_vertex(name_from);
    int id_to = find_vertex(name_to);
    Edge tmp(id_to, weight);
    vertex[id_from].edges.push_back(tmp);
}
void Graph::remove_edge(string name_from, string name_to)
{
    if (!has_vertex(name_from))
        throw "Error, not found vertex from";
    if (!has_vertex(name_to))
        throw "Error, not found vertex to";
    if (!has_edge(name_from, name_to))
        throw "Error, not found edge";
    int id_from = find_vertex(name_from);
    int id_to = find_vertex(name_to);
    vector<Edge>::iterator it = vertex[id_from].edges.begin() + find_edge(name_from, name_to);
    vertex[id_from].edges.erase(it);
}
bool Graph::has_edge(string name_from, string name_to) const
{
    if (find_edge(name_from, name_to) != -1)
        return true;
    else
        throw "Error, not found edge";
}

void Graph::all_edges(string name_from)
{
    if (!has_vertex(name_from))
        throw "Error, not found vertex from";
    int id_from = find_vertex(name_from);
    system("cls");
    for (int i = 0; i < vertex[id_from].edges.size(); i++)
        cout << vertex[id_from].name << " --" << vertex[id_from].edges[i].weight << "--> " << vertex[vertex[id_from].edges[i].id_destination].name << endl;
}

size_t Graph::order() const
{
    return vertex.size();
}
size_t Graph::degree(string name) const
{
    if (!has_vertex(name))
        throw "Error, not found vertex";
    int id = find_vertex(name);
    int count = 0;
    for (int i = 0; i < vertex[id].edges.size(); i++)
        count++;
    return count;
}

// vector<Graph::Edge> Graph::shortest_path() const
// {
// }
void Graph::walk(string name_from)
{
    if (!has_vertex(name_from))
        throw "Error, not found vertex from";
    int index_from = find_vertex(name_from);
    int white = 0, gray = 1, black = 2;
    cout << vertex[index_from].name;
    set_color(index_from, gray);
    for (auto iter_e = vertex[index_from].edges.begin(); iter_e != vertex[index_from].edges.end(); iter_e++)
    {
        if (vertex[iter_e->id_destination].color == white)
        {
            cout << "->";
            walk(vertex[iter_e->id_destination].name);
        }
    }
    set_color(index_from, black);
    if (check_color())
        clear_color();
}
