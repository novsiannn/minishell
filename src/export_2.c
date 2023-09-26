/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:35:23 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 14:09:34 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	builtin_export(char **argv)
{
	int	i;
	int	index;

	if (!argv[1])
	{
		print_export();
		return (0);
	}
	i = 0;
	while (argv[++i])
	{
		if (!ft_strchr(argv[i], '='))
			continue ;
		else if (!check_var_name(argv[i]))
			ft_putstr_fd("export: not valid in this context\n", 2);
		index = find_path_env(g_shell_h->envp, argv[i]);
		change_env(argv[i], index);
	}
	return (0);
}
