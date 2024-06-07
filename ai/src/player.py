import re
from ai.src.action import *
from ai.src.utils import print_verbose
from ai.src.utils import *

LVLS_MANDATORY = {
    1: {"linemate": 1},
    2: {"linemate": 1, "deraumere": 1, "sibur": 1},
    3: {"linemate": 2, "sibur": 1, "phiras": 2},
    4: {"linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
    5: {"linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
    6: {"linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
    7: {"linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1},
}

class Player:
    def __init__(self, team_name: str) -> None:
        self.team = team_name
        self.logged = False
        self.data_to_send = f"{team_name}\n"
        self.inventory = {"food": 0, "linemate": 0, "deraumere": 0, "sibur": 0, "mendiane": 0, "phiras": 0, "thystame": 0}
        self.map = []
        self.look_arround: str = ""
        self.level = 1
        self.step = 0
        self.action = []
        self.object_to_go = ""
        self.verbose = False

    def incantation_possible(self):
        required_ressources = LVLS_MANDATORY[self.level].copy()
        print_verbose(self.verbose, f"Incantation --> {self.level} --> {required_ressources}\n")

    def find_collectible(self, object: str):
        for i in range(len(self.map[0])):
            for y in range (len(self.map[0][i])):
                if object in self.map[0][i][y]:
                    print_verbose(self.verbose, f"{object} found in {(i, y)} !\n")
                    return (i, y)

    def parse_look_command(self, data: str) -> List:
        tmp = data.split(",")
        list = []
        for i in range(len(tmp)):
            list.append(' '.join(re.split(r'\W+', tmp[i])[1:]))
        data = list
        map = generate_empty_map()
        map = fill_map_with_data(map, data)
        self.map = map
        print_verbose(self.verbose, f"Map: {self.map}\n")
        self.find_collectible("food")

    def take_action(self):
        if self.step == 0:
            if self.action:
                self.data_to_send = self.action[0]
                self.action = self.action[1:]
            else:
                self.data_to_send = "Inventory\n"
                self.step += 1
            print_verbose(self.verbose, f"Action: {self.data_to_send}")
        elif self.step == 1:
            self.incantation_possible()
            self.step += 1
        elif self.step == 2:
            self.data_to_send = "Look\n"
            self.step += 1
        elif self.step == 3:
            if self.inventory["food"] < 35:
                self.parse_look_command(self.look_arround)
                self.step += 1
            else:
                self.step += 1
        elif self.step == 4:
            self.step += 1
        elif self.step == 5:
            self.data_to_send = "Look\n"
            self.step = 0
