/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:48:42 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/26 19:34:30 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	expander(void)
{
	t_token_list	*tmp;
	char			*buf;

	tmp = g_shell_h->head;
	while (tmp)
	{
		if (tmp->type == DOUBLE_QUOTES)
		{
			buf = resolve_dollar(tmp->tok);
			free(tmp->tok);
			tmp->tok = buf;
			buf = NULL;
		}
		tmp = tmp->next;
	}
}

void	if_empty_var_name(int *j, char **res)
{
	ft_strlcat(res[*j], "$", 2);
	*j += 1;
}

// void	not_empty_var_name(char **var_name, char **res, int *j)
// {
// 	char	*var_value;

// 	var_value = find_in_env(*var_name);
// 	if (var_value)
// 		ft_strlcat(res[*j], var_value, ft_strlen(var_value) + 1);
// 	*j += ft_strlen(var_value);
// }

char	*resolve_dollar(char *inp)
{
	int		i;
	int		j;
	char	*res;
	char	*var_name;
	char	*var_value;

	res = ft_calloc(define_malloc(&i, &j, inp) + 1, 1);
	j = 0;
	while (inp[i] != '\0')
	{
		if (inp[i] == '$')
		{
			var_name = get_var_name(&inp[++i]);
			if (*var_name == '\0')
				if_empty_var_name(&j, &res);
			else
			{
				var_value = find_in_env(var_name);
				if (var_value)
					ft_strlcat(&res[j], var_value, ft_strlen(var_value) + 1);
				j += ft_strlen(var_value);
			}
			i += ft_strlen(var_name);
			free(var_name);
		}
		else
		{
			res[j] = inp[i];
			j++;
			i++;
		}
	}
	res[j] = '\0';
	return (res);
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
