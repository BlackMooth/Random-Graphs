experiment: compile
	@echo "un cop s'executi el programa has de tornar a introduir apartat i nombre nodes al terminal"
	./graph.exe > randomGeometric_${nodes}_${apartat}.csv	

#exemple crida = >_make RGG.o
RGG.o: randomGeometric.cc GraphRGG.hh
	@g++ -c randomGeometric.cc GraphRGG.cc

#exemple crida = >_make RGG.exe
RGG.exe: randomGeometric.o GraphRGG.o
	@g++ -o graph.exe *.o

#exemple crida = >_make compile
compile: RGG.o RGG.exe

#exemple crida = >_make clean
clean:
	@rm *.o
	@rm *.exe

#exemple crida = >_make clean_all
clean_all: clean
	@rm *.csv
