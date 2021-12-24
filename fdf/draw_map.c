/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 13:22:35 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop(t_wframe	*wframe)
{
	if (wframe->draw_new)
		draw_frame(wframe);
	wframe->draw_new = false;
	mlx_put_image_to_window(wframe->window.mlx,
		wframe->window.win, wframe->frame.img, 0, 0);
	mlx_string_put(wframe->window.mlx, wframe->window.win, 1000, 30,
		0xFFFFFF, "fdf project by AMALECKI");
	mlx_string_put(wframe->window.mlx, wframe->window.win, 1000, 70,
		0xFF0000, "ZOOM-IN ZOOM-OUT + -");
	mlx_string_put(wframe->window.mlx, wframe->window.win, 1000, 90,
		0xFF0000, "TRANSLATE ARROW KEYS");
	mlx_string_put(wframe->window.mlx, wframe->window.win, 1000, 110,
		0xFF0000, "ORTHOGRAPHIC PROJECTION o KEY");
	mlx_string_put(wframe->window.mlx, wframe->window.win, 1000, 130,
		0xFF0000, "ROTATE Z X Y AXIS z x y KEYS");
	mlx_string_put(wframe->window.mlx, wframe->window.win, 1000, 150,
		0xFF0000, "SCALE HEIGHT h KEY");
	mlx_string_put(wframe->window.mlx, wframe->window.win, 1000, 170,
		0xFFFF00, "EXIT escape KEY");
	return (1);
}

int	mouse_move(int x, int y, t_wframe *wframe)
{
	mlx_clear_window(wframe->window.mlx, wframe->window.win);
	if (1)
		mlx_string_put(wframe->window.mlx, wframe->window.win, x, y, 0xFFFFFF, "Where going");
	return (1);
}

void	init_wframe(t_wframe *wframe, t_points ***data, int lines, int columns)
{
	wframe->data = data;
	wframe->lines = lines;
	wframe->cols = columns;
	wframe->center = true;
	wframe->draw_new = true;
	wframe->orthographic = false;
	wframe->window.mlx = mlx_init();
	wframe->window.win = mlx_new_window(wframe->window.mlx, 1200, 700,
			"AMAZING fdf PROJECT BY AMALECKI@42WOLFSBURG");
	wframe->frame.img = mlx_new_image(wframe->window.mlx, W, H);
	wframe->frame.addr = mlx_get_data_addr(wframe->frame.img,
			&wframe->frame.bits_per_pixel, &wframe->frame.line_length,
			&wframe->frame.endian);
}

void	scale_height(int keycode, t_wframe	*wframe)
{
	reset(wframe->data, wframe->lines, wframe->cols);
	wframe->center = true;
	if (keycode == XK_Page_Up)
		scale_z(wframe->data, wframe->lines, wframe->cols, 1.4);
	if (keycode == XK_Page_Down)
		scale_z(wframe->data, wframe->lines, wframe->cols, 0.7);
	if (wframe->orthographic)
		orthographic(wframe->data, wframe->lines, wframe->cols);
}

void	init_scale_z(t_wframe *wframe, double min, double max)
{
	int	k;
	int	l;

	k = 0;
	while (k < wframe->lines)
	{
		l = 0;
		while (l < wframe->cols)
		{
			wframe->data[k][l]->z = (wframe->data[k][l]->z - min)
				/ (max - min) * 20;
			wframe->data[k][l]->h = wframe->data[k][l]->z;
			l++;
		}
		k++;
	}
}

void	normalize_z(t_wframe *wframe)
{
	int		k;
	int		l;
	double	min;
	double	max;

	min = wframe->data[0][0]->z;
	max = wframe->data[0][0]->z;
	k = 0;
	while (k < wframe->lines)
	{
		l = 0;
		while (l < wframe->cols)
		{
			if (wframe->data[k][l]->z > max)
				max = wframe->data[k][l]->z;
			if (wframe->data[k][l]->z < max)
				min = wframe->data[k][l]->z;
			l++;
		}
		k++;
	}
	init_scale_z(wframe, min, max);
}

void	draw_map(t_points ***data, int lines, int columns)
{
	t_wframe	wframe;

	init_wframe(&wframe, data, lines, columns);
	normalize_z(&wframe);
	//scale_xy(wframe.data, wframe.lines, wframe.cols, 10);
	mlx_key_hook(wframe.window.win, &key_hook, &wframe);
	mlx_hook(wframe.window.win, 6, 1L << 6, &mouse_move, &wframe);
	mlx_loop_hook(wframe.window.mlx, &loop, &wframe);
	mlx_loop(wframe.window.mlx);
	mlx_destroy_image(wframe.window.mlx, wframe.frame.img);
	mlx_destroy_window(wframe.window.mlx, wframe.window.win);
	mlx_destroy_display(wframe.window.mlx);
	free(wframe.window.mlx);
}
