/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:10:53 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/22 18:24:03 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_frame(t_image *frame)
{
	char	*dst;
	int		color;
	int		i;
	int		j;

	color = 0x00000000;
	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			dst = frame->addr + i * frame->line_length
				+ j * (frame->bits_per_pixel / 8);
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

void	center_projection(t_wframe *wframe)
{
}


int	draw_frame(t_wframe	*wframe)
{
	int		i;
	int		j;

	clear_frame(&wframe->frame);
	center_projection(wframe);
	//calculate_projection!!!!
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

void	init_points(t_points ***data, int lines, int cols)
{
	int	k;
	int	l;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			data[k][l]->x *= F;
			data[k][l]->y *= F;
			data[k][l]->z *= F;
			data[k][l]->f = F;
			l++;
		}
		k++;
	}
}

void	scale_xy(t_points ***data, int lines, int cols, float factor)
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

void	rotate_z(t_points ***data, int lines, int cols, float radians)
{
	int		k;
	int		l;
	float	sin_r;
	float	cos_r;

	sin_r = sin(radians);
	cos_r = cos(radians);
	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			data[k][l]->x = data[k][l]->x * cos_r - data[k][l]->y * sin_r;
			data[k][l]->y = data[k][l]->x * sin_r + data[k][l]->y * cos_r;
			l++;
		}
		k++;
	}
}

void	reset(t_points ***data, int lines, int cols)
{
	int	k;
	int	l;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			data[k][l]->x = l * data[k][l]->f;
			data[k][l]->y = k * data[k][l]->f;
			data[k][l]->h = data[k][l]->z;
			l++;
		}
		k++;
	}
}

void	translate(t_wframe *wframe, int x, int y)
{
	int	k;
	int	l;

	k = 0;
	while (k < wframe->lines)
	{
		l = 0;
		while (l < wframe->cols)
		{
			wframe->data[k][l]->x += x * F;
			wframe->data[k][l]->y += y * F;
			l++;
		}
		k++;
	}
}

void	swap(int *z, int *x)
{
	int	temp;

	temp = *z;
	*z = *x;
	*x = temp;
}
