from pytest import raises
from ai.src.utils import *

def test_clean_str():
    str1: str = "[Salut ]\n"
    str2: str = "Salut"

    assert clean_str(str1) == str2

def test_print_verbose(capsys):
    print_verbose(True, "DEBUG")

    out, _ = capsys.readouterr()
    assert out == "DEBUG"

def test_print_no_verbose(capsys):
    print_verbose(False, "DEBUG")

    out, _ = capsys.readouterr()
    assert out == ""

def test_generate_empty_map():
    list = generate_empty_map()

    assert list == [[[]], [[], [], []], [[],[],[],[],[]], [[],[],[],[],[],[],[]]]

def test_get_nb_of_line_in_array():
    data = ["player food food", "food", "linemate", " "]

    assert get_nb_of_line_in_array(data) == 2

def test_fill_empty_map_with_data():
    list = generate_empty_map()
    data = ["player food food", "food", "linemate", " "]

    assert fill_map_with_data(list, data) == [[["player food food"]], [["food"], ["linemate"], [" "]], [[],[],[],[],[]], [[],[],[],[],[],[],[]]]

def test_fill_empty_map_with_empty_data():
    list = generate_empty_map()
    data = []

    assert fill_map_with_data(list, data) == [[[]], [[], [], []], [[],[],[],[],[]], [[],[],[],[],[],[],[]]]