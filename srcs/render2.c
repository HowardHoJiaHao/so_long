/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hho-jia- <hho-jia-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:08:58 by hho-jia-          #+#    #+#             */
/*   Updated: 2025/09/29 12:08:58 by hho-jia-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	draw_pixel(t_sprite *buffer, int color, int y, int x)
{
	char	*pixel;

	if (color != (int)0xFF000000)
	{
		pixel = buffer->img_addr + ((y * buffer->size_line)
				+ (x *(buffer->bpp / 8)));
		*(unsigned int *)pixel = color;
	}
}

void	buffer_sprite(t_game *game, t_sprite *sprite, t_point pos)
{
	int		i;
	int		j;
	int		color;
	int		location;
	t_point	temp;

	i = 0;
	while (i < sprite->size.y)
	{
		j = 0;
		while (j < sprite->size.x)
		{
			location = (i * sprite->size_line) + (j * sprite->bpp / 8);
			color = *(unsigned int *)(sprite->img_addr + location);
			temp.y = pos.y + i;
			temp.x = pos.x + j;
			draw_pixel(&game->buffer, color, temp.y, temp.x);
			j++;
		}
		i++;
	}
}
