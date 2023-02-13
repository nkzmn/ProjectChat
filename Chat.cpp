#include "Chat.h"

void menu()
{
	int choice = 0;
	while (choice < 1 || choice > 3)
	{
		std::cout << "1 - регистрация/вход, 2 - чат, 3 - выход" << std::endl;
		std::cin >> choice;

		switch (choice)
		{
		case 1:

			break;
		case 2:

			break;
		case 3:
			exit(0);
			break;
		default:
			std::cout << "Неверное значение!" << std::endl;
			break;
		}
	}
}

void chat()
{
	menu();
}