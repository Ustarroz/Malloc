/*
** malloc.h for malloc in /home/puilla_e/semestre4/psu/PSU_2016_malloc
**
** Made by Edouard Puillandre
** Login   <puilla_e@epitech.net>
**
** Started on  Fri Jan 27 12:26:11 2017 Edouard Puillandre
// Last update Wed Feb  8 18:07:23 2017 puilla_e
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
void		show_alloc_mem(void);
t_metadata	*add_in_list(size_t size, t_metadata *list);
void		 set_mem(t_metadata *tmp, t_metadata *node);
void		*calloc(size_t nmenb, size_t size);
t_metadata      *add_first(size_t size, t_metadata **list);
t_metadata      *merge_free(t_metadata *tmp);
t_metadata	*ptr_to_metadata(void *ptr, t_metadata *list);
void		*sbrk_size(size_t nb, size_t pagges, int dir);

# endif /* ! MALLOC_H_ */
