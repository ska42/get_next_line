/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 12:17:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/10/18 13:40:25 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef FD_LIMIT
#  define FD_LIMIT 10241
# endif

# ifndef BUFF_SIZE
#  define BUFF_SIZE 4096
# endif

int		get_next_line(int fd, char **line);

#endif
