#include <iostream>
#include <string>
#include <fstream>
#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#else
#include<unistd.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define CloseSocket close
#endif

int main() 
{
	setlocale(LC_ALL, "");
#ifdef _WIN32
	// инициализация библиотеки Winsock
	WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0) {
		std::cerr << "Ошибка при инициализации Winsock" << std::endl;
		return 1;
	}
#else
    int result;
#endif

	// создание TCP сокета
#ifdef _WIN32
    SOCKET serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#else
    int serversocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#endif

	// связывание сокета с локальным хостом и портом
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(8000);
	result = bind(serversocket, (sockaddr*)&server_address, sizeof(server_address));
#ifdef _WIN32
	if (result != 0) {
		std::cerr << "Ошибка при связывании сокета" << std::endl;
		closesocket(serversocket);
		WSACleanup();
		return 1;
	}
#else
    if (result != 0) {
        std::cerr << "Ошибка при связывании сокета" << std::endl;
        close(serversocket);
        return 1;
    }
#endif

	// прослушивание входящих соединений
	result = listen(serversocket, SOMAXCONN);
	if (result != 0) {
		std::cerr << "Ошибка при прослушивании соединений" << std::endl;
#ifdef _WIN32
		closesocket(serversocket);
		WSACleanup();
#else
        close(serversocket);
#endif
		return 1;
	}

	// ожидание подключения клиента
#ifdef _WIN32
	sockaddr_in client_address;
	int client_address_len = sizeof(client_address);
	SOCKET clientsocket = accept(serversocket, (sockaddr*)&client_address, &client_address_len);
	char client_ip[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
	std::cout << "Подключение от " << client_ip << ":" << ntohs(client_address.sin_port) << " было успешно установлено" << std::endl;
#else
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);
    int clientsocket = accept(serversocket, (sockaddr*)&client_address, &client_address_len);
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
    std::cout << "Подключение от " << client_ip << ":" << ntohs(client_address.sin_port) << " было успешно установлено" << std::endl;
#endif

	while (true) 
	{
		std::fstream msg_file = std::fstream("../Client/messages.txt", std::ios::in | std::ios::out | std::ios::app);
		// получение сообщения от клиента
		char buffer[1024] = { 0 };
		result = recv(clientsocket, buffer, 1024, 0);
#ifdef _WIN32
		if (result == SOCKET_ERROR) {
			int error = WSAGetLastError();
			if (error == WSAECONNRESET) {
				std::cout << "Соединение было непредвиденно разорвано." << std::endl;
			}
			else {
				std::cerr << "Ошибка при чтении сообщения: " << error << std::endl;
			}
			break;
		}
#else
        if (result == -1) {
            int error = errno;
            if (error == ECONNRESET) {
                std::cout << "Соединение было непредвиденно разорвано." << std::endl;
            }
            else {
                std::cerr << "Ошибка при чтении сообщения: " << error << std::endl;
            }
            break;
        }
#endif
		else if (result == 0) {
			std::cout << "Клиент закрыл соединение" << std::endl;
			break;
		}

		std::string data = buffer;
		std::cout << "Получено сообщение: " << data << std::endl;
		msg_file << data << std::endl;
		msg_file.close();

		// отправка ответа клиенту
		std::string response = "Сообщение доставлено";
		result = send(clientsocket, response.c_str(), response.length(), 0);
#ifdef _WIN32
        if (result == SOCKET_ERROR)
        {
            std::cerr << "Ошибка при отправке сообщения" << std::endl;
            break;
        }
#else
        if (result == -1)
        {
            std::cerr << "Ошибка при отправке сообщения" << std::endl;
            break;
        }
#endif
	}

	// закрытие соединений
#ifdef _WIN32
	closesocket(clientsocket);
	closesocket(serversocket);
	WSACleanup();
#else
    close(clientsocket);
    close(serversocket);
#endif

	return 0;
}
