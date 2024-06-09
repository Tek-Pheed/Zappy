from typing import List
from ai.src.utils import clean_str

RESSOURCES = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

def take_minerals(cases: dict):
    instruction: List[str] = []
    for i in range (len(cases)):
        current_case = cases[i].split(" ")
        for items in current_case:
            if items in RESSOURCES:
                instruction.append(f"Take {items}\n")
    return instruction

def get_inventory(response: str, inv: dict) -> dict:
    for char in "[]":
        response = response.replace(char, "")
    response = response.split(",")
    for i in range(len(response)):
        response[i] = response[i][1:]
    for elem in response:
        if elem:
            inv[elem.split()[0]] = int(elem.split()[1])
    return inv


def get_case_around_player(response: str) -> dict:
    res = dict()

    response = clean_str(response)
    response = response.split(",")
    for i in range(len(response)):
        if i != 0:
            response[i] = response[i][1:]
        if i == len(response) - 1:
            response[i] = response[i].rstrip()
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
