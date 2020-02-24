build:
	g++ -std=c++11 -pthread -o master master.cpp
	g++ -std=c++11 -pthread -o node node.cpp

run:
	./master -ip 127.0.0.1 -port 8080 &
	./node -ip 127.0.0.2 -port 8333 -serverip 127.0.0.1 -serverport 8080 &
	./node -ip 127.0.0.3 -port 9432 -serverip 127.0.0.1 -serverport 8080 &
	./node -ip 127.0.0.4 -port 9333 -serverip 127.0.0.1 -serverport 8080