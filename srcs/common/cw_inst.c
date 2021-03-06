/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_inst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthierce <jthierce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 21:27:06 by amalsago          #+#    #+#             */
/*   Updated: 2020/06/17 20:04:24 by amalsago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"
#include "cw_vm.h"
#include "cw_inst.h"
#include "cw_op.h"

/*
** Create a t_cw_inst with all field initialized to 0.
*/

t_cw_inst		*cw_inst_create(void)
{
	t_cw_inst	*inst;

	if (!(inst = malloc(sizeof(t_cw_inst))))
		return (NULL);
	ft_bzero(inst, sizeof(t_cw_inst));
	return (inst);
}

/*
** Destroy a t_cw_inst and set it to NULL.
*/

void			cw_inst_destroy(t_cw_inst **inst)
{
	free(*inst);
	*inst = NULL;
}

/*
** cw_inst_get_args() set up binary values of arguments and
** count their amount
*/

static void		cw_inst_get_args(t_cw_inst *inst, unsigned opc)
{
	inst->args_count = 0;
	inst->args[0] = (opc >> 6) & 0x03;
	inst->args[1] = (opc >> 4) & 0x03;
	inst->args[2] = (opc >> 2) & 0x03;
	if (inst->args[0])
		inst->args_count++;
	else
		return ;
	if (inst->args[1])
		inst->args_count++;
	else
		return ;
	if (inst->args[2])
		inst->args_count++;
	else
		return ;
}

/*
** cw_inst_dump() prints t_cw_inst structure
*/

void			cw_inst_dump(t_cw_inst *inst)
{
	unsigned	i;
	char		*op_name;

	i = -1;
	op_name = cw_op_list()[inst->opc - 1].name;
	ft_printf("opc:           %d (%s)\n", inst->opc, op_name);
	ft_printf("has_coding_byte:  ", inst->opc);
	(inst->has_coding_byte == TRUE) ? ft_printf("TRUE") : ft_printf("FALSE");
	ft_printf("\nargs_count:       %d\n", inst->args_count);
	(inst->args_count != 0) ? ft_printf("types:            ") : 0;
	while (++i < inst->args_count)
	{
		if (inst->types[i] == T_REG)
			ft_printf("T_REG");
		else if (inst->types[i] == T_DIR)
			ft_printf("T_DIR");
		else if (inst->types[i] == T_IND)
			ft_printf("T_IND");
		(i + 1 < inst->args_count) ? ft_putchar(' ') : ft_putchar('\n');
	}
}

/*
** cw_inst_fill() fills up t_cw_inst structure according to encoding byte,
** ang get argument's binary values and their type (T_REG | T_DIR | T_IND)
*/

void			cw_inst_fill(t_cw_vm *vm)
{
	unsigned	i;

	i = -1;
	ft_bzero(&vm->inst, sizeof(t_cw_inst));
	vm->inst.opc = vm->game.procs->opc;
	if (vm->game.byte_codage[vm->inst.opc - 1])
		vm->inst.has_coding_byte = TRUE;
	else
		vm->inst.has_coding_byte = FALSE;
	if (vm->inst.has_coding_byte == TRUE)
	{
		cw_inst_get_args(&vm->inst, vm->arena[
				(vm->game.procs->pos + 1) % CW_MEM_SIZE]);
		while (++i < vm->inst.args_count)
			if (vm->inst.args[i] == 0x01)
				vm->inst.types[i] = T_REG;
			else if (vm->inst.args[i] == 0x02)
				vm->inst.types[i] = T_DIR;
			else if (vm->inst.args[i] == 0x03)
				vm->inst.types[i] = T_IND;
	}
}
