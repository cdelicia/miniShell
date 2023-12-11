/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdelicia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 11:52:29 by cdelicia          #+#    #+#             */
/*   Updated: 2019/05/19 20:41:25 by cdelicia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_counter(int n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

int		ft_power(int n)
{
	int p;

	p = 1;
	while (n > 1)
	{
		p = p * 10;
		n--;
	}
	return (p);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	un;
	char			c;
	int				bit;

	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n < 0)
		un = -n;
	else
		un = n;
	bit = ft_power(ft_counter(un));
	while (bit != 0)
	{
		c = un / bit + '0';
		ft_putchar_fd(c, fd);
		un = un % bit;
		bit = bit / 10;
	}
}
