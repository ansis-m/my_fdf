/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/22 11:08:23 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_image *frame, int x, int y, float density)
{
	char	*dst;
	int		color;
	int		intensity;

	intensity = 0xFF * density;
	color = (intensity << 24 | intensity << 16 | intensity << 8 | intensity);
	dst = frame->addr
		+ (x * frame->line_length + y * (frame->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_image *frame, t_points a, t_points b)
{
	bool	steep;
	float	dx;
	float	dy;
	float	gradient;
	float	intersect_y;
	int		i;

	steep = (abs(b.y - a.y) > abs(b.x - a.x));
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
	//printf("x: %d, %d\ty: %d, %d\t gradient: %f\n", a.x, b.x, a.y, b.y, gradient);
	intersect_y = a.y;
	
	while (a.x < b.x)
	{
		i = intersect_y;
		if (steep)
		{
			pixel_put(frame, i/1000, a.x/1000, 0.5); //rfPartOfNumber(intersect_y)
			pixel_put(frame, (i - 1)/1000, a.x/1000, 1); //fPartOfNumber(intersect_y)
		}
		else
		{
			pixel_put(frame, a.x/1000, i/1000, 0.5); //rfPartOfNumber(intersect_y)
			pixel_put(frame, a.x/1000, (i - 1)/1000, 1); //fPartOfNumber(intersect_y)
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
		wframe->window.win, wframe->frame.img, 10, 10);
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
	{
		wframe->window.mlx->end_loop = True;
	}
	else if (keycode == XK_KP_Subtract)
		scale_xy(wframe->data, wframe->lines, wframe->cols, 0.9);
	else if (keycode == XK_KP_Add)
		scale_xy(wframe->data, wframe->lines, wframe->cols, 1.1);
	printf("keycode: %d\n", keycode);
	wframe->draw_new = true;
	return (0);
}

void	draw_map(t_points ***data, int lines, int columns)
{
	t_wframe	wframe;

	wframe.data = data;
	wframe.lines = lines;
	wframe.cols = columns;
	scale_xy(wframe.data, wframe.lines, wframe.cols, 10000);
	translate(wframe, 10, 10);
	wframe.draw_new = true;
	wframe.window.mlx = mlx_init();
	wframe.window.win = mlx_new_window(wframe.window.mlx, 1200, 600, "Hello fucker!");
	wframe.frame.img = mlx_new_image(wframe.window.mlx, 600, 600);
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
