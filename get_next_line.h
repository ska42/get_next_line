/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 19:26:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/17 23:39:44 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef FD_LIMIT
#  define FD_LIMIT 10241
# endif

# ifndef BUFF_SIZE
#  define BUFF_SIZE 4
# endif

int		get_next_line(int fd, char **line);

#endif
