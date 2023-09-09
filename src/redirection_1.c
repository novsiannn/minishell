/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:47:07 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/09 17:18:22 by nikitos          ###   ########.fr       */
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
		return here_doc(token_tmp, tmp);
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
		// else if ((*tok)->type == SINGLE_QUOTES
		// 	|| (*tok)->type == DOUBLE_QUOTES || (*tok)->type == WORD)
		// {
		// 	//
		// }
		// else if ((*tok)->type == PIPE)
		// {
		// 	//
		// }
		else
			*tok = (*tok)->next;
	}
	printf("%d\n", *first);
	printf("%d\n", *count_words);
	return (0); // zahodit
}

t_pipe_group	*redirection(void)
{
	t_pipe_group	*tmp;
	t_token_list	*token_tmp;
	int				i;
	int				count_words;

	i = 0;
	count_words = 0;
	// printf("YES");
	g_shell_h->pipes = init_pipe(0);
	tmp = g_shell_h->pipes;
	token_tmp = g_shell_h->head;
	redirection_loop(&tmp, &token_tmp, &i, &count_words);
	return (tmp); // пока просто для компиляции, потом убрать
}