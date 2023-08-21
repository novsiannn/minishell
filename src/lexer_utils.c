/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:33:57 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/18 21:50:53 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_type(char symbol)
{
	if (symbol == ' ' || (symbol >= 8 && symbol <= 14))
		return (SPAC);
	else if (symbol == '|')
		return (PIPE);
	else if (symbol == '>')
		return (GREATER_THAN);
	else if (symbol == '<')
		return (LESS_THAN);
	else if (symbol == '\"')
		return (DOUBLE_QUOTES);
	else if (symbol == '\'')
		return (SINGLE_QUOTES);
	return (WORD);
}

char	*get_word(char *str, int start, int end)
{
	char	*new_str;
	int		i;

	i = 0;
	new_str = malloc(sizeof(char) * (end - start + 1));
	if (!new_str)
		return (NULL);
	while (start < end)
		new_str[i++] = str[start++];
	new_str[i] = 0;
	return (new_str);
}

void	get_final_type(t_token_list **token)
{
	t_token_list	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (tmp->tok[0] == '|' && tmp->len == 1)
			tmp->type = PIPE;
		else if (tmp->tok[0] == '>' && tmp->len == 1)
			tmp->type = GREATER_THAN;
		else if (tmp->tok[0] == '<' && tmp->len == 1)
			tmp->type = LESS_THAN;
		else if (tmp->tok[0] == '"' && tmp->len == 1)
			tmp->type = DOUBLE_QUOTES;
		else if (tmp->tok[0] == '\'' && tmp->len == 1)
			tmp->type = SINGLE_QUOTES;
		else if (tmp->len == 2 && tmp->tok[0] == '<' && tmp->tok[1] == '<')
			tmp->type = HEREDOCK;
		else if (tmp->len == 2 && tmp->tok[0] == '>' && tmp->tok[1] == '>')
			tmp->type = APPEND;
		else if (tmp->len == 2 && tmp->tok[0] == '-' && tmp->tok[1] == 'n')
			tmp->type = EXPANSION;
		else
			tmp->type = WORD;
	
		tmp = tmp->next;
	}
}

int	get_words_minishell(char *str)
{
	int n;

	n = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	while (*str != '\0')
	{
		n++;
		if (*str == '\'' || *str == '\"' || *str == ' ')
		{
			str++;
			continue;
		}
		while (*str != '\0' && *str != ' ' && *str != '\"' \
		&& *str != '\t' && *str != '\n' && *str != '\'')
			str++;
	}
	return (n);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}
