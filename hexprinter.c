/*
** hexprinter.c for malloc in /home/puilla_e/semestre4/psu/PSU_2016_malloc
**
** Made by Edouard Puillandre
** Login   <puilla_e@epitech.net>
**
** Started on  Fri Jan 27 13:42:04 2017 Edouard Puillandre
** Last update Fri Jan 27 13:49:28 2017 Edouard Puillandre
*/

#include <unistd.h>

static void printnbhex_rec(unsigned long ptr)
{
  char c;
  if (ptr == 0)
    return ;
  printnbhex_rec(ptr / 16);
  c = ptr % 16;
  if (c >= 10)
    c = 'A' + c - 10;
  else
    c = c + '0';
  write(1, &c, 1);
}

void printnbhex(void *ptr)
{
  if (ptr == 0)
    {
      write(1, "0", 1);
      return ;
    }
  write(1, "0x", 2);
  printnbhex_rec((unsigned long) ptr);
}
