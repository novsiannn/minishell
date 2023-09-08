/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:34:13 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/08 17:02:38 by ikhristi         ###   ########.fr       */
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
		pipe->argc[i] = NULL;
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

void	skip_space(t_token **token)
{
	*token = (*token)->next;
	while ((*token) && ((*token)->type == SPACE
			|| ((*token)->type == WORD && !((*token)->info))))
		tmp = tmp->next;
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
