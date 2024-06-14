from pytest import raises
from ai.src.action import get_inventory

def test_get_inventory():
    inv: dict = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
    res: str = "[ food 4, linemate 0, deraumere 0, sibur 0, mendiane 0, phiras 400, thystame 1 ]"

    inv = get_inventory(res, inv)

    assert inv == {"food": 4, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 400, "thystame": 1}