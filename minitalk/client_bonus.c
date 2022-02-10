/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:17:03 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/10 16:46:27 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

size_t	g_charnum = 0;

void	error_print(int fd, char *str)
{
	ft_putstr_fd(str, fd);
	exit(0);
}

void	decimal_to_bin(int pid, char message)
{
	int	result;
	int	i;

	result = 0;
	i = 7;
	while (i >= 0)
	{
		result = message >> i & 1;
		if (result == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				error_print(2, "failed to send message\n");
		}
		else if (result == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				error_print(2, "failed to send message\n");
		}
		i--;
		usleep(100);
	}
}

void	send_message(int pid, char *message)
{
	int	index;

	index = 0;
	while (message[index] != '\0')
	{
		decimal_to_bin(pid, message[index]);
		index++;
	}
	return ;
}

void	clienthandler(int signum, siginfo_t *siginfo, void *context)
{
	(void)signum;
	(void)siginfo;
	(void)context;
	g_charnum++;
}

int	main(int argc, char **argv)
{
	struct sigaction	catch;

	g_charnum = 0;
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = clienthandler;
	if (sigaction(SIGUSR1, &catch, NULL) == -1)
		exit (1);
	if (sigaction(SIGUSR2, &catch, NULL) == -1)
		exit (1);
	if (argc != 3)
		error_print(2, "invalid arguement number\n");
	else
	{
		send_message(ft_atoi(argv[1]), argv[2]);
		usleep(100);
		if (g_charnum != ft_strlen(argv[2]))
		{
			write(1, "receive error\n", 15);
			return (1);
		}
		else
			write(1, "message received\n", 18);
	}
	return (1);
}
