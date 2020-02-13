run: dircheck
	- make first

first:
	docker build -t cs4500:0.1 .
	cp *.h ./part1
	- docker run -ti -v "$$(pwd)/part1":/part1 cs4500:0.1 bash -c "cd ./part1; cmake ."
	- docker run -ti -v "$$(pwd)/part1":/part1 cs4500:0.1 bash -c "cd ./part1; make basic_example && ./basic_example"
