/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/20 10:24:58 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	draw_frame(t_wframe	*wframe)
{
	// static int i = 10;
	// static int j = 10;
	// pixel_put(wframe.frame, i, j, 0x000000FF);
	// mlx_put_image_to_window(wframe.window.mlx, wframe.window.win, wframe->frame->img, 0, 0);
	// i = (i +1)%860;
	// j = (j+1)%540;
}

int	mouse_move(int x, int y, t_wframe *wframe)
{
	mlx_clear_window(wframe->window.mlx, wframe->window.win);
	if (1)
		mlx_string_put(wframe->window.mlx, wframe->window.win, x, y, 0x00FFFFFF, "Where going");
}

int	key_hook(int keycode, t_wframe	*wframe)
{
	if (keycode == XK_Escape)
	{
		wframe->window.mlx->end_loop = True;
	}
	printf("keycode: %d\n", keycode);
	return (0);
}

int	mouse_hook(int keycode, t_wframe *wframe)
{
	printf("mouse keycode: %d\n", keycode);
	return (0);
}

void	draw_map(t_points ***data, int lines, int columns)
{
	t_wframe	wframe;

	wframe.data = data;
	wframe.window.mlx = mlx_init();
	wframe.window.win = mlx_new_window(wframe.window.mlx, 1200, 600, "Hello fucker!");
	wframe.frame.img = mlx_new_image(wframe.window.mlx, 800, 600);
	wframe.frame.addr = mlx_get_data_addr(wframe.frame.img, &wframe.frame.bits_per_pixel, &wframe.frame.line_length, &wframe.frame.endian);
	mlx_key_hook(wframe.window.win, &key_hook, &wframe);
	mlx_mouse_hook(wframe.window.win, &mouse_hook, &wframe);
	mlx_hook(wframe.window.win, 6, 1L << 6, &mouse_move, &wframe);
	mlx_loop_hook(wframe.window.mlx, &draw_frame, &wframe);
	mlx_loop(wframe.window.mlx);
	mlx_destroy_image(wframe.window.mlx, wframe.frame.img);
	mlx_destroy_window(wframe.window.mlx, wframe.window.win);
	mlx_destroy_display(wframe.window.mlx);
	free(wframe.window.mlx);
}

/*
typedef struct s_wframe
{
	t_vars		window;
	t_image		frame;
	t_points	***data;
}				t_wframe;
*/