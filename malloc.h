/*
** malloc.h for malloc in /home/puilla_e/semestre4/psu/PSU_2016_malloc
**
** Made by Edouard Puillandre
** Login   <puilla_e@epitech.net>
**
** Started on  Fri Jan 27 12:26:11 2017 Edouard Puillandre
// Last update Fri Jan 27 16:56:07 2017 voyevoda
*/

#ifndef MALLOC_H_
# define MALLOC_H_

#include <stdbool.h>
#include <stddef.h>
typedef struct s_metadata
{
  void			*data;
  struct s_metadata	*next;
  struct s_metadata	*prev;
  size_t		size;
  bool			free;
}		t_metadata;

#define METADATA_SIZE sizeof(t_metadata)

void		*malloc(size_t size);
void		free(void *ptr);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem();
t_metadata	*add_in_list(size_t size, t_metadata *list);

# endif /* ! MALLOC_H_ */
