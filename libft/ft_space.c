/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ommadhi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 03:02:33 by ommadhi           #+#    #+#             */
/*   Updated: 2019/04/20 03:03:07 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_space(char c)
{
	if (c == '\n' || c == '\r' || c == '\v')
		return (1);
	if (c == '\t' || c == ' ' || c == '\f')
		return (1);
	return (0);
}
