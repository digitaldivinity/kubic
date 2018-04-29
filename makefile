kubic.o: kubic.cpp
	g++ -Wall -ansi -c kubic.cpp
kubic : kubic.o
	g++ -Wall -ansi kubic.o -o kubic -lsfml-graphics -lsfml-window -lsfml-system
run: kubic
	./kubic
