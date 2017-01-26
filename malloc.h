//
// malloc.h for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
//
// Made by voyevoda
// Login   <voyevoda@epitech.net>
//
// Started on  Thu Jan 26 14:42:23 2017 voyevoda
// Last update Thu Jan 26 16:24:29 2017 voyevoda
//

#ifndef MALLOC_H_
# define MALLOC_H_

#include <stdbool.h>
typedef struct s_metadata
{
  void			*data;
  struct s_metadata	*next;
  struct s_metadata	*prev;
  size_t		size;
  bool			free;
}		t_mtadata;

#define METADATA_SIZE sizeof(t_metadata);

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
# endif /* ! MALLOC_H_ */
