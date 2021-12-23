/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:22:10 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/23 19:36:47 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<limits.h>
#define _USE_MATH_DEFINES
# include	<math.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h> 
# include	<stdio.h>
# include	"get_next_line.h"
# include	"./minilibx-linux/mlx.h"
# include	"./minilibx-linux/mlx_int.h"

//width of an image
# define W	1000
//height of an image
# define H	700

typedef struct s_points
{
	double	h;
	double	x;
	double	y;
	double	z;
	double	f;
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
	bool		center;
	bool		orthographic;
}				t_wframe;

void		free_line_ptrs(char *line_ptrs[1000]);
t_points	*init_struct(int i, int j, int k);
void		init_file_read(char *filename, int *fd, int *lines, int *columns);
void		read_file(char *file, char *pointer[1000], int *lines, int *cols);
int			ft_atoi(const char *nptr);
void		draw_map(t_points ***data, int lines, int columns);
void		pixel_put(t_image *img, int x, int y, double color);
int			mouse_move(int x, int y, t_wframe *wframe);
void		clear_frame(t_image *frame);
void		swap(double *z, double *x);
int			draw_frame(t_wframe	*wframe);
void		scale_xy(t_points ***data, int lines, int cols, double factor);
void		translate(t_wframe *wframe, int x, int y);
void		reset(t_points ***data, int lines, int cols);
void		init_points(t_points ***data, int lines, int cols);
void		rotate_z(t_points ***data, int lines, int cols, double radians);
void		rotate_x(t_points ***data, int lines, int cols, double radians);
void		rotate_y(t_points ***data, int lines, int cols, double radians);
void		orthographic(t_points ***data, int lines, int cols);
void		center_projection(t_wframe *wframe);
void		draw_line(t_image *frame, t_points a, t_points b);
void		get_min_max(t_wframe *wframe, int xxyy[4]);

#endif
