/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:23:45 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/07 15:10:31 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	list_value_split(t_token_list **list, int type)
{
	t_token_list	*tmp;
	int				splited_tokens;
	int				start;
	int				end;
	char			*str;
	char			*buf;

	tmp = *list;
	start = 0;
	end = 0;
	splited_tokens = 0;
	buf = ft_strdup(tmp->tok);
	while (buf[end] != '\0')
	{
	if (get_type(buf[end]) != type || buf[end + 1] == '\0')
		{
			if (buf[end + 1] == '\0' && get_type(buf[end]) == type)
				end++;
			str = get_word(buf, start, end);
			if (!splited_tokens)
			{
				splited_tokens = 1;
				free(tmp->tok);
				tmp->tok = ft_strdup(str);
				tmp->len = ft_strlen(tmp->tok);
			}
			else
				tmp = ft_put_between_token(tmp, tmp->next, str);
			free (str);
			type = get_type(buf[end]);
			start = end;
		}
		if (get_type(buf[end - 1]) != type && \
		buf[end + 1] == '\0' && buf[end] != '\0')
		{
			str = get_word(buf, start, end + 1);
			tmp = ft_put_between_token(tmp, tmp->next, str);
			free(str);
		}
		end++;
	}
}

// int	change_first_node(t_token_list *tmp, int start, int end, char *buf)
// {
// 	char	*str;

// 	str = get_word(buf, start, end);
// 	free(tmp->tok);
// 	tmp->tok = ft_strdup(str);
// 	tmp->len = ft_strlen(tmp->tok);
// 	return (1);
// }

// void	compare_symbols(t_token_list *list, int start, int end, char *buf)
// {
// 	char	*str;

// 	str = get_word(buf, start, end);
// 	list = ft_put_between_token(list, list->next, str);
// 	free (str);
// }

// void	last_letter(t_token_list *list, char *buf, int sta, int end)
// {
// 	char	*str;

// 	str = get_word(buf, sta, end + 1);
// 	list = ft_put_between_token(list, list->next, str);
// 	free(str);
// }

void	list_value_cmp(t_token_list **list)
{
	int				i;
	int				type;
	t_token_list	*temp;

	temp = *list;
	while (temp != NULL)
	{
		i = 0;
		type = get_type(temp->tok[i]);
		while (temp->tok[i] != '\0')
		{
			if (get_type(temp->tok[i]) != type)
			{
				list_value_split(&temp, type);
				break ;
			}
			else
				i++;
		}
		temp = temp->next;
	}
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
