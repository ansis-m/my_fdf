/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/20 21:56:57 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_image *frame, int x, int y, float density)
{
	char	*dst;
	int		color;

	color = 0xFFFFFF;
	dst = frame->addr + (x * frame->line_length + y * (frame->bits_per_pixel / 8));
	*(unsigned int *)dst = color; //TO DO
}

void	swap(int *z, int *x)
{
	int	temp;

	temp = *z;
	*z = *x;
	*x = temp;
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
	intersect_y = a.y;
	if (steep)
	{
		while (a.x < a.y)
		{
			i = intersect_y;
			pixel_put(frame, a.x, i, 0.5); //rfPartOfNumber(intersect_y)
			pixel_put(frame, a.x, i - 1, 0.5); //fPartOfNumber(intersect_y)
			intersect_y += gradient;
			a.x++;
		}
	}
}

int	draw_frame(t_wframe	*wframe) //create a new frame here!!!!!!!!
{
	int		i;
	int		j;
	t_image	new;

	if (wframe->draw_new)
	{
		new.img = mlx_new_image(wframe->window.mlx, 600, 600);
		new.addr = mlx_get_data_addr(new.img, &new.bits_per_pixel, &new.line_length, &new.endian);
		i = 0;
		while(i < wframe->lines)
		{
			j = 0;
			while (j < wframe->cols)
			{
				if (i < wframe->lines - 1)
					draw_line(&new, *(wframe->data[i][j]), *(wframe->data[i + 1][j]));
				if (j < wframe->cols - 1)
					draw_line(&new, *(wframe->data[i][j]), *(wframe->data[i][j + 1]));
				j++;
			}
			i++;
		}
		mlx_destroy_image(wframe->window.mlx, wframe->frame.img);
		wframe->frame = new;
		printf("new\n");
		//wframe->draw_new = false; //To BE REMOVED
	}
	mlx_put_image_to_window(wframe->window.mlx, wframe->window.win, wframe->frame.img, 0, 0);
}

int	mouse_move(int x, int y, t_wframe *wframe)
{
	mlx_clear_window(wframe->window.mlx, wframe->window.win);
	if (1)
		mlx_string_put(wframe->window.mlx, wframe->window.win, x, y, 0xFFFFFF, "Where going");
}

void	scale(t_points ***data, int lines, int cols, float factor)
{
	int	k;
	int	l;

	printf("hello from scale\n");
	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			data[k][l]->x *= factor;
			data[k][l]->y *= factor;
			data[k][l]->z *= factor;
			data[k][l]->h *= factor;
			l++;
		}
		k++;
	}
}

int	key_hook(int keycode, t_wframe	*wframe)
{
	if (keycode == XK_Escape)
	{
		wframe->window.mlx->end_loop = True;
	}
	else if (keycode == XK_KP_Subtract)
		scale(wframe->data, wframe->lines, wframe->cols, 0.9);
	else if (keycode == XK_KP_Add)
		scale(wframe->data, wframe->lines, wframe->cols, 1.1);
	printf("keycode: %d\n", keycode);
	return (0);
}

int	mouse_hook(int keycode, t_wframe wframe)
{
	printf("mouse keycode: %d\n", keycode);
	return (0);
}

void	draw_map(t_points ***data, int lines, int columns)
{
	t_wframe	wframe;

	wframe.data = data;
	wframe.lines = lines;
	wframe.cols = columns;
	scale(wframe.data, wframe.lines, wframe.cols, 30);
	wframe.draw_new = true;
	wframe.window.mlx = mlx_init();
	wframe.window.win = mlx_new_window(wframe.window.mlx, 1200, 600, "Hello fucker!");
	wframe.frame.img = mlx_new_image(wframe.window.mlx, 600, 600);
	wframe.frame.addr = mlx_get_data_addr(wframe.frame.img, &wframe.frame.bits_per_pixel, &wframe.frame.line_length, &wframe.frame.endian);
	printf("frame from main: %p\n", &wframe.frame);
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

pixel_put(&wframe->frame, i, j, 0x0000FF);
*/