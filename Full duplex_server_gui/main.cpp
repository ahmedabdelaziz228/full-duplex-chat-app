#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#pragma comment(lib, "ws2_32.lib")

HWND hChat, hInput;
SOCKET client_socket;

void SaveMessage(const char* sender, const char* message)
{
    FILE* file = fopen("chat_history.txt", "a");

    if (file == NULL)
        return;

    time_t now = time(NULL);
    struct tm* t = localtime(&now);

    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", t);

    fprintf(file, "[%s] %s: %s\n", timeStr, sender, message);

    fclose(file);
}

void AddToChat(const char* sender, const char* message)
{
    char oldText[8192];

    GetWindowText(hChat, oldText, sizeof(oldText));

    strcat(oldText, sender);
    strcat(oldText, ": ");
    strcat(oldText, message);
    strcat(oldText, "\r\n");

    SetWindowText(hChat, oldText);
}

DWORD WINAPI ReceiveThread(LPVOID arg)
{
    char buffer[1024];

    while (1)
    {
        int received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        if (received > 0)
        {
            buffer[received] = '\0';

            AddToChat("Client", buffer);
            SaveMessage("Client", buffer);
        }
        else
        {
            AddToChat("System", "Client disconnected");
            break;
        }
    }

    return 0;
}

void SendMsg()
{
    char msg[1024];

    GetWindowText(hInput, msg, sizeof(msg));

    if (strlen(msg) == 0)
        return;

    send(client_socket, msg, strlen(msg), 0);

    AddToChat("Server", msg);
    SaveMessage("Server", msg);

    SetWindowText(hInput, "");
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            hChat = CreateWindow(
                "EDIT",
                "",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
                10, 10, 450, 250,
                hwnd,
                NULL,
                NULL,
                NULL
            );

            hInput = CreateWindow(
                "EDIT",
                "",
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                10, 270, 330, 30,
                hwnd,
                NULL,
                NULL,
                NULL
            );

            CreateWindow(
                "BUTTON",
                "Send",
                WS_VISIBLE | WS_CHILD,
                350, 270, 110, 30,
                hwnd,
                (HMENU)1,
                NULL,
                NULL
            );

            break;
        }

        case WM_COMMAND:
        {
            if (LOWORD(wp) == 1)
                SendMsg();

            break;
        }

        case WM_DESTROY:
        {
            closesocket(client_socket);
            WSACleanup();
            PostQuitMessage(0);
            break;
        }
    }

    return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR args, int ncmd)
{
    WSADATA wsa;
    SOCKET server_socket;

    WSAStartup(MAKEWORD(2, 2), &wsa);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(3000);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server, sizeof(server));
    listen(server_socket, 1);

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "ChatServer";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        "ChatServer",
        "Chat Server",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        200, 200, 500, 370,
        NULL,
        NULL,
        hInst,
        NULL
    );

    AddToChat("System", "Waiting for client...");

    client_socket = accept(server_socket, NULL, NULL);

    AddToChat("System", "Client connected");

    CreateThread(NULL, 0, ReceiveThread, NULL, 0, NULL);

    MSG message;

    while (GetMessage(&message, NULL, 0, 0))
    {
        TranslateMessage(&message);
        DispatchMessage(&message);
    }

    closesocket(server_socket);

    return 0;
}