/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalecki <amalecki@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 09:21:13 by amalecki          #+#    #+#             */
/*   Updated: 2021/12/19 11:24:48 by amalecki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

void	read_file(char *filename, char *pointer[1000], int *lines, int *columns)
{
	int			fd;
	int			i;

	fd = open(filename, O_RDONLY);
	*lines = 0;
	while (true)
	{
		pointer[*lines] = get_next_line(fd);
		if (!pointer[*lines])
			break ;
		*lines += 1;
	}
	pointer[*lines + 1] = NULL;
	close(fd);
	*columns = 0;
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

int	main(int argc, char *argv[])
{
	int			lines;
	int			columns;
	char		*pointer[1000];

	read_file(argv[1], pointer, &lines, &columns);
	printf("lines %d\t\tcolumns %d\n", lines, columns);
	for (int i = 0; pointer[i] != NULL; i++)
		printf("%s", pointer[i]);
	return (1);
}
