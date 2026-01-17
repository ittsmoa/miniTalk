/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 04:59:28 by moatieh           #+#    #+#             */
/*   Updated: 2026/01/17 04:59:28 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

volatile sig_atomic_t g_ack = 0;

static int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res);
}

static void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack = 1;
}

static void	send_char(int server_pid, unsigned char c)
{
	int		i;
	int		bit;
	sigset_t	mask;
	sigset_t	oldmask;

	sigemptyset(&mask);
	sigaddset(&mask, SIGUSR1);
	sigprocmask(SIG_BLOCK, &mask, &oldmask);

	i = 7;
	while (i >= 0)
	{
		g_ack = 0;
		bit = (c >> i) & 1;
		if (bit == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (!g_ack)
			sigsuspend(&oldmask);
		i--;
	}
	sigprocmask(SIG_SETMASK, &oldmask, NULL);
}

int	main(int argc, char **argv)
{
	int					server_pid;
	int					i;
	struct sigaction	sa;

	if (argc != 3)
		return (1);

	server_pid = ft_atoi(argv[1]);
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	while (argv[2][i])
	{
		send_char(server_pid, argv[2][i]);
		i++;
	}
	send_char(server_pid, '\0');
	return (0);
}



