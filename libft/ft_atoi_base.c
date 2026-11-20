/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibondarc <ibondarc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 10:54:09 by ibondarc          #+#    #+#             */
/*   Updated: 2024/09/13 12:50:16 by ibondarc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_hex_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int result = 0;
	int sign = 1;
	int value;
 
	if (!str || str_base < 2 || str_base > 16)
		return (0);

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	
	int i = 0;
	while (str[i])
	{
		value = ft_is_hex_digit(str[i]);
		if ( value == -1 || value > str_base)
			return -1;

		result = result * str_base + value;
		i++;
	}
	return (result * sign);
}