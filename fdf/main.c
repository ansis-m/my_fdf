/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:21:13 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/24 10:57:35 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void	check(void *data, char **line_ptrs)
{
	if (!data)
	{
		free_line_ptrs(line_ptrs);
		perror("Error allocating memory");
		exit(1);
	}
}

void	get_data(t_points ***data, char **line_ptrs, int lines, int cols)
{
	int	i;
	int	j;
	int	k;
	int	z;

	i = 0;
	while (i < lines)
	{
		data[i] = (t_points **)malloc(sizeof(t_points *) * cols);
		check((void *)data[i], line_ptrs);
		j = 0;
		z = 0;
		while (j < cols)
		{
			k = ft_atoi(line_ptrs[i] + z);
			while (line_ptrs[i][z] < '0' || line_ptrs[i][z] > '9')
				z++;
			while (line_ptrs[i][z] != '\n' && line_ptrs[i][z] != ' ')
				z++;
			data[i][j] = init_struct(i, j, k);
			check((void *)data[i][j], line_ptrs);
			j++;
		}
		i++;
	}
}

void	free_data(t_points ***data, int lines, int columns)
{
	int	a;
	int	b;

	a = 0;
	while (a < lines)
	{
		b = 0;
		while (b < columns)
		{
			free(data[a][b]);
			b++;
		}
		free(data[a]);
		a++;
	}
	free(data);
}

int	main(int argc, char *argv[])
{
	int			lines;
	int			columns;
	char		*line_ptrs[1000];
	t_points	***data;

	if (argc != 2)
		return (1);
	read_file(argv[1], line_ptrs, &lines, &columns);
	data = (t_points ***)malloc(sizeof(t_points **) * lines);
	check((void *)data, line_ptrs);
	get_data(data, line_ptrs, lines, columns);
	free_line_ptrs(line_ptrs);
	if (lines * columns >= 2)
		draw_map(data, lines, columns);
	free_data(data, lines, columns);
	return (0);
}
