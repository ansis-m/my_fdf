/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/23 16:58:38 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_image *frame, int x, int y, double density)
{
	char	*dst;
	int		color;
	int		intensity;

	intensity = 0xFF * density;
	color = (intensity << 16 | intensity << 8 | intensity);
	dst = frame->addr
		+ (x * frame->line_length + y * (frame->bits_per_pixel / 8));
	if (*(unsigned int *)dst < color)
		*(unsigned int *)dst = color;
}

int	roundd(double intersect_y)
{
	intersect_y += 0.5;
	return ((int)intersect_y);
}

double	fraction(double x)
{
	int	integer;

	integer = x;
	if (x > 0)
		return (x - integer);
	return (x - integer + 1);
}

double	residue(double x)
{
	return (1 - fraction(x));
}

void	draw_line(t_image *frame, t_points a, t_points b)
{
	bool	steep;
	double	dx;
	double	dy;
	double	gradient;
	double	intersect_y;

	steep = ((b.y - a.y) * (b.y - a.y) > (b.x - a.x) * (b.x - a.x));
	if (steep)
	{
		swap(&a.x, &a.y);
		swap(&b.x, &b.y);
	}
	if (a.x > b.x)
	{
		swap(&a.x, &b.x);
		swap(&a.y, &b.y);
	}
	dx = b.x - a.x;
	dy = b.y - a.y;
	if (b.x == a.x)
		gradient = 1;
	else
		gradient = dy / dx;
	intersect_y = a.y;
	while (a.x < b.x)
	{
		if (steep)
		{
			pixel_put(frame, roundd(intersect_y), a.x, residue(intersect_y));
			pixel_put(frame, roundd(intersect_y) - 1, a.x, fraction(intersect_y));
		}
		else
		{
			pixel_put(frame, a.x, roundd(intersect_y), residue(intersect_y));
			pixel_put(frame, a.x, roundd(intersect_y) - 1, fraction(intersect_y));
		}
		intersect_y += gradient;
		a.x++;
	}
}

int	loop(t_wframe	*wframe)
{
	if (wframe->draw_new)
		draw_frame(wframe);
	wframe->draw_new = false;
	mlx_put_image_to_window(wframe->window.mlx,
		wframe->window.win, wframe->frame.img, 0, 0);
	return (1);
}

int	mouse_move(int x, int y, t_wframe *wframe)
{
	mlx_clear_window(wframe->window.mlx, wframe->window.win);
	if (1)
		mlx_string_put(wframe->window.mlx, wframe->window.win, x, y, 0xFFFFFF, "Where going");
}

int	key_hook(int keycode, t_wframe	*wframe)
{
	if (keycode == XK_Escape)
		wframe->window.mlx->end_loop = True;
	else if (keycode == XK_KP_Subtract)
		scale_xy(wframe->data, wframe->lines, wframe->cols, 0.8);
	else if (keycode == XK_KP_Add)
	{
		scale_xy(wframe->data, wframe->lines, wframe->cols, 1.2);
		wframe->center = true;
	}
	else if (keycode == XK_Down)
	{
		translate(wframe, 10, 0);
		wframe->center = false;
	}
	else if (keycode == XK_Up)
	{
		translate(wframe, -10, 0);
		wframe->center = false;
	}
	else if (keycode == XK_Right)
	{
		translate(wframe, 0, 10);
		wframe->center = false;
	}
	else if (keycode == XK_Left)
	{
		translate(wframe, 0, -10);
		wframe->center = false;
	}
	wframe->draw_new = true;
	return (0);
}

void	isometric(t_points ***data, int lines, int cols)
{
	int	k;
	int	l;
	double	a;
	double	b;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			a = data[k][l]->x;
			b = data[k][l]->y;
			data[k][l]->x = (a - data[k][l]->z) * 0.8944;
			data[k][l]->y = (a + data[k][l]->z) * 0.4472 - b;
			data[k][l]->h = 1;
			l++;
		}
		k++;
	}
}

void	draw_map(t_points ***data, int lines, int columns)
{
	t_wframe	wframe;

	wframe.data = data;
	wframe.lines = lines;
	wframe.cols = columns;
	scale_xy(wframe.data, wframe.lines, wframe.cols, 10);
	rotate_z(wframe.data, wframe.lines, wframe.cols, M_PI* 0.7);
	rotate_y(wframe.data, wframe.lines, wframe.cols, M_PI + 0.6154729074);
	rotate_x(wframe.data, wframe.lines, wframe.cols, M_PI / 8);


	
	//reset(wframe.data, wframe.lines, wframe.cols);  //NOT needed here but elswhere
	wframe.center = true;
	wframe.draw_new = true;
	wframe.window.mlx = mlx_init();
	wframe.window.win = mlx_new_window(wframe.window.mlx, 1200, 600, "Hello fucker!");
	wframe.frame.img = mlx_new_image(wframe.window.mlx, W, H);
	wframe.frame.addr = mlx_get_data_addr(wframe.frame.img, &wframe.frame.bits_per_pixel, &wframe.frame.line_length, &wframe.frame.endian);
	mlx_key_hook(wframe.window.win, &key_hook, &wframe);
	mlx_hook(wframe.window.win, 6, 1L << 6, &mouse_move, &wframe);
	mlx_loop_hook(wframe.window.mlx, &loop, &wframe);
	mlx_loop(wframe.window.mlx);
	mlx_destroy_image(wframe.window.mlx, wframe.frame.img);
	mlx_destroy_window(wframe.window.mlx, wframe.window.win);
	mlx_destroy_display(wframe.window.mlx);
	free(wframe.window.mlx);
}
