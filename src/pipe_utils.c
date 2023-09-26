/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:34:13 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/26 15:02:59 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe_group	*init_pipe(int index)
{
	t_pipe_group	*pipe;
	int				i;

	i = 0;
	pipe = malloc (sizeof(t_pipe_group));
	pipe->argv = malloc(sizeof(char *) * 100);
	while (i < 100)
	{
		pipe->argv[i] = NULL;
		i++;
	}
	pipe->cmd = NULL;
	pipe->heredoc = NULL;
	pipe->input = -1;
	pipe->output = -1;
	pipe->next = NULL;
	pipe->pipe_index = index;
	return (pipe);
}

void	skip_space(t_token_list **tmp)
{
	*tmp = (*tmp)->next;
	while ((*tmp) && ((*tmp)->type == SPACE
			|| ((*tmp)->type == WORD && !((*tmp)->tok))))
		*tmp = (*tmp)->next;
}

void	charjoinfree(char **str, char ch)
{
	char	*adder;
	char	*new;

	adder = malloc(2);
	adder[0] = ch;
	adder[1] = '\0';
	new = ft_strjoin(*str, adder);
	free (*str);
	free (adder);
	*str = new;
}

int	get_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
