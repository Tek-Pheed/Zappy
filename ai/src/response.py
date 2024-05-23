from ai.src.data_model import Inventory

def get_inventory(response: str, inv: Inventory) -> Inventory:
    for i in range(len(response)):
        if "food" in response[i]:
            inv = Inventory(int(response[i].split(" ")[2]), inv.linemate, inv.deraumere, inv.sibur, inv.mendiane, inv.phiras, inv.thystame)
        if "linemate" in response[i]:
            inv = Inventory(inv.food, int(response[i].split(" ")[2]), inv.deraumere, inv.sibur, inv.mendiane, inv.phiras, inv.thystame)
        if "deraumere" in response[i]:
            inv = Inventory(inv.food, inv.linemate, int(response[i].split(" ")[2]), inv.sibur, inv.mendiane, inv.phiras, inv.thystame)
        if "sibur" in response[i]:
            inv = Inventory(inv.food, inv.linemate, inv.deraumere, int(response[i].split(" ")[2]), inv.mendiane, inv.phiras, inv.thystame)
        if "mendiane" in response[i]:
            inv = Inventory(inv.food, inv.linemate, inv.deraumere, inv.sibur, int(response[i].split(" ")[2]), inv.phiras, inv.thystame)
        if "phiras" in response[i]:
            inv = Inventory(inv.food, inv.linemate, inv.deraumere, inv.sibur, inv.mendiane, int(response[i].split(" ")[2]), inv.thystame)
        if "thystame" in response[i]:
            inv = Inventory(inv.food, inv.linemate, inv.deraumere, inv.sibur, inv.mendiane, inv.phiras, int(response[i].split(" ")[2]))
    return inv
