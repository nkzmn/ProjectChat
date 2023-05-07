К исправлению:
1. ~~Файл User.h - void setUserGender(int gender) { _gender=gender; }  параметр имеет значение int~~ (исправленно)
2. ~~Возможно использовать std::vector<char> _password через std::string~~ (нет возможности)
3. ~~Файл Message.h #include "User.h" – лишний~~ (исправленно)
4. ~~Файл Chat.cpp строка 152 – переменная char с; в коде не используется???~~ (используется)
5. ~~Строка 223 и 226 вместо _messages.push_back(Message{ _currentUser->getUserLogin(), "All", text }) - _messages.emplace_back(_currentUser->getUserLogin(), "All", text)~~ (исправленно)
