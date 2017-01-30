CC	= gcc

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra -Werror -fpic -g
CFLAGS	+=

LFLAGS	+= -pthread

LIBNAME	= libmy_malloc.so

LIBSRC	= malloc.c hexprinter.c fct_malloc.c fct_free.c

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
