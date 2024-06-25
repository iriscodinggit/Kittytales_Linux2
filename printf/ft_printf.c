/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:07:43 by irlozano          #+#    #+#             */
/*   Updated: 2023/11/25 14:56:24 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format(va_list arguments, char format, size_t *counter)
{
	if (format == 'c')
		ft_putchar(va_arg(arguments, int), counter);
	else if (format == 's')
		ft_putstr(va_arg(arguments, char *), counter);
	else if (format == 'd' || format == 'i')
		ft_putnbr(va_arg(arguments, int), counter);
	else if (format == 'u')
		ft_putnbr(va_arg(arguments, unsigned int), counter);
	else if (format == 'p')
		ft_putpointer(va_arg(arguments, unsigned long), counter);
	else if (format == 'u')
		ft_putnbr(va_arg(arguments, unsigned int), counter);
	else if (format == 'X')
		ft_puthexa(va_arg(arguments, unsigned int), counter, 'X');
	else if (format == 'x')
		ft_puthexa(va_arg(arguments, unsigned int), counter, 'x');
	else if (format == '%')
		ft_putchar('%', counter);
}

int	ft_printf(char const *str, ...)
{
	va_list		arguments;
	size_t		counter;
	size_t		i;

	if (!str)
		return (0);
	counter = 0;
	i = 0;
	va_start(arguments, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			ft_format(arguments, str[i], &counter);
		}
		else
			ft_putchar(str[i], &counter);
		i++;
	}
	va_end(arguments);
	return (counter);
}
