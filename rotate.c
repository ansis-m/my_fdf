/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:26:42 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/23 19:27:56 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_z(t_points ***data, int lines, int cols, double radians)
{
	int		k;
	int		l;
	double	a;
	double	b;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			a = data[k][l]->x;
			b = data[k][l]->y;
			data[k][l]->x = a * cos(radians) - b * sin(radians);
			data[k][l]->y = a * sin(radians) + b * cos(radians);
			l++;
		}
		k++;
	}
}

void	rotate_x(t_points ***data, int lines, int cols, double radians)
{
	int		k;
	int		l;
	double	a;
	double	b;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			a = data[k][l]->y;
			b = data[k][l]->z;
			data[k][l]->y = a * cos(radians) + b * sin(radians);
			data[k][l]->z = b * cos(radians) - a * sin(radians);
			l++;
		}
		k++;
	}
}

void	rotate_y(t_points ***data, int lines, int cols, double radians)
{
	int		k;
	int		l;
	double	a;
	double	b;

	k = 0;
	while (k < lines)
	{
		l = 0;
		while (l < cols)
		{
			a = data[k][l]->x;
			b = data[k][l]->z;
			data[k][l]->x = a * cos(radians) + b * sin(radians);
			data[k][l]->z = b * cos(radians) - a * sin(radians);
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
			data[k][l]->z = data[k][l]->h;
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
			wframe->data[k][l]->x += x;
			wframe->data[k][l]->y += y;
			l++;
		}
		k++;
	}
}
