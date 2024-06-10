import re
import random
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
        self.ready_to_level_up = False
        self.verbose = False

    def incantation_possible(self) -> bool:
        required_ressources = LVLS_MANDATORY[self.level].copy()
        print_verbose(self.verbose, f"Checking Incantation --> {self.level} --> {required_ressources}\n")
        for r in required_ressources:
            if required_ressources[r] > self.inventory[r]:
                return False
        return True

    def what_i_search(self) -> str:
        list = []

        required_ressources = LVLS_MANDATORY[self.level].copy()
        for r in required_ressources:
            if r not in self.inventory or required_ressources[r] > self.inventory[r]:
                list.append(r)
        if len(list) == 0:
            list.append("food")
        return random.choice(list)

    def size_of_look(self, map: list) -> int:
        nb: int = 0

        for case in map:
            if case == []:
                return nb
            nb += 1
        return nb

    def find_collectible(self, object: str):
        for i in range(len(self.map)):
            for y in range(self.size_of_look(self.map[i])):
                if object in self.map[i][y][0]:
                    print_verbose(self.verbose, f"{object} found in {(i, y)} !\n")
                    return [i, y]
        return None

    def parse_look_command(self, data: str, object: str) -> List:
        tmp = data.split(",")
        list = []
        for i in range(len(tmp)):
            list.append(' '.join(re.split(r'\W+', tmp[i])[1:]))
        data = list
        map = generate_empty_map()
        map = fill_map_with_data(map, data)
        print_verbose(self.verbose, f"Map: {self.map}\n")
        self.map = map
        coord = self.find_collectible(object)
        action = []
        if coord == None:
            action.append(random.choice(["Right\n", "Forward\n", "Left\n"]))
            action.append(random.choice(["Right\n", "Forward\n", "Left\n"]))
            action.append(random.choice(["Right\n", "Forward\n", "Left\n"]))
            return action
        elif coord[0] == 0 and coord[1] == 0:
            action.append(f"Take {object}\n")
            return action
        else:
            for i in range(coord[0]):
                action.append("Forward\n")
            if coord[1] == 0:
                action.append(f"Take {object}\n")
            if coord[0] == 0:
                for i in range(coord[1]):
                    action.append("Forward\n")
                action.append(f"Take {object}\n")
                action.append(f"Inventory\n")
            if coord[1] < len(self.map[coord[0]]) / 2:
                action.append("Right\n")
                for i in range(int((len(self.map[coord[0]]) / 2)) - coord[1]):
                    action.append("Forward\n")
                action.append(f"Take {object}\n")
                action.append(f"Inventory\n")
            if coord[1] > len(self.map[coord[0]]) / 2:
                action.append("Right\n")
                for i in range(coord[1] - int((len(self.map[coord[0]]) / 2))):
                    action.append("Forward\n")
                action.append(f"Take {object}\n")
                action.append(f"Inventory\n")
        return action

    def drop_items_for_incantation(self):
        data = self.look_arround.split(",")[0]
        while True:
            if len(data) == 0 or data[0].isalpha():
                break
            data = data[1:]
        data = data.split(" ")
        required_ressources = LVLS_MANDATORY[self.level].copy()
        for r in required_ressources:
            for r2 in data:
                    if r == r2:
                        required_ressources[r] -= 1
        for r in required_ressources:
            if required_ressources[r] > 0:
                continue
            print(r in self.inventory and self.inventory[r] != 0)
            if r in self.inventory and self.inventory[r] != 0:
                self.action = ["Set " + r + "\n"]
                self.action.append("Look\n")
                self.inventory[r] -= 1
                return
        self.step = 6
        self.data_to_send = ""
        return

    def begin_incantation(self):
        data = self.look_arround.split(",")[0]
        while True:
            if len(data) == 0 or data[0].isalpha():
                break
            data = data[1:]
        data = data.split(" ")
        required_ressources = LVLS_MANDATORY[self.level].copy()
        for r in required_ressources:
            for r2 in data:
                if r == r2:
                    required_ressources[r] -= 1
        for r in required_ressources:
            if required_ressources[r] > 0:
                return
        self.data_to_send = "Incantation\n"
        self.action = ["Incantation\n"]
        self.step += 1

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
            if (self.incantation_possible()):
                self.step = 4
            else:
                self.step += 1
        elif self.step == 2:
            self.data_to_send = "Look\n"
            self.step += 1
        elif self.step == 3:
            if "food" in self.inventory and self.inventory["food"] < 35:
                self.action = self.parse_look_command(self.look_arround, "food")
                self.step = 0
            else:
                self.object_to_go = self.what_i_search()
                self.action = self.parse_look_command(self.look_arround, self.object_to_go)
                self.step = 0
        elif self.step == 4:
            self.data_to_send = "Look\n"
            self.step += 1
        elif self.step == 5:
            if self.incantation_possible():
                print("Begin Incantation")
                self.begin_incantation()
            if self.step != 6:
                self.drop_items_for_incantation()
                print(self.action)
                if self.action:
                    self.data_to_send = self.action[0]
                    self.action = self.action[1:]
                else:
                    self.data_to_send = "Inventory\n"
        elif self.step == 6:
            if self.action:
                self.data_to_send = self.action[0]
                self.action = self.action[1:]
                print(f"Action: {self.action}")
        elif self.step == 7:
            self.data_to_send = ""
