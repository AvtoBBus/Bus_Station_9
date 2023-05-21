#pragma once
#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
using namespace std;

class Graph
{
private:
    struct Edge
    {
        int id_destination;
        double weight;

        Edge(int id_destination, double weight = 1.0)
        {
            this->id_destination = id_destination;
            this->weight = weight;
        }
    };

    struct Vertex
    {
        string name;
        vector<Edge> edges;
        int color; // 0-white; 1-gray; 2-black
        string prev_vertex;

        Vertex(string new_name)
        {
            this->name = new_name.substr(0);
            this->color = 0;
        }
    };

    vector<Vertex> vertex;

    int find_vertex(string name) const;
    int find_edge(string name_from, string name_to) const;
    void set_color(int index, int new_color);
    bool check_color();
    void clear_color();

public:
    string print_graph();

    void add_vertex(string name);
    void remove_vertex(string name);
    bool has_vertex(string name) const;
    bool all_vertex() const;

    void add_edge(string name_from, string name_to, double weight);
    void remove_edge(string name_from, string name_to);
    bool has_edge(string name_from, string name_to) const;

    void all_edges(string name_from);

    size_t order() const;
    size_t degree(string name) const;

    vector<Edge> shortest_path() const;
    void walk(string name_from);
};