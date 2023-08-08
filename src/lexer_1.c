/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:23:45 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/08 19:29:41 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	list_value_split(t_token_list **list, int type)
{
	t_token_list	*tmp;
	char			*buf;

	tmp = *list;
	buf = ft_strdup(tmp->tok);
	while (buf[(*list)->k] != '\0')
	{
		if (get_type(buf[(*list)->k]) != type || buf[(*list)->k + 1] == '\0')
		{
			if (buf[(*list)->k + 1] == '\0' && \
			get_type(buf[(*list)->k]) == type)
				(*list)->k++;
			split_value(&tmp, buf, list, &type);
		}
		if (get_type(buf[(*list)->k - 1]) != type && \
		buf[(*list)->k + 1] == '\0' && buf[(*list)->k] != '\0')
			last_letter(tmp, buf, (*list)->i, (*list)->k);
		(*list)->k++;
	}
}

void	split_value(t_token_list **tmp, char *buf, \
t_token_list **list, int *type)
{
	char	*str;

	str = get_word(buf, (*list)->i, (*list)->k);
	if ((*list)->corrective_token == 0)
		change_node(*tmp, buf, list);
	else
		*tmp = ft_put_between_token(*tmp, (*tmp)->next, str);
	free (str);
	*type = get_type(buf[(*list)->k]);
	(*list)->i = (*list)->k;
}

void	*find_words(char *input, t_token_list **list)
{
	int				start;
	int				end;

	start = 0;
	end = 0;
	while (input[start])
	{
		while (((input[start] >= 8 && input[start] <= 14) || \
		input[start] == 32) && input[start] != '\0')
			start++;
		end = start;
		while (!(input[start] >= 8 && input[start] <= 14) && \
		input[end] != ' ' && input[end] != '\0')
			end++;
		if (!list)
			*list = delete_spaces(input, start, end);
		else if (input[start] != '\0' && input[start] != 32)
			ft_lstadd_back_minishell(list, \
			delete_spaces(input, start, end));
		start = end;
	}
	return (0);
}

void	lexer(char *input)
{
	t_token_list	*list;

	list = NULL;
	find_words(input, &list);
	list->i = 0;
	list->k = 0;
	list_value_cmp(&list);
	get_final_type(&list);
	check_quotes(list);
	while (list != NULL)
	{
		printf("[%s] - [%d] \n", list->tok, list->type);
		list = list->next;
	}
	ft_clear_tokens(&list);
	write(1, "\n", 1);
}
