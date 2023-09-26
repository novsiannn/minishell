/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 23:18:14 by novsiann          #+#    #+#             */
/*   Updated: 2023/09/26 15:02:38 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_lstsize_n(t_token_list *start, t_token_list *finish)
{
	int	i;

	i = 0;
	while (start != finish)
	{
		i++;
		start = start->next;
	}
	return (i);
}

void	check_quotes(t_token_list *tokens)
{
	int	quote;

	quote = -1;
	while (tokens)
	{
		if (quote == -1)
		{
			if (tokens->type == DOUBLE_QUOTES || tokens->type == SINGLE_QUOTES)
			{
				quote = tokens->type;
			}
		}
		else
		{
			if (quote == tokens->type)
			{
				quote = -1;
			}
		}
		tokens = tokens->next;
	}
	if (quote != -1)
		printf("Quotes are not closed\n");
}
