/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:04:38 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 10:40:51 by ikhristi         ###   ########.fr       */
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
	int	pipe_fd[2]; // в pipe_fd[0] читаем . в pipe_fd[1] мы можем записывать и брать из него в другой процесс инфу
	int	pid;//or

	pipe(pipe_fd); // создает канал который связывает stdin and stdout
	child_sig(); // ставит сигналы на дочерный процесс
	pid = fork(); // fork создает два подпроцесса которые работают одновременно, родительский и дочерний. pid = -1 Это ошибка. 0 это значит что код выполняется в дочернем процессе. > 0 значит что код идет в родительском процессе
	if (pid == 0)
		child_process_prep(data, in_fd, out_fd, pipe_fd); //Надо сделать эту функцию
	waitpid(pid, &(g_shell_h->error), 0); // waitpid ждет завершение дочернего процесса и в g_shell_h->error запишется запишется информация о завершение процесса
	signals(); // тут я думаю понятно
	if ((g_shell_h->error) > 255)
		(g_shell_h->error) /= 256; // чекаем на ошибку
	close(pipe_fd[1]); // тут ясно
	if (in_fd > 2) // с этими ебучими файл дискрипторами я до конца не разобрался но надо на примере смотреть
		close(in_fd);
	if (out_fd > 2)
		close(out_fd);
	return (pipe_fd[0]);
}

int	command_exec_prep(t_pipe_group *data, t_pipe_group *prev, int in_fd, int out_fd)
{
	char *x_p;

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

int executor(t_pipe_group *data)
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
