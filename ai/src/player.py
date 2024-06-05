from ai.src.action import *
from ai.src.utils import print_verbose

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
        self.cases_arround = {}
        self.level = 1
        self.step = 0
        self.action = []
        self.verbose = False

    def incantation_possible(self):
        required_ressources = LVLS_MANDATORY[self.level].copy()

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
            if "food" in self.inventory and self.inventory["food"] < 35:
                self.action = take_food(self.cases_arround)
                self.step += 1
            else:
                self.action = take_minerals(self.cases_arround)
                self.step += 1
        elif self.step == 4:
            self.data_to_send = "Inventory\n"
            self.step = 0
