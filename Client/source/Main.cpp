#include "../include/Chat.h"

int main()
{
	std::setlocale(LC_ALL, "");
/*#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData); // Инициализация использования сокета на Windows
#endif*/

	Chat chat;

	/*WSADATA wsa_data;
	int result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
	if (result != 0) {
		std::cerr << "Ошибка при инициализации Winsock" << std::endl;
		return 1;
	}*/

	// подключение к серверу
	/*SOCKET clientsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_address.sin_port = htons(8000);
	result = connect(clientsocket, (sockaddr*)&server_address, sizeof(server_address));
	if (result == SOCKET_ERROR) {
		std::cerr << "Ошибка при подключении к серверу" << std::endl;
		closesocket(clientsocket);
		WSACleanup();
		return 1;
	}*/
	
	chat.tcpConnect();

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
/*#ifdef _WIN32
	closesocket(chat.connection);
	closesocket(chat.socket_file_descriptor);
	WSACleanup(); // Очистка сокета на Windows
#else
	close(chat.connection);
	close(chat.sockert_file_descriptor);
#endif*/

	closesocket(chat.clientsocket);
	WSACleanup();

	return 0;
}