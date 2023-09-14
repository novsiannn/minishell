/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:38 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/14 15:23:27 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	exec_builtin_parent(t_pipe_group *pipes)
{
	int err;

	if (ft_strcmp(pipes->argv[0], "unset") == 0)
		err = b_unset(&pipes->argv[1]);
	else if (ft_strcmp(pipes->argv[0], "export") == 0)
		err = b_export(pipes->argv);
	// else if (ft_strcmp(pipes->argv[0], "cd") == 0)
	// 	err = b_cd(pipes->argv[1]);
	// else if (ft_strcmp(pipes->argv[0], "exit") == 0)
	// 	err = b_exit(pipes->argv);
	else
		return (-1);
	g_shell_h->error = err;
	return (0);
}

int executor(t_pipe_group *data)
{
	int				pipe_fd;
	t_pipe_group	*prev;

	pipe_fd = STDIN_FILENO;
	prev = NULL;
	while (data)
	{
		if (g_shell_h->last == 0 && exec_builin_parent(data) != -1)
		{
			data = data->next;
			continue ;
		}
		prev = data;
		data = data->next;
	}
}