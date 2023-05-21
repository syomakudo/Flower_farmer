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

/*ゴール（E）のアドレスを格納する
**count_Eをインクリメント
*/
void	put_add_goal(t_data *data, size_t j, size_t i, t_mapcheck *cmap)
{
	data->y_goal = j;
	data->x_goal = i;
	cmap->count_e++;
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
				put_add_goal(data, j, i, cmap);
			i++;
		}
		i = 0;
		j++;
	}
	if (cmap->count_p != 1 || data->items == 0 || cmap->count_e != 1)
		return (-1);
	return (0);
}
