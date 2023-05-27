#include <iostream>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#define CloseSocket closesocket
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define SOCKET int
#define INVALID_SOCKET -1
#define CloseSocket close
#endif

#define MESSAGE_LENGTH 1024
#define PORT 7777

int main() 
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData); // Инициализация использования сокета на Windows
#endif

	int socket_file_descriptor, client_socket_file_descriptor, bytes_received;
	struct sockaddr_in server_address, client_address;
	char message[MESSAGE_LENGTH];

	socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);

	if (socket_file_descriptor == -1)
	{
		std::cout << "Socket creation failed.!" << std::endl;
		exit(1);
	}

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = INADDR_ANY;

	if (bind(socket_file_descriptor, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
	{
		std::cout << "Socket binding failed.!" << std::endl;
		exit(1);
	}

	if (listen(socket_file_descriptor, 5) == -1)
	{
		std::cout << "Listen failed.!" << std::endl;
		exit(1);
	}

	std::cout << "Listening for incoming connections..." << std::endl;

	while (1)
	{
		socklen_t client_address_size = sizeof(client_address);
		client_socket_file_descriptor = accept(socket_file_descriptor, (struct sockaddr *)&client_address, &client_address_size);

		if (client_socket_file_descriptor == -1)
		{
			std::cout << "Unable to accept connection.!" << std::endl;
			continue;
		}

		std::cout << "Connection accepted from " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << std::endl;

		// Принимаем и отправляем сообщения
		while (bytes_received = recv(client_socket_file_descriptor, message, sizeof(message), 0))
		{
			if (bytes_received == -1)
			{
				std::cout << "Error receiving data from client.!" << std::endl;
				break;
			}

			// Добавим символ конца строки для вывода на экран
			message[bytes_received] = '\0';

			std::cout << "Received message from client: " << message << std::endl;

			// Отправляем ответ клиенту
			send(client_socket_file_descriptor, message, bytes_received, 0);
			memset(message, 0, MESSAGE_LENGTH);
		}

		// Закрываем соединение
		if (bytes_received == 0)
		{
			std::cout << "Client disconnected.!" << std::endl;
		}
		else
		{
			std::cout << "Error in communication.!" << std::endl;
		}
#ifdef _WIN32
		closesocket(client_socket_file_descriptor);
#else
		close(client_socket_file_descriptor);
#endif
	}
#ifdef _WIN32
	closesocket(socket_file_descriptor);
#else
	close(socket_file_descriptor);
#endif

#ifdef _WIN32
	WSACleanup();
#endif

	return 0;
}