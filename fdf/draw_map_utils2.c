/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:37:47 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 18:04:41 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	orthographic(t_points ***data, int lines, int cols)
{
	rotate_z(data, lines, cols, M_PI * 0.7);
	rotate_y(data, lines, cols, M_PI + 0.6154729074);
	rotate_x(data, lines, cols, M_PI / 8);
}

void	scale_z(t_points ***data, int lines, int cols, double factor)
{
	int	k;
	int	l;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			data[k][l]->h *= factor;
			data[k][l]->z *= factor;
			l++;
		}
		k++;
	}
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
	double	divisor;
	int		k;
	int		l;

	divisor = 1;
	if (max != min)
		divisor = (max - min) / 20;
	k = 0;
	while (k < wframe->lines)
	{
		l = 0;
		while (l < wframe->cols)
		{
			wframe->data[k][l]->z = (wframe->data[k][l]->z - min)
				/ divisor;
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
