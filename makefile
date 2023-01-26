DEBUG_FLAGS = -g -DDEBUG
CFLAGS = -Wall -std=gnu99 -lm
EXE = escalona
CC = g++

#------------------------------------------------------------------------------
.PHONY : all clean

#------------------------------------------------------------------------------
all : $(EXE)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

$(EXE): conflito.o $(EXE).o visao.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^
#------------------------------------------------------------------------------
clean :
	$(RM) *.o

purge : clean
	$(RM) $(EXE)
