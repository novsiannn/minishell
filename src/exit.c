/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 16:09:40 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 17:53:14 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	command_exit(char **arg)
{
	int	len;
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
