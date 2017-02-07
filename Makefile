##
## Makefile for malloc in /home/puilla_e/semestre4/psu/PSU_2016_malloc
## 
## Made by Edouard Puillandre
## Login   <puilla_e@epitech.net>
## 
## Started on  Mon Jan 30 13:49:30 2017 Edouard Puillandre
## Last update Tue Feb  7 15:51:19 2017 puilla_e
##

CC	= gcc-6

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra -Werror -fpic -g
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
