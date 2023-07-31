/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:23:45 by novsiann          #+#    #+#             */
/*   Updated: 2023/07/31 22:56:22 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	cut_word(char *str, int start, int end)
{
	while (*str && start <= end)
	{
		write(1, &str[start], 1);
		start++;
	}
}

void	lexer(char *input)//
{
	int				start;
	int				end;
	// int				type;

	start = 0;
	end = 0;
	// type = get_type(input[i]);
	while (input[start])
	{
		while (input[start] >= 8 && input[start] <= 14 && input[start] == 32 &&input[start] != '\0')
			start++;
		end = start;
		while (!(input[end] >= 8 && input[end] <= 14) && input[start] != 32 && input[end] != '\0')
			end++;
		// printf("%d , %d", start, end);
		cut_word(input, start, end);
		start = end;
	}
	// return (list);
}
