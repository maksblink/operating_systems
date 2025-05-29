# 🚀 Multithreaded Chat Server in Python

![Python](https://img.shields.io/badge/Python-3.6%2B-blue)  
![Socket](https://img.shields.io/badge/Socket-Networking-orange)  
![Threading](https://img.shields.io/badge/Threading-Multithreaded-brightgreen)

## 📋 Project Description

This project implements a multithreaded chat server using:
- `socket` for network communication
- `threading` to handle multiple clients simultaneously

## 🌟 Features

### Server
- 🧵 Creates a separate thread for each client
- 🔒 Synchronizes messages between clients
- 📢 Broadcasts messages to all participants
- 🏷️ Manages user nicknames
- ♻️ Handles client disconnections

### Client
- ✍️ Sends messages
- 👀 Displays messages from others
- 🚪 Allows leaving the chat using `exit`

## 🛠️ Requirements
- Python 3.6+
- Terminal/OS that supports multithreading

## 🚀 Running the Project

1. **Server**:
```bash
python ChatServer.py
```

2. **Client** (in a separate terminal):
```bash
python ChatClient.py
```

## 🖥️ Sample Session

```
$ python client.py
Choose your nickname: Alice
Connected to the server!
Bob has joined the chat!
Bob: Hi everyone!
Alice: Hi Bob!
```

## 📁 Project Structure

```
project2/
├── Chatclient.py   # Client implementation
├── Chatserver.py   # Server implementation
└── README.md       # Documentation
```

## 📜 License

MIT License - [LICENSE](LICENSE)
