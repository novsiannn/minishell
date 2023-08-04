/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:24:39 by ikhristi          #+#    #+#             */
/*   Updated: 2023/08/04 19:24:20 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token_list	*create_token(int length, char *start, int type)
{
	t_token_list	*token;

	token = malloc(sizeof(t_token_list));
	if (!token)
		return (NULL);
	token -> len = length;
	token -> type = type;
	token -> tok = ft_strdup(start);
	token -> next = NULL;
	token -> prev = NULL;
	return (token);
}


void ft_lstadd_back_minishell(t_token_list **lst, t_token_list *new)
{
 t_token_list *last;

 if (new == NULL)
  return ;
 if (lst)
 {
  if (*lst)
  {
   last = ft_lstlast_minishell(*lst);
   last->next = new;
   new->prev = last;
  }
  else
  {
   *lst = new;
   (*lst)->prev = NULL;
  }
 }
}

t_token_list	*ft_lstlast_minishell(t_token_list *lst)
{
	while (lst != NULL)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void ft_clear_tokens(t_token_list **tokens)
{
 t_token_list *current;
 t_token_list *tmp;

 if (!tokens || !(*tokens))
  return ;
 current = *tokens;
 while (current)
 {
  tmp = current->next;
  current->len = 0;
  free(current->tok);
  current->tok = NULL;
  current->type = 0;
  current->next = NULL;
  current->prev = NULL;
  free(current);
  current = tmp;
 }
 *tokens = NULL;
}

t_token_list	*ft_put_between_token(t_token_list *prev, t_token_list *next, char *value)
{
	t_token_list	*new_token;
	int				length;

	length = ft_strlen(value);
	new_token = create_token(length, value, 1);
	// printf("%p->%p->%p->%s\n",prev,new_token,next,value);
	if (next != NULL)
		next->prev = new_token;
	new_token->next = next;
	new_token->prev = prev;
	prev->next = new_token;
	return (new_token);
}
