/*
** fct_free.c for bonjour in /home/voyevoda/rendu/systeme_unix/PSU_2016_malloc
**
** Made by voyevoda
** Login   <voyevoda@epitech.net>
**
** Started on  Mon Jan 30 13:22:59 2017 voyevoda
** Last update Mon Jan 30 13:52:06 2017 Edouard Puillandre
*/

#include "malloc.h"

t_metadata      *merge_free(t_metadata *tmp)
{
  t_metadata    *node;

  node = tmp->next;
  tmp->size += node->size + METADATA_SIZE;
  tmp->next = node->next;
  if (node->next != NULL)
    node->next->prev = tmp;
  return (tmp);
}

t_metadata	*ptr_to_metadata(void *ptr, t_metadata *list)
{
  t_metadata	*tmp;

  tmp = list;
  if (ptr == NULL)
    return (NULL);
  while (tmp != NULL)
    {
      if (tmp->data == ptr)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}
