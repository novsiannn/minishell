/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 17:43:04 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/26 17:52:51 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	command_exec_prep(t_pipe_group *data, t_pipe_group *prev, \
						int in_fd, int out_fd)
{
	char	*x_p;

	if (data->output != -1)
		out_fd = data->output;
	else if (g_shell_h->last == data->pipe_index)
		out_fd = STDOUT_FILENO;
	if (data->input != -1)
		in_fd = data->input;
	else if (prev && prev->output != -1)
		in_fd = STDIN_FILENO;
	x_p = get_working_path(data->cmd, g_shell_h->envp);
	if (!x_p)
	{
		throw_error("minishell: command not found\n");
		return (STDIN_FILENO);
	}
	free(x_p);
	return (fork_and_execute(data, in_fd, out_fd));
}

int	executor(t_pipe_group *data)
{
	int				pipe_fd;
	t_pipe_group	*prev;

	pipe_fd = STDIN_FILENO;
	prev = NULL;
	while (data)
	{
		if (g_shell_h->last == 0 && exec_builtin_parent(data) != -1)
		{
			data = data->next;
			continue ;
		}
		pipe_fd = command_exec_prep(data, prev, pipe_fd, -1);
		prev = data;
		data = data->next;
	}
	if (pipe_fd > 2)
		close(pipe_fd);
	return (0);
}
