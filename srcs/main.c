#include "../minilibx-linux/mlx.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROW 3 // 行数
#define COL 5 // 列数

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}			t_img;

/*
**col:横のマスの数
**row:縦のマスの数
*/
typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		x_now;
	int		y_now;
	int		x_start;
	int		y_start;
	int		x_goal;
	int		y_goal;
	int		items;
	int		x_max;
	int		y_max;
	int		col;
	int		row;
}			t_data;

/*mapエラーチェック用の構造体*/
typedef struct s_mapcheck
{
	int		count_P;
	int		count_C;
	int		count_E;

}			t_mapcheck;

/*初期化*/
void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->x_now = 0;
	data->y_now = 0;
	data->x_start = 0;
	data->y_start = 0;
	data->x_goal = 0;
	data->y_goal = 0;
	data->items = 0;
	data->x_max = 0;
	data->y_max = 0;
	data->col = 0;
	data->row = 0;
}

/*初期化mapcheck*/
void	init_mapcheck(t_mapcheck *cmap)
{
	cmap->count_P = 0;
	cmap->count_C = 0;
	cmap->count_E = 0;
}

/*エラーを出力
** -1 malloc_error
** -2 file open error
** -3 file read error
** -4 file close error
** -5 gnl error
** -6 map error
*/
void	ft_error(int i)
{
	if (i == 0)
		printf("map invalid\n");
	else if (i == -1)
		printf("malloc_error\n");
	else if (i == -2)
		printf("file open error\n");
	else if (i == -3)
		printf("file read error\n");
	else if (i == -4)
		printf("file close error\n");
	else if (i == -5)
		printf("gnl error\n");
	exit(1);
}

/*gnlを使用する*/
void	read_map(t_data *data, char *file_name)
{
	int	fd;
	int	i;
	int	row;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(-2);
	i = 0;
	row = data->row;
	while (row-- > 0)
	{
		data->map[i] = get_next_line(fd);
		if (data->map[i] == NULL)
			ft_error(-5);
		i++;
	}
	data->map[i] = NULL;
	if (close(fd) == -1)
		ft_error(-4);
}

/*ファイルの行数を返す
**rowに行数を代入
*/
int	count_read_row(char *file_name)
{
	int		fd;
	int		count;
	char	buf[1];
	int		i;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(-2);
	i = -2;
	while (1)
	{
		i = read(fd, buf, 1);
		if (i == 0)
			break ;
		else if (i == -1)
			ft_error(-3);
		if (buf[0] == '\n')
			count++;
	}
	if (close(fd) == -1)
		ft_error(-4);
	if (count == 0)
		return (0);
	return (count + 1);
}


//チェック関数//////////////////////////////////////////////
/*mapの行の文字数が有効かどうか
**有効なら0を返す
**無効なら-1を返す
**colに文字数を代入
**結果的に列の文字数が有効かどうかも判定してくれる。count_read_rowで行数を取得してるから。
*/
int	check_row(t_data *data)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (data->map[i] != NULL)
	{
		count = ft_strlen(data->map[i]);
		if (i == 0)
			data->col = count;
		if (count != data->col)
			return (-1);
		i++;
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
	while (data->map[i] != NULL)
	{
		while (data->map[i][j] != '\0')
		{
			if (i == 0 || i == data->row - 1)
			{
				if (data->map[i][j] != '1')
					return (-1);
			}
			else if (j == 0 || j == data->col - 1)
			{
				if (data->map[i][j] != '1')
					return (-1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

/*スタート（P）のアドレスを格納する
**count_Pをインクリメント
*/
void put_add_start(t_data *data, size_t i, size_t j, t_mapcheck *cmap)
{
	data->x_start = i;
	data->y_start = j;
	cmap->count_P++;
}

/*ゴール（E）のアドレスを格納する
**count_Eをインクリメント
*/
void put_add_goal(t_data *data, size_t i, size_t j, t_mapcheck *cmap)
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
int	check_PCE(t_data *data, t_mapcheck *cmap)
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

int	main(void)
{
	t_data	data;
	int		i;
	int		j;
	char	*file_name;
	t_img	img[5];

	file_name = "./maps/test1_no.ber";
	init_data(&data);
	/*make_map*/
	data.row = count_read_row(file_name);
	if (data.row == 0)
		ft_error(0);
	data.map = malloc(sizeof(char *) * (data.row + 1));
	if (data.map == NULL)
		ft_error(-1);
	read_map(&data, file_name);


	/*check_map*/
	t_mapcheck cmap;
	init_mapcheck(&cmap);
	if (check_row(&data) == -1)
		ft_error(0);
	if (check_frame(&data) == -1)
		ft_error(0);
	if (check_PCE(&data, &cmap) == -1)
		ft_error(0);


	// 2次元配列の値を出力する
	for (int i = 0; i < data.row; i++)
	{
		for (int j = 0; j < data.col; j++)
		{
			printf("%c ", data.map[i][j]); // %c で文字を表示
		}
		printf("\n");
	}
	// メモリの解放
	for (int i = 0; i < data.row; i++)
	{
		free(data.map[i]);
	}
	free(data.map);
	return (0);


	/*make_window*/
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 50 * data.col, 50 * data.row, "Hello");
	img[0].img = mlx_xpm_file_to_image(data.mlx,
										"./img/snake.xpm",
										&img[0].width,
										&img[0].height);
	img[1].img = mlx_xpm_file_to_image(data.mlx,
										"./img/tooth.xpm",
										&img[1].width,
										&img[1].height);
	img[2].img = mlx_xpm_file_to_image(data.mlx,
										"./img/bacteria.xpm",
										&img[2].width,
										&img[2].height);
	img[3].img = mlx_xpm_file_to_image(data.mlx,
										"./img/trashBox2.xpm",
										&img[3].width,
										&img[3].height);
	img[4].img = mlx_xpm_file_to_image(data.mlx,
										"./img/dentist2.xpm",
										&img[4].width,
										&img[4].height);
	i = 0;
	while (i < data.row)
	{
		j = 0;
		while (j < data.col)
		{
			if (data.map[i][j] == '1')
				mlx_put_image_to_window(data.mlx, data.win, img[1].img, j * 50,
						i * 50);
			else if (data.map[i][j] == 'C')
				mlx_put_image_to_window(data.mlx, data.win, img[2].img, j * 50,
						i * 50);
			else if (data.map[i][j] == 'P')
				mlx_put_image_to_window(data.mlx, data.win, img[4].img, j * 50,
						i * 50);
			else if (data.map[i][j] == 'E')
				mlx_put_image_to_window(data.mlx, data.win, img[3].img, j * 50,
						i * 50);
			j++;
		}
		i++;
	}
	// 2次元配列の値を出力する
	for (int i = 0; i < data.row; i++)
	{
		for (int j = 0; j < data.col; j++)
		{
			printf("%c ", data.map[i][j]); // %c で文字を表示
		}
		printf("\n");
	}
	// メモリの解放
	for (int i = 0; i < data.row; i++)
	{
		free(data.map[i]);
	}
	free(data.map);
	return (0);
}
