/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:33:57 by novsiann          #+#    #+#             */
/*   Updated: 2023/07/31 18:47:22 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_type(char symbol)
{
	if (symbol == ' ' || (symbol >= 8 && symbol <= 14))
		return (SPACE);
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