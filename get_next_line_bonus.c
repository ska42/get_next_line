/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:17:24 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/18 12:17:30 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_substr(char buffer[])
{
	int		i;
	int		j;
	char	cpy[BUFF_SIZE + 1];

	cpy[BUFF_SIZE] = '\0';
	i = 0;
	while (buffer[i] != '\n' && i < BUFF_SIZE)
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (i < BUFF_SIZE)
		cpy[j++] = buffer[i++];
	cpy[j] = '\0';
	i = -1;
	while (cpy[++i])
		buffer[i] = cpy[i];
	buffer[i] = '\0';
}

int		check_file(int fd, char files[][BUFF_SIZE + 1])
{
	int length;

	if (fd < 0)
		return (-1);
	length = 0;
	if (files[fd][0] == '\0' && (length = read(fd, files[fd], BUFF_SIZE)) <= 0)
		return (length);
	length = 0;
	if (files[fd][0] != '\0')
		while (files[fd][length]
							&& files[fd][length] != '\n' && length < BUFF_SIZE)
			length++;
	return (length);
}

int		copy_and_cut_buffer(int size, int length, char **line, char buffer[])
{
	int				i;
	char			*cpy;

	if (!(cpy = malloc(sizeof(char) * (size))))
		return (-1);
	i = -1;
	while (++i < size - length)
		cpy[i] = (*line)[i];
	i = -1;
	while (++i + (size - length) < size)
		cpy[i + (size - length)] = buffer[i];
	free((*line));
	if (!((*line) = malloc(sizeof(char) * (size + 1))))
		return (-1);
	i = -1;
	while (++i < size)
		(*line)[i] = cpy[i];
	(*line)[size] = '\0';
	free(cpy);
	ft_substr(buffer);
	return (1);
}

int		copy_and_reset(int size, int length, char **line, char buffer[])
{
	int				i;
	char			*cpy;

	if (!(cpy = malloc(sizeof(char) * (size))))
		return (-1);
	i = -1;
	while (++i < size - length)
		cpy[i] = (*line)[i];
	i = -1;
	while (++i + (size - length) < size)
		cpy[i + (size - length)] = buffer[i];
	free((*line));
	if (!((*line) = malloc(sizeof(char) * (size))))
		return (-1);
	i = -1;
	while (++i < size)
		(*line)[i] = cpy[i];
	free(cpy);
	i = 0;
	while (i < BUFF_SIZE)
		buffer[i++] = '\0';
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int				length;
	int				size;
	static char		files[FD_LIMIT + 1][BUFF_SIZE + 1];

	if ((length = check_file(fd, files)) < 0)
		return (length);
	if (files[fd][0] == '\0')
		return (length);
	if (!((*line) = malloc(sizeof(char) * 0)))
		return (-1);
	size = 0;
	while ((size += length) > -1 && files[fd][0] != '\0')
	{
		if (files[fd][length] == '\n' || length == 0)
			return (copy_and_cut_buffer(size, length, line, files[fd]));
		else if (copy_and_reset(size, length, line, files[fd]) < 0)
			return (-1);
		if (!length && files[fd][0] == '\0')
			return (length);
		if ((length = check_file(fd, files)) < 0)
			return (length);
	}
	if (size > 0)
		return (copy_and_cut_buffer(size, length, line, files[fd]));
	return (0);
}
