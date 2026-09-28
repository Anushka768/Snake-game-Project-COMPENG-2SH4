CC=g++
CFLAGS=-I. -g
OBJ = GameMechs.o objPos.o objPosArrayList.o MacUILib.o Player.o Food.o Project.o 
DEPS = *.h
EXEC = Project

ifeq (${OS}, Windows_NT)
	OSSETTING = -DWINDOWS
else
	OSSETTING = -DPOSIX
	POSTLINKER = -lncurses
endif

%.o: %.cpp $(DEPS)
	$(CC) ${OSSETTING} -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC) ${OSSETTING} -o $@ $^ $(CFLAGS) ${POSTLINKER}

clean :
	rm -f ${OBJ} ${EXEC} ${EXEC}.exe
	

