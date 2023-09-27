/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:16:37 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/27 16:41:40 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	put_skip(t_token_list **tmp)
{
	if ((*tmp)->type && (*tmp)->type != -1)
	{
		*tmp = (*tmp)->next;
		return (1);
	}
	return (0);
}

void	delete_empty_node(t_token_list **list)
{
	t_token_list	*tmp;

	tmp = *list;
	while (tmp != NULL)
	{
		printf("%s\n", tmp->tok);
		tmp = tmp->next;
	}
}

int	main_allocate(char **splited, char *readed)
{
	if (ft_init_list(&(g_shell_h->head), readed, splited) == 1)
	{
		free_readed_and_splited(readed, splited);
		return (1);
	}
	ft_lexer();
	expander();
	g_shell_h->pipes = redirection();
	if (g_shell_h->pipes == NULL)
	{
		free_readed_and_splited(readed, splited);
		return (1);
	}
	return (0);
}

int	define_malloc(int *i, int *j, char *inp)
{
	char	*var_name;
	char	*var_value;

	*i = 0;
	*j = 0;
	while (inp[*i])
	{
		if (inp[*i] == '$')
		{
			var_name = get_var_name(&inp[++(*i)]);
			var_value = find_in_env(var_name);
			(*i) += ft_strlen(var_name);
			(*j) += ft_strlen(var_value);
			free(var_name);
		}
		else
		{
			(*i)++;
			(*j)++;
		}
	}
	*i = 0;
	return (*j);
}

char	*get_var_name(char *inp)
{
	char	*ret;
	int		i;

	i = 0;
	while (inp[i] && (ft_isalnum(inp[i]) || inp[i] == '_'))
		i++;
	ret = malloc(i + i);
	i = 0;
	while (inp[i] && (ft_isalnum(inp[i]) || inp[i] == '_'))
	{
		ret[i] = inp[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
