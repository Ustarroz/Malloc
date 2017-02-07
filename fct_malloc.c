/*
** fct_malloc.c for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
**
** Made by voyevoda
** Login   <voyevoda@epitech.net>
**
** Started on  Fri Jan 27 16:49:24 2017 voyevoda
** Last update Tue Feb  7 18:49:59 2017 puilla_e
*/
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "malloc.h"

void	*calloc(size_t nmenb, size_t size)
{
  void	*tmp;

  if ((tmp = malloc(size * nmenb)) == NULL)
    return (NULL);
  memset(tmp, 0, size * nmenb);
  return (tmp);
}

void		set_mem(t_metadata *tmp, t_metadata *node)
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

static t_metadata	*add_last(size_t size, t_metadata *lastnode)
{
  t_metadata		*tmp;
  size_t		stock;
  size_t		pages;
  size_t		nb;

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

t_metadata	*add_in_list(size_t size, t_metadata *list)
{
  t_metadata	*tmp;
  t_metadata	node;

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
  return (add_last(size, tmp));
}

t_metadata      *add_first(size_t size, t_metadata **list)
{
  t_metadata    *tmp;
  size_t	pages;
  size_t	nb;

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
  *list = tmp;
  return (tmp);
}
