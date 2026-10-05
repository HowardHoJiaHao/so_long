/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:08:55 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/09/29 12:08:55 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_sprite(t_game *game, char c, t_point pos)
{
	if (c == WALL)
		buffer_sprite(game, &game->wall, pos);
	else if (c == COLLECTIBLES)
		buffer_sprite(game, &game->collectibles, pos);
	else if (c == EXIT)
		buffer_sprite(game, &game->exit, pos);
}

static void	buffer_player(t_game *game)
{
	t_point	pos;

	pos.y = game->map.starting_p.y * IMG_H;
	pos.x = game->map.starting_p.x * IMG_W;
	if (game->player_state == 0)
		buffer_sprite(game, &game->player_front, pos);
	else if (game->player_state == 1)
		buffer_sprite(game, &game->player_back, pos);
	else if (game->player_state == 2)
		buffer_sprite(game, &game->player_left, pos);
	else if (game->player_state == 3)
		buffer_sprite(game, &game->player_right, pos);
}

static void	buffer_fixed_elements(t_game *game)
{
	int		i;
	int		j;
	t_point	pos;

	i = 0;
	while (i < game->map.h)
	{
		j = 0;
		while (j < game->map.w)
		{
			pos.y = i * IMG_H;
			pos.x = j * IMG_W;
			buffer_sprite(game, &game->floor, pos);
			check_sprite(game, game->map.matrix[i][j], pos);
			j++;
		}
		i++;
	}
}

//must return int cuz loop hook expects an 
//int to be returned to indicate success
int	print_game_map(t_game *game)
{
	char	*movements;
	char	*string;

	game->buffer.img_ptr = mlx_new_image(game->mlx_ptr,
			game->map.w * IMG_W, game->map.h * IMG_H);
	game->buffer.img_addr = mlx_get_data_addr(game->buffer.img_ptr,
			&game->buffer.bpp, &game->buffer.size_line, &game->buffer.endian);
	buffer_fixed_elements(game);
	buffer_player(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr,
		game->buffer.img_ptr, 0, 0);
	movements = ft_itoa(game->moves);
	string = ft_strjoin("Movements: ", movements);
	mlx_string_put(game->mlx_ptr, game->win_ptr, 40, 20, 0xFFFFFF, string);
	free(string);
	free(movements);
	mlx_destroy_image(game->mlx_ptr, game->buffer.img_ptr);
	return (0);
}
