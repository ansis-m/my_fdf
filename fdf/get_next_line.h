/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:36:23 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/19 09:44:01 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include	<stdlib.h>
# include	<unistd.h>
# include	<stdbool.h>
# include <limits.h>

# define OPEN_MAX_F 6000
# define BUFFER_SIZE 50

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
bool	linebreak(char const *buffer);
size_t	ft_strlen(const char *c);
void	concatenate(char **remainder, char *buffer);
void	read_and_concatenate(int *bytes, int fd, char **remainder);
char	*ft_strdup(const char *c);
void	*ft_memset(void *s, int c, size_t n);

#endif