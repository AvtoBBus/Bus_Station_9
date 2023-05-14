import numpy as np
import matplotlib.pyplot as plt


def cm_to_inch(value):
    return value/2.54


def start_create_graph(file_path_list: list):

    list_num_of_node = [[]for i in range(6)]
    list_comparison = [[] for i in range(6)]
    list_copy = [[] for i in range(6)]
    list_text = [
        "Random_change_comp",
        "Random_change_copy",
        "Random_shell_comp",
        "Random_shell_copy",
        "Sorted_change_comp",
        "Sorted_change_copy",
        "Sorted_shell_comp",
        "Sorted_shell_copy",
        "Reversed_change_comp",
        "Reversed_change_copy",
        "Reversed_shell_comp",
        "Reversed_shell_copy",
    ]
    for j in range(len(file_path_list)):
        help_list = []

        with open(file_path_list[j], "r", encoding="utf-8") as file:
            help_list = file.readlines()

        for i in range(len(help_list)):
            list_num_of_node[j].append(float(help_list[i].split(sep=" ")[0]))
            list_comparison[j].append(float(help_list[i].split(sep=" ")[1]))
            list_copy[j].append(float(help_list[i].split(sep=" ")[2]))

    count = 0
    figure = plt.figure(figsize=(cm_to_inch(35), cm_to_inch(20)))

    margins = {
        "left": 0.040,
        "bottom": 0.060,
        "right": 0.990,
        "top": 0.950
    }
    figure.subplots_adjust(**margins)
    
    for i in range(1, 13):
        plt.subplot(6, 2, i)
        plt.xlabel("Number of node")
        plt.grid(True)
        if i % 2 == 1:
            plt.ylabel("Comp count")
            plt.plot(list_num_of_node[count], list_comparison[count])
            plt.text(0, list_comparison[count][-1] / 2, list_text[i-1])
        else:
            plt.ylabel("Copy count")
            plt.plot(list_num_of_node[count], list_copy[count])
            plt.text(0, list_copy[count][-1] / 2, list_text[i-1])
            count += 1

    plt.show()


if __name__ == "__main__":

    list_of_file = [
        "build/Debug/random_mass_change.txt",
        "build/Debug/random_mass_shell.txt",
        "build/Debug/reversed_mass_change.txt",
        "build/Debug/reversed_mass_shell.txt",
        "build/Debug/sorted_mass_change.txt",
        "build/Debug/sorted_mass_shell.txt"
    ]
    start_create_graph(list_of_file)
