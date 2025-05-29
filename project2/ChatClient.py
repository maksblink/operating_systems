import socket
import threading


class ChatClient:
    def __init__(self, host='127.0.0.1', port=55555):
        self.host = host
        self.port = port
        self.client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.nickname = None

    def receive(self):
        while True:
            try:
                message = self.client.recv(1024).decode('utf-8')
                if message == 'NICK':
                    self.client.send(self.nickname.encode('utf-8'))
                else:
                    print(message, end='')
            except:
                print("Wystąpił błąd!")
                self.client.close()
                break

    def write(self):
        while True:
            message = input('')
            if message.lower() == 'exit':
                self.client.close()
                break
            self.client.send(f'{self.nickname}: {message}\n'.encode('utf-8'))

    def start(self):
        self.client.connect((self.host, self.port))

        self.nickname = input("Wybierz swój nickname: ")

        receive_thread = threading.Thread(target=self.receive)
        receive_thread.start()

        write_thread = threading.Thread(target=self.write)
        write_thread.start()


if __name__ == "__main__":
    chat_client = ChatClient()
    chat_client.start()