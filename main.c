/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:21:13 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/19 12:15:32 by amalecki         ###   ########.fr       */
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

int	main(int argc, char *argv[])
{
	int			lines;
	int			columns;
	char		*line_ptrs[1000];

	read_file(argv[1], line_ptrs, &lines, &columns);
	//get_data(line_ptrs, lines, columns);
	printf("lines %d\t\tcolumns %d\n", lines, columns);
	for (int i = 0; line_ptrs[i] != NULL; i++)
		printf("%s", line_ptrs[i]);
	free_line_ptrs(line_ptrs);
	return (1);
}
