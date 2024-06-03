import socket
import selectors

class Server:
    def __init__(self, hostname, port):
            self.hostname = hostname
            self.port = port
            self.socket = None
            self.selectors = selectors.DefaultSelector()

    def init_connection(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.settimeout(10)
            print(f"Connection to {self.hostname}:{self.port}")
            self.socket.setblocking(False)
            self.socket.connect_ex((self.hostname, self.port))
            print("Connection etablished")
            events = selectors.EVENT_READ | selectors.EVENT_WRITE
            self.selectors.register(self.socket, events)
        except Exception as e:
            print(f"Error: {e}")
            exit(84)

    def receive_message(self, buffer_size=1024):
        return self.socket.recv(buffer_size).decode('utf-8')

    def send_message(self, command: str):
        if self.socket:
            try:
                self.socket.sendall(command.encode("utf-8"))
            except Exception as e:
                print(f"Error: {e}")
                self.close_connection()
                exit(84)
        else:
            print("Error: no connection")

    def close_connection(self):
        if self.socket:
            try:
                self.socket.close()
            except Exception as e:
                print(f"Error: {e}")
                exit(84)
        else:
            print("Error: no connection")
