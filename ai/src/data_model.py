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
    name: str
    level: int
    inv: Inventory
