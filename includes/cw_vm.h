/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthierce <jthierce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 15:01:47 by jthierce          #+#    #+#             */
/*   Updated: 2020/06/07 14:37:10 by amalsago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_VM_H
# define CW_VM_H

# define CW_MAX_PLAYERS		4

# include <stdlib.h>
# include "cw_errors.h"
# include "cw_vm_parsing.h"
# include "cw_vm_player.h"

typedef struct	s_cw_vm
{
	t_cw_data		data;
	t_bool			dump;
	t_cw_player		players[CW_MAX_PLAYERS];
	unsigned char	arena[CW_MEM_SIZE + 1];

}				t_cw_vm;

void	cw_vm_usage(void);
int		cw_vm_parsing(int argc, char **argv, t_cw_vm *vm);
int		cw_vm_get_data(char **argv);
int		cw_vm_get_player(t_cw_vm *vm, char *filename);
int		cw_vm_is_valid_extension(const char *argv, const char *extension);
void	cw_vm_print_data(t_cw_data *data);
int		cw_vm_read_player(t_cw_vm *vm);
void	cw_vm_check_nbr_players(t_cw_vm *vm);
int		cw_vm_ini_arena(t_cw_vm *vm);
void	cw_vm_intro_players(t_cw_vm *vm);
void	cw_vm_battle(t_cw_vm *vm);

#endif