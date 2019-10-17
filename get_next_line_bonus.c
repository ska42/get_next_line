/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:04:50 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/16 19:19:12 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
**	FT_STRJOIN
**	Allocate memory for returned pointer str which is s + the unallocated part
**	of buffer before /n (all the buffer if no /n).
**	return (char *)
*/

char	*ft_strjoin(char **s, char *buffer, int length, int nblbuf)
{
	int		i;
	int		j;
	int		k;
	int		n;
	char	*str;

	if (!(str = malloc((length) * sizeof(char))))
		return (0);
	n = 0;
	while (nblbuf > 0 && n < BUFFER_SIZE)
		if (buffer[n++] == '\n')
			nblbuf--;
	i = 0;
	while (i + n < BUFFER_SIZE && buffer[i + n] != '\n')
		i++;
	j = -1;
	while (++j < length - i)
		str[j] = (*s)[j];
	k = j;
	j = -1;
	while (++j < length - k)
		str[k + j] = buffer[j + n];
	free(*s);
	return (str);
}

/*
**	FT_STRJOIN_WITH_ZERO
**	Allocate memory for returned pointer str which is s + the unallocated part
**	of buffer before /n (all the buffer if no /n) and add '\0' to the string
**	return (char *)
*/

char	*ft_strjoin_with_zero(char **s, char *buffer, int length, int nblbuf)
{
	int		k;
	int		n;
	char	*str;

	if (!(str = malloc((length) * sizeof(char))))
		return (0);
	n = 0;
	k = 0;
	while (k < nblbuf && buffer && n < BUFFER_SIZE)
		if (buffer[n++] == '\n')
			k++;
	if (!(k *= 0) && buffer)
		while (k + n < BUFFER_SIZE && buffer[k + n] != '\n')
			k++;
	nblbuf = -1;
	while (++nblbuf < (length - 1) - k)
		str[nblbuf] = (*s)[nblbuf];
	free(*s);
	k = -1;
	if (!buffer)
		return (str = 0);
	while (++k < (length - 1) - nblbuf)
		str[k + nblbuf] = buffer[k + n];
	str[length - 1] = '\0';
	return (str);
}

/*
**	END_OF_FILE
**	Handle the case where read return (0).
**	return (int)
*/

int		end_of_file(t_file **file, char **line, int length, int nblbuf)
{
	int i;
	int j;

	if (BUFFER_SIZE == 1)
		*line = ft_strjoin_with_zero(line, (*file)->buffer, length + 2, nblbuf);
	(*file)->nblbuf = 0;
	if (!(*line))
	{
		free((*file)->buffer);
		(*file)->buffer = 0;
		return (0);
	}
	i = 0;
	j = 0;
	while (i < length && (*line)[i])
		if ((*line)[i++] != '\n')
			j++;
	if (!j)
		return (0);
	free((*file)->buffer);
	(*file)->buffer = 0;
	return (1);
}

/*
**	FILL_LINE
**	Fill the line with str_join and str_join_with_zero.
**	return (int)
*/

int		fill_line(int fd, t_file ***files, int i, char **line)
{
	int j;
	int length;
	int nblbuf;

	length = 0;
	nblbuf = (*files)[i]->nblbuf;
	while (nblbuf == (int)(*files)[i]->nblbuf)
	{
		length += get_line_break((*files)[i]->buffer, &((*files)[i]->nblbuf));
		if (nblbuf != (int)(*files)[i]->nblbuf)
			*line = ft_strjoin_with_zero(line, (*files)[i]->buffer,
															length + 1, nblbuf);
		else
		{
			*line = ft_strjoin(line, (*files)[i]->buffer, length, nblbuf);
			j = 0;
			while (j < BUFFER_SIZE)
				(*files)[i]->buffer[j++] = 0;
			if (!(read(fd, (*files)[i]->buffer, BUFFER_SIZE)))
				return (end_of_file(&((*files)[i]), line, length, nblbuf));
			(*files)[i]->nblbuf = 0;
			nblbuf = 0;
		}
	}
	return (1);
}

/*
**	GET_NEXT_LINE
**	Get the next line of the file of file descriptor fd and put it in the line
**	pointer.
**	return (int)
*/

int		get_next_line(int fd, char **line)
{
	int				index;
	static t_file	**files;

	if (fd < 0 || !line)
		return (-1);
	if ((index = check_files(fd, &files)) == -1)
		return (-1);
	if (!(*line = malloc(0)))
		return (-1);
	if (!(files[index]->buffer))
		return (0);
	return (fill_line(fd, &files, index, line));
}
