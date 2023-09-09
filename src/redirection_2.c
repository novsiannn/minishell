/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:16 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/09 17:22:18 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	open_output(t_pipe_group **tmp, t_token_list **token_tmp, int type)
{
	if (type == APPEND)
		(*tmp)->output = open((*token_tmp)->tok,
				O_WRONLY | O_APPEND | O_CREAT, 0777);
	else
		(*tmp)->output = open((*token_tmp)->tok,
				O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if ((*tmp)->output < 0)
		return (1);
	return (0);
}