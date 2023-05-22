SRC = ../source/Chat.cpp Main.cpp
HEADER = ../include/User.h ../include/Message.h ../include/Chat.h
TARGET = Server
PREFIX = /usr/local/bin

server: $(SRC)
	g++ -o $(TARGET) $(HEADER) $(SRC)

install: 
	install $(TARGET) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGET)
