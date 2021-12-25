/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:01:45 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/25 11:59:20 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_image *frame, int x, int y, unsigned int color)
{
	char				*dst;

	dst = frame->addr
		+ (x * frame->line_length + y * (frame->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	swap(double *z, double *x)
{
	double	temp;

	temp = *z;
	*z = *x;
	*x = temp;
}

int	roundd(double intersect_y)
{
	intersect_y += 0.5;
	return ((int)intersect_y);
}

double	fraction(double x)
{
	int	integer;

	integer = x;
	if (x > 0)
		return (x - integer);
	return (x - integer + 1);
}

double	residue(double x)
{
	return (1 - fraction(x));
}
