EXEC=mt_mummer
CC=g++
CFLAGS=-I. 
OBJECTS= mt_mummer.o fasta.o query.o queries.o args.o
#----------------------------------------------
%.o: %.cpp	
	$(CC) -c -std=c++11 -lpthread $< $(CFLAGS)
#----------------------------------------------

#----------------------------------------------
${EXEC}: $(OBJECTS)
	$(CC) -o ${EXEC} $(OBJECTS) -lpthread
#----------------------------------------------

clean:
	rm -rf ./${EXEC}
	rm -rf ./*.o
