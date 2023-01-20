### Created by Michael Janeway on Sept 26, 2022

boggle: boggle.o dictionary.o boardGenerator.o scoreboard.o wordChecker.o menu.o
	gcc -Wall -std=c99 dictionary.o boardGenerator.o scoreboard.o wordChecker.o menu.o boggle.o -o boggle
boggle.o: boggle.c dictionary.h boardGenerator.h wordChecker.h scoreboard.h
	gcc -Wall -std=c99 -c boggle.c
dictionary.o: dictionary.c dictionary.h
	gcc -Wall -std=c99 -c dictionary.c
boardGenerator.o: boardGenerator.c boardGenerator.h
	gcc -Wall -std=c99 -c boardGenerator.c
scoreboard.o: scoreboard.c scoreboard.h
	gcc -Wall -std=c99 -c scoreboard.c
wordChecker.o: wordChecker.c wordChecker.h
	gcc -Wall -std=c99 -c wordChecker.c
menu.o: menu.c menu.h
	gcc -Wall -std=c99 -c menu.c
test: scoreboard.o testHarness.o
	gcc -Wall -std=c99 scoreboard.o testHarness.o -o test
testHarness.o:
	gcc -Wall -std=c99 -c testHarness.c
clean:
	rm -f *.o boggle test
clear:#for windows users
	del *.o *.exe