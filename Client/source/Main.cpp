#include "../include/Chat.h"

int main()
{
#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData); // Инициализация использования сокета на Windows
#endif

	std::ifstream msg_file("messages.txt");

	if (!msg_file.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		exit(1);
	}

	Chat chat;

	chat.socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
	if (chat.socket_file_descriptor == -1) {
		std::cout << "Creation of Socket failed!" << std::endl;
		exit(1);
	}

	// Установим адрес сервера
	chat.serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
	// Зададим номер порта
	chat.serveraddress.sin_port = htons(PORT);
	// Используем IPv4
	chat.serveraddress.sin_family = AF_INET;
	// Установим соединение с сервером
	chat.connection = connect(chat.socket_file_descriptor, (struct sockaddr*)&chat.serveraddress, sizeof(chat.serveraddress));
	if (chat.connection == -1) {
		std::cout << "Connection with the server failed.!" << std::endl;
		exit(1);
	}
	else
	{
		std::cout << "Connection established with the server!" << std::endl;
		std::cout << "---------------------------------------" << std::endl;
	}


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
	closesocket(chat.connection);
	closesocket(chat.socket_file_descriptor);
	WSACleanup(); // Очистка сокета на Windows
#else
	close(chat.connection);
	close(chat.sockert_file_descriptor);
#endif

	return 0;
}