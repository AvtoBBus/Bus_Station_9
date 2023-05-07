#include "sorts.h"
#include <vector>

using namespace std;

void change_sort(vector<int> *mas, stats &result)
{
    int min_index = 0;
    for (int i = 0; i < mas->size(); i++)
    {
        min_index = i;
        for (int j = i + 1; j < mas->size(); j++)
        {
            result.comparison_count += 1;
            if ((*mas)[j] < (*mas)[min_index])
            {
                min_index = j;
            }
        }
        result.copy_count += 1;
        int tmp = (*mas)[i];
        (*mas)[i] = (*mas)[min_index];
        (*mas)[min_index] = tmp;
    }
}

void shell_sort(vector<int> *mas, stats &result)
{
    int step = 0, i = 0, j = 0;
    for (step = mas->size() / 2; step > 0; step /= 2)
    {
        for (i = step; i < mas->size(); i++)
        {
            int tmp = (*mas)[i];
            for (j = i; j >= step; j -= step)
            {
                result.comparison_count += 1;
                if (tmp < (*mas)[j - step])
                {

                    result.copy_count += 1;
                    (*mas)[j] = (*mas)[j - step];
                }
                else
                {
                    break;
                }
            }
            result.copy_count += 1;
            (*mas)[j] = tmp;
        }
    }
}