build:
	g++ -std=c++11 -pthread -o client client.cpp
	g++ -std=c++11 -pthread -o server server.cpp

run:
	./server -ip 127.0.0.1 -port 8081 &
	./client -ip 127.0.0.1 -port 8333 -serverip 127.0.0.1 -serverport 8081 &
	./client -ip 127.0.0.1 -port 9432 -serverip 127.0.0.1 -serverport 8081 &
	./client -ip 127.0.0.1 -port 9333 -serverip 127.0.0.1 -serverport 8081
