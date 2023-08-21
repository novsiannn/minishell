/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 19:54:03 by nikitos           #+#    #+#             */
/*   Updated: 2023/08/21 19:52:14 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*words_allocate(char *str)
{
	int		len;
	int		i;
	char	*words;

	i = 0;
	len = ft_words_len(str);
	words = malloc(sizeof(char) * (len + 1));
	words[len] = '\0';
	while (i < len)
	{
		words[i] = str[i];
		i++;
	}
	return (words);
}

void	fill_array_end(char **array, char **str, int *word_index)
{
	array[*word_index] = words_allocate(*str);
	(*word_index)++;
	while (**str != '\0' && **str != ' ' && **str != '\"' \
		&& **str != '\t' && **str != '\n' && **str != '\'')
			(*str)++;
}

void	fill_array(char **array, char *str)
{
	int	word_index;

	word_index = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n')
		str++;
	while (*str != '\0')
	{
		if (*str == '\'' || *str == '\"')
		{
			array[word_index] = quotes_allocate(str);
			str++;
			word_index++;
			continue ;
		}
		if (*str == ' ')
		{
			array[word_index] = malloc(2);
			array[word_index][0] = ' ';
			array[word_index][1] = '\0';
			str++;
			word_index++;
			continue ;
		}
		fill_array_end(array, &str, &word_index);
	}
}

int	ft_words_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t' \
		&& str[i] != '\n' && str[i] != '\"' && str[i] != '\'')
		i++;
	return (i);
}

char	*quotes_allocate(char *str)
{
	char	*quotes;

	quotes = malloc(2);
	if (*str == '\'')
		quotes[0] = '\'';
	else
		quotes[0] = '\"';
	quotes[1] = '\0';
	return (quotes);
}
