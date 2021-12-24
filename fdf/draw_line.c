/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:05:04 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 14:13:56 by amalecki         ###   ########.fr       */
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
	}
	*dx = b->x - a->x;
	*dy = b->y - a->y;
	return (steep);
}

void	draw_line(t_image *frame, t_points a, t_points b)
{
	bool	steep;
	double	dx;
	double	dy;
	double	gradient;

	steep = normalize_points(&a, &b, &dx, &dy);
	gradient = dy / dx;
	if (b.x == a.x)
		gradient = 1;
	while (a.x < b.x)
	{
		if (steep)
		{
			pixel_put(frame, roundd(a.y), a.x, residue(a.y));
			pixel_put(frame, roundd(a.y) - 1, a.x, fraction(a.y));
		}
		else
		{
			pixel_put(frame, a.x, roundd(a.y), residue(a.y));
			pixel_put(frame, a.x, roundd(a.y) - 1, fraction(a.y));
		}
		a.y += gradient;
		a.x++;
	}
}
