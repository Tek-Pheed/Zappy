import socket

class Server:
    def __init__(self, hostname, port):
            self.hostname = hostname
            self.port = port
            self.socket = None

    def init_connection(self):
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.settimeout(10)
            address = (self.hostname, self.port)
            print(f"Connection to {self.hostname}:{self.port}")
            self.socket.connect(address)
            print("Connection etablished")
        except Exception as e:
            print(f"Error: {e}")
            exit(84)

    def receive_message(self, buffer_size=1024):
        if self.socket:
            try:
                data = self.socket.recv(buffer_size)
                return data.decode('utf-8')
            except Exception as e:
                print(f"Error: {e}")
        else:
            print("Error: no connection")

    def send_message(self, command: str):
        if self.socket:
            try:
                self.socket.sendall(command.encode("utf-8"))
            except Exception as e:
                print(f"Error: {e}")
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
