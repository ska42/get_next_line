/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:05:12 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/16 19:18:37 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

/*
**	DEFINE BUFFER_SIZE IF NOT DURING COMPILATION (-D)
*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/*
**	STRUCT s_file
**	int		fd			-> file_descriptor
**	size_t	nblbuf		-> number of lines readed on current buffer
**	char	*buffer		-> actual buffer
*/
# ifndef S_FILE
#  define S_FILE

typedef	struct		s_file
{
	int				fd;
	size_t			nblbuf;
	char			*buffer;
}					t_file;

# endif

/*
**	get_next_line_utils
*/
int					init_files(t_file ***files);
int					new_file(int fd, t_file **new_file, char *buffer);
int					first_read(int fd, t_file ***files,
										char *buffer, int count);
int					check_files(int fd, t_file ***files);
int					get_line_break(char *buffer, size_t *nblbuf);

/*
**	get_next_line
*/
char				*ft_strjoin(char **s, char *buffer, int length, int nblbuf);
char				*ft_strjoin_with_zero(char **s,
										char *buffer, int length, int nblbuf);
int					end_of_file(t_file **files, char **line,
										int length, int nblbuf);
int					fill_line(int fd, t_file ***files, int i, char **line);
int					get_next_line(int fd, char **line);

#endif
