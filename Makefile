.SUFFIXES:
.SUFFIXES: .o .a .out .so


SRC       =main.c textual.c


CC        =gcc
CFLAG     =-c -g -Wall -pg
DFLAG     =-shared -fPIC
LFLAG     =-pg

OBJ       =$(patsubst %.c, %.o, $(SRC))
DEPS      =fdependent
inch      =./inc
incs      =./src
INC       =-I$(inch) -I$(incs)
SHELL     =/bin/sh
TARGET    =fswap.out


vpath %.o ./obj

.PHONY:ALL LINK clean


ALL:$(TARGET)

-include $(DEPS)

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $(INC) -o $@ $<
	mv $@ ./obj

$(DEPS):$(SRC)
	$(CC) $(INC) -MM $^ >$@

$(TARGET):$(OBJ)
	$(MAKE) LINK

LINK:$(OBJ)
	$(CC) $(LFLAG) $(INC) -o $(TARGET) $^

clean:
	-rm -rf $(TARGET) $(DEPS) ./obj/*
