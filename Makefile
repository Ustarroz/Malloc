CC	= gcc

RM	= rm -f

CFLAGS	+= -W -Wall -Wextra -Werror -fpic
CFLAGS	+=

LFLAGS	+=

LIBNAME	= libmy_malloc.so

LIBSRC	= malloc.c hexprinter.c

LIBOBJ	= $(LIBSRC:.c=.o)

$(LIBNAME): $(LIBOBJ)
	$(CC) -shared -o $(LIBNAME) $(LIBOBJ)

all: $(LIBNAME)

clean:
	$(RM) $(LIBOBJ)

fclean: clean
	$(RM) $(LIBNAME)

re: fclean all

.PHONY: all clean fclean re
