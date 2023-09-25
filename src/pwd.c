/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:24:28 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/25 13:41:41 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// int ft_pwd(void)
// {
//     char    *pwd;
    
//     pwd = find_in_env("PWD");
//     printf("%s", pwd);
//     return (1);
// }
int	ft_pwd(void)
{
	int		j;
	char	*pwd;

	j = 0;
	j = find_path_env(g_shell_h->envp, "PWD");
	pwd = ft_strchr(g_shell_h->envp[j], '=');
	pwd++;
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	return (1);
}