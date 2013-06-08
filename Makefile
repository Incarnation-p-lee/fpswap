.SUFFIXES:
.SUFFIXES: .o .a .out .so


SRC       =main.c maintain.c \
           network.c textual.c \
           iofile.c


CC        =gcc
CFLAG     =-c -g -Wall -pg -pthread
DFLAG     =-shared -fPIC
LFLAG     =-pg -pthread

OBJ       =$(patsubst %.c, %.o, $(SRC))
DEPS      =fdependent
inch      =./inc
incs      =./src
INC       =-I$(inch) -I$(incs)
SHELL     =/bin/sh
TARGET    =fswap.out
OBJ_DR    =obj


vpath %.o $(OBJ_DR)

.PHONY:ALL LINK clean


ALL:$(TARGET)

-include $(DEPS)

$(OBJ):%.o:%.c
	$(CC) $(CFLAG) $(INC) -o $@ $<
	mv $@ ./obj

$(DEPS):$(SRC)
	$(CC) $(INC) -MM $^ >$@
ifneq ($(OBJ_DR), $(wildcard $(OBJ_DR)))
	mkdir $(OBJ_DR)
endif

$(TARGET):$(OBJ)
	$(MAKE) LINK

LINK:$(OBJ)
	$(CC) $(LFLAG) $(INC) -o $(TARGET) $^

clean:
	-rm -rf $(TARGET) $(DEPS) ./obj/*
