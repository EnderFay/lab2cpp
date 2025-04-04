all: a

a: head.h main.cpp func.cpp
	g++ head.h main.cpp func.cpp -o a

clean:
	rm -f a
