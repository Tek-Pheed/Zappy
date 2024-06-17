from typing import List

RESSOURCES = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"]

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
