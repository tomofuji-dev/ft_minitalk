/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujiwar <tfujiwar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 06:50:59 by tfujiwar          #+#    #+#             */
/*   Updated: 2022/10/28 12:12:00 by tfujiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static t_bool	check_args(int argc, char *argv[])
{
	char	*pid;
	size_t	i;

	if (argc != 3)
		return (FALSE);
	pid = argv[1];
	i = 0;
	while (pid[i])
	{
		if (ft_isdigit(pid[i++]) == 0)
			return (FALSE);
	}
	if (ft_atoi(pid) < 100 || ft_atoi(pid) > 99998)
		return (FALSE);
	return (TRUE);
}

static void	handle_signal(int signal)
{
	if (signal == SIGUSR2)
		exit(1);
}

static void	send_message(pid_t pid, char *msg)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (i < (int)ft_strlen(msg) + 1)
	{
		c = msg[i];
		j = 8;
		while (j-- > 0)
		{
			if (((c >> j) & 1) == 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	s_sa;

	if (!check_args(argc, argv))
		exit(1);
	s_sa.sa_handler = handle_signal;
	sigaction(SIGUSR2, &s_sa, NULL);
	send_message(ft_atoi(argv[1]), argv[2]);
	while (1)
		pause();
	return (0);
}
