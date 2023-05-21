/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:29:04 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/22 00:30:00 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*画像を表示*/
void	put_img(t_data *data, void *img, int i, int j)
{
	mlx_put_image_to_window(data->mlx, data->win, img, i * 50, j * 50);
}

/*map表示
*マップをmlx_put_image_to_windowを用いて表示する
*mapの各要素に対応する画像を表示する
@param data
@param img
*/
int	draw_map(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->row)
	{
		i = 0;
		while (i < data->col)
		{
			if (data->map[j][i] == '0')
				put_img(data, data->img[0].img, i, j);
			else if (data->map[j][i] == '1')
				put_img(data, data->img[1].img, i, j);
			else if (data->map[j][i] == 'C')
				put_img(data, data->img[2].img, i, j);
			else if (data->map[j][i] == 'P' || data->map[j][i] == 'X')
				put_img(data, data->img[3].img, i, j);
			else if (data->map[j][i] == 'E')
				put_img(data, data->img[4].img, i, j);
			i++;
		}
		j++;
	}
	return (0);
}

/*Pの移動回数をカウント&移動
*キーボードイベントの処理
@param data
@param y
@param x
*/
void	move_map(t_data *data, int y, int x)
{
	static int	count;

	if (!count)
		count = 0;
	ft_printf("the number of steps :%d\n", ++count);
	if (data->map[y][x] == 'C')
		data->count++;
	if (data->map[y][x] == 'E' && data->count == data->items)
		free_all(data);
	if (data->map[y][x] == 'E' && data->count != data->items)
		data->map[y][x] = 'X';
	else
		data->map[y][x] = 'P';
	if (data->map[data->y_now][data->x_now] == 'X')
		data->map[data->y_now][data->x_now] = 'E';
	else
		data->map[data->y_now][data->x_now] = '0';
	data->x_now = x;
	data->y_now = y;
}

/*キーボタンが入力された時の場合分け
・A,LEFT:左
・D,RIGHT:右
・W,UP:上
・S,DOWN:下
・ESC:終了
*/
int	key_event(int keycode, t_data *data)
{
	if (keycode == KEY_A || keycode == LEFT)
		if (data->map[data->y_now][data->x_now - 1] != '1')
			move_map(data, data->y_now, data->x_now - 1);
	if (keycode == KEY_D || keycode == RIGHT)
		if (data->map[data->y_now][data->x_now + 1] != '1')
			move_map(data, data->y_now, data->x_now + 1);
	if (keycode == KEY_W || keycode == UP)
		if (data->map[data->y_now - 1][data->x_now] != '1')
			move_map(data, data->y_now - 1, data->x_now);
	if (keycode == KEY_S || keycode == DOWN)
		if (data->map[data->y_now + 1][data->x_now] != '1')
			move_map(data, data->y_now + 1, data->x_now);
	if (keycode == KEY_ESC)
		free_all(data);
	return (0);
}

/* ×を押された場合にウィンドウを閉じて終了する
 */
int	button_event(t_data *data)
{
	free_all(data);
	return (0);
}
