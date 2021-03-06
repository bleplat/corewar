/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_champion_save_to_file.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bleplat <bleplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 18:23:35 by bleplat           #+#    #+#             */
/*   Updated: 2020/06/18 06:49:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "libft.h"

#include "cw_errors.h"
#include "cw_champion.h"

static int	write_name(t_cw_champion *champion, int fd)
{
	int		rst;
	int		len;

	rst = 0;
	len = champion->name ? ft_strlen(champion->name) : 0;
	if (len > CW_PROG_NAME_LENGTH)
		return (write(fd, champion->name, CW_PROG_NAME_LENGTH));
	rst |= write(fd, champion->name, len);
	while (len < CW_PROG_NAME_LENGTH)
	{
		rst |= write(fd, "\0", 1);
		len++;
	}
	return (rst);
}

static int	write_comment(t_cw_champion *champion, int fd)
{
	int		rst;
	int		len;

	rst = 0;
	len = champion->comment ? ft_strlen(champion->comment) : 0;
	if (len > CW_COMMENT_LENGTH)
		return (write(fd, champion->comment, CW_COMMENT_LENGTH));
	rst |= write(fd, champion->comment, len);
	while (len < CW_COMMENT_LENGTH)
	{
		rst |= write(fd, "\0", 1);
		len++;
	}
	return (rst);
}

/*
** Save a champion to a file descriptor.
*/

int			cw_champion_save_to_fd(t_cw_champion *champion, int fd)
{
	int		rst;
	char	tmp[4];

	rst = 0;
	ft_bigendian32_write((unsigned char *)tmp, CW_EXEC_MAGIC);
	rst |= write(fd, tmp, 4);
	rst |= write_name(champion, fd);
	rst |= write(fd, "\0\0\0\0", 4);
	ft_bigendian32_write((unsigned char *)tmp, champion->code_len);
	rst |= write(fd, tmp, 4);
	rst |= write_comment(champion, fd);
	rst |= write(fd, "\0\0\0\0", 4);
	rst |= write(fd, champion->code, champion->code_len);
	if (rst < 0)
		return (CW_ERROR_WRITING_OUTPUT_FILE);
	return (0);
}

/*
** Save a champion to a file.
** Use standard output if NULL is provided.
*/

int			cw_champion_save_to_file(t_cw_champion *champion, const char *file)
{
	int		rst;
	int		fd;

	if (file == NULL)
		return (cw_champion_save_to_fd(champion, 1));
	fd = open(file, O_WRONLY | O_CREAT, S_IRWXU | S_IROTH);
	if (fd < 0)
		return (CW_ERROR_OPENING_OUTPUT_FILE);
	rst = cw_champion_save_to_fd(champion, fd);
	close(fd);
	return (rst);
}
