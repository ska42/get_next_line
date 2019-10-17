/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:18:05 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/17 23:39:17 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

char	*ft_strcat(int size, int length, char **line, char file[])
{
	int		i;
	char	*cpy;

	if (!(cpy = malloc(sizeof(char) * (size))))
		return (NULL);
	i = -1;
	while (++i < size - length)
		cpy[i] = (*line)[i];
	i = -1;
	while (++i + (size - length) < size)
		cpy[i + (size - length)] = file[i];
	return (cpy);
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
		while (files[fd][length] && files[fd][length] != '\n' && length < BUFF_SIZE)
			length++;
	return (length);
}

int		copy_and_cut_buffer(int size, int length, char **line, char buffer[])
{
	int				i;
	char			*cpy;

	cpy = ft_strcat(size, length, line, buffer);
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

	cpy = ft_strcat(size, length, line, buffer);
	free((*line));
	if (!((*line) = malloc(sizeof(char) * (size))))
		return (-1);
	i = -1;
	while (++i < size)
		(*line)[i] = cpy[i];
	free(cpy);
	buffer[0] = '\0';
	return (1);
}

int		get_next_line(int fd, char **line)
{
	int				i;
	int				length;
	int				size;
	static char		files[FD_LIMIT + 1][BUFF_SIZE + 1];

	if (!((*line) = malloc(sizeof(char) * 0)))
		return (-1);
	if ((length = check_file(fd, files)) <= 0)
		return (length);
	if (files[fd][0] == '\0')
		return (length);
	size = length;
	while (files[fd][0] != '\0')
	{
		if (files[fd][length] == '\n' || length == 0)
			return(copy_and_cut_buffer(size, length, line, files[fd]));
		else
			if (copy_and_reset(size, length, line, files[fd]) < 0)
				return (-1);
		if (!length && files[fd][0] == '\0')
			return (length);
		if ((length = check_file(fd, files)) < 0)
			return (length);
		size += length;
	}
	printf("SIZE %i\n", size);
	if (size > 0)
	{
		i = copy_and_cut_buffer(size, length, line, files[fd]);
		files[fd][0] = '\0';
		return (i);
	}
	return (0);
}


#include <fcntl.h>
#include <stdio.h>

int		main()
{
	int fd;
	int fd2;
	int ret;
	char *line;

	fd = open("test", O_RDONLY);
	fd2 = open("test2", O_RDONLY);
	/**
	ret = get_next_line(fd, &line);
	printf("RET : %i\n", ret);
	printf("LINE : %s\n", line);
	ret = get_next_line(fd2, &line);
	printf("RET : %i\n", ret);
	printf("LINE : %s\n", line);
	ret = get_next_line(fd, &line);
	printf("RET : %i\n", ret);
	printf("LINE : %s\n", line);
	ret = get_next_line(fd2, &line);
	printf("RET : %i\n", ret);
	printf("LINE : %s\n", line);
	ret = get_next_line(fd2, &line);
	printf("RET : %i\n", ret);
	printf("LINE : %s\n", line);
	ret = get_next_line(fd, &line);
	printf("RET : %i\n", ret);
	printf("LINE : %s\n", line);
**/
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		printf("RET : %i\n", ret);
		printf("LINE : %s\n", line);
		ret = get_next_line(fd, &line);
	}
	printf("RET : %i\n", ret);
	printf("LINE : %s\n", line);
	return (0);
}
