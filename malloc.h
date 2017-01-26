//
// malloc.h for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
//
// Made by voyevoda
// Login   <voyevoda@epitech.net>
//
// Started on  Thu Jan 26 14:42:23 2017 voyevoda
// Last update Thu Jan 26 14:50:23 2017 voyevoda
//

#ifndef MALLOC_H_
# define MALLOC_H_

typedef struct s_metadata
{
  void			*data;
  struct s_metadata	*next;
  s_size		size;
  bool			free;
}		metadata;


# endif /* ! MALLOC_H_ */
