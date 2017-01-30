##
## Makefile for malloc in /home/puilla_e/semestre4/psu/PSU_2016_malloc
## 
## Made by Edouard Puillandre
## Login   <puilla_e@epitech.net>
## 
## Started on  Mon Jan 30 13:49:30 2017 Edouard Puillandre
## Last update Mon Jan 30 13:56:47 2017 Edouard Puillandre
##

CC	= gcc

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra -Werror -fpic
CFLAGS	+=

LFLAGS	+= -pthread

LIBNAME	= libmy_malloc.so

LIBSRC	= malloc.c \
	  hexprinter.c \
	  fct_malloc.c \
	  fct_free.c

LIBOBJ	= $(LIBSRC:.c=.o)

$(LIBNAME): $(LIBOBJ)
	$(CC) -shared -o $(LIBNAME) $(LIBOBJ) $(LFLAGS)

all: $(LIBNAME)

clean:
	$(RM) $(LIBOBJ)

fclean: clean
	$(RM) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
