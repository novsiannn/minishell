/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:02:26 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 15:06:11 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_new(char *arg)
{
	char	*str;
	int		j;

	str = ft_substr(arg, 0, find_index_of_char(arg, '=') + 1);
	j = find_path_env(g_shell_h->envp, str);
	if (j != -1)
	{
		free(g_shell_h->envp[j]);
		g_shell_h->envp[j] = ft_strdup(arg);
	}
	else
		g_shell_h->envp[(g_shell_h->current_env)++] = ft_strdup(arg);
	free(str);
}

int	check_arg(char *str)
{
	if (change_dir(str) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}

int	command_cd(char *arg)
{
	int		i;
	int		res;
	char	*key;

	i = 0;
	res = 0;
	if (!arg)
	{
		i = find_path_env(g_shell_h->envp, "HOME");
		if (i == -1)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		key = cut_key(g_shell_h->envp, i, "HOME");
		if (change_dir(key) == -1)
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		free(key);
	}
	else
		res = check_arg(arg);
	return (res);
}

int	change_dir(char *arg)
{
	char	*current;
	char	*tmp;
	char	*str1;
	char	*str2;

	current = getcwd(0, 256);
	if (chdir(arg) == -1)
	{
		free(current);
		return (-1);
	}
	tmp = getcwd(0, 256);
	str1 = ft_strjoin("OLDPWD=", current);
	str2 = ft_strjoin("PWD=", tmp);
	set_new(str1);
	set_new(str2);
	free(current);
	free(tmp);
	return (1);
}

char	*cut_key(char **env, int index, char *key)
{
	char	*buf;

	buf = ft_substr(env[index], ft_strlen(key) + 1,
			(ft_strlen(env[index]) - 1 - ft_strlen(key)));
	return (buf);
}
