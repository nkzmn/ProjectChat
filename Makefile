TARGETCLIENT = Client
TARGETSERVER = Server

# Directories
CLIENT_DIR = Client
SERVER_DIR = TcpServer

# Source files
CLIENT_SOURCES = $(wildcard $(CLIENT_DIR)/source/*.cpp)
SERVER_SOURCES = $(wildcard $(SERVER_DIR)/source/*.cpp)

# Include directories
CLIENT_INCLUDES = $(wildcard $(CLIENT_DIR)/include/*.h)

PREFIX = /usr/local/bin

client:
	g++ -o Client $(CLIENT_INCLUDES) $(CLIENT_SOURCES)

server:
	g++ -o Server $(SERVER_SOURCES)

install: 
	install $(TARGETCLIENT) $(PREFIX)
	install $(TARGETSERVER) $(PREFIX)

uninstall:
	rm -rf $(PREFIX)/$(TARGETCLIENT)
	rm -rf $(PREFIX)/$(TARGETSERVER)

