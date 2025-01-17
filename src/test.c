/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafnasci <rafnasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 20:47:09 by rafnasci          #+#    #+#             */
/*   Updated: 2025/01/17 01:52:01 by rafnasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/test.h"

char **get_map(void)
{
    char **map = malloc(sizeof(char *) * 25);
	map[0] = "111111111111111111111111";
	map[1] = "100000000000000000000001";
	map[2] = "100000000000000000000001";
	map[3] = "100000000000000000000001";
	map[4] = "100000000000000000000001";
	map[5] = "100000000000000000000001";
	map[6] = "100000000000000000000001";
	map[7] = "100000000000000000000001";
	map[8] = "100000000000000000000001";
	map[9] = "100000000000010000000001";
	map[10] = "100000000000000000000001";
	map[11] = "100000000000000000000001";
	map[12] = "100000000000000000000001";
	map[13] = "100000000000000000000001";
	map[14] = "100000000000000000000001";
	map[15] = "100000000000000000000001";
	map[16] = "100000000000000000000001";
	map[17] = "100000000000000000000001";
	map[18] = "100000000000000000000001";
	map[19] = "100000000000000000000001";
	map[20] = "100000000000000000000001";
	map[21] = "100000000000000000000001";
	map[22] = "100000000000000000000001";
	map[23] = "111111111111111111111111";
  map[24] = NULL;
  return (map);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	move_player(t_player *player)
{
	double	rot_speed;
	double	move_speed;

	move_speed = 0.009;
	rot_speed = 0.009;
	if (player->p_up)
	{ 
		if (player->game->map.map[(int)(player->posx + player->dirx * move_speed)][(int)player->posy] == '0')
			player->posx += player->dirx * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy + player->diry * move_speed)] == '0')
			player->posy += player->diry * move_speed;
	}
	if (player->p_dw)
	{ 
		if (player->game->map.map[(int)(player->posx - player->dirx * move_speed)][(int)player->posy] == '0')
			player->posx -= player->dirx * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy - player->diry * move_speed)] == '0')
			player->posy -= player->diry * move_speed;
	}
	if (player->p_lf) // A key
	{ 
		if (player->game->map.map[(int)(player->posx - player->diry * move_speed)][(int)player->posy] == '0')
			player->posx -= player->diry * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy + player->dirx * move_speed)] == '0')
			player->posy += player->dirx * move_speed;
	}
	if (player->p_rg) // D key
	{ 
		if (player->game->map.map[(int)(player->posx + player->diry * move_speed)][(int)player->posy] == '0')
			player->posx += player->diry * move_speed;
		if (player->game->map.map[(int)player->posx][(int)(player->posy - player->dirx * move_speed)] == '0')
			player->posy -= player->dirx * move_speed;
	}
	if (player->right_r)
	{ // Rotate right
   		 double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(-rot_speed) - player->diry * sin(-rot_speed);
		player->diry = oldDirX * sin(-rot_speed) + player->diry * cos(-rot_speed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(-rot_speed) - player->planey * sin(-rot_speed);
		player->planey = oldPlaneX * sin(-rot_speed) + player->planey * cos(-rot_speed);
	}
	if (player->left_r)
	{ // Rotate right
   		 double oldDirX = player->dirx;
		player->dirx = player->dirx * cos(rot_speed) - player->diry * sin(rot_speed);
		player->diry = oldDirX * sin(rot_speed) + player->diry * cos(rot_speed);
		double oldPlaneX = player->planex;
		player->planex = player->planex * cos(rot_speed) - player->planey * sin(rot_speed);
		player->planey = oldPlaneX * sin(rot_speed) + player->planey * cos(rot_speed);
	}
	return (0);
}

int	key_true(int keycode, t_player *player)
{
	//printf("%d\n", keycode);
	if (keycode == 65307) //pour esc, pas oublier de free
		exit(0);
	if (keycode == 119)
		player->p_up = 1;
	if (keycode == 115)
		player->p_dw = 1;
	if (keycode == 97)
		player->p_lf = 1;
	if (keycode == 100)
		player->p_rg = 1;
	if (keycode == 65361)
		player->left_r = 1;
    if (keycode == 65363)
		player->right_r = 1;
	return (0);
}

int	key_false(int keycode, t_player *player)
{
	if (keycode == 119)
		player->p_up = 0;
	if (keycode == 115)
		player->p_dw = 0;
	if (keycode == 97)
		player->p_lf = 0;
	if (keycode == 100)
		player->p_rg = 0;
	if (keycode == 65361)
        player->left_r = 0;
    if (keycode == 65363)
		player->right_r = 0;
	return (0);
}

void	clear_image(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, 0);
			x++;
		}
		y++;
	}
}

int peutetre(t_game *game)
{
	int	x;

	x = -1;
	clear_image(game);
	while (++x < WIDTH - 1)
	{
		// printf("x : %d\n", x);
		double cameraX = 2 * x / (double)WIDTH - 1; // Camera space coordinate
		double rayDirX = game->p1.dirx + game->p1.planex * cameraX;
		double rayDirY = game->p1.diry + game->p1.planey * cameraX;

		//which box of the map we're in
		int mapX = (int) game->p1.posx;
		int mapY = (int) game->p1.posy;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);

		int stepX, stepY;
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = ( game->p1.posx - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 -  game->p1.posx) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = ( game->p1.posy - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 -  game->p1.posy) * deltaDistY;
		}

		int hit = 0, side; // was a NS or a EW wall hit?
		while (!hit) {
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (mapX < 0)
				mapX = 0;
			if (game->map.map[mapX][mapY] > '0')
			{
				// printf("oui\n");
				hit = 1; // Check for wall hit
			}
		}
		// Calculate distance to the wal
		double perpWallDist;
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else 
			perpWallDist = (sideDistY - deltaDistY);
		int lineHeight = (int)(HEIGHT / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = game->p1.posy + perpWallDist * rayDirY;
		else
			wallX = game->p1.posx + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)64);
		if(side == 0 && rayDirX > 0)
			texX = 64 - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = 64 - texX - 1;
		double step = 1.0 * 64 / lineHeight;
		double texPos = (drawStart - HEIGHT / 2 + lineHeight / 2) * step;
		int	y = -1;
		while (++y < drawStart)
			my_mlx_pixel_put(&game->img, x, y, 0xFFFFFF);
		y--;
		//y = drawStart - 1;
		while (y++ <= drawEnd)
		{
			int color;
			int texY = (int)texPos & (64 - 1);
			texPos += step;
			color = 0;
			int k = 0;
			t_wall *wall;
			if (side == 1)
			{
				if (stepY == -1)
					wall = &game->wall2;
				else
					wall = &game->wall4;
			}
			else
			{
				if (stepX == -1)
					wall = &game->wall;
				else
					wall = &game->wall3;
			}
			while (k < wall->info)
			{
				if (wall->wall[texY][texX] == wall->col[k].c)
				{
					color = wall->col[k].id;
					break ;
				}
				k++;
			}
			my_mlx_pixel_put(&game->img, x, y, color);
		}
	y--;
	while (y++ < HEIGHT)
			my_mlx_pixel_put(&game->img, x, y, 0xFF0000);
	}
	move_player(&game->p1);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	ft_exit(t_game *game)
{
	//il faut free
	(void)game;
	exit(0);
}

int mouse_move(int x, int y, t_player *player)
{
	(void)y;
    static int lastMouseX = -1;
    if (lastMouseX == -1) {
        lastMouseX = x;
        return 0;
    }
	int deltaX;
	deltaX = 0;
	if (x > lastMouseX)
		deltaX = 1;
	else
		deltaX = -1;
    lastMouseX = x;

    double rot_speed = 0.005 * deltaX;

    // Rotate the camera direction
    double oldDirX = player->dirx;
    player->dirx = player->dirx * cos(-rot_speed) - player->diry * sin(-rot_speed);
    player->diry = oldDirX * sin(-rot_speed) + player->diry * cos(-rot_speed);

    // Rotate the camera plane
    double oldPlaneX = player->planex;
    player->planex = player->planex * cos(-rot_speed) - player->planey * sin(-rot_speed);
    player->planey = oldPlaneX * sin(-rot_speed) + player->planey * cos(-rot_speed);
    return 0;
}


void	game_loop(t_game *game)
{
	peutetre(game);
	mlx_hook(game->win, 2, 1L<<0, key_true, &game->p1);
	mlx_hook(game->win, 3, 1L<<1, key_false, &game->p1);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, &game->p1);
	mlx_hook(game->win, 17, 0, ft_exit, game);
	mlx_loop_hook(game->mlx, peutetre, game);
	mlx_loop(game->mlx);
}

void init_player(t_game *game)
{
	game->p1.posx = 12;
	game->p1.posy = 13;
	game->p1.dirx = -1;
	game->p1.diry = 0;
	game->p1.planex = 0;
	game->p1.planey = 0.66;
	game->p1.game = game;
	game->p1.left_r = 0;
	game->p1.right_r = 0;
	game->p1.p_dw = 0;
	game->p1.p_up = 0;
	game->p1.p_lf = 0;
	game->p1.p_rg = 0;
}

int main(void)
{
	t_game	game;

	init_player(&game);
	game.map.map = get_map();
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "Cub3d");
	game.img.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.img.addr = mlx_get_data_addr(game.img.img, &game.img.bits_per_pixel,
			&game.img.line_length, &game.img.endian);
	parse_xpm(&game.wall, "test.xpm");
	parse_xpm(&game.wall2, "test2.xpm");
	parse_xpm(&game.wall3, "test3.xpm");
	parse_xpm(&game.wall4, "test4.xpm");
	mlx_mouse_hide(game.mlx, game.win);
	game_loop(&game);
}
