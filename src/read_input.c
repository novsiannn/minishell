/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 16:53:49 by novsiann          #+#    #+#             */
/*   Updated: 2023/08/08 18:02:11 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_input(void)
{
	char	cwd[256];
	char	*ret;

	getcwd(cwd, sizeof(cwd));
	ft_strlcat(cwd, " : ", 256);
	ret = readline(cwd);
	if (ret && *ret)
		add_history(ret);
	return (ret);
}
