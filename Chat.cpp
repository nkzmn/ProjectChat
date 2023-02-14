#include "Chat.h"

void menu()
{
    int choice = 0;
    int id = -1;
    while (choice < 1 || choice > 3)
    {
        std::cout << "1 - Регистрация/вход\n2 - Чат\n3 - Выход" << std::endl;
        std::cin >> choice;

        switch (choice)
        {
            //Регистрация/вход
        case 1:
            //user;
            if (id == 0)
                return;//registration;
            else if (id > 0)
                return;//login;
            else
            {
                std::cout << "Неккоректный id" << std::endl;
                choice = 0;
            }
            break;

            //Сообщения
        case 2:
        {
            int choice2 = 0;
            while (choice2 < 1 || choice2 > 3)
            {
                std::cout << "1 - Написать сообщение\n2 - Показать сообщения\n3 - Назад" << std::endl;
                std::cin >> choice2;

                switch (choice2)
                {
                case 1:
                    return; //writeMessage;
                    break;
                case 2:
                    return; //getMessage;
                    break;
                case 3:
                    choice = 0;
                    break;
                default:
                    std::cout << "Неверное значение!" << std::endl;
                    break;
                }
            }
            break;
        }
        //Выход
        case 3:
            exit(0);
            break;
        default:
            std::cout << "Неверное значение!" << std::endl;
            break;
        }
    }
}