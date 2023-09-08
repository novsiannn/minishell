/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:19:16 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/08 20:47:21 by novsiann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*here_doc_init(char **file_name, t_token_list **token_tmp,
						t_pipe_group **tmp, int *file)
{
	char	*limiter;

	*file_name = ft_strdup(".heredoc");
	charjoin_free(file_name, (*tmp)->pipe_index + '0');
	limiter = (*token_tmp)->tok;
	*file = open(*file_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	return (limiter);
}

int	here_doc(t_token_list **token_tmp, t_pipe_group **tmp)
{
	char	*limit;
	int		file;
	char	*file_name;

	limit = here_doc_init(&file_name, token_tmp, tmp, &file);
}