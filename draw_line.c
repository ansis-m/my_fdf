/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 09:23:58 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/23 13:33:34 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	draw_line(t_image *frame, t_points a, t_points b)
// {
// 	int	x;
// 	int	y;
// 	int	end;
// 	int	p;
// 	int	dx;
// 	int	dy;

// 	dx = (a.x - b.x) > 0 ? a.x - b.x : b.x - a.x;
// 	dy = (a.y - b.y) > 0 ? a.y - b.y : b.y - a.y;
// 	p = (2 * dy - dx);
// 	if (a.x > b.x)
// 	{
// 		x = b.x;
// 		y = b.y;
// 		end = a.x;
// 	}
// 	else
// 	{
// 		x = a.x;
// 		y = a.y;
// 		end = b.x;
// 	}
// 	pixel_put(frame, x, y, 1);
// 	while (x <= end)
// 	{
// 		if (p < 0)
// 		{
// 			x++;
// 			p = p + 2 * dy;
// 		}
// 		else
// 		{
// 			x++;
// 			y++;
// 			p = p + 2 * (dy - dx);
// 		}
// 		pixel_put(frame, x, y, 1);
// 	}
// }
