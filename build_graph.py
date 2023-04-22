import numpy as np
import matplotlib.pyplot as plt
import multiprocessing as mpc
import random


def start_create_graph(file_path_list: list):

    list_num_of_node = [[], [], []]
    list_time = [[], [], []]
    fig, axs = plt.subplots(nrows=3, ncols=1, figsize=(9, 7))
    for j in range(len(file_path_list)):
        help_list = []

        with open(file_path_list[j], "r", encoding="utf-8") as file:
            help_list = file.readlines()

        for i in range(len(help_list)):
            list_num_of_node[j].append(float(help_list[i].split(sep=";")[0]))
            if help_list[i].split(sep=";")[1] == '\n':
                list_time[j].append(
                    float(help_list[i].split(sep=";")[1][:-1]))
            else:
                list_time[j].append(float(help_list[i].split(sep=";")[1]))

        for i in range(len(help_list)):
            list_num_of_node[j].append(float(help_list[i].split(sep=";")[0]))
            if help_list[i].split(sep=";")[1] == '\n':
                list_time[j].append(
                    float(help_list[i].split(sep=";")[1][:-1]))
            else:
                list_time[j].append(float(help_list[i].split(sep=";")[1]))

    axs[0].plot(list_num_of_node[0], list_time[0])
    axs[1].plot(list_num_of_node[1], list_time[1], '--')
    axs[2].plot(list_num_of_node[2], list_time[2], ':')
    plt.show()


if __name__ == "__main__":

    list_of_file = [
        "build/Debug/Node_fill.txt",
        "build/Debug/Node_search.txt",
        "build/Debug/Node_insert_erase.txt"
    ]
    start_create_graph(list_of_file)
