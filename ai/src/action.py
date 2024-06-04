from typing import List
from ai.src.player import Player
from ai.src.server import Server

RESSOURCES = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

LVLS_MANDATORY = {
    1: {"linemate": 1},
    2: {"linemate": 1, "deraumere": 1, "sibur": 1},
    3: {"linemate": 2, "sibur": 1, "phiras": 2},
    4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
    5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
    6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
    7: {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
}

def take_food(cases: dict, player: Player, server: Server):
    instruction: List[str] = []
    for i in range (len(cases)):
        if "food" in cases[i]:
            instruction.append("Take food\n")
        else:
            instruction.append("Forward\n")
            if i == 1:
                instruction.append("Right\n")
            elif i == 3:
                instruction.append("Left\n")
    return instruction

def take_minerals(cases: dict, player: Player, server: Server):
    instruction: List[str] = []
    for i in range (len(cases)):
        current_case = cases[i].split(" ")
        for items in current_case:
            if items in RESSOURCES:
                instruction.append(f"Take {items}\n")
    return instruction

def get_inventory(response: str, inv: dict) -> dict:
    for i in range(len(response)):
        if "food" in response[i]:
            inv["food"] = int(response[i].split(" ")[2])
        if "linemate" in response[i]:
            inv["linemate"] = int(response[i].split(" ")[2])
        if "deraumere" in response[i]:
            inv["deraumere"] = int(response[i].split(" ")[2])
        if "sibur" in response[i]:
            inv["sibur"] = int(response[i].split(" ")[2])
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

def get_number_of_team_unused(response: str) -> int:
    return int(response)

def get_OK_KO(response: str) -> bool:
    if "ok" in response:
        return True
    else:
        return False

def get_incantation(response: str):
    if "ko" in response:
        return False
    else:
        return response
