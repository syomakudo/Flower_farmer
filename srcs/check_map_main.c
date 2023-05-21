/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:39:53 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/21 19:54:50 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

/*初期化mapcheck*/
void	init_mapcheck(t_mapcheck *cmap)
{
	cmap->count_p = 0;
	cmap->count_c = 0;
	cmap->count_e = 0;
}

/*mapの行の文字数が有効かどうか
**有効なら0を返す
**無効なら-1を返す
**colに文字数を代入
**結果的に列の文字数が有効かどうかも判定してくれる。count_read_rowで行数を取得してるから。
*/
int	check_row(t_data *data)
{
	size_t	j;
	size_t	count;

	j = 0;
	count = 0;
	while (data->map[j] != NULL)
	{
		count = ft_strlen(data->map[j]);
		if (j == 0)
			data->col = count;
		if (count != data->col)
			return (-1);
		j++;
	}
	return (0);
}

/*mapの外枠が1で囲まれているか*/
int	check_frame(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->map[j] != NULL)
	{
		while (data->map[j][i] != '\0')
		{
			if (j == 0 || j == data->row - 1)
			{
				if (data->map[j][i] != '1')
					return (-1);
			}
			else if (i == 0 || i == data->col - 1)
			{
				if (data->map[j][i] != '1')
					return (-1);
			}
			i++;
		}
		i = 0;
		j++;
	}
	return (0);
}

void	check_map(t_data *data)
{
	t_mapcheck	cmap;

	init_mapcheck(&cmap);
	if (check_row(data) == -1)
		ft_error(0);
	if (check_frame(data) == -1)
		ft_error(0);
	if (check_count_pce(data, &cmap) == -1)
		ft_error(0);
	if (check_position_pce(data) == -1)
		ft_error(0);
}
