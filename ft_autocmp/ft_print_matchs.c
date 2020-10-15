/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_matchs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:13:28 by ommadhi           #+#    #+#             */
/*   Updated: 2020/10/15 20:16:11 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_autocmp.h"

int                     ft_check_is_safe(void)
{
    struct termios      config;
    char                *termname;
    int                 fd;

    fd = open(ttyname(2), O_RDWR);
    if (tcgetattr(fd, &config) < 0)
        ft_putendl_fd("error", fd);
    config.c_lflag &= ~(ICANON);
    if (tcsetattr(fd, TCSANOW, &config) < 0)
        ft_putendl_fd("error", fd);
    termname = getenv("TERM");
    if (termname == NULL)
    {
        ft_putstr("ft_select: TERM Variable Not set !!");
        return (-1);
    }
    if (tgetent(NULL, termname) <= 0)
    {
        ft_putendl_fd("failure to unitialise Temrcap", 2);
        return (-1);
    }
 //   tputs(tgetstr("ti", NULL), 0, ft_putsfd);
//    tputs(tgetstr("cl", NULL), 0, ft_putsfd);
    return (0);
}

int				ft_putsfd(int p)
{
	write(1, &p, 1);
	return (1);
}

static int				ft_get_max_lent(t_dlist *match)
{
	int					maxlent;

	maxlent = 0;
	while (match)
	{
		if (maxlent < ft_strlen(match->data))
			maxlent = ft_strlen(match->data);
		match = match->next;
	}
	return (maxlent);
}

void					ft_print_matchs(t_dlist *match, int index)
{
	int					i;
	int					j;
	int 				maxlent;
	struct winsize		w;

	ft_check_is_safe();
	ioctl(0, TIOCGWINSZ, &w);
	i = 0;
	j = g_pos.y + 1;
	maxlent = ft_get_max_lent(match);
	while (match)
	{
		if (i + maxlent == w.ws_col)
		{
			i = 0;
			j++;
		}
		tputs(tgoto(tgetstr("cm", NULL), i, j), 0, ft_putsfd);
		i = (i + maxlent + 1);
		ft_putstr(match->data);
		match = match->next;
	}
}
