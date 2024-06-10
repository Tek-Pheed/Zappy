from sys import argv as av
from ai.src.arguments import parse_args
from ai.src.server import *
from ai.src.action import *
from ai.src.player import Player
from ai.src.utils import print_verbose

class AI:
    def __init__(self) -> None:
        self.args = None
        self.server: Server
        self.player: Player

    def init_core(self):
        self.server = Server(self.args.h, self.args.p)
        self.server.init_connection()
        self.player = Player(self.args.n)
        self.player.verbose = self.args.verbose

    def run(self):
        message = ""
        running = 0
        while True:
            event = self.server.selectors.select(timeout=None)
            for _, mask in event:
                if mask & selectors.EVENT_READ:
                    data = self.server.receive_message()
                    if data:
                        message += data
                    else:
                        self.server.selectors.unregister(self.server.socket)
                        self.server.close_connection()
                    tmp = message.split("\n")
                    for elem in tmp[:-1]:
                        if "dead" in elem:
                            print("I'm dead")
                            self.server.close_connection()
                            exit(0)
                        if "Elevation underway" in elem:
                            self.player.step = 7
                        elif "Current level:" in elem:
                            print(int(''.join(filter(str.isdigit, elem))))
                            self.player.level = int(''.join(filter(str.isdigit, elem)))
                            if self.player.level == 8:
                                exit(0)
                            print(elem)
                            print(self.player.level)
                            self.player.step = 0
                            print(self.player.step)
                        elif self.player.data_to_send == "Inventory\n":
                            try:
                                self.player.inventory = get_inventory(elem, self.player.inventory)
                                print_verbose(self.player.verbose, f"{self.player.inventory}\n")
                            except ValueError:
                                print_verbose(self.player.verbose, f"Error {elem}")
                                pass
                        elif self.player.data_to_send == "Look\n":
                            self.player.look_arround = elem
                        message = message.split("\n")[-1]
                        running = 1

                if mask & selectors.EVENT_WRITE:
                    if self.player.logged and running == 1:
                        self.player.take_action()
                    if running != 0 and self.player.data_to_send:
                        if self.player.logged == False and self.player.team in self.player.data_to_send:
                            self.player.logged = True
                        self.server.send_message(self.player.data_to_send)
                        running = 0

if __name__ == "__main__":
    ai: AI = AI()
    ai.args = parse_args(av[1:])

    ai.init_core()
    ai.run()
