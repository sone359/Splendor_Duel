OBJS = main.o stockGemmes.o plateau.o sac.o pyramide.o Joueur.o Effet.o CarteRoyale.o partie.o interfaceConsole.o
CC = g++ 

test : $(OBJS)
	$(CC) -o $@ $(OBJS)

main.o : main.cpp Back/stockGemmes.h Back/plateau.h Back/sac.h Back/partie.h Console/interfaceConsole.h
	$(CC) -c $*.cpp

stockGemmes.o : Back/stockGemmes.cpp Back/stockGemmes.h tools.h
	$(CC) -c Back/$*.cpp

plateau.o : Back/plateau.cpp Back/plateau.h Back/stockGemmes.h tools.h
	$(CC) -c Back/$*.cpp

sac.o : Back/sac.cpp Back/sac.h Back/stockGemmes.h tools.h
	$(CC) -c Back/$*.cpp

pyramide.o : Back/pyramide.cpp Back/pyramide.h Back/carte_joaillerie.h tools.h
	$(CC) -c Back/$*.cpp

Joueur.o : Back/Joueur.cpp Back/Joueur.h Back/carte_joaillerie.h Back/CarteRoyale.h Back/stockGemmes.h
	$(CC) -c Back/$*.cpp

Effet.o : Back/Effet.cpp Back/Effet.h Back/carte_joaillerie.h tools.h
	$(CC) -c Back/$*.cpp

CarteRoyale.o : Back/CarteRoyale.cpp Back/CarteRoyale.h Back/Effet.h
	$(CC) -c Back/$*.cpp

partie.o : Back/partie.cpp Back/partie.h Back/stockGemmes.h tools.h Back/plateau.h Back/sac.h Back/Joueur.h Back/CarteRoyale.h Back/pyramide.h Back/carte_joaillerie.h
	$(CC) -c Back/$*.cpp

interfaceConsole.o : Console/interfaceConsole.cpp Console/interfaceConsole.h Back/plateau.h Back/Joueur.h 
	$(CC) -c Console/$*.cpp

clean : 
	rm -rf *.o

.PHONY : clean