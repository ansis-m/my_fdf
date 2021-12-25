/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/25 12:33:47 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	loop(t_wframe	*wframe)
{
	if (wframe->draw_new)
	{
		mlx_clear_window(wframe->window.mlx, wframe->window.win);
		if (!draw_frame(wframe))
			mlx_string_put(wframe->window.mlx, wframe->window.win, W, 250,
				0xFF0000, "EXCEEDED MAX DIMENSSION. SCALE DOWN!");
	}
	wframe->draw_new = false;
	mlx_put_image_to_window(wframe->window.mlx,
		wframe->window.win, wframe->frame.img, 0, 0);
	put_strings(wframe);
	return (0);
}

int	draw_frame(t_wframe	*wframe)
{
	double		zrange[4];

	get_zrange(wframe, zrange);
	if (wframe->center)
		center_projection(wframe);
	if (!check_size(wframe))
		return (0);
	clear_frame(&wframe->frame);
	draw_frame_helper(wframe, zrange);
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
	wframe->orthographic = true;
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
	orthographic(wframe.data, wframe.lines, wframe.cols);
	mlx_key_hook(wframe.window.win, &key_hook, &wframe);
	mlx_loop_hook(wframe.window.mlx, &loop, &wframe);
	mlx_loop(wframe.window.mlx);
	mlx_destroy_image(wframe.window.mlx, wframe.frame.img);
	mlx_destroy_window(wframe.window.mlx, wframe.window.win);
	mlx_destroy_display(wframe.window.mlx);
	free(wframe.window.mlx);
}
