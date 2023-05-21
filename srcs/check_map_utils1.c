/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoma.k <syoma.k@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 12:40:54 by syoma.k           #+#    #+#             */
/*   Updated: 2023/05/22 00:42:22 by syoma.k          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
/*このファイルではP,C,Eの数チェックをしている*/

/*スタート（P）のアドレスを格納する
**count_Pをインクリメント
*/
void	put_add_start(t_data *data, size_t j, size_t i, t_mapcheck *cmap)
{
	data->y_start = j;
	data->x_start = i;
	cmap->count_p++;
}

/*P,C,Eがあるかチェック
**それぞれカウントして、PとEが1つずつあるかチェック
**Cは1つ以上あるかチェックして個数をdata->itemsに格納
**PとEの位置をdataに格納
*/
int	check_count_pce(t_data *data, t_mapcheck *cmap)
{
	size_t	j;
	size_t	i;

	j = 0;
	i = 0;
	while (data->map[j] != NULL)
	{
		while (data->map[j][i] != '\0')
		{
			if (data->map[j][i] == 'P')
				put_add_start(data, j, i, cmap);
			else if (data->map[j][i] == 'C')
				data->items++;
			else if (data->map[j][i] == 'E')
				cmap->count_e++;
			i++;
		}
		i = 0;
		j++;
	}
	if (cmap->count_p != 1 || data->items == 0 || cmap->count_e != 1)
		return (-1);
	return (0);
}
