/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 21:44:01 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/06 14:44:41 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	charjoin_free(char **str, char letter)
{
	char	*to_add;
	char	*res;

	to_add = malloc(2);
	to_add[0] = letter;
	to_add[1] = 0;
	res = ft_strjoin(*str, to_add);
	free(*str);
	free(to_add);
	*str = res;
}

void	find_tokens_loop(t_token_list **tmp, t_token_list **new, t_token_list **new_tok)
{
	int	i;

	i = 0;
	while ((*tmp)->tok[i])
	{
		if ((*tmp)->tok[i] == '|' || (*tmp)->tok[i] == '>'\
		|| (*tmp)->tok[i] == '<')
		{
			(*new)->next = new_token_and_type(&i, (*tmp)->tok);
			(*new_tok) = (*new)->next;
			(*new_tok)->next = malloc(sizeof(t_token_list));
			(*new) = (*new_tok)->next;
			(*new)->type = WORD;
			(*new)->tok = NULL;
			continue ;
		}
		else
			charjoin_free(&((*new)->tok), (*tmp)->tok[i]);
		i++;
	}
}

void	find_tokens(t_token_list **tmp)
{
	t_token_list	*new;
	t_token_list	*new_tok;
	t_token_list	*new_struct;

	new = malloc(sizeof(t_token_list));
	new_struct = new;
	new->type = WORD;
	new->tok = NULL;
	find_tokens_loop(tmp, &new, &new_tok);
	free((*tmp)->tok);
	(*tmp)->tok = NULL;
	new->next = (*tmp)->next;
	(*tmp)->next = new_struct;
	(*tmp) = new->next;
}

void	split_words(t_token_list **list)
{
	t_token_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			find_tokens(&tmp);
			continue ;
		}
		tmp = tmp->next;
	}
}