/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 17:48:42 by ikhristi          #+#    #+#             */
/*   Updated: 2023/09/27 16:41:29 by ikhristi         ###   ########.fr       */
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

void	append_var_value_to_result(char *var_name, char *res, int *j)
{
	char	*var_value;

	var_value = find_in_env(var_name);
	if (var_value)
	{
		ft_strlcat(&res[*j], var_value, ft_strlen(var_value) + 1);
		*j += ft_strlen(var_value);
	}
}

void	copy_character_to_result(char *inp, char *res, int *i, int *j)
{
	res[*j] = inp[*i];
	(*j)++;
	(*i)++;
}

char	*resolve_dollar(char *inp)
{
	int		i;
	int		j;
	char	*res;
	char	*var_name;

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
				append_var_value_to_result(var_name, res, &j);
			i += ft_strlen(var_name);
			free(var_name);
		}
		else
			copy_character_to_result(inp, res, &i, &j);
	}
	res[j] = '\0';
	return (res);
}
