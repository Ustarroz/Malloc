/*
** malloc.c for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
**
** Made by voyevoda
** Login   <voyevoda@epitech.net>
**
** Started on  Thu Jan 26 14:51:23 2017 voyevoda
** Last update Mon Jan 30 13:45:45 2017 voyevoda
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"
#include "hexprinter.h"

static t_metadata	*list = NULL;
static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void    *realloc(void *ptr, size_t size)
{
  void          *cpy;
  t_metadata    node;
  t_metadata    *tmp;

  if (ptr == NULL)
    return malloc(size);
  tmp = ptr - METADATA_SIZE;
  if (tmp->size == size)
    return (ptr);
  if (tmp->size < size)
    {
      cpy = malloc(size);
      memcpy(cpy, ptr, tmp->size);
      free(ptr);
      return (cpy);
    }
  pthread_mutex_lock(&mutex);
  tmp->free = false;
  node = *tmp;
  tmp->size = size;
  if (node.size - tmp->size >= METADATA_SIZE)
    set_mem(tmp, &node);
  pthread_mutex_unlock(&mutex);
  return (tmp->data);
}

void		*malloc(size_t size)
{
  t_metadata	*tmp;

  pthread_mutex_lock(&mutex);
  if (list == NULL)
    {
      if ((tmp = add_first(size, &list)) == NULL)
	{
	  pthread_mutex_unlock(&mutex);
	return (NULL);
	}
    }
  else
    if ((tmp = add_in_list(size, list)) == NULL)
      {
	pthread_mutex_unlock(&mutex);
	return (NULL);
      }
  pthread_mutex_unlock(&mutex);
  return tmp->data;
}

void		free(void *ptr)
{
  t_metadata	*tmp;
  unsigned int	pages;

  pages = getpagesize();
  if ((tmp = ptr_to_metadata(ptr, list)) == NULL)
    return;
  pthread_mutex_lock(&mutex);
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
  pthread_mutex_unlock(&mutex);
}

void		show_alloc_mem(void)
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
