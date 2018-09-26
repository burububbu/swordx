#set compiler
CC = gcc

#set obj folder
OBJD = obj

#set library folder
LIBD = library

#paratmeters-making arguments -Wall view errors and warnings, -I$(LIBD) specifies the location of past files
CFLAGS = -Wall -I$(LIBD)

# objects includes
OBJ =$(OBJD)/swordx.o \
	$(OBJD)/node.o \
	$(OBJD)/parLog.o \
	
# c,h folders
vpath %.c src
vpath %.h $(LIBD)

# all needs swordx
all: swordx

# swordx include objects
swordx: $(OBJ)
	$(CC) $^ $(CFLAGS) -o $@

# objects are into OBJD and include .c and .h
$(OBJD)/%.o: %.c %.h
	$(CC) $(CFLAGS) -o $@ -c $<

# node include node.h
$(OBJD)/node.o: node.c node.h
	$(CC) $(CFLAGS) -o $@ -c $<
	
# parLog include parLog.h
$(OBJD)/parLog.o: parLog.c parLog.h
	$(CC) $(CFLAGS) -o $@ -c $<

# swordx needs .c and all .h files
$(OBJD)/swordx.o: swordx.c node.h parLog.h
	$(CC) $(CFLAGS) -o $@ -c $<

# The .PHONY rule keeps make from doing something with a file named clean
.PHONY: clean
clean:
	rm swordx obj/*.o