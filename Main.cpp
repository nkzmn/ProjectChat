#include "Chat.h"

int main(int argc, char* argv[])
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