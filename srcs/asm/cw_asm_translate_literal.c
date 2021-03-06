/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_asm_translate_literal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleplat <bleplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 18:23:11 by bleplat           #+#    #+#             */
/*   Updated: 2020/06/18 05:43:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_asm.h"

static int	translate_iliteral(t_cw_asm *state, t_cw_linst *linst,
								int type, int i_int)
{
	int		rst;

	(void)state;
	if ((rst = ft_atoi00check(&rst, &linst->raw[i_int])) < 0)
		return (cw_asmr(CW_ASMR_INT_INVALID, i_int, linst));
	if (!(linst->literal = cw_literal_create(type, &linst->raw[i_int])))
		return (CW_ERROR_MALLOC_FAILED);
	return (CW_SUCCESS);
}

static int	translate_literal2(t_cw_asm *state, t_cw_linst *linst,
								int type, int i_space)
{
	int		rst;
	int		i_quote;

	i_quote = cw_asm_skip_spaces_index(linst, i_space);
	if (type != CW_LITERAL_TYPE_NAME && type != CW_LITERAL_TYPE_COMMENT)
		return (translate_iliteral(state, linst, type, i_quote));
	if ((rst = cw_asm_dismember_string(state, linst, i_quote)) < 0)
		return (rst);
	if (!(linst->literal = cw_literal_create(type, &linst->raw[i_quote + 1])))
		return (CW_ERROR_MALLOC_FAILED);
	linst->raw[i_quote] = '\"';
	linst->raw[ft_strlen(linst->raw)] = '\"';
	return (CW_SUCCESS);
}

/*
** Simply translate a literal.
** This is, in fact, a substep of insts translation.
*/

int			cw_asm_translate_literal(t_cw_asm *state, t_cw_linst *linst)
{
	int		i_lit;
	char	bck;
	int		type;
	int		i_end;

	i_lit = cw_asm_skip_spaces_index(linst, 0);
	if (linst->raw[i_lit] != '.')
		return (CW_SUCCESS);
	i_end = i_lit;
	i_end = cw_asm_skip_alnums_index(linst, i_lit + 1);
	bck = linst->raw[i_end];
	linst->raw[i_end] = '\0';
	type = cw_literal_get_type(&linst->raw[i_lit]);
	linst->raw[i_end] = bck;
	if (type == CW_LITERAL_TYPE_NONE)
		return (cw_asmr(CW_ASMR_LITERAL_UNKNOWN, i_lit, linst));
	return (translate_literal2(state, linst, type, i_end));
}
