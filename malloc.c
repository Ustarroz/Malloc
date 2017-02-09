/*
** malloc.c for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
**
** Made by voyevoda
** Login   <voyevoda@epitech.net>
**
** Started on  Thu Jan 26 14:51:23 2017 voyevoda
** Last update Thu Feb  9 16:15:08 2017 puilla_e
*/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "malloc.h"
#include "hexprinter.h"

static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;

void	*calloc(size_t nmenb, size_t size)
{
  void	*tmp;

  pthread_mutex_lock(&mutex);
  tmp = calloc_mutex(nmenb, size);
  pthread_mutex_unlock(&mutex);
  return (tmp);
}

void	*realloc(void *ptr, size_t size)
{
  void	*cpy;

  pthread_mutex_lock(&mutex);
  cpy = realloc_mutex(ptr, size);
  pthread_mutex_unlock(&mutex);
  return (cpy);
}

void	*malloc(size_t size)
{
  void	*tmp;

  pthread_mutex_lock(&mutex);
  tmp = malloc_mutex(size);
  pthread_mutex_unlock(&mutex);
  return (tmp);
}

void		free(void *ptr)
{
  pthread_mutex_lock(&mutex);
  free_mutex(ptr);
  pthread_mutex_unlock(&mutex);
}

void		show_alloc_mem(void)
{
  pthread_mutex_lock(&mutex);
  show_alloc_mem_mutex();
  pthread_mutex_unlock(&mutex);
}
