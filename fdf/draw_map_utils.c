/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:10:53 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 18:04:53 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_frame(t_image *frame)
{
	char	*dst;
	int		color;
	int		i;
	int		j;

	color = 0x000000;
	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			dst = frame->addr + i * frame->line_length
				+ j * (frame->bits_per_pixel / 8);
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	get_min_max(t_wframe *wframe, int xxyy[4])
{
	int		i;
	int		j;

	i = 0;
	while (i < wframe->lines)
	{
		j = 0;
		while (j < wframe->cols)
		{
			if (wframe->data[i][j]->x > xxyy[0])
				xxyy[0] = wframe->data[i][j]->x;
			if (wframe->data[i][j]->x < xxyy[1])
				xxyy[1] = wframe->data[i][j]->x;
			if (wframe->data[i][j]->y > xxyy[2])
				xxyy[2] = wframe->data[i][j]->y;
			if (wframe->data[i][j]->y < xxyy[3])
				xxyy[3] = wframe->data[i][j]->y;
			j++;
		}
		i++;
	}
}

void	center_projection(t_wframe *wframe)
{
	int		xxyy[4];
	int		i;
	int		j;

	xxyy[0] = wframe->data[0][0]->x;
	xxyy[1] = wframe->data[0][0]->x;
	xxyy[2] = wframe->data[0][0]->y;
	xxyy[3] = wframe->data[0][0]->y;
	get_min_max(wframe, xxyy);
	i = 0;
	while (i < wframe->lines)
	{
		j = 0;
		while (j < wframe->cols)
		{
			wframe->data[i][j]->x += (H - xxyy[0] - xxyy[1]) / 2;
			wframe->data[i][j]->y += (W - xxyy[2] - xxyy[3]) / 2;
			j++;
		}
		i++;
	}
}

bool	check_size(t_wframe	*wframe)
{
	int		xxyy[4];

	xxyy[0] = wframe->data[0][0]->x;
	xxyy[1] = wframe->data[0][0]->x;
	xxyy[2] = wframe->data[0][0]->y;
	xxyy[3] = wframe->data[0][0]->y;
	get_min_max(wframe, xxyy);
	if (xxyy[0] > H || xxyy[1] < 0)
		return (false);
	return (true);
}

void	scale_xy(t_points ***data, int lines, int cols, double factor)
{
	int	k;
	int	l;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			data[k][l]->x *= factor;
			data[k][l]->y *= factor;
			data[k][l]->f *= factor;
			l++;
		}
		k++;
	}
}
