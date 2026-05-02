# Full Duplex GUI Chat Application

A simple full-duplex GUI chat application built using C++ and WinSock on Windows.

The project contains two applications:

- Chat Server
- Chat Client

Both applications can send and receive messages in real time. The chat messages are displayed inside a GUI window, and the conversation is automatically saved into a text file.

---

## Features

- Full-duplex communication between client and server
- GUI interface for both server and client
- Real-time message sending and receiving
- Messages appear on both sides:
  - Server window shows server messages and client messages
  - Client window shows client messages and server messages
- Chat history is saved automatically
- Uses TCP sockets with WinSock
- Written in C++

---

## Project Structure

```txt
Full_duplex_gui_chat_history/
|
├── Full_duplex_gui_work/
│   |
│   ├── Full duplex_server_gui/
│   │   ├── main.cpp
│   │   ├── Full duplex_server_gui.cbp
│   │   └── ...
│   |
│   ├── Full duplex_client_gui/
│   │   ├── main.cpp
│   │   ├── Full duplex_client_gui.cbp
│   │   └── ...
|
├── README.md
└── .gitignore
```

---

## Technologies Used

- C++
- WinSock2
- Windows API
- TCP Socket Programming
- VS Code / Code::Blocks
- MinGW g++

---

## How It Works

The application uses a client-server architecture.

The server creates a TCP socket and waits for a client connection. The client connects to the server using the local IP address:

```cpp
127.0.0.1
```

After the connection is established, both sides can send and receive messages at the same time.

This is called full-duplex communication.

---

## Server

The server application:

- Creates a socket
- Binds the socket to port `3000`
- Listens for client connections
- Accepts a client connection
- Sends messages to the client
- Receives messages from the client
- Displays all messages in the server GUI
- Saves all messages in `chat_history.txt`

Server port:

```cpp
3000
```

---

## Client

The client application:

- Creates a socket
- Connects to the server using IP `127.0.0.1`
- Sends messages to the server
- Receives messages from the server
- Displays all messages in the client GUI
- Saves all messages in `chat_history.txt`

Client connection IP:

```cpp
127.0.0.1
```

---

## Chat History

The application automatically saves the conversation in a text file called:

```txt
chat_history.txt
```

Each message is saved with:

- Date
- Time
- Sender name
- Message content

Example:

```txt
[2026-05-02 20:30:15] Server: Hello Client
[2026-05-02 20:30:18] Client: Hello Server
```

Each application creates its own `chat_history.txt` file in its running directory.

For example:

```txt
Full duplex_server_gui/chat_history.txt
Full duplex_client_gui/chat_history.txt
```

---

## How to Run Using VS Code

Before running the project, make sure you have MinGW installed and `g++` added to your system PATH.

You can check that by running:

```powershell
g++ --version
```

If the command works, you can compile and run the project.

---

## Run the Server

Open a terminal inside the server folder:

```powershell
cd "Full_duplex_gui_work\Full duplex_server_gui"
```

Compile the server:

```powershell
g++ main.cpp -o server.exe -lws2_32 -mwindows
```

Run the server:

```powershell
.\server.exe
```

The server should be started before the client.

---

## Run the Client

Open another terminal inside the client folder:

```powershell
cd "Full_duplex_gui_work\Full duplex_client_gui"
```

Compile the client:

```powershell
g++ main.cpp -o client.exe -lws2_32 -mwindows
```

Run the client:

```powershell
.\client.exe
```

After running both applications, you can start chatting.

---

## Important Notes

Start the server first, then start the client.

The server listens on port:

```txt
3000
```

The client connects to:

```txt
127.0.0.1
```

This means the project runs locally on the same device.

If you want to run the client on another device, you need to replace `127.0.0.1` with the server device IP address.

---

## Common Errors

### 1. g++ is not recognized

If you see this error:

```txt
g++ is not recognized as an internal or external command
```

That means MinGW is not installed or not added to PATH.

Install MinGW or MSYS2, then add the compiler path to the system environment variables.

---

### 2. main.cpp not found

If you see this error:

```txt
main.cpp: No such file or directory
```

That means you are not inside the correct folder.

Make sure you are inside either:

```txt
Full duplex_server_gui
```

or:

```txt
Full duplex_client_gui
```

before running the compile command.

---

### 3. WinSock errors

If you get errors related to:

```txt
socket
send
recv
bind
listen
accept
connect
```

Make sure you added this option while compiling:

```powershell
-lws2_32
```

Example:

```powershell
g++ main.cpp -o server.exe -lws2_32 -mwindows
```

---

## Main Functions

### SaveMessage

This function saves every message into `chat_history.txt`.

```cpp
void SaveMessage(const char* sender, const char* message)
```

It saves the message with date and time.

---

### AddToChat

This function displays the message inside the GUI chat box.

```cpp
void AddToChat(const char* sender, const char* message)
```

---

### ReceiveThread

This function keeps receiving messages in the background.

```cpp
DWORD WINAPI ReceiveThread(LPVOID arg)
```

It allows the program to receive messages while the user can still send messages.

---

### SendMsg

This function sends the message written by the user.

```cpp
void SendMsg()
```

It also displays the sent message in the GUI and saves it in the history file.

---

## Example Output

Server window:

```txt
System: Waiting for client...
System: Client connected
Server: Hello
Client: Hi
Server: How are you?
Client: Fine
```

Client window:

```txt
System: Connected to server
Server: Hello
Client: Hi
Server: How are you?
Client: Fine
```

---

## Future Improvements

Possible improvements for this project:

- Add username support
- Add multiple clients
- Add private messages
- Add message encryption
- Add better GUI design
- Add file transfer
- Save chat history in JSON format
- Add login and registration system

---

## Author

Created as a C++ socket programming project.

---

## License

This project is for educational purposes.
