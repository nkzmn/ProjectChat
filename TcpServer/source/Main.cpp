#include <iostream>
#include <string.h>

#ifdef _WIN32
#include <winsock2.h>
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

	struct sockaddr_in serveraddress, client;

#ifdef _WIN32
	int length;
#else
	socklen_t length;
#endif

	SOCKET sockert_file_descriptor, connection;
	int bind_status, connection_status;
	char message[MESSAGE_LENGTH];

	// Создадим сокет
	sockert_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (sockert_file_descriptor == INVALID_SOCKET)
	{
		std::cout << "Socket creation failed.!" << std::endl;
		exit(1);
	}
	 
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	// Зададим номер порта для связи
	serveraddress.sin_port = htons(PORT);
	// Используем IPv4
	serveraddress.sin_family = AF_INET;
	// Привяжем сокет
	bind_status = bind(sockert_file_descriptor, (struct sockaddr*)&serveraddress,
		sizeof(serveraddress));
	if (bind_status == -1) {
		std::cout << "Socket binding failed.!" << std::endl;
		exit(1);
	}
	// Поставим сервер на прием данных 
	connection_status = listen(sockert_file_descriptor, 5);
	if (connection_status == -1) {
		std::cout << "Socket is unable to listen for new connections.!" << std::endl;
		exit(1);
	}
	else {
		std::cout << "Server is listening for new connection: " << std::endl;
	}
	length = sizeof(client);
	connection = accept(sockert_file_descriptor, (struct sockaddr*)&client, &length);
	if (connection == -1) {
		std::cout << "Server is unable to accept the data from client.!" << std::endl;
		exit(1);
	}

/*	while (1) 
	{
#ifdef _WIN32
		memset(message, 0, MESSAGE_LENGTH);
		recv(connection, message, sizeof(message), 0);
		if (strncmp("end", message, 3) == 0)
		{
			std::cout << "Client Exited." << std::endl;
			std::cout << "Server is Exiting..!" << std::endl;
			break;
		}
		std::cout << "Data received from client: " << message << std::endl;
		memset(message, 0, MESSAGE_LENGTH);
		std::cout << "Enter the message you want to send to the client: " << std::endl;
		std::cin >> message;
		int bytes = send(connection, message, sizeof(message), 0);

#else
		bzero(message, MESSAGE_LENGTH);
		read(connection, message, sizeof(message));
		if (strncmp("end", message, 3) == 0) {
			std::cout << "Client Exited." << std::endl;
			std::cout << "Server is Exiting..!" << std::endl;
			break;
		}
		std::cout << "Data received from client: " << message << std::endl;
		bzero(message, MESSAGE_LENGTH);
		std::cout << "Enter the message you want to send to the client: " << std::endl;
		std::cin >> message;
		ssize_t bytes = write(connection, message, sizeof(message));

#endif

		// Если передали >= 0  байт, значит пересылка прошла успешно
		if (bytes >= 0) 
		{
			std::cout << "Data successfully sent to the client.!" << std::endl;
		}
	}
*/
	// закрываем сокет, завершаем соединение
#ifdef _WIN32
	closesocket(connection);
	closesocket(sockert_file_descriptor);
	WSACleanup(); // Очистка сокета на Windows
#else
	close(connection);
	close(sockert_file_descriptor);
#endif

	return 0;
}