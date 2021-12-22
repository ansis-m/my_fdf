/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 10:10:53 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/22 10:34:40 by amalecki         ###   ########.fr       */
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
	while (i < 601)
	{
		j = 0;
		while (j < 601)
		{
			dst = frame->addr + i * frame->line_length
				+ j * (frame->bits_per_pixel / 8);
			*(unsigned int *)dst = color;
			j++;
		}
		i++;
	}
}

int	draw_frame(t_wframe	*wframe)
{
	int		i;
	int		j;

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
			l++;
		}
		k++;
	}
}

void	translate(t_wframe wframe, int x, int y)
{
	int	k;
	int	l;

	k = 0;
	while (k < wframe.lines)
	{
		l = 0;
		while (l < wframe.cols)
		{
			wframe.data[k][l]->x += x;
			wframe.data[k][l]->y += y;
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
