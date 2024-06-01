import subprocess
from sys import argv as av
from ai.src.arguments import parse_args
from ai.src.server import *
from ai.src.response import *
from ai.src.action import *
from ai.src.player import Player

class AI:
    def __init__(self) -> None:
        self.args = None
        self.server: Server
        self.player: Player

    def run(self, args):
        self.server = Server(args.h, args.p)
        message = ""
        self.server.init_connection()
        self.player = Player(args.n)
        while True:
            event = self.server.selectors.select(timeout=None)
            for _, mask in event:
                if mask & selectors.EVENT_READ:
                    data = self.server.socket.recv(1024).decode("utf-8")
                    if data:
                        message += data
                    else:
                        self.server.selectors.unregister(self.server.socket)
                        self.server.close_connection()
                    tmp = data.split("\n")
                    for elem in tmp[:-1]:
                        if "dead" in elem:
                            self.server.close_connection()
                            exit(0)
                        if "Inventory" in self.player.data_to_send:
                            self.player.inventory = get_inventory(elem, self.player.inventory)

                if mask & selectors.EVENT_WRITE:
                    if self.player.logged == False and self.player.team in self.player.data_to_send:
                        self.player.logged = True
                        self.server.socket.send(self.player.data_to_send.encode())
                    else:
                        subprocess.Popen(["python3", "zappy_ai","-p", str(self.args.p), "-n", self.args.n, "-h", self.args.h])

if __name__ == "__main__":
    ai: AI = AI()
    ai.args = parse_args(av[1:])

    ai.run(ai.args)
