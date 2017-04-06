#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'Recebimentos.c'
# 'make clean'  removes all .o and executable files
#
# define the C compiler to use
CC = gcc
# define any compile-time flags
CFLAGS = -g -std=c99
# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lm
# define the C source files
SRCS = Cliente.c Recebimento.c Recebimentos.c ClienteExcecoes.c RecebimentoExcecoes.c RecebimentosExcecoes.c dependencias/stringHandling.c dependencias/data.c
# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)
# define the executable file 
MAIN = App
#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#
.PHONY: depend clean
all:$(MAIN)
		@echo Executavel $(MAIN) criado com sucesso.
$(MAIN): $(OBJS) 
		$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS) $(MAIN).c
# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@
clean:
		$(RM) *.o *~ $(MAIN)
depend: $(SRCS)
		makedepend $(INCLUDES) $^
# DO NOT DELETE THIS LINE -- make depend needs
		
