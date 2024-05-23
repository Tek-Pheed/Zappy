from sys import argv as av
from ai.src.arguments import parse_args
from ai.src.data_model import *
from ai.src.server import *
from ai.src.response import *

args = parse_args(av[1:])

server: Server = Server(args.h, args.p)
server.init_connection()
server.receive_message()
server.send_message(args.n + "\n")
server.receive_message()
inv: Inventory = Inventory(0, 0, 0, 0, 0, 0, 0)
while True:
    server.send_message("Inventory\n")
    res = server.receive_message()
    if res == "dead\n":
        server.close_connection()
        exit(0)
    inv = get_inventory(res.split(","), inv)
    print(inv)
    server.send_message("Look\n")
    res = server.receive_message()
    print(res)


server.close_connection()
