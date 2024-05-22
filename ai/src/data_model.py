from typing import NamedTuple

class Inventory(NamedTuple):
    food: int
    linemate: int
    deraumere: int
    sibur: int
    mendiane: int
    phiras: int
    thystame: int

class Player(NamedTuple):
    level: int
    inv: Inventory
