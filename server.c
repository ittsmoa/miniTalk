/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moatieh <moatieh@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 04:00:34 by moatieh           #+#    #+#             */
/*   Updated: 2026/01/17 04:00:34 by moatieh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static void ft_putnbr(int n)
{
    char    c;

    if(n >=10)
        ft_putnbr(n / 10 );
    c = (n % 10) + '0';
    write(1, &c, 1);
}

static void handler(int sig, siginfo_t *info, void *context)
{
    static unsigned char current_char;
    static int bit_counter;
    int bit;

    (void)context;
    if (sig == SIGUSR1)
        bit = 0;
    else
        bit = 1;
    current_char = (current_char << 1) | bit;
    bit_counter++;
    kill(info->si_pid, SIGUSR1);

    if (bit_counter == 8)
    {
        if (current_char == '\0')
            write(1, "\n", 1);
        else
            write(1, &current_char, 1);
        current_char = 0;
        bit_counter = 0;
    }
}


static void set_signals(void)
{
    struct sigaction sa;

    sa.sa_sigaction = handler;
    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}


int	main(void)
{
	write(1, "Server PID: ", 12);
	ft_putnbr(getpid());
	write(1, "\n", 1);

	set_signals();

	while (1)
		pause();

	return (0);
}
