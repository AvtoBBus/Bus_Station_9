#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <time.h>
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
int Graph::randomaizer(int last_x) const
{
    int x = last_x;
    x = (1021 * x + 24631) % 116640;
    return x;
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
                ss << vertex[iter_e->id_destination].name << "(" << iter_e->weight << "), ";
            ss << "\n";
        }
        cout << ss.str() << endl;
        return ss.str();
    }
}
void Graph::create_random_graph(int vertex_num)
{
    if (!vertex_num)
        throw "I can't create graph with zero vertex(";
    for (int i = 0; i < vertex_num; i++)
    {
        stringstream ss;
        ss << "vertex_";
        ss << i + 1;
        add_vertex(ss.str());
    }
    srand(unsigned(time(nullptr)));
    int val = rand() % 100;
    int index_to = rand();
    for (int chance = 100; chance > 0; chance /= 1.5)
    {
        for (auto iter_v = vertex.begin(); iter_v != vertex.end(); iter_v++)
        {
            val = randomaizer(val);
            if (val % 100 > (100 - chance))
            {
                int counter = 0;
                index_to = randomaizer(index_to) % vertex_num;
                if (!has_edge(iter_v->name, vertex[index_to].name))
                    add_edge(iter_v->name, vertex[index_to].name, double((rand() % 100) + 5));
            }
        }
    }
}
bool Graph::empty_graph() const
{
    return vertex.empty();
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
    cout << endl
         << "All vertex:" << endl;
    for (auto iter_v = vertex.begin(); iter_v != vertex.end(); iter_v++)
        cout << "(" << iter_v->name << ") ";
    cout << endl;
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
        return false;
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

void Graph::clear_graph()
{
    if (!vertex.size())
        throw "Error, graph already empty";
    vertex.clear();
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

vector<Graph::Edge> Graph::shortest_path(string name_from, string name_to) const
{
    const int INF = INT32_MAX;
    struct ed
    {
        int id_from, id_to;
        double weight;

        ed(int id_from, int id_to, double weight)
        {
            this->id_from = id_from;
            this->id_to = id_to;
            this->weight = weight;
        }
    };
    vector<ed> all_edges;
    for (int i = 0; i < vertex.size(); i++)
    {
        for (int j = 0; j < vertex[i].edges.size(); j++)
        {
            ed tmp(i, vertex[i].edges[j].id_destination, vertex[i].edges[j].weight);
            all_edges.push_back(tmp);
        }
    }
    vector<int> distances(vertex.size(), INF);
    distances[find_vertex(name_from)] = 0;

    vector<vector<ed>> s_paths(distances.size());
    for (int i = 0; i < distances.size() - 1; ++i)
    {
        for (int j = 0; j < all_edges.size(); ++j)
        {
            if (distances[all_edges[j].id_from] < INF)
            {
                if (distances[all_edges[j].id_to] > distances[all_edges[j].id_from] + all_edges[j].weight)
                {
                    distances[all_edges[j].id_to] = distances[all_edges[j].id_from] + all_edges[j].weight;
                    if (!s_paths[all_edges[j].id_to].size())
                        s_paths[all_edges[j].id_to].push_back(all_edges[j]);
                    else
                        s_paths[all_edges[j].id_to][0] = all_edges[j];
                }
            }
        }
    }
    if (distances[find_vertex(name_to)] == INT32_MAX)
        throw "This graph is incoherent!";
    for (int j = 0; j < all_edges.size(); ++j)
    {
        if (distances[all_edges[j].id_to] > distances[all_edges[j].id_from] + all_edges[j].weight)
        {
            throw "Error, this graph have cicle below zero!";
        }
    }
    vector<Graph::Edge> result;
    while (true)
    {
        int i = 0, index_end = find_vertex(name_to);
        while (i < s_paths.size())
        {
            if (s_paths[i].size())
            {
                if (s_paths[i][0].id_to == index_end)
                {
                    index_end = s_paths[i][0].id_from;
                    if (result.size() == 0)
                        result.push_back(vertex[s_paths[i][0].id_from].edges[find_edge(vertex[s_paths[i][0].id_from].name, vertex[s_paths[i][0].id_to].name)]);
                    else
                        result.insert(result.begin(), vertex[s_paths[i][0].id_from].edges[find_edge(vertex[s_paths[i][0].id_from].name, vertex[s_paths[i][0].id_to].name)]);
                    i = 0;
                }
                else
                {
                    i++;
                }
                if (index_end == find_vertex(name_from))
                    return result;
            }
            else
                i++;
        }
    }
}
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
string Graph::find_storage()
{
    int storage_id = -1;
    double min_medium_dist = INT32_MAX;
    for (int iter_v = 0; iter_v < vertex.size(); iter_v++)
    {
        double counter = 0.0;
        for (int iter = 0; iter < vertex.size(); iter++)
        {
            if (iter != iter_v)
            {
                try
                {
                    vector<Edge> help_vec = shortest_path(vertex[iter_v].name, vertex[iter].name);
                    for (auto iter = help_vec.begin(); iter != help_vec.end(); iter++)
                        counter += iter->weight;
                }
                catch (const char *error)
                {
                    cout << error << endl;
                    throw "A vertex with no outgoing edges is found!";
                }
            }
        }
        if (counter / (vertex.size() - 1) < min_medium_dist)
        {
            min_medium_dist = counter / (vertex.size() - 1);
            storage_id = iter_v;
        }
    }
    stringstream ss;
    ss << "\n";
    ss << vertex[storage_id].name;
    ss << " is storage\n";
    return ss.str();
}