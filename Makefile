
 #
 # Author: Hermann Stamm-Wilbrandt
 #         Institut fuer Informatik III
 #         Roemerstr. 164 
 #         Bonn University
 #         D-53117 Bonn 
 #         Germany
 # email:  hermann@holmium.informatik.uni-bonn.de
 # phone:  0228-550-260  internal: x260 or x28, Fax: 0228-550-382
 #
 # For my safety:
 #
 # The programs are distributed in the hope that they will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 #

CC     = gcc                                       # SUN
CFLAGS = -D__linux__ -g # -Wall -I$(XHOME)/include  -DCHECK      # SUN 
OBJS0   = basic.o array.o set.o b_stack.o list.o 

LIBS0 = -lm

all:	randomgraph

basic.o: basic.h
	$(CC) $(CFLAGS) -c basic.c

array.o: array.h
	$(CC) $(CFLAGS) -c array.c

set.o: set.h
	$(CC) $(CFLAGS) -c set.c

list.o: list.h
	$(CC) $(CFLAGS) -c list.c

b_stack.o: b_stack.h
	$(CC) $(CFLAGS) -c b_stack.c

is_embedding.o: is_embedding.c is_embedding.h
	$(CC) $(CFLAGS) -c is_embedding.c

randomgraph: $(OBJS0) randomgraph.o randomgrapho.o triangulate.o is_embedding.o
	$(CC) $(CFLAGS) $(OBJS0) randomgraph.o randomgrapho.o triangulate.o is_embedding.o -o randomgraph $(LIBS0)

triangulate.o: triangulate.c triangulate.h
	$(CC) $(CFLAGS) -c triangulate.c


clean:	
	rm -f core *.o randomgraph *.u *.ps

