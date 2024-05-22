from sys import argv as av
from ai.src.arguments import parse_args
from ai.src.data_model import *

args = parse_args(av[1:])

inv: Inventory = Inventory(2, 0, 0, 0, 0, 0, 0)
p: Player = Player(0, inv)
print(p)
