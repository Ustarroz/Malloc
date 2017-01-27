/*
** malloc.c for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
**
** Made by voyevoda
** Login   <voyevoda@epitech.net>
**
** Started on  Thu Jan 26 14:51:23 2017 voyevoda
** Last update Fri Jan 27 16:58:31 2017 voyevoda
*/

#include <stdio.h>
#include <unistd.h>
#include "malloc.h"
#include "hexprinter.h"

static t_metadata	*list = NULL;

t_metadata	*add_first(size_t size)
{
  t_metadata	*tmp;
  int		pages;
  int		nb;

  pages = getpagesize();
  nb = (size + METADATA_SIZE) / pages;
  if ((size + METADATA_SIZE) % pages != 0)
    ++nb;
  if ((tmp = sbrk(nb * pages)) == NULL)
    return (NULL);
  tmp->next = NULL;
  tmp->prev = NULL;
  tmp->size = size;
  tmp->free = false;
  tmp->data = (void *)tmp + METADATA_SIZE;
  list = tmp;
  return (tmp);
}

void	*malloc(size_t size)
{
  t_metadata	*tmp;

  if (list == NULL)
    {
      if ((tmp = add_first(size)) == NULL)
	return (NULL);
    }
  else
    if ((tmp = add_in_list(size, list)) == NULL)
      return (NULL);
  return tmp->data;
}

t_metadata	*merge_free(t_metadata *tmp)
{
  t_metadata	*node;

  node = tmp->next;
  tmp->size += node->size + METADATA_SIZE;
  tmp->next = node->next;
  if (node->next != NULL)
    node->next->prev = tmp;
  return (tmp);
}

void	free(void *ptr)
{
  t_metadata	*tmp;
  unsigned int	pages;

  pages = getpagesize();
  if (ptr == NULL)
    return;
  tmp = ptr - METADATA_SIZE;
  tmp->free = true;
  if (tmp->next != NULL && tmp->next->free == true)
    tmp = merge_free(tmp);
  if (tmp->prev != NULL && tmp->prev->free == true)
    tmp = merge_free(tmp->prev);
  if (tmp->next == NULL && ptr == list)
    {
      sbrk(-(tmp->size + METADATA_SIZE));
      list = NULL;
    }
  else if (tmp->next == NULL && ((void *) tmp - (void *) list) / pages <
	   (tmp->data + tmp->size - (void *) list) / pages)
    {
      tmp->prev->next = NULL;
      sbrk((((void *)tmp - (void *)list) /
	    pages + 1 - (sbrk(0) - (void *)list) / pages) * pages);
    }
}

void	show_alloc_mem()
{
  t_metadata *tmp;

  my_putstr("break : ");
  printnbhex(sbrk(0));
  write (1, "\n", 1);
  if (list == NULL)
    return;
  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->free == false)
	{
	  printnbhex(tmp->data);
	  my_putstr(" - ");
	  printnbhex(tmp->data + tmp->size);
	  my_putstr(" : ");
	  printnbdec(tmp->size);
	  write(1, "\n", 1);
	}
      tmp = tmp->next;
    }
}
