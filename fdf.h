/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:22:10 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/19 12:41:16 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdbool.h>
# include	<limits.h>
# include	<math.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h> 
# include	<stdio.h>
# include	"get_next_line.h"
# include	"./minilibx-linux/mlx.h"
# include	"./minilibx-linux/mlx_int.h"

typedef struct s_points
{
	int	h;
	int	x;
	int	y;
	int	z;
}	t_points;

#endif
