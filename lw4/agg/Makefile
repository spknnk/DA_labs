ag : main.o apostolico.o
	g++ -Wall -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -o ag main.o apostolico.o
main.o : main.cpp apostolico.h
	g++ -std=c++14 -c main.cpp
apostolico.o : apostolico.cpp apostolico.h
	g++ -std=c++14 -c apostolico.cpp
clear :
	rm *.o ag