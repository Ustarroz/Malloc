/*
** fct_mutex.c for PSU_2016_malloc in /home/puilla_e/Documents/semestre4/psu/PSU_2016_malloc
**
** Made by puilla_e
** Login   <puilla_e@epitech.net>
**
** Started on  Thu Feb  9 15:57:50 2017 puilla_e
** Last update Thu Feb  9 16:28:52 2017 puilla_e
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"
#include <stdint.h>
#include "hexprinter.h"

static t_metadata	*list = NULL;

void	*calloc_mutex(size_t nmenb, size_t size)
{
  void	*tmp;

  if ((tmp = malloc_mutex(size * nmenb)) == NULL)
    return (NULL);
  memset(tmp, 0, size * nmenb);
  return (tmp);
}

void		*realloc_mutex(void *ptr, size_t size)
{
  void          *cpy;
  t_metadata    node;
  t_metadata    *tmp;

  if (ptr == NULL)
    return (malloc_mutex(size));
  if ((tmp = ptr_to_metadata(ptr, list)) == NULL)
    return (ptr);
  if (tmp->size == size)
    return (ptr);
  if (tmp->size < size)
    {
      if ((cpy = malloc_mutex(size)) == NULL)
	return (NULL);
      memcpy(cpy, ptr, tmp->size);
      free_mutex(ptr);
      return (cpy);
    }
  tmp->free = false;
  node = *tmp;
  tmp->size = (node.size - size >= METADATA_SIZE) ? size : tmp->size;
  if (node.size - size >= METADATA_SIZE)
    set_mem(tmp, &node);
  return (tmp->data);
}

void		*malloc_mutex(size_t size)
{
  t_metadata	*tmp;
  size_t	size_pad;

  if (SIZE_MAX - METADATA_SIZE < size)
    return (NULL);
  size_pad = (size == 0) ? size : (size - 1) / 8 * 8 + 8;
  if (list == NULL)
    {
      if ((tmp = add_first(size_pad, &list)) == NULL)
	return (NULL);
    }
  else
    if ((tmp = add_in_list(size_pad, list)) == NULL)
      return (NULL);
  return (tmp->data);
}

void		free_mutex(void *ptr)
{
  t_metadata	*tmp;
  size_t	pages;

  pages = getpagesize();
  if ((tmp = ptr_to_metadata(ptr, list)) == NULL || tmp->free == true)
    return ;
  tmp->free = true;
  if (tmp->next != NULL && tmp->next->free == true)
    tmp = merge_free(tmp);
  if (tmp->prev != NULL && tmp->prev->free == true)
    tmp = merge_free(tmp->prev);
  if (tmp->next == NULL && tmp == list)
    {
      sbrk_size((sbrk(0) - (void *) list) / pages, pages, -1);
      list = NULL;
    }
  else if (tmp->next == NULL && ((void *) tmp - (void *) list) / pages <
	   (tmp->data + tmp->size - (void *) list) / pages)
    {
      tmp->prev->next = NULL;
      sbrk_size(((void *)tmp - (void *)list) / pages + 1
		- (sbrk(0) - (void *)list) / pages, pages, -1);
    }
}

void		show_alloc_mem_mutex(void)
{
  t_metadata	*tmp;

  my_putstr("break : ");
  printnbhex(sbrk(0));
  write (1, "\n", 1);
  if (list == NULL)
    return ;
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
