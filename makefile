DEBUG_FLAGS = -g -DDEBUG
CFLAGS = -Wall -std=c++17
EXE = escalona
CC = g++

#------------------------------------------------------------------------------
.PHONY : all clean

#------------------------------------------------------------------------------
all : $(EXE)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: all


$(EXE): conflito.o $(EXE).o visao.o util.o
	$(CC) -o $@ $^ $(CFLAGS)

util.o: util.cpp
%.o: %.cpp
	$(CC) $(CFLAGS) -c $^
#------------------------------------------------------------------------------
clean :
	$(RM) *.o

purge : clean
	$(RM) $(EXE)
