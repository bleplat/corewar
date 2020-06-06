/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vm_valid_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthierce <jthierce@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 15:33:02 by jthierce          #+#    #+#             */
/*   Updated: 2020/06/06 22:21:28 by amalsago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "cw_vm.h"
#include "cw_vm_player.h"

/*
** cw_vm_read_magic_number() reads first 4 bytes of `.cor` file and checks
** the validity of magic number
*/

int		cw_vm_read_magic_number(int fd)
{
	unsigned char	magic_number[4];
	int32_t			magic_number_int;

	if (read(fd, magic_number, 4) != 4)
	{
		ft_dprintf(2, "{RED}ERROR READ MAGIC NUMBER\n{}");
		close(fd);
		return (CW_VM_READ_ERROR);
	}
	magic_number_int = ft_bigendian32_read(magic_number);
	if (magic_number_int != CW_EXEC_MAGIC)
	{
		ft_dprintf(2, "{RED}NOT VALID MAGIC NUMBER\n{}");
		close(fd);
		return(CW_VM_ERROR_NOT_VALID_PLAYER);
	}
	return (CW_SUCCESS);
}

/*
** cw_vm_read_champion_name() reads next 128 bytes `.cor` file, retreives
** champion name and store it in t_cw_champion
*/

int		cw_vm_read_champion_name(int fd, t_cw_player *player)
{
	char	name[CW_PROG_NAME_LENGTH + 1];

	if (read(fd, name, CW_PROG_NAME_LENGTH) != CW_PROG_NAME_LENGTH)
	{
		close(fd);
		ft_dprintf(2, "{RED}ERROR READ CHAMPION NAME\n{}");
		return (CW_VM_READ_ERROR);
	}
	name[ft_strlen(name)] = '\0';
	if ((player->champion->name = ft_strdup(name)) == NULL)
	{
		ft_dprintf(2, "{red}ERROR MALLOC FAILED\n{}");
		return (CW_ERROR_MALLOC_FAILED);
	}
	return (CW_SUCCESS);
}

/*
** cw_vm_read_champion_null() reads next 4 bytes `.cor` and look if
** the name is not too long
*/

int		cw_vm_read_champion_null(int fd)
{
	char	str[CW_CHAMPION_NULL];

	if (read(fd, str, CW_CHAMPION_NULL) != CW_CHAMPION_NULL)
	{
		close(fd);
		ft_dprintf(2, "{RED}ERROR READ CHAMPION NULL\n{}");
		return (CW_VM_READ_ERROR);
	}
	if (ft_memcmp(str, "\0\0\0\0", CW_CHAMPION_NULL) != 0)
	{
		ft_dprintf(2, "{red}NAME IS TOO LONG\n{}");
		return (CW_VN_ERROR_NAME_TOO_LONG);
	}
	return (CW_SUCCESS);
}

/*
** cw_vm_read_exec_code_len() reads next 4 bytes representing the size
** of champion's executable code
*/

int		cw_vm_read_exec_code_len(int fd, t_cw_player *player)
{
	int				i;
	unsigned char	code_len[4];

	i = -1;
	if (read(fd, code_len, CW_EXEC_CODE_LEN) != CW_EXEC_CODE_LEN)
	{
		close(fd);
		ft_dprintf(2, "{RED}ERROR READ CHAMPION EXEC CODE LEN\n{}");
		return (CW_VM_READ_ERROR);
	}
	while (++i < CW_EXEC_CODE_LEN)
		player->champion->code_len += code_len[i];
	return (CW_SUCCESS);
}

/*
** cw_vm_valid_player() opens `.cor` file, create champions and checks the
** validity of data provided in `.cor`
*/

int		cw_vm_valid_player(t_cw_data *data, t_cw_player *players)
{
	int		i;
	int		fd;
	int		ret;

	i = -1;
	while (++i < data->nbr_players)
	{
		if ((fd = open(data->filename[i], O_RDONLY)) == -1)
		{
			while (i != -1)
				cw_champion_destroy(&players[--i].champion);
			free(players);
			ft_dprintf(2, "{red}Cannot open file\n{}");
			exit(CW_VM_ERROR_OPEN_FAILED);
		}
		if (cw_champion_create(&players[i].champion) != CW_SUCCESS)
		{
			while (i != -1)
				cw_champion_destroy(&players[i--].champion);
			free(players);
			ft_dprintf(2, "{red}champion_create() failed\n{}");
			exit(CW_VM_ERROR_OPEN_FAILED);
		}
		if (((ret = cw_vm_read_magic_number(fd)) != CW_SUCCESS)
			|| ((ret = cw_vm_read_champion_name(fd, &players[i])) != CW_SUCCESS)
			|| ((ret = cw_vm_read_champion_null(fd)) != CW_SUCCESS)
			|| ((ret = cw_vm_read_exec_code_len(fd, &players[i])) != CW_SUCCESS))
		{
			while (i != -1)
				cw_champion_destroy(&players[i--].champion);
			free(players);
			exit(ret);
		}
		close(fd);
	}
	return (CW_SUCCESS);
}
