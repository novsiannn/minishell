/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhristi <ikhristi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 19:11:47 by nikitos           #+#    #+#             */
/*   Updated: 2023/07/28 15:31:44 by ikhristi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int main()
{
	char *str;
	int i = 0;

	while(i < 10)
	{
		str = readline("minishell => ");
		add_history(str);
		printf("%s", str);
		printf("\n");
		i++;
		printf("Денчика хотят");
	}
	return (1);
}