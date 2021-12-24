/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:05:04 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 10:06:34 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_image *frame, t_points a, t_points b)
{
	bool	steep;
	double	dx;
	double	dy;
	double	gradient;
	double	intersect_y;

	steep = ((b.y - a.y) * (b.y - a.y) > (b.x - a.x) * (b.x - a.x));
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
	while (a.x < b.x)
	{
		if (steep)
		{
			pixel_put(frame, roundd(intersect_y), a.x, residue(intersect_y));
			pixel_put(frame, roundd(intersect_y) - 1, a.x, fraction(intersect_y));
		}
		else
		{
			pixel_put(frame, a.x, roundd(intersect_y), residue(intersect_y));
			pixel_put(frame, a.x, roundd(intersect_y) - 1, fraction(intersect_y));
		}
		intersect_y += gradient;
		a.x++;
	}
}
