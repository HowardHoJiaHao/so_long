/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:08:40 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/09/29 12:08:40 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_exit(char **grid, int y, int x)
{
	if (grid[y - 1][x] == 'E')
		grid[y - 1][x] = 'F';
	if (grid[y + 1][x] == 'E')
		grid[y + 1][x] = 'F';
	if (grid[y][x - 1] == 'E')
		grid[y][x - 1] = 'F';
	if (grid[y][x + 1] == 'E')
		grid[y][x + 1] = 'F';
}

void	flood_fill(char **grid, int y, int x)
{
	grid[y][x] = 'F';
	check_exit(grid, y, x);
	if (grid[y - 1][x] != WALL && grid[y - 1][x] != 'F')
		flood_fill(grid, y - 1, x);
	if (grid[y + 1][x] != WALL && grid[y + 1][x] != 'F')
		flood_fill(grid, y + 1, x);
	if (grid[y][x - 1] != WALL && grid[y][x - 1] != 'F')
		flood_fill(grid, y, x - 1);
	if (grid[y][x + 1] != WALL && grid[y][x + 1] != 'F')
		flood_fill(grid, y, x + 1);
}

int	check_floodfill(char **grid, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			if (ft_strchr("CE", grid[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
