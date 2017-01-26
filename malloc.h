//
// malloc.h for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
//
// Made by voyevoda
// Login   <voyevoda@epitech.net>
//
// Started on  Thu Jan 26 14:42:23 2017 voyevoda
// Last update Thu Jan 26 15:33:32 2017 voyevoda
//

#ifndef MALLOC_H_
# define MALLOC_H_

#include <stdbool.h>
typedef struct s_metadata
{
  void			*data;
  struct s_metadata	*next;
  size_t		size;
  bool			free;
}		metadata;

#define METADATA_SIZE sizeof(metadata);

void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
# endif /* ! MALLOC_H_ */
