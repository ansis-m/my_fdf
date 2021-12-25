/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:22:10 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/25 13:16:51 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define _USE_MATH_DEFINES
# include	<math.h>
# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<limits.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h> 
# include	"get_next_line.h"
# include	"../minilibx-linux/mlx.h"
# include	"../minilibx-linux/mlx_int.h"

//width of an image
# define W	1000
//height of an image
# define H	700

//width of the display
# define WD	1200
//height of the display
# define HD	700

typedef struct s_points
{
	double	h;
	double	x;
	double	y;
	double	z;
	double	f;
}	t_points;

typedef struct s_image
{
	XShmSegmentInfo	shm;
	XImage			*img;
	Pixmap			pix;
	GC				gc;
	int				line_length;
	int				bits_per_pixel;
	int				width;
	int				height;
	int				endian;
	int				type;
	int				format;
	char			*addr;
}	t_image;

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

unsigned int	get_color(double fraction, double zrange[3]);
void			free_line_ptrs(char *line_ptrs[1000]);
t_points		*init_struct(int i, int j, int k);
void			init_file_read(char *filename, int *fd,
					int *lines, int *columns);
void			read_file(char *file, char *pointer[1000],
					int *lines, int *cols);
int				ft_atoi(const char *nptr);
void			draw_map(t_points ***data, int lines, int columns);
void			pixel_put(t_image *img, int x, int y, unsigned int color);
void			clear_frame(t_image *frame);
void			swap(double *z, double *x);
int				draw_frame(t_wframe	*wframe);
void			scale_xy(t_points ***data, int lines, int cols, double factor);
void			scale_z(t_points ***data, int lines, int cols, double factor);
void			scale_height(int keycode, t_wframe	*wframe);
void			translate(t_wframe *wframe, int x, int y);
void			reset(t_points ***data, int lines, int cols);
void			init_points(t_points ***data, int lines, int cols);
void			rotate_z(t_points ***data, int lines, int cols, double radians);
void			rotate_x(t_points ***data, int lines, int cols, double radians);
void			rotate_y(t_points ***data, int lines, int cols, double radians);
void			orthographic(t_points ***data, int lines, int cols);
void			center_projection(t_wframe *wframe);
void			draw_line(t_wframe *wframe,
					double zrange[3], t_points a, t_points b);
void			get_min_max(t_wframe *wframe, int xxyy[4]);
void			init_wframe(t_wframe *wframe, t_points ***data,
					int lines, int columns);
int				roundd(double intersect_y);
double			fraction(double x);
double			residue(double x);
void			manage_translate(int keycode, t_wframe	*wframe);
void			manage_orthographic(t_wframe	*wframe);
void			manage_rotate(int keycode, t_wframe	*wframe);
int				key_hook(int keycode, t_wframe	*wframe);
void			normalize_z(t_wframe *wframe);
void			init_scale_z(t_wframe *wframe, double min, double max);
void			normalize_xy(t_wframe *wframe);
bool			normalize_points(t_points *a, t_points *b,
					double *dx, double *dy);
bool			check_size(t_wframe	*wframe);
void			manage_parallel(int keycode, t_wframe	*wframe);
void			put_strings(t_wframe	*wframe);
void			get_zrange(t_wframe	*wframe, double zrange[3]);
void			draw_frame_helper(t_wframe	*wframe, double zrange[3]);
void			draw_line_helper(t_wframe *wframe,
					double zrange[3], t_points *a, t_points *b);

#endif
