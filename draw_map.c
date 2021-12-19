/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 16:13:48 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/19 18:18:18 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	mouse_move(int x, int y, t_vars *vars)
{
	mlx_clear_window(vars->mlx, vars->win);
	if (1)
		mlx_string_put(vars->mlx, vars->win, x, y, 0x00FFFFFF, "Where going");
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
	{
		vars->mlx->end_loop = True;
	}
	printf("keycode: %d\n", keycode);
	return (0);
}

void	draw_map(t_points ***data, int lines, int columns)
{
	t_vars	vars;
	t_image	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1200, 600, "Hello fucker!");
	//img.img = mlx_new_image(vars.mlx, 800, 600);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	mlx_key_hook(vars.win, &key_hook, &vars);
	mlx_hook(vars.win, 6, 1L << 6, &mouse_move, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
}
