/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils_bonus1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:16:58 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/10 16:48:08 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	return (index);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10 && n >= 0)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else if (n > 0)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	int	index;

	index = 0;
	if (fd < 0)
		return ;
	while (s[index] != '\0')
	{
		write(fd, &s[index], 1);
		index++;
	}
}
