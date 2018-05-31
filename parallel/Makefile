EXEC=premummer
CC=g++
CFLAGS=-I. 

#----------------------------------------------
%.o: %.cpp	
	$(CC) -c -std=c++11 -lpthread $< $(CFLAGS)
#----------------------------------------------

#----------------------------------------------
${EXEC}: premummer.o
	$(CC) -o ${EXEC} premummer.o -lpthread
#----------------------------------------------

clean:
	rm -rf ./${EXEC}
	rm -rf ./*.o
