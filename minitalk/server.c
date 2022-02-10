/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:16:41 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/10 16:28:32 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	binary_to_decimal(int binary, int pid)
{
	static unsigned char	ch = 0;
	static int				index = 7;

	ch += (binary << index--);
	if (index < 0)
	{
		write(1, &ch, 1);
		index = 7;
		ch = 0;
		if (kill(pid, SIGUSR1) == -1)
		{
			exit(0);
		}
		usleep(100);
	}
}

void	serverhandler(int signum, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	binary_to_decimal(signum == SIGUSR2, siginfo->si_pid);
}

int	main(void)
{
	struct sigaction	catch;

	ft_putstr_fd("Server PID : ", 1);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 2);
	catch.sa_flags = SA_SIGINFO;
	catch.sa_sigaction = serverhandler;
	if (sigaction(SIGUSR1, &catch, NULL) == -1)
		exit(1);
	if (sigaction(SIGUSR2, &catch, NULL) == -1)
		exit(1);
	while (1)
		pause();
	return (0);
}
