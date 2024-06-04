from ai.src.server import Server

def get_food(cases: dict, player: dict, server: Server):
    for i in range (len(cases)):
        if "food" in cases[i]:
            server.send_message("Take food\n")
        else:
            server.send_message("Forward\n")
            if i == 1:
                server.send_message("Right\n")
            elif i == 3:
                server.send_message("Left\n")

def get_inventory(response: str, inv: dict) -> dict:
    for i in range(len(response)):
        match response[i]:
            case "food":
                inv["food"] = int(response[i].split(" ")[2])
            case "linemate":
                inv["linemate"] = int(response[i].split(" ")[2])
            case "deraumere":
                inv["deraumere"] = int(response[i].split(" ")[2])
            case "sibur":
                inv["sibur"] = int(response[i].split(" ")[2])
            case "mendiane":
                inv["mendiane"] = int(response[i].split(" ")[2])
            case "phiras":
                inv["phiras"] = int(response[i].split(" ")[2])
            case "thystame":
                inv["thystame"] = int(response[i].split(" ")[2])
    return inv

def get_case_around_player(response: str) -> dict:
    res = dict()

    for i in range(len(response)):
        res[i] = response[i]
    return res

def get_number_of_team_unused(response: str) -> int:
    return int(response)

def get_OK_KO(response: str) -> bool:
    if "ok" in response:
        return True
    else:
        return False

def get_incantation(response: str):
    if "ko" in response:
        return False
    else:
        return response
