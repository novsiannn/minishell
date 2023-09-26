/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:00:52 by nikitos           #+#    #+#             */
/*   Updated: 2023/09/26 18:10:32 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	here_doc(t_token_list **token_tmp, t_pipe_group **tmp)
{
	char	*limit;
	int		file;
	char	*file_name;
	char	*buf;

	limit = here_doc_init(&file_name, token_tmp, tmp, &file);
	if (file < 0)
		return (throw_error("couldn't open HEREDOC\n"));
	while (1)
	{
		buf = readline("heredoc> ");
		if (!buf)
		{
			free(buf);
			return (1);
		}
		if (!ft_strcmp(limit, buf))
			break ;
		charjoinfree(&buf, '\n');
		write(file, buf, ft_strlen(buf));
		free(buf);
	}
	close(file);
	heredoc_last(token_tmp, tmp, &file_name, &buf);
	return (0);
}

void	heredoc_last(t_token_list **token_tmp,
				t_pipe_group **tmp, char **file_name, char **buf)
{
	free(*buf);
	(*tmp)->input = open(*file_name, O_RDONLY);
	(*tmp)->heredoc = *file_name;
	*token_tmp = (*token_tmp)->next;
}

char	*here_doc_init(char **file_name, t_token_list **token_tmp,
						t_pipe_group **tmp, int *file)
{
	char	*limiter;

	*file_name = ft_strdup(".heredoc");
	charjoinfree(file_name, (*tmp)->pipe_index + '0');
	limiter = (*token_tmp)->tok;
	*file = open(*file_name, O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	return (limiter);
}
