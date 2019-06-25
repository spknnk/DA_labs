all : lw2

lw2 : main.o rb.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o lw2 main.o rb.o
main.o : main.cpp rb.h
	g++ -std=c++14 -c -O3 main.cpp
rb.o : rb.cpp rb.h
	g++ -std=c++14 -c -O3 rb.cpp
clean :
	rm -f *.o