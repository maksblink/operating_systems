import socket
import threading
import time

class ChatServer:
    def __init__(self, host='127.0.0.1', port=55555):
        self.host = host
        self.port = port
        self.server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server.bind((self.host, self.port))
        self.server.listen()
        self.clients = []
        self.nicknames = []
        self.lock = threading.Lock()

    def broadcast(self, message):
        with self.lock:
            for client in self.clients:
                try:
                    client.send(message.encode('utf-8'))
                except:
                    self.remove_client(client)

    def remove_client(self, client):
        with self.lock:
            if client in self.clients:
                index = self.clients.index(client)
                self.clients.remove(client)
                nickname = self.nicknames[index]
                self.nicknames.remove(nickname)
                self.broadcast(f'{nickname} opuścił czat!\n')
                client.close()

    def handle_client(self, client):
        while True:
            try:
                message = client.recv(1024).decode('utf-8')
                if message:
                    self.broadcast(message)
                else:
                    self.remove_client(client)
                    break
            except:
                self.remove_client(client)
                break

    def receive(self):
        print("Serwer czatu działa i nasłuchuje...")
        while True:
            client, address = self.server.accept()
            print(f"Połączono z {str(address)}")

            client.send('NICK'.encode('utf-8'))
            nickname = client.recv(1024).decode('utf-8')

            with self.lock:
                self.nicknames.append(nickname)
                self.clients.append(client)

            print(f'Nickname klienta to {nickname}!')
            self.broadcast(f'{nickname} dołączył do czatu!\n')
            client.send('Połączono z serwerem!'.encode('utf-8'))

            thread = threading.Thread(target=self.handle_client, args=(client,))
            thread.start()

    def start(self):
        receive_thread = threading.Thread(target=self.receive)
        receive_thread.start()
        receive_thread.join()

if __name__ == "__main__":
    chat_server = ChatServer()
    chat_server.start()