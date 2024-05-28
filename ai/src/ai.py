from sys import argv as av
from ai.src.arguments import parse_args
from ai.src.server import *
from ai.src.response import *

def create_team(args, server):
    server.init_connection()
    server.receive_message()
    server.send_message(args.n + "\n")
    server.receive_message()

args = parse_args(av[1:])

server: Server = Server(args.h, args.p)
create_team(args, server)
player = dict()
player["team"] = args.n
inv = dict()
player["inventory"] = inv
while True:
    server.send_message("Inventory\n")
    res = server.receive_message()
    if res == "dead\n":
        server.close_connection()
        exit(0)
    inv = get_inventory(res.split(","), inv)
    print(player)


server.close_connection()
