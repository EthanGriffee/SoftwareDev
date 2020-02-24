build:
	g++ -std=c++11 -pthread -o server server.cpp
	g++ -std=c++11 -pthread -o client client.cpp

run:
	./server -ip 127.0.0.1 &
	./client -ip 127.0.0.2 &
	./client -ip 127.0.0.3 &
	./client -ip 127.0.0.4 