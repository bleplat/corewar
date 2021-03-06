/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vm_usage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthierce <jthierce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 21:07:33 by amalsago          #+#    #+#             */
/*   Updated: 2020/06/16 21:42:13 by amalsago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cw_vm.h"
#include <unistd.h>

/*
** Show the correct usage of program
*/

int		cw_vm_usage(void)
{
	ft_dprintf(STDERR_FILENO, "usage: " \
			"./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	return (CW_VM_USAGE);
}
