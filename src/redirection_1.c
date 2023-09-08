/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:47:07 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/08 17:18:20 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_red(t_token **token_tmp,
					t_pipe_group **tmp)
{
	int	type;

	type = (*token_tmp)->type;
	skip_space(token_tmp);
	if (!(*token_tmp) || ((*token_tmp)->type != DOUBLE_QUOTES
			&& (*token_tmp)->type != SINGLE_QUOTES
			&& (*token_tmp)->type != WORD))
		return (throw_error(SYNTAX_ERROR));
	if (type == HEREDOC)
		return
}

int	redirection_loop(t_pipe_group **tmp, t_token **tok,
					int *first, int *count_words)
{
	while (*tok)
	{
		if ((*tok)->type == GREATER_THAN || (*tok)->type == LESS_THAN
			|| (*tok)->type == APPEND || (*tok)->type == HEREDOC)
		{
			//
		}
		else if ((*tok)->type == SINGLE_QUOTES
			|| (*tok)->type == DOUBLE_QUOTES || (*tok)->type == WORD)
		{
			//
		}
		else if ((*tok)->type == PIPE)
		{
			//
		}
		else
			*tok = (*tok)->next;
	}
}

t_pipe_group	*redirection(void)
{
	t_pipe_group	*tmp;
	t_token			*token_tmp;
	int				i;
	int				count_words;

	first = 0;
	g_shell_h->pipes = init_pipe(0);
	tmp = g_shell_h->pipes;
	token_tmp = g_shell_h->head;
}