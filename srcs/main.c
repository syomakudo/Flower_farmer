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
		printf("map invalid\n");
	else if (num == -1)
		printf("malloc_error\n");
	else if (num == -2)
		printf("file open error\n");
	else if (num == -3)
		printf("file read error\n");
	else if (num == -4)
		printf("file close error\n");
	else if (num == -5)
		printf("gnl error\n");
	exit(1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		j;
	int		i;
	char	*file_name;
	t_img	img[5];

	(void)argc;
	(void)argv;
	file_name = "/Users/syoma.k/Desktop/so_long/maps/3ok.ber";
	int		fd;

	data = make_map(file_name);

	for (int j = 0; j < data.row; j++)
		printf("%s\n", data.map[j]);
	printf("row: %d\n", data.row);
	printf("col: %d\n", data.col);

	/*check_map*/
	check_map(&data);

	// メモリの解放
	for (int j = 0; j < data.row; j++)
	{
		free(data.map[j]);
	}
	free(data.map);


	return 0;


	/*mapのスタートとゴールの位置を出力*/
	printf("start: %d,%d\n", data.y_start, data.x_start);
	printf("goal: %d,%d\n", data.y_goal, data.x_goal);

	// 2次元配列の値を出力する
	for (int j = 0; j < data.row; j++)
	{
		for (int i = 0; i < data.col; i++)
		{
			printf("%c ", data.map[j][i]); // %c で文字を表示
		}
		printf("\n");
	}
	// メモリの解放
	for (int j = 0; j < data.row; j++)
	{
		free(data.map[j]);
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
	j = 0;
	while (j < data.row)
	{
		i = 0;
		while (i < data.col)
		{
			if (data.map[j][i] == '1')
				mlx_put_image_to_window(data.mlx, data.win, img[1].img, i * 50,
						j * 50);
			else if (data.map[j][i] == 'C')
				mlx_put_image_to_window(data.mlx, data.win, img[2].img, i * 50,
						j * 50);
			else if (data.map[j][i] == 'P')
				mlx_put_image_to_window(data.mlx, data.win, img[4].img, i * 50,
						j * 50);
			else if (data.map[j][i] == 'E')
				mlx_put_image_to_window(data.mlx, data.win, img[3].img, i * 50,
						j * 50);
			i++;
		}
		j++;
	}
	// 2次元配列の値を出力する
	for (int j = 0; j < data.row; j++)
	{
		for (int i = 0; i < data.col; i++)
		{
			printf("%c ", data.map[j][i]); // %c で文字を表示
		}
		printf("\n");
	}
	// メモリの解放
	for (int j = 0; j < data.row; j++)
	{
		free(data.map[j]);
	}
	free(data.map);
	return (0);
}
