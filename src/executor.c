/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:38 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 17:43:35 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	child_proccess_managing_outfds(int out_fd, int pipe_fd[])
{
	if (out_fd == -1 || out_fd == -2)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		return (pipe_fd[1]);
	}
	if (out_fd != STDOUT_FILENO)
		dup2(out_fd, STDOUT_FILENO);
	return (out_fd);
}

int	exec_builtin_child(t_pipe_group *pipes)
{
	int	err;

	if (ft_strcmp(pipes->argv[0], "pwd") == 0 && !(pipes->argv[1]))
		err = (ft_pwd());
	else if (ft_strcmp(pipes->argv[0], "env") == 0 && !(pipes->argv[1]))
		err = (print_env());
	else if (ft_strcmp(pipes->argv[0], "echo") == 0)
		err = (b_echo(pipes->argv));
	else
		return (-1);
	g_shell_h->error = err;
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

void	child_process_prep(t_pipe_group *data, int in_fd,
								int out_fd, int pipe_fd[])
{
	int		out;
	char	*x_p;

	if (in_fd != STDIN_FILENO)
		dup2(in_fd, STDIN_FILENO);
	out = child_proccess_managing_outfds(out_fd, pipe_fd);
	if (exec_builtin_child(data) != -1)
		exit(0);
	x_p = get_working_path(data->cmd, g_shell_h->envp);
	execve(x_p, data->argv, g_shell_h->envp);
	throw_error_exec("minishell: couldn't run process\n");
	close(in_fd);
	close(out);
	exit(-1);
}

int	fork_and_execute(t_pipe_group *data, int in_fd, int out_fd)
{
	int	pipe_fd[2];
	int	pid;

	pipe(pipe_fd);
	child_sig();
	pid = fork();
	if (pid == 0)
		child_process_prep(data, in_fd, out_fd, pipe_fd);
	waitpid(pid, &(g_shell_h->error), 0);
	signals();
	if ((g_shell_h->error) > 255)
		(g_shell_h->error) /= 256;
	close(pipe_fd[1]);
	if (in_fd > 2)
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
	return (pipe_fd[0]);
}
