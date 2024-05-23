from sys import argv as av
from ai.src.arguments import parse_args
from ai.src.data_model import *
from ai.src.server import *

if len(av) <= 1:
    print("Error: not enought args")
    exit(84)

args = parse_args(av[1:])

server: Server = Server(args.h, args.p)
server.init_connection()

inv: Inventory = Inventory(0, 0, 0, 0, 0, 0, 0)
p: Player = Player(args.n, 0, inv)
print(p)
