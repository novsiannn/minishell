/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:38 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/18 20:21:39 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int command_exit(char **arg)
{
	int len;
	int	exit_status;

	exit_status = 1;
	len = get_arr_len(arg);
	if (len > 2)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
		return (1);
	}
	else if (len == 1)
		exit_status = 0;
	else if (arg[1])
	{
		if (!(ft_isdigit(arg[1][0])))
		{
			ft_putstr_fd("exit\nminishell: argument is not a numebr\n", 2);
			return (1);
		}
		exit_status = ft_atoi(arg[1]);
	}
	free_shell_h();
	exit(exit_status % 256);
	return (0);
}

int	exec_builtin_parent(t_pipe_group *pipes)
{
	int	err;

	if (ft_strcmp(pipes->argv[0], "unset") == 0)
		err = b_unset(&pipes->argv[1]);
	else if (ft_strcmp(pipes->argv[0], "export") == 0)
		err = builtin_export(pipes->argv);
	else if (ft_strcmp(pipes->argv[0], "cd") == 0)
		err = command_cd(pipes->argv[1]);
	else if (ft_strcmp(pipes->argv[0], "exit") == 0)
		err = command_exit(pipes->argv);
	else
		return (-1);
	g_shell_h->error = err;
	return (0);
}

int executor(t_pipe_group *data)
{
	// int				pipe_fd;
	// t_pipe_group	*prev;

	// pipe_fd = STDIN_FILENO;
	// prev = NULL;
	while (data)
	{
		if (g_shell_h->last == 0 && exec_builtin_parent(data) != -1)
		{
			data = data->next;
			continue ;
		}
		// prev = data;
		data = data->next;
	}
	return (1);
}
