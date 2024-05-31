from ai.src.server import Server

def send_request(server: Server, message: str) -> str:
    server.send_message(f"{message}\n")
    res = server.receive_message()
    if "dead" in res:
        server.close_connection()
        exit(0)
    return res

def create_team(args, server: Server):
    server.init_connection()
    server.receive_message()
    server.send_message(args.n + "\n")
    server.receive_message()

def get_food(cases: dict, player: dict, server: Server):
    for i in range (len(cases)):
        if "food" in cases[i]:
            send_request(server, "Take food")
        else:
            send_request(server, "Forward")
            if i == 1:
                send_request(server, "Right")
            elif i == 3:
                send_request(server, "Left")
