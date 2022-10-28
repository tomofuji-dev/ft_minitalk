/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 06:48:31 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/28 12:02:56 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int signal, siginfo_t *info, void *ucontext)
{
	static char	c = 0;
	static int	i = 0;

	(void) ucontext;
	c <<= 1;
	if (signal == SIGUSR2)
		c |= 1;
	if (++i == 8)
	{
		i = 0;
		if (c == '\0')
		{
			kill(info->si_pid, SIGUSR2);
			return ;
		}
		ft_putchar_fd(c, STDOUT);
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	s_sa;

	ft_putstr_fd("PID: ", STDOUT);
	ft_putnbr_fd(getpid(), STDOUT);
	ft_putchar_fd('\n', STDOUT);
	s_sa.sa_sigaction = &handle_signal;
	s_sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_sa, NULL);
	sigaction(SIGUSR2, &s_sa, NULL);
	while (1)
		pause();
	return (0);
}
