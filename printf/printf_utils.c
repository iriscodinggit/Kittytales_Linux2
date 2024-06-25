/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irlozano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:36:30 by irlozano          #+#    #+#             */
/*   Updated: 2023/11/25 15:04:44 by irlozano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(char c, size_t *counter)
{
	write(1, &c, 1);
	(*counter)++;
}

void	ft_putstr(char *s, size_t *counter)
{
	size_t	i;

	i = 0;
	if (!s)
	{
		write(1, "(null)", 6);
		(*counter) += 6;
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], counter);
		i++;
	}
}

void	ft_putnbr(long n, size_t *counter)
{
	long long int	t;

	t = n;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		(*counter) += 11;
		return ;
	}
	if (t < 0)
	{
		t *= -1;
		ft_putchar('-', counter);
	}
	if (t > 9)
	{
		ft_putnbr(t / 10, counter);
		ft_putchar(t % 10 + '0', counter);
	}
	else
		ft_putchar(t + '0', counter);
}

void	ft_putpointer(unsigned long pointer, size_t *counter)
{
	char	string[25];
	size_t	i;
	char	*base_sixteen;
	int		write_error;

	base_sixteen = "0123456789abcdef";
	i = 0;
	write_error = write(1, "0x", 2);
	if (write_error == -1)
		return ;
	(*counter) += 2;
	if (pointer == 0)
	{
		ft_putchar('0', counter);
		return ;
	}
	while (pointer != 0)
	{
		string[i] = base_sixteen[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
		ft_putchar(string[i], counter);
}

void	ft_puthexa(unsigned int nbr, size_t *counter, char case_type)
{
	char	string[25];
	char	*base_sixteen;
	size_t	i;

	if (case_type == 'X')
		base_sixteen = "0123456789ABCDEF";
	else
		base_sixteen = "0123456789abcdef";
	i = 0;
	if (nbr == 0)
	{
		ft_putchar('0', counter);
		return ;
	}
	while (nbr != 0)
	{
		string[i] = base_sixteen[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i--)
		ft_putchar(string[i], counter);
}
