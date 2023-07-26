/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:21:10 by nikitos           #+#    #+#             */
/*   Updated: 2023/01/07 12:14:56 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**words(char **ptr_str, const char *s, char delim, int word_count)
{
	int	i;
	int	word;
	int	length;

	i = 0;
	word = 0;
	length = 0;
	while (s[i] && word < word_count)
	{
		while (s[i] && s[i] == delim)
			i++;
		while (s[i] && s[i] != delim)
		{
			i++;
			length++;
		}
		ptr_str[word] = ft_substr (s, i - length, length);
		length = 0;
		word++;
	}
	ptr_str[word] = 0;
	return (ptr_str);
}

int	count_words(const char *str, char delim)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] == delim)
		{
			while (str[i] && str[i] == delim)
				i++;
		}
		else
		{
			while (str[i] && str[i] != delim)
				i++;
			counter++;
		}
	}
	return (counter);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		i;

	if (!s)
		return (NULL);
	i = count_words(s, c);
	ptr = malloc((sizeof (char *) * (i + 1)));
	if (!ptr)
		return (NULL);
	words(ptr, s, c, i);
	return (ptr);
}
