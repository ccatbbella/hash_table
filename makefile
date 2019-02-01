all: prog1A prog1B
prog1A: hash.h
	g++ hash.cpp prog1B.cpp -o prog1A
prog1B: hash.h
	g++ hash.cpp prog1B.cpp -o prog1B
clean:
	rm -f prog1B prog1A
