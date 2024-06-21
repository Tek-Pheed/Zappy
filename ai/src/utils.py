from typing import List

def clean_str(str: str) -> str:
    str = str.replace("[", "")
    str = str.replace(" ", "", 1)
    str = str.replace("]", "")
    str = str.replace("\n", "")
    return str

def print_verbose(verbose: bool, str):
    if verbose:
        print(f"{str}", end="")

def generate_empty_map(data) -> List:
    res: List = []
    nbCase = 1

    line: int = 0

    if (len(data) == 4):
        line = 2
    elif (len(data) == 9):
        line = 3
    elif (len(data) == 16):
        line = 4
    elif (len(data) == 25):
        line = 5
    elif (len(data) == 36):
        line = 6
    elif (len(data) == 49):
        line = 7
    elif (len(data) == 64):
        line = 8
    elif (len(data) == 81):
        line = 9

    for _ in range(line):
        res.append([[] for j in range(nbCase)])
        nbCase += 2
    return res

def get_nb_of_line_in_array(array: List) -> int:
    return int(len(array) ** 1/2)

def fill_map_with_data(map: List, data: List) -> List:
    nb = 1
    case = 0

    line = get_nb_of_line_in_array(data)
    for current in range(line):
        if case == len(data):
            break
        for i in range(nb):
            map[current][i].append(data[case])
            case += 1
        nb += 2
    return map
