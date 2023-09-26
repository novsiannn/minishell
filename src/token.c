/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:24:39 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/26 18:13:05 by ikhristi         ###   ########.fr       */
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
	if (start != NULL)
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
