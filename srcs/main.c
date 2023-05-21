/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:41:15 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/22 01:01:03 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*エラーを出力
** 0 map invalid
** -1 malloc_error
** -2 file open error
** -3 file read error
** -4 file close error
** -5 gnl error
** -6 map error
*/
void	ft_error(int num)
{
	if (num == 0)
		ft_printf("Error\nmap invalid\n");
	else if (num == -1)
		ft_printf("Error\nmalloc_error\n");
	else if (num == -2)
		ft_printf("Error\nfile open error\n");
	else if (num == -3)
		ft_printf("Error\nfile read error\n");
	else if (num == -4)
		ft_printf("Error\nfile close error\n");
	else if (num == -5)
		ft_printf("Error\ngnl error\n");
	else if (num == 1)
		ft_printf("Error\nargument error\n");
	exit(1);
}

/*
*mapの解放
*mlx_destroy_imageでimgを解放
*mlx_destroy_windowでwindowを解放
*/
void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (data->img[i].img != NULL)
			mlx_destroy_image(data->mlx, data->img[i].img);
		i++;
	}
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	free_map(data->map);
	exit(0);
}

/*mlxの前処理*/
void	set_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 50 * data->col, 50 * data->row,
			"Flower farmer");
	data->img[0].img = mlx_xpm_file_to_image(data->mlx, IMG_ZERO,
			&data->img[0].width, &data->img[0].height);
	data->img[1].img = mlx_xpm_file_to_image(data->mlx, IMG_WALL,
			&data->img[1].width, &data->img[1].height);
	data->img[2].img = mlx_xpm_file_to_image(data->mlx, IMG_ITEM,
			&data->img[2].width, &data->img[2].height);
	data->img[3].img = mlx_xpm_file_to_image(data->mlx, IMG_PLAYER,
			&data->img[3].width, &data->img[3].height);
	data->img[4].img = mlx_xpm_file_to_image(data->mlx, IMG_GOAL,
			&data->img[4].width, &data->img[4].height);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		ft_error(1);
	data = make_map(argv[1]);
	check_map(&data);
	if (data.row > 20 || data.col > 33)
		ft_error(0);
	set_mlx(&data);
	data.x_now = data.x_start;
	data.y_now = data.y_start;
	mlx_hook(data.win, KEY_PRESS, 1L << 0, key_event, &data);
	mlx_hook(data.win, DESTROY_NOTIFY, 0L, button_event, &data);
	mlx_loop_hook(data.mlx, draw_map, &data);
	mlx_loop(data.mlx);
	free_all(&data);
	return (0);
}
