/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:47:07 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/26 15:03:39 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_red(t_token_list **token_tmp,
					t_pipe_group **tmp)
{
	int	type;

	type = (*token_tmp)->type;
	skip_space(token_tmp);
	if (!(*token_tmp) || ((*token_tmp)->type != DOUBLE_QUOTES
			&& (*token_tmp)->type != SINGLE_QUOTES
			&& (*token_tmp)->type != WORD))
		return (throw_error(SYNTAX_ERROR));
	if (type == HEREDOCK)
		return (here_doc(token_tmp, tmp));
	if (type == LESS_THAN)
	{
		(*tmp)->input = open((*token_tmp)->tok, O_RDONLY);
		if ((*tmp)->input < 0)
			return (throw_error(OPEN_ERROR));
	}
	else if (type == GREATER_THAN || type == APPEND)
	{
		if (open_output(tmp, token_tmp, type))
			return (throw_error(OPEN_ERROR));
	}
	*token_tmp = (*token_tmp)->next;
	return (0);
}

int	add_word(t_pipe_group **tmp, t_token_list **token_tmp,
					int *first, int *count_words)
{
	if (!((*token_tmp)->tok))
	{
		*token_tmp = (*token_tmp)->next;
		return (1);
	}
	(*tmp)->argv[*count_words] = ft_strdup((*token_tmp)->tok);
	if (!(*first))
	{
		(*tmp)->cmd = (*tmp)->argv[*count_words];
		*first = 1;
	}
	(*count_words)++;
	*token_tmp = (*token_tmp)->next;
	return (0);
}

int	add_pipe(t_pipe_group **tmp, t_token_list **token_tmp,
			int *first, int *count_words)
{
	if (!(*first))
		return (1);
	(*tmp)->argv[*count_words] = NULL;
	*count_words = 0;
	*first = (*tmp)->pipe_index;
	*token_tmp = (*token_tmp)->next;
	(*tmp)->next = init_pipe(*first + 1);
	*tmp = (*tmp)->next;
	*first = 0;
	return (0);
}

int	redirection_loop(t_pipe_group **tmp, t_token_list **tok,
					int *first, int *count_words)
{
	while (*tok)
	{
		if ((*tok)->type == GREATER_THAN || (*tok)->type == LESS_THAN
			|| (*tok)->type == APPEND || (*tok)->type == HEREDOCK)
		{
			create_red(tok, tmp);
			if (g_shell_h->pipes == NULL)
				return (1);
		}
		else if ((*tok)->type == SINGLE_QUOTES
			|| (*tok)->type == DOUBLE_QUOTES || (*tok)->type == WORD)
		{
			if (add_word(tmp, tok, first, count_words))
				continue ;
		}
		else if ((*tok)->type == PIPE)
		{
			if (add_pipe(tmp, tok, first, count_words))
				return (throw_error(SYNTAX_ERROR));
		}
		else
			*tok = (*tok)->next;
	}
	return (0);
}

t_pipe_group	*redirection(void)
{
	t_pipe_group	*tmp;
	t_token_list	*token_tmp;
	int				i;
	int				count_words;

	i = 0;
	count_words = 0;
	g_shell_h->pipes = init_pipe(0);
	tmp = g_shell_h->pipes;
	token_tmp = g_shell_h->head;
	if (redirection_loop(&tmp, &token_tmp, &i, &count_words))
		return (NULL);
	if (!i)
	{
		throw_error("minishell: syntax error near unexpected token\n");
		return (NULL);
	}
	tmp->argv[count_words] = NULL;
	return (g_shell_h->pipes);
}
