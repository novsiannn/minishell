/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:45:55 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/25 14:47:00 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo_putstr_fd(char *arg, int fd)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\\')
			i++;
		write(fd, &arg[i], 1);
		i++;
	}
}

int	b_echo(char **args)
{
	int	i;
	int	n;

	n = 0;
	i = 1;
	if (!args[1])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (args[1][0] == '-' && args[1][1] == 'n' && !args[1][2])
	{
		i = 2;
		n = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			write(1, " ", 1);
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
