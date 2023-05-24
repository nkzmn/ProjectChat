#include "../include/Chat.h"

int main()
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData); // Инициализация использования сокета на Windows
#endif

	Client client;

	client.socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (client.socket_file_descriptor == -1) {
		std::cout << "Creation of Socket failed!" << std::endl;
		exit(1);
	}

	// Установим адрес сервера
	client.serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	// Зададим номер порта
	client.serveraddress.sin_port = htons(PORT);
	// Используем IPv4
	client.serveraddress.sin_family = AF_INET;
	// Установим соединение с сервером
	client.connection = connect(client.socket_file_descriptor, (struct sockaddr*)&client.serveraddress, sizeof(client.serveraddress));
	if (client.connection == -1) {
		std::cout << "Connection with the server failed.!" << std::endl;
		exit(1);
	}

	Chat chat;

	chat.startChat();

	while (chat.isChatWork())
	{
		chat.showLoginMenu();
		
		while (chat.getCurrentUser())
		{
			chat.showUserMenu();
		}
	}

	// закрываем сокет, завершаем соединение
#ifdef _WIN32
	closesocket(client.connection);
	closesocket(client.socket_file_descriptor);
	WSACleanup(); // Очистка сокета на Windows
#else
	close(client.connection);
	close(client.sockert_file_descriptor);
#endif

	return 0;
}