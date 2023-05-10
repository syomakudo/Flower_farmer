#include "include.h"

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

int	main(void)
{
	t_data	data;
	int		i;
	int		j;
	char	*file_name;
	t_img	img[5];

	file_name = "./maps/test1_no.ber";
	
	make_map(&data,file_name);

	/*check_map*/
	check_map(&data);

	/*mapのスタートとゴールの位置を出力*/
	printf("start: %d,%d\n", data.x_start, data.y_start);
	printf("goal: %d,%d\n", data.x_goal, data.y_goal);

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
