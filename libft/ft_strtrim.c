/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:21:54 by novsiann          #+#    #+#             */
/*   Updated: 2023/01/07 12:19:59 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const chr, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == chr)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*s2;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] && is_set(s1[i], set))
		i++;
	if (!(*(s1 + i)))
	{
		s2 = malloc(1);
		*s2 = 0;
		return (s2);
	}
	j = ft_strlen(s1) - 1;
	while (is_set(s1[j], set))
		j--;
	s2 = ft_substr(s1, i, j - i + 1);
	return (s2);
}
