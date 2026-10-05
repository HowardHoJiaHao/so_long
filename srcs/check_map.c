/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:08:26 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/09/29 12:08:26 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_map_size(t_game *game)
{
	char	*temp;
	char	*line;
	int		c_width;

	c_width = 0;
	game->map.array = ft_strdup("");
	line = get_next_line(game->map.fd);
	while (line)
	{
		if (game->map.h != 0)
			c_width = game->map.w;
		game->map.w = 0;
		temp = game->map.array;
		game->map.array = ft_strjoin(temp, line);
		free (temp);
		while (line[game->map.w] != '\n' && line[game->map.w])
			game->map.w++;
		check_map_rectangular (game, c_width, line);
		free (line);
		line = get_next_line (game->map.fd);
		game->map.h++;
	}
}

static char	**make_matrix(t_game *game)
{
	int		i;
	int		len;
	int		count;
	char	**grid;

	i = 0;
	count = 0;
	grid = malloc (game->map.h * sizeof(char *));
	while (game->map.array[i])
	{
		len = 0;
		grid[count] = malloc(game->map.w + 1);
		while (game->map.array[i] != '\n' && game->map.array[i])
		{
			i++;
			len++;
		}
		ft_strlcpy(grid[count], game->map.array + i - len, game->map.w + 1);
		count ++;
		if (game->map.array[i] == '\n')
			i++;
	}
	return (grid);
}

static void	check_minimum_asset(t_game *game)
{
	int		i;
	char	c;

	i = 0;
	while (game->map.array[i])
	{
		c = game->map.array[i];
		if (!ft_strrchr ("PCE10\n", c))
			error_mssg ("Map has Unknown Character", game);
		if (c == COLLECTIBLES)
			game->map.collect++;
		else if (c == EXIT)
			game->map.exit++;
		else if (c == PLAYER)
			game->map.player++;
		i++;
	}
	if (game->map.player != 1 || game->map.exit != 1 || game->map.collect < 1)
		error_mssg ("Asset Insufficient", game);
}

static void	valid_map(t_game *game)
{
	int		i;
	int		j;
	char	**grid;

	i = 0;
	grid = game->map.matrix;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			if (grid[i][0] != WALL || grid[game->map.h - 1][j] != WALL
				|| grid[0][j] != WALL
				|| grid[i][game->map.w - 1] != WALL)
				error_mssg("Map not surrounded by walls", game);
			else if (grid[i][j] == PLAYER)
			{
				game->map.starting_p.x = j;
				game->map.starting_p.y = i;
			}
			j++;
		}
		i++;
	}
}

void	check_map(t_game *game)
{
	char	**grid;
	t_point	s_pos;

	check_map_size (game);
	game->map.matrix = make_matrix (game);
	check_minimum_asset (game);
	valid_map (game);
	grid = make_matrix (game);
	s_pos = game->map.starting_p;
	flood_fill (grid, s_pos.y, s_pos.x);
	if (check_floodfill (grid, game))
	{
		free_grid (grid, game);
		error_mssg ("Some exit or collectibles cannot be reached", game);
	}
	free_grid(grid, game);
}
