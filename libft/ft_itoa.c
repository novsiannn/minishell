/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikitos <nikitos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 15:55:10 by nikitos           #+#    #+#             */
/*   Updated: 2022/12/31 14:13:33 by nikitos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_sign(int n)
{
	int	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	return (sign);
}

static int	counting_digits(int num)
{
	int	count;

	count = 0;
	while (num)
	{
		num = num / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*str;
	int		sign;

	count = counting_digits(n) + (n <= 0);
	sign = check_sign(n);
	str = (char *)malloc(sizeof(char) * (count + 1));
	if (!str)
		return (str);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str[count] = '\0';
	while (n)
	{
		str[--count] = (char)((n % 10) * sign + '0');
		n = n / 10;
	}
	if (sign == -1)
		str[--count] = '-';
	return (str);
}
