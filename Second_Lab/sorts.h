#pragma once
#include <vector>

using namespace std;

struct stats
{
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

void change_sort(vector<int> *mas, stats &result);
void shell_sort(vector<int> *mas, stats &result);