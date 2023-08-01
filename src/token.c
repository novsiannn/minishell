/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:24:39 by ikhristi          #+#    #+#             */
/*   Updated: 2023/08/01 13:08:45 by novsiann         ###   ########.fr       */
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
	token -> tok = start;
	token -> next = NULL;
	token -> prev = NULL;
	return (token);
}

void	add_token(t_token_list **first, t_token_list *to_add)
{
	t_token_list	*temp;

	if (!to_add)
	{
		return ;
	}
	if (!(*first))
	{
		*first = to_add;
		return ;
	}
	temp = *first;
	while (temp->next)
		temp = temp -> next;
	temp->next = to_add;
	to_add->prev = temp;
}

void	ft_lstadd_back_minishell(t_token_list **lst, t_token_list *new)
{
	t_token_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast_minishell(*lst);
			last->next = new;
		}
		else
		{
			*lst = new;
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

