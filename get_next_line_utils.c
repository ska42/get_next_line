/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:46:43 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/17 17:54:12 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "get_next_line_bonus.h"

/*
**	INIT_FILES
**	initialize the array of struct t_file files.
**	return (int)
*/

int		init_files(t_file ***files)
{
	if (!((*files) = malloc(sizeof(char *))))
		return (-1);
	(*files)[0] = 0;
	return (0);
}

/*
**	NEW_FILE
**	Create a new t_list file, initialize parameters and
**	add it to new_file array.
**	return (int)
*/

int		new_file(int fd, t_file **new_file, char *buffer)
{
	int j;

	if (!(*new_file = malloc(sizeof(t_file))))
		return (-1);
	(*new_file)->fd = fd;
	(*new_file)->nblbuf = 0;
	if (!((*new_file)->buffer = malloc(sizeof(char) * BUFFER_SIZE)))
		return (0);
	j = -1;
	while (++j < BUFFER_SIZE)
		(*new_file)->buffer[j] = buffer[j];
	return (1);
}

/*
**	FIRST_READ
**	Read the new file set to t_file pointer array by malloc a new array size + 1
**	return (int)
*/

int		first_read(int fd, t_file ***files, char *buffer, int count)
{
	int			i;
	int			j;
	t_file		**new_files;

	if (read(fd, buffer, BUFFER_SIZE) == -1)
		return (-1);
	if (!(new_files = malloc(sizeof(t_file *) * (count + 2))))
		return (-1);
	i = 0;
	while (*files && (*files)[i])
	{
		new_files[i] = (*files)[i];
		i++;
	}
	if (!(new_file(fd, &new_files[i], buffer)))
		return (-1);
	new_files[++i] = 0;
	free(*files);
	if (!(*files = malloc(sizeof(t_file *) * (count + 2))))
		return (-1);
	j = -1;
	while (++j <= i)
		(*files)[j] = new_files[j];
	free(new_files);
	return (i - 1);
}

/*
**	CHECK_FILES
**	Check if the file fd if already on files or not.
**	return (int)
*/

int		check_files(int fd, t_file ***files)
{
	int			i;
	int			j;
	char		buffer[BUFFER_SIZE];

	i = -1;
	if (!files && init_files(&(*files)) == -1)
		return (-1);
	while (*files && (*files)[++i])
	{
		if ((*files)[i]->fd == fd)
		{
			if (!((*files)[i]->buffer) && read(fd, buffer, BUFFER_SIZE) > 0
					&& ((*files)[i]->buffer = malloc(sizeof(char) * BUFFER_SIZE)))
			{
				j = -1;
				while (++j < BUFFER_SIZE)
					(*files)[i]->buffer[j] = buffer[j];
			}
			return (i);
		}
	}
	i = 0;
	while (i < BUFFER_SIZE)
		buffer[i++] = 0;
	return (first_read(fd, files, buffer, i));
}

/*
**	GET_LINE_BREAK
**	Get nblbuf + 1 line break from buffer.
**	return (int)
*/

int		get_line_break(char *buffer, size_t *nblbuf)
{
	int i;
	int j;
	int k;

	j = 0;
	k = 0;
	while (k < (int)*nblbuf)
	{
		if (buffer[j] == '\n')
			k++;
		j++;
	}
	i = 0;
	while (i + j < BUFFER_SIZE && buffer[i + j] != '\n')
		i++;
	if (i + j == BUFFER_SIZE)
		return (i);
	else
		(*nblbuf)++;
	return (i);
}
