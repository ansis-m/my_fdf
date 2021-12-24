/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 18:24:42 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop(t_wframe	*wframe)
{
	if (wframe->draw_new)
	{
		mlx_clear_window(wframe->window.mlx, wframe->window.win);
		if (!draw_frame(wframe))
			mlx_string_put(wframe->window.mlx, wframe->window.win, W, 200,
				0xFFFFFF, "EXCEEDED MAX DIMENSSION. SCALE DOWN!");
	}
	wframe->draw_new = false;
	mlx_put_image_to_window(wframe->window.mlx,
		wframe->window.win, wframe->frame.img, 0, 0);
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 30,
		0xFFFFFF, "fdf project by AMALECKI");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 70,
		0xFF0000, "ZOOM-IN ZOOM-OUT + -");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 90,
		0xFF0000, "TRANSLATE ARROW KEYS");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 110,
		0xFF0000, "ORTHOGRAPHIC PROJECTION o KEY");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 130,
		0xFF0000, "ROTATE Z X Y AXIS z x y KEYS");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 150,
		0xFF0000, "SCALE HEIGHT PgUp PgDn KEYS");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 170,
		0xFFFF00, "EXIT escape KEY");
	return (0);
}

int	draw_frame(t_wframe	*wframe)
{
	int		i;
	int		j;

	if (wframe->center)
		center_projection(wframe);
	if (!check_size(wframe))
		return (0);
	clear_frame(&wframe->frame);
	i = 0;
	while (i < wframe->lines)
	{
		j = 0;
		while (j < wframe->cols)
		{
			if (i < wframe->lines - 1)
				draw_line(&wframe->frame,
					*(wframe->data[i][j]), *(wframe->data[i + 1][j]));
			if (j < wframe->cols - 1)
				draw_line(&wframe->frame,
					*(wframe->data[i][j]), *(wframe->data[i][j + 1]));
			j++;
		}
		i++;
	}
	return (1);
}

void	normalize_xy(t_wframe *wframe)
{
	double	k;

	if (H / wframe->cols > W / wframe->lines)
		k = W / wframe->lines / 1.5;
	else
		k = H / wframe->cols / 1.5;
	scale_xy(wframe->data, wframe->lines, wframe->cols, k);
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
	wframe->window.win = mlx_new_window(wframe->window.mlx, WD, HD,
			"AMAZING fdf PROJECT BY AMALECKI@42WOLFSBURG");
	wframe->frame.img = mlx_new_image(wframe->window.mlx, W, H);
	wframe->frame.addr = mlx_get_data_addr(wframe->frame.img,
			&wframe->frame.bits_per_pixel, &wframe->frame.line_length,
			&wframe->frame.endian);
}

void	draw_map(t_points ***data, int lines, int columns)
{
	t_wframe	wframe;

	init_wframe(&wframe, data, lines, columns);
	normalize_z(&wframe);
	normalize_xy(&wframe);
	mlx_key_hook(wframe.window.win, &key_hook, &wframe);
	mlx_loop_hook(wframe.window.mlx, &loop, &wframe);
	mlx_loop(wframe.window.mlx);
	mlx_destroy_image(wframe.window.mlx, wframe.frame.img);
	mlx_destroy_window(wframe.window.mlx, wframe.window.win);
	mlx_destroy_display(wframe.window.mlx);
	free(wframe.window.mlx);
}
