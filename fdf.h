/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:22:10 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/22 18:22:36 by amalecki         ###   ########.fr       */
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

//Scaling factor F
# define F 10000
//width of an image
# define W	600
//height of an image
# define H	600

typedef struct s_points
{
	int	h;
	int	x;
	int	y;
	int	z;
	int	f;
}	t_points;

typedef struct  s_image
{
	XImage                  *img;
	Pixmap                  pix;
	GC                              gc;
	int                             line_length;
	int                             bits_per_pixel;
	int                             width;
	int                             height;
	int		endian;
	int                             type;
	int                             format;
	char                    *addr;
	XShmSegmentInfo shm;
}                               t_image;

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
void		clear_frame(t_image *frame);
void		swap(int *z, int *x);
int			draw_frame(t_wframe	*wframe);
void		scale_xy(t_points ***data, int lines, int cols, float factor);
void		translate(t_wframe *wframe, int x, int y);
void		reset(t_points ***data, int lines, int cols);
void		isometric(t_points ***data, int lines, int cols);
void		init_points(t_points ***data, int lines, int cols);
void		rotate_z(t_points ***data, int lines, int cols, float radians);
void		center_projection(t_wframe *wframe);

#endif
