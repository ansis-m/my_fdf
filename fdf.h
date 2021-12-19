/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:22:10 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/19 16:16:27 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<limits.h>
# include	<math.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h> 
# include	<stdio.h>
# include	"get_next_line.h"
# include	"./minilibx-linux/mlx.h"
# include	"./minilibx-linux/mlx_int.h"

typedef struct s_points
{
	int	h;
	int	x;
	int	y;
	int	z;
}	t_points;

void		free_line_ptrs(char *line_ptrs[1000]);
t_points	*init_struct(int i, int j, int k);
void		init_file_read(char *filename, int *fd, int *lines, int *columns);
void		read_file(char *file, char *pointer[1000], int *lines, int *cols);
int			ft_atoi(const char *nptr);
void		draw_map(t_points ***data, int lines, int columns);

#endif
