from typing import Dict, List

def get_inventory(response: str, inv: dict) -> dict:
    for i in range(len(response)):
        if "food" in response[i]:
            inv["food"] = int(response[i].split(" ")[2])
        if "linemate" in response[i]:
            inv["linemate"] = int(response[i].split(" ")[2])
        if "deraumere" in response[i]:
            inv["deraumere"] = int(response[i].split(" ")[2])
        if "sibur" in response[i]:
            inv["deraumere"] = int(response[i].split(" ")[2])
        if "mendiane" in response[i]:
            inv["mendiane"] = int(response[i].split(" ")[2])
        if "phiras" in response[i]:
            inv["phiras"] = int(response[i].split(" ")[2])
        if "thystame" in response[i]:
            inv["thystame"] = int(response[i].split(" ")[2])
    return inv

def get_case_around_player(response: str) -> dict:
    res = dict()

    for i in range(len(response)):
        res[i] = response[i]
    return res
