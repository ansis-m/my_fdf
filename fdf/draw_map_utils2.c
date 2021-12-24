/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 19:37:47 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 11:24:27 by amalecki         ###   ########.fr       */
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
