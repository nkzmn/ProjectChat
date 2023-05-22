SRC = Chat.cpp Main.cpp
HEADER = User.h Message.h Chat.h
TARGET = Chat
PREFIX = /usr/local/bin

chat: $(SRC)
	g++ -o $(TARGET) $(HEADER) $(SRC)

install: 
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
