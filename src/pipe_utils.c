/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:34:13 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/08 20:00:02 by novsiann         ###   ########.fr       */
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
		tmp = (*tmp)->next;
}

char	*charjoinfree(char **str, char ch)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc((size_t)ft_strlen(str) + 2);
	if (!res)
		return (NULL);
	while (str[i] != '\0')
	{
		res[i] = str[i];
		i++;
	}
	res[i++] = ch;
	res[i] = '\0';
	free(str);
	return (res);
}
