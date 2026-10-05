/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:08:47 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/09/29 12:08:47 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	*get_file_name(char *arg)
{
	char	*filename;

	filename = ft_strrchr(arg, '/');
	if (filename != NULL)
		return (filename + 1);
	return (filename);
}

static void	check_cml_argument(int argc, char *arg, t_game *game)
{
	int		i;
	char	*file_type;
	int		fd;

	i = 0;
	if (argc != 2)
		error_mssg("Wrong number of arguments", game);
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		error_mssg("Unable to open map file", game);
	game->map.fd = fd;
	file_type = get_file_name(arg);
	if (file_type[0] == '.')
		error_mssg("Bad file extension", game);
	while (file_type[i] != '.')
		file_type++;
	if (ft_strncmp(".ber", file_type, 5) != 0)
		error_mssg("Bad file extension", game);
}

int	main(int argc, char *argv[])
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	check_cml_argument(argc, argv[1], &game);
	check_map(&game);
	init_mlx(&game);
	load_sprite(&game);
	mlx_loop_hook(game.mlx_ptr, print_game_map, &game);
	mlx_hook(game.win_ptr, 17, 0L, close_game, &game);
	mlx_key_hook(game.win_ptr, handle_input, &game);
	mlx_loop(game.mlx_ptr);
}
