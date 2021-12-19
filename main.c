/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:21:13 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/19 15:09:53 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

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
	pointer[*lines + 1] = NULL;
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
	point->x = j;
	point->y = i;
	point->h = k;
	point->z = k;
	return (point);
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
		j = 0;
		z = 0;
		while (j < cols)
		{
			k = atoi(line_ptrs[i] + z);
			while (line_ptrs[i][z] < '0' || line_ptrs[i][z] > '9')
				z++;
			while (line_ptrs[i][z] != '\n' && line_ptrs[i][z] != ' ')
				z++;
			printf("z:%d", z);
			data[i][j] = init_struct(i, j, k);
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	int			lines;
	int			columns;
	char		*line_ptrs[1000];
	t_points	***data;

	read_file(argv[1], line_ptrs, &lines, &columns);
	data = (t_points ***)malloc(sizeof(t_points **) * lines);
	if (!data)
	{
		perror("Error allocating memory");
		exit(1);
	}
	get_data(data, line_ptrs, lines, columns);
	// printf("lines %d\t\tcolumns %d\n", lines, columns);
	// for (int i = 0; line_ptrs[i] != NULL; i++)
	// 	printf("%s", line_ptrs[i]);

	for(int i = 0; i < lines; i++)
	{
		for(int j = 0; j < columns; j++)
			printf("%d,%d(%d)  ", data[i][j]->x, data[i][j]->y, data[i][j]->h);
		printf("\n");
	}
	free_line_ptrs(line_ptrs);
	return (1);
}
