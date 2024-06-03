from sys import argv as av
from ai.src.arguments import parse_args
from ai.src.server import *
from ai.src.response import *
from ai.src.action import *

args = parse_args(av[1:])

server: Server = Server(args.h, args.p)
create_team(args, server)
player = dict()
player["team"] = args.n
inv = dict()
player["inventory"] = inv
while True:
    res = send_request(server, "Inventory")
    inv = get_inventory(res.split(","), inv)
    arround = send_request(server, "Look")
    arround = arround.replace("[", "")
    arround = arround.replace(" ", "", 1)
    arround = arround.replace("]", "")
    arround = arround.replace("\n", "")
    cases = get_case_around_player(arround.split(","))
    get_food(cases, player, server)
    print(inv)

server.close_connection()
