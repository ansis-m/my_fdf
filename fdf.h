/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:22:10 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/20 19:51:20 by amalecki         ###   ########.fr       */
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

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_vars
{
	t_xvar		*mlx;
	t_win_list	*win;
}				t_vars;

typedef struct s_wframe
{
	t_vars		window;
	t_image		frame;
	t_points	***data;
	int			lines;
	int			cols;
	bool		draw_new;
}				t_wframe;

void		free_line_ptrs(char *line_ptrs[1000]);
t_points	*init_struct(int i, int j, int k);
void		init_file_read(char *filename, int *fd, int *lines, int *columns);
void		read_file(char *file, char *pointer[1000], int *lines, int *cols);
int			ft_atoi(const char *nptr);
void		draw_map(t_points ***data, int lines, int columns);

void		pixel_put(t_image *img, int x, int y, float color);
int			mouse_move(int x, int y, t_wframe *wframe);

#endif
