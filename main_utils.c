/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 15:27:35 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/22 13:04:39 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_line_ptrs(char *line_ptrs[1000])
{
	while (*line_ptrs)
	{
		free(*line_ptrs);
		line_ptrs++;
	}
}

t_points	*init_struct(int i, int j, int k)
{
	t_points	*point;

	point = (t_points *)malloc(sizeof(t_points));
	if (point)
	{
		point->x = j;
		point->y = i;
		point->h = k;
		point->z = k;
		point->f = F;
	}
	return (point);
}

void	init_file_read(char *filename, int *fd, int *lines, int *columns)
{
	*fd = open(filename, O_RDONLY);
	if (*fd <= 0)
	{
		perror("Error opening file");
		exit(1);
	}
	*lines = 0;
	*columns = 0;
}

void	read_file(char *filename, char *pointer[1000], int *lines, int *columns)
{
	int			fd;
	int			i;

	init_file_read(filename, &fd, lines, columns);
	while (true)
	{
		pointer[*lines] = get_next_line(fd);
		if (!pointer[*lines])
			break ;
		*lines += 1;
	}
	close(fd);
	i = 0;
	while (pointer[0] && pointer[0][i])
	{
		if (pointer[0][i] >= '0' && pointer[0][i] <= '9')
		{
			*columns += 1;
			while (pointer[0][i] >= '0' && pointer[0][i] <= '9')
				i++;
		}
		i++;
	}
}
