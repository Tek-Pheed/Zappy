from pytest import raises
from src.player import Player

def test_player_default_inventory():
    p: Player = Player("test")

    assert p.inventory == {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}

def test_player_default_level():
    p: Player = Player("test")

    assert p.level == 1

def test_player_team_name():
    p: Player = Player("test")

    assert p.team == "test"

def test_player_first_data_to_send():
    p: Player = Player("test")

    assert p.data_to_send == f"{p.team}\n"
