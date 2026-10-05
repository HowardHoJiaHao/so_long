/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:08:36 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/09/29 12:08:36 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	check_map_rectangular(t_game *game, int c_width, char *line)
{
	if (game->map.w != c_width && game->map.h != 0)
	{
		while (line)
		{
			free (line);
			line = get_next_line(game->map.fd);
		}
		error_mssg("Map is Not Rectangle", game);
	}
}

void	error_mssg(char *message, t_game *game)
{
	ft_printf("Error\n""%s\n", message);
	if (game->map.matrix)
		free_grid(game->map.matrix, game);
	if (game->map.array)
		free(game->map.array);
	exit(EXIT_FAILURE);
}

void	free_grid(char **grid, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.h)
		free(grid[i++]);
	free(grid);
}

void	destroy_sprite(t_game *game)
{
	mlx_destroy_image(game->mlx_ptr, game->player_right.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_left.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_front.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->player_back.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->floor.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->collectibles.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->wall.img_ptr);
	mlx_destroy_image(game->mlx_ptr, game->exit.img_ptr);
}

void	free_map(t_game *game)
{
	if (game->map.matrix)
		free_grid(game->map.matrix, game);
	if (game->map.array)
		free(game->map.array);
}
