#include "Chat.h"
#include <clocale>
int main()
{
	setlocale (LC_ALL, "");

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
	
	return 0;
}