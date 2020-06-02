/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:54:11 by bleplat           #+#    #+#             */
/*   Updated: 2018/12/13 17:08:26 by bleplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_pow(int nb, unsigned int p)
{
	int		total;

	total = 1;
	while (p > 0)
	{
		total *= nb;
		p--;
	}
	return (total);
}
