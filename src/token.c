/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:24:39 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/04 20:29:50 by nikitos          ###   ########.fr       */
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
	if(start != NULL)	
		token -> tok = ft_strdup(start);
	token -> next = NULL;
	token -> prev = NULL;
	return (token);
}

t_token_list	*new_token_and_type(int *i, char *str)
{
	t_token_list	*new;

	new = malloc(sizeof(t_token_list));
	new->tok = NULL;
	if (str[*i] == '|')
		new->type = PIPE;
	else if (str[(*i)] == '<' && str[(*i) + 1] && str[(*i) + 1] == '<')
	{
		new->type = HEREDOCK;
		(*i) += 2;
		return (new);
	}
	else if (str[(*i)] == '>' && str[(*i) + 1] && str[(*i) + 1] == '>')
	{
		new->type = APPEND;
		(*i) += 2;
		return (new);
	}
	else if (str[(*i)] == '<')
		new->type = LESS_THAN;
	else if (str[(*i)] == '>')
		new->type = GREATER_THAN;
	(*i)++;
	return (new);
}

// void	ft_lstadd_back_minishell(t_token_list **lst, t_token_list *new)
// {
// 	t_token_list	*last;

// 	if (new == NULL)
// 		return ;
// 	if (lst)
// 	{
// 		if (*lst)
// 		{
// 			last = ft_lstlast_minishell(*lst);
// 			last->next = new;
// 			new->prev = last;
// 		}
// 		else
// 		{
// 			*lst = new;
// 			(*lst)->prev = NULL;
// 		}
// 	}
// }

// t_token_list	*ft_lstlast_minishell(t_token_list *lst)
// {
// 	while (lst != NULL)
// 	{
// 		if (lst->next == NULL)
// 			return (lst);
// 		lst = lst->next;
// 	}
// 	return (NULL);
// }

// t_token_list	*ft_put_between_token(t_token_list *prev, \
// t_token_list *next, char *value)
// {
// 	t_token_list	*new_token;
// 	int				length;

// 	if (value)
// 		length = ft_strlen(value);
// 	else
// 		length = 1;
// 	new_token = create_token(length, value, 1);
// 	if (next != NULL)
// 		next->prev = new_token;
// 	new_token->next = next;
// 	new_token->prev = prev;
// 	prev->next = new_token;
// 		return (new_token);
// }
