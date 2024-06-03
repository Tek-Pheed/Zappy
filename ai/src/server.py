import socket
import select

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
            self.socket.setblocking(False)
        except Exception as e:
            print(f"Error: {e}")
            exit(84)

    def receive_message(self, buffer_size=1024):
        if self.socket:
            try:
                readable, _, _ = select.select([self.socket], [], [], 1)
                if self.socket in readable:
                    data = self.socket.recv(buffer_size)
                    if data:
                        return data.decode('utf-8')
                    else:
                        print("Connection closed by the server !")
                        self.close_connection()
                        return None
            except Exception as e:
                print(f"Error: {e}")
                self.close_connection()
                exit(84)
        else:
            print("Error: no connection")

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
