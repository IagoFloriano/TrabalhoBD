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

util.o: util.cpp
	$(CC) $(CFLAGS) -c $^

$(EXE): conflito.o $(EXE).o visao.o util.hpp
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp util.hpp
	$(CC) $(CFLAGS) -c $^
#------------------------------------------------------------------------------
clean :
	$(RM) *.o

purge : clean
	$(RM) $(EXE)
