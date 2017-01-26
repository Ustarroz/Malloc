/*
** malloc.c for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
**
** Made by voyevoda
** Login   <voyevoda@epitech.net>
**
** Started on  Thu Jan 26 14:51:23 2017 voyevoda
** Last update Thu Jan 26 22:59:27 2017 voyevoda
*/

#include <stdio.h>
#include <unistd.h>
#include "malloc.h"

static t_metadata	*list = NULL;

t_metadata	*add_last(size_t size, t_metadata *lastnode)
{
  t_metadata	*tmp;
  size_t	stock;
  int		pages;
  int		nb;

  stock = sbrk(0) - (lastnode->data + lastnode->size);
  if (stock < METADATA_SIZE + size)
    {
      pages = getpagesize();
      nb = (size - stock + METADATA_SIZE) / pages;
      if ((size - stock + METADATA_SIZE) % pages != 0)
	++nb;
      sbrk(pages * nb);
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

t_metadata	*add_in_list(size_t size)
{
  t_metadata *tmp;
  t_metadata *var;
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
	    {
	      var = tmp->data + tmp->size;
	      var->size = node->size - tmp->size - METADATA_SIZE;
	      var->next = tmp->next;
	      var->prev = tmp;
	      var->free = true;
	      var->data = (void *) var + METADATA_SIZE;
	      tmp->next->prev = var;
	      tmp->next = var;
	    }
	  return (tmp);
	}
      tmp = tmp->next;
    }
  return (add_last(size, tmp));
}

void	add_first(size_t size)
{
  t_metadata	*tmp;
  int		pages;
  int		nb;

   pages = getpagesize();
  nb = (size + METADATA_SIZE) / pages;
  if ((size + METADATA_SIZE) % pages != 0)
    ++nb;
  tmp = sbrk(nb * pages);
  tmp->next = NULL;
  tmp->prev = NULL;
  tmp->size = size;
  tmp->free = false;
  tmp->data = (void *)tmp + METADATA_SIZE;
  list = tmp;
}

void	*malloc(size_t size)
{
  t_metadata	*tmp;

  tmp = list;
  while(tmp != NULL)
    tmp = tmp->next;
  if (tmp == NULL)
    add_first(size);


  return tmp + METADATA_SIZE;
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
  t_metadata *tmp;

  if (ptr == NULL)
    return;
  tmp = ptr - METADATA_SIZE;
  tmp->free = true;
  if (tmp->next != NULL && tmp->next->free == true)
    tmp = merge_free(tmp);
  if (tmp->prev != NULL && tmp->prev->free == true)
    tmp = merge_free(tmp->prev);
  if (tmp->next == NULL)
    {
      sbrk(-tmp->size - METADATA_SIZE);
      if (tmp->prev != NULL)
	tmp->prev->next = NULL;
      else
	list = NULL;
    }
}

void	*realloc(void *ptr, size_t size)
{

}

void	show_alloc_mem()
{
  t_metadata *tmp;

  printf("break : %#X\n", sbrk(0));
  if (list == NULL)
    return;
  tmp = list;
  while (tmp != NULL)
    {
      if (tmp->free ==false)
	printf("%#X - %#X : %d bytes\n",tmp->data, tmp->data + tmp->size, tmp->size);
      tmp = tmp->next;
    }
}
