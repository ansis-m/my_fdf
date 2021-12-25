/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 08:47:19 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/25 11:56:36 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_strings(t_wframe	*wframe)
{
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 30,
		0xFFFFFF, "fdf project by AMALECKI");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 70,
		0xFFFFFF, "ZOOM-IN ZOOM-OUT + -");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 90,
		0xFFFFFF, "TRANSLATE ARROW KEYS");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 110,
		0xFFFFFF, "ROTATE Z X Y AXIS: z x y");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 130,
		0xFFFFFF, "SCALE HEIGHT: PgUp PgDn");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 150,
		0xFFFFFF, "ORTHOGRAPHIC PROJECTION: o");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 170,
		0xFFFFFF, "PARALLEL PROJECTION X: 1");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 190,
		0xFFFFFF, "PARALLEL PROJECTION Y: 2");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 210,
		0xFFFFFF, "PARALLEL PROJECTION Z: 3");
	mlx_string_put(wframe->window.mlx, wframe->window.win, W, 230,
		0xFF0000, "EXIT escape KEY");
}

void	get_zrange(t_wframe	*wframe, double zrange[3])
{
	int	k;
	int	l;

	zrange[1] = wframe->data[0][0]->h;
	k = 0;
	while (k < wframe->lines)
	{
		l = 0;
		while (l < wframe->cols)
		{
			if (wframe->data[k][l]->h > zrange[1])
				zrange[1] = wframe->data[k][l]->h;
			l++;
		}
		k++;
	}
}
