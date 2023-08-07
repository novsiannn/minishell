/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 18:33:57 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/06 16:12:41 by ikhristi         ###   ########.fr       */
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

void	get_final_type(t_token_list **token)
{
	t_token_list *tmp;

	tmp = *token;
	while(tmp)
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
		else if(tmp->len == 2 && tmp->tok[0] == '<' && tmp->tok[1] == '<')
			tmp->type = HEREDOCK;
		else if(tmp->len == 2 && tmp->tok[0] == '>' && tmp->tok[1] == '>')
			tmp->type = APPEND;
		else if(tmp->len == 2 && tmp->tok[0] == '-' && tmp->tok[1] == 'n')
			tmp->type = EXPANSION;
		else
			tmp->type = WORD;		
		tmp = tmp->next;
	}
}