/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:05:04 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/25 12:35:36 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

bool	normalize_points(t_points *a, t_points *b, double *dx, double *dy)
{
	bool	steep;

	steep = ((b->y - a->y) * (b->y - a->y) > (b->x - a->x) * (b->x - a->x));
	if (steep)
	{
		swap(&a->x, &a->y);
		swap(&b->x, &b->y);
	}
	if (a->x > b->x)
	{
		swap(&a->x, &b->x);
		swap(&a->y, &b->y);
		swap(&a->h, &b->h);
	}
	*dx = b->x - a->x;
	*dy = b->y - a->y;
	return (steep);
}

unsigned int	get_color(double fraction, double zrange[3])
{
	unsigned int		color;
	int					intensity;
	int					tone;
	double				gradient;

	gradient = zrange[2] / zrange[1];
	if (gradient < 0)
		gradient = -gradient;
	intensity = 0xFF * fraction;
	tone = 255 * gradient;
	color = (tone << 16 | (255 - tone) << 8 | intensity);
	return (color);
}

void	draw_line_helper(t_wframe *wframe, double zrange[4],
			t_points *a, t_points *b)
{
	double	zincrement;	

	zincrement = 0;
	if (b->x != a->x && a->h != b->h)
		zincrement = (b->h - a->h) / (b->x - a->x);
	while (a->x < b->x)
	{
		if (zrange[3])
		{
			pixel_put(&wframe->frame, roundd(a->y), (int)a->x,
				get_color(residue(a->y), zrange));
			pixel_put(&wframe->frame, roundd(a->y) - 1, (int)a->x,
				get_color(fraction(a->y), zrange));
		}
		else
		{
			pixel_put(&wframe->frame, (int)a->x, roundd(a->y),
				get_color(residue(a->y), zrange));
			pixel_put(&wframe->frame, (int)a->x, roundd(a->y) - 1,
				get_color(fraction(a->y), zrange));
		}
		zrange[2] += zincrement;
		a->y += zrange[0];
		a->x++;
	}
}

void	draw_line(t_wframe *wframe, double zrange[4], t_points a, t_points b)
{
	bool	steep;
	double	dx;
	double	dy;
	double	gradient;

	steep = normalize_points(&a, &b, &dx, &dy);
	gradient = dy / dx;
	if (b.x == a.x)
		gradient = 1;
	zrange[2] = a.h;
	zrange[0] = gradient;
	zrange[3] = 0;
	if (steep)
		zrange[3] = 1;
	draw_line_helper(wframe, zrange, &a, &b);
}
