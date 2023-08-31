/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: novsiann <novsiann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:48:42 by ikhristi          #+#    #+#             */
/*   Updated: 2023/08/31 18:23:51 by novsiann         ###   ########.fr       */
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
			free(buf);
		}
		tmp = tmp->next;
	}
}

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
			var_value = find_in_env(var_name);
			if (var_value)
				ft_strlcat(&res[j], var_value, ft_strlen(var_value) + 1);
			i += ft_strlen(var_name);
			j += ft_strlen(var_value);
			free(var_name);
			// free(var_value);
		}
		else
		{
			res[j] = inp[i];
			j++;
			i++;
		}
	}
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
			// free(var_value);
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