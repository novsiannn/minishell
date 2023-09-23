/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:24:56 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/23 16:25:15 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_working_path_loop(char ***binary_paths, char **one_path,
								char **one_command_path, char	*cmd)
{
	int	i;

	i = 0;
	while ((*binary_paths)[i++])
	{
		*one_path = ft_strjoin((*binary_paths)[i], "/");
		*one_command_path = ft_strjoin(*one_path, cmd);
		free(*one_path);
		if (!access(*one_command_path, F_OK))
		{
			free_string_arr(*binary_paths);
			return (*one_command_path);
		}
		free(*one_command_path);
	}
	free_string_arr(*binary_paths);
	return (NULL);
}

char	*get_working_path(char *cmd, char **env)
{
	int		j;
	char	*one_command_path;
	char	*one_path;
	char	**binary_paths;

	if (!access(cmd, F_OK))
		return (ft_strdup(cmd));
	j = find_path_env(env, "PWD=");
	if (j == -1)
		return (NULL);
	one_command_path = ft_strjoin(env[j], cmd);
	if (!access(one_command_path, F_OK))
		return (one_command_path);
	free(one_command_path);
	j = find_path_env(env, "PATH=");
	if (j == -1)
		return (NULL);
	binary_paths = ft_split(env[j] + 5, ':');
	return (get_working_path_loop(&binary_paths,
			&one_path, &one_command_path, cmd));
}
