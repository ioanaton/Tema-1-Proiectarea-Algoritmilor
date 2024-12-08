# Exemplu de Makefile pentru soluții scrise în C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: p1 p2 p3 p4 p5
run-p1:
	./p1
run-p2:
	./p2
run-p3:
	./p3
run-p4:
	./p4
run-p5:
	./p5

# Nu uitați să modificați numele surselor și, eventual, ale executabilelor.
p1: 
	$(CC) -o $@ $^ $(CCFLAGS) feribot.cpp
p2: 
	$(CC) -o $@ $^ $(CCFLAGS) nostory.cpp
p3: 
	$(CC) -o $@ $^ $(CCFLAGS) sushi.cpp
p4: 
	$(CC) -o $@ $^ $(CCFLAGS) semnale.cpp
p5: 
	$(CC) -o $@ $^ $(CCFLAGS) badgpt.cpp
	


# Vom șterge executabilele.
clean:
	rm -f p1 p2 p3 p4 p5
