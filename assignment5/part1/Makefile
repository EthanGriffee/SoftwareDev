build:
	g++ -std=c++11 -pthread bench.cpp
	g++ -std=c++11 -o generate generate.cpp



run: 
	./generate

	@echo Map test on Rower one time 3.5 million lines:
	time ./a.out 1

	@echo PMap test on Rower one time 3.5 million lines:
	time ./a.out 2

	@echo Map test on Rower one time 1.75 million lines:
	time ./a.out 3

	@echo PMap test on Rower one time 1.75 million lines:
	time ./a.out 4

	@echo Map test on Rower one time 350k lines:
	time ./a.out 5

	@echo PMap test on Rower one time 350k lines:
	time ./a.out 6

	@echo Map test on Rower two time 3.5 million lines:
	time ./a.out 7

	@echo PMap test on Rower two time 3.5 million lines:
	time ./a.out 8

	@echo Map test on Rower two time 1.75 million lines:
	time ./a.out 9

	@echo PMap test on Rower two time 1.75 million lines:
	time ./a.out 10

	@echo Map test on Rower two time 350k lines:
	time ./a.out 11

	@echo PMap test on Rower two time 350k lines:
	time ./a.out 12