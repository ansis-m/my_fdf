/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycode_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 10:30:52 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 10:38:22 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	manage_translate(int keycode, t_wframe	*wframe)
{
	if (keycode == XK_Down)
	{
		translate(wframe, 10, 0);
		wframe->center = false;
	}
	else if (keycode == XK_Up)
	{
		translate(wframe, -10, 0);
		wframe->center = false;
	}
	else if (keycode == XK_Right)
	{
		translate(wframe, 0, 10);
		wframe->center = false;
	}
	else if (keycode == XK_Left)
	{
		translate(wframe, 0, -10);
		wframe->center = false;
	}
}

void	manage_orthographic(t_wframe	*wframe)
{
	reset(wframe->data, wframe->lines, wframe->cols);
	wframe->center = true;
	if (wframe->orthographic)
		wframe->orthographic = false;
	else
	{
		orthographic(wframe->data, wframe->lines, wframe->cols);
		wframe->orthographic = true;
	}
}

void	manage_rotate(int keycode, t_wframe	*wframe)
{
	if (keycode == XK_x)
	{
		wframe->center = true;
		rotate_x(wframe->data, wframe->lines, wframe->cols, M_PI / 16);
	}
	else if (keycode == XK_y)
	{
		wframe->center = true;
		rotate_y(wframe->data, wframe->lines, wframe->cols, M_PI / 16);
	}
	else if (keycode == XK_z)
	{
		wframe->center = true;
		rotate_z(wframe->data, wframe->lines, wframe->cols, M_PI / 16);
	}
}

int	key_hook(int keycode, t_wframe	*wframe)
{
	if (keycode == XK_Escape)
		wframe->window.mlx->end_loop = True;
	else if (keycode == XK_KP_Subtract)
	{
		scale_xy(wframe->data, wframe->lines, wframe->cols, 0.8);
		wframe->center = true;
	}
	else if (keycode == XK_KP_Add)
	{
		scale_xy(wframe->data, wframe->lines, wframe->cols, 1.2);
		wframe->center = true;
	}
	else if (keycode == XK_Down || keycode == XK_Up
		|| keycode == XK_Right || keycode == XK_Left)
		manage_translate(keycode, wframe);
	else if (keycode == XK_o)
		manage_orthographic(wframe);
	else if (keycode == XK_x || keycode == XK_y || keycode == XK_z)
		manage_rotate(keycode, wframe);
	wframe->draw_new = true;
	return (0);
}
