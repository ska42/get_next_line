/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 12:28:54 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/21 11:58:40 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_substr(char buffer[])
{
	long	i;
	long	j;
	char	cpy[BUFFER_SIZE + 1];

	i = 0;
	while (i < BUFFER_SIZE + 1)
		cpy[i++] = '\0';
	i = 0;
	while (buffer[i] != '\n' && i < BUFFER_SIZE && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	j = 0;
	while (i < BUFFER_SIZE)
		cpy[j++] = buffer[i++];
	i = -1;
	while (++i < BUFFER_SIZE)
		buffer[i] = cpy[i];
	buffer[i] = '\0';
}

int		check_file(int fd, char files[][BUFFER_SIZE + 1])
{
	int		b;
	long	len;
	long	nb_read;

	b = 0;
	if (fd < 0 || fd > 10240)
		return (-1);
	len = 0;
	while (files[fd][len] && files[fd][len] != '\n' && len < BUFFER_SIZE)
		len++;
	if (len > 0 || files[fd][len] == '\n')
		return (len);
	if ((nb_read = read(fd, files[fd], BUFFER_SIZE)) < 0)
		return (nb_read);
	len = 0;
	while (files[fd][len] != '\n' && len < nb_read)
		len++;
	return (len);
}

int		copy_and_cut_buffer(int size, int length, char **line, char buffer[])
{
	long			i;
	char			cpy[size];

	i = -1;
	while (++i < size - length)
		cpy[i] = (*line)[i];
	i = -1;
	while (++i + (size - length) < size)
		cpy[i + (size - length)] = buffer[i];
	free((*line));
	if (!((*line) = malloc(sizeof(char) *
					(size + ((buffer[length] == '\n' || !length) ? 1 : 0)))))
		return (-1);
	i = -1;
	while (++i < size)
		(*line)[i] = cpy[i];
	if (!(i *= 0) && (buffer[length] == '\n' || !length))
	{
		(*line)[size] = '\0';
		ft_substr(buffer);
		return (1);
	}
	while ((buffer[length] != '\n' || length) && i < BUFFER_SIZE)
		buffer[i++] = '\0';
	return (0);
}

int		get_next_line(int fd, char **line)
{
	int				length;
	int				size;
	static char		files[10242][BUFFER_SIZE + 1];

	if (!line || BUFFER_SIZE <= 0 || !((*line) = malloc(sizeof(char)))
		|| (length = check_file(fd, files)) < 0)
		return (-1);
	if (!length && files[fd][length] != '\n')
		(*line)[0] = '\0';
	size = 0;
	while ((size += length) > -1 && (length || files[fd][length] == '\n'))
	{
		if (copy_and_cut_buffer(size, length, line, files[fd]) != 0)
			return (1);
		if ((length = check_file(fd, files)) < 0)
			return (length);
	}
	if (size > 0)
		return (copy_and_cut_buffer(size, length, line, files[fd]));
	return (0);
}
