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