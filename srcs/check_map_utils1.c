#include "include.h"
/*このファイルではP,C,Eの数チェックをしている*/

/*スタート（P）のアドレスを格納する
**count_Pをインクリメント
*/
void	put_add_start(t_data *data, size_t i, size_t j, t_mapcheck *cmap)
{
	data->x_start = i;
	data->y_start = j;
	cmap->count_P++;
}

/*ゴール（E）のアドレスを格納する
**count_Eをインクリメント
*/
void	put_add_goal(t_data *data, size_t i, size_t j, t_mapcheck *cmap)
{
	data->x_goal = i;
	data->y_goal = j;
	cmap->count_E++;
}

/*P,C,Eがあるかチェック
**それぞれカウントして、PとEが1つずつあるかチェック
**Cは1つ以上あるかチェックして個数をdata->itemsに格納
**PとEの位置をdataに格納
*/
int	check_count_pce(t_data *data, t_mapcheck *cmap)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (data->map[i][j] == 'P')
				put_add_start(data, i, j, cmap);
			else if (data->map[i][j] == 'C')
				data->items++;
			else if (data->map[i][j] == 'E')
				put_add_goal(data, i, j, cmap);
			j++;
		}
		j = 0;
		i++;
	}
	if (cmap->count_P != 1 || data->items == 0 || cmap->count_E != 1)
		return (-1);
	return (0);
}
