from sys import argv as av
import subprocess
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
                        print_verbose(self.player.verbose, f"[RECEIVE] {elem}\n")
                        if "dead" in elem:
                            print("I'm dead")
                            self.server.close_connection()
                            exit(0)
                        if "Elevation underway" in elem:
                            self.player.step = 7
                        elif "Current level:" in elem:
                            self.player.level = int(''.join(filter(str.isdigit, elem)))
                            if self.player.level == 8:
                                exit(0)
                            print_verbose(self.player.verbose, f"[INFO] {elem}\n")
                            self.player.player_incantation = 1
                            self.player.ready_to_level_up = False
                            self.player.step = 0
                        elif "message" in elem:
                            self.player.broadcast_receive = elem
                            self.player.parse_broadcast()
                            message = message.split("\n")[-1]
                            continue
                        elif self.player.data_to_send == "Connect_nbr\n":
                            if "ko" in elem:
                                self.player.data_to_send = "Connect_nbr\n"
                                self.player.step = 0
                            else:
                                self.player.team_slot = int(elem)
                        elif self.player.data_to_send == "Fork\n":
                            if self.args.thread == True and self.player.can_fork:
                                subprocess.Popen(["python3","zappy_ai","-p", str(self.args.p), "-n", self.player.team, "-h", self.args.h, "--thread"])
                                self.player.can_fork = False
                        elif self.player.data_to_send == "Inventory\n":
                            try:
                                self.player.inventory = get_inventory(elem, self.player.inventory)
                            except (ValueError, IndexError):
                                print_verbose(self.player.verbose, f"[ERROR] {elem}\n")
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
