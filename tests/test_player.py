from pytest import raises
from ai.src.player import Player

def test_default_player():
    p: Player = Player("zap")

    assert p.team == "zap" and p.logged == False

def test_incantation_not_possible():
    p: Player = Player("zap")

    assert p.incantation_possible() == False

def test_incantation_possible():
    p: Player = Player("zap")

    p.inventory = {"linemate": 1}

    assert p.incantation_possible() == True

def test_search_minerals():
    p: Player = Player("zap")

    assert p.what_i_search() == "linemate"

def test_size_of_look():
    p: Player = Player("zap")
    map: list = [[["player food food"]], [["food"], ["linemate"], [" "]]]

    assert p.size_of_look(map) == 2

def test_find_collectible():
    p: Player = Player("zap")
    map: list = [[["player food food"]], [["food"], ["linemate"], [" "]]]

    p.map = map

    assert p.find_collectible("food") == [0, 0]

def test_parse_look_command():
    p: Player = Player("zap")

    assert p.parse_look_command("[player food food, food, linemate, ]", "food") == ["Take food\n"]

def test_walk_to_broadcast_emitter():
    p: Player = Player("zap")

    assert "Broadcast" in p.walk_to_broadcast_emitter(0, "")
