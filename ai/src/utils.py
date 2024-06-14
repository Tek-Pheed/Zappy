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

def generate_empty_map() -> List:
    res: List = []
    nbCase = 1

    for _ in range(4):
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
