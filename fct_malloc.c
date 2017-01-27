/*
** fct_malloc.c for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
**
** Made by voyevoda
** Login   <voyevoda@epitech.net>
**
** Started on  Fri Jan 27 16:49:24 2017 voyevoda
** Last update Fri Jan 27 17:15:34 2017 voyevoda
*/
#include <string.h>
#include <unistd.h>
#include "malloc.h"

static void	set_mem(t_metadata *tmp, t_metadata *node)
{
  t_metadata    *var;

  var = tmp->data + tmp->size;
  var->size = node->size - tmp->size - METADATA_SIZE;
  var->next = tmp->next;
  var->prev = tmp;
  var->free = true;
  var->data = (void *) var + METADATA_SIZE;
  if (tmp->next != NULL)
    tmp->next->prev = var;
  tmp->next = var;
}

void    *realloc(void *ptr, size_t size)
{
  void          *cpy;
  t_metadata    node;
  t_metadata    *tmp;

  if (ptr == NULL)
    return malloc(size);
  tmp = ptr - METADATA_SIZE;
  tmp->free = false;
  if (tmp->size == size)
    return (ptr);
  if (tmp->size < size)
    {
      cpy = malloc(size);
      memcpy(cpy, ptr, tmp->size);
      free(ptr);
      return (cpy);
    }
  node = *tmp;
  tmp->size = size;
  if (node.size - tmp->size >= METADATA_SIZE)
    set_mem(tmp, &node);
  return (tmp->data);
}

static t_metadata      *add_last(size_t size, t_metadata *lastnode)
{
  t_metadata    *tmp;
  size_t        stock;
  int           pages;
  int           nb;

  stock = sbrk(0) - (lastnode->data + lastnode->size);
  if (stock < METADATA_SIZE + size)
    {
      pages = getpagesize();
      nb = (size - stock + METADATA_SIZE) / pages;
      if ((size - stock + METADATA_SIZE) % pages != 0)
	++nb;
      if (sbrk(pages * nb) == (void *)-1)
	return (NULL);
    }
  tmp = lastnode->data + lastnode->size;
  tmp->size = size;
  tmp->next = NULL;
  tmp->prev = lastnode;
  tmp->free = false;
  tmp->data = (void *)tmp + METADATA_SIZE;
  lastnode->next = tmp;
  return (tmp);
}

t_metadata      *add_in_list(size_t size, t_metadata *list)
{
  t_metadata *tmp;
  t_metadata  node;

  tmp = list;
  while (tmp->next != NULL)
    {
      if (tmp->free == true && size <= tmp->size)
	{
	  node = *tmp;
	  tmp->size = size;
	  tmp->free = false;
	  tmp->data = (void *)tmp + METADATA_SIZE;
	  if (node.size - tmp->size >= METADATA_SIZE)
	    set_mem(tmp, &node);
	  return (tmp);
	}
      tmp = tmp->next;
    }
  return add_last(size, tmp);
}
