from pytest import raises
from ai.src.arguments import *

def test_invalid_args():
    args = ["test", "01", "test"]
    with raises(SystemExit) as exitStatus:
            parse_args(args)
    assert exitStatus.value.code == 84

def test_not_enought_args():
    args = ["22", "test"]
    with raises(SystemExit) as exitStatus:
        parse_args(args)
    assert exitStatus.value.code == 84

def test_not_enought_args2():
    args = ["22"]
    with raises(SystemExit) as exitStatus:
        parse_args(args)
    assert exitStatus.value.code == 84

def test_no_args():
    args = []
    with raises(SystemExit) as exitStatus:
        parse_args(args)
    assert exitStatus.value.code == 84
