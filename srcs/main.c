#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../minilibx-linux/mlx.h"
#include "get_next_line.h"

#define ROW 3  // 行数
#define COL 5  // 列数

typedef struct	s_img
{
	void	*img;
	int		width;
	int		height;
}				t_img;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		x_now;
	int		y_now;
	int		x_max;
	int		y_max;
	int		col;
	int		row;
}				t_data;

/*初期化*/
void init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->x_now = 0;
	data->y_now = 0;
	data->x_max = 0;
	data->y_max = 0;
	data->col = 0;
	data->row = 0;
}

/*エラーを出力
** -1 malloc_error
** -2 file open error
** -3 file read error
** -4 file close error
** -5 gnl error
** -6 map error
*/
void ft_error(int i)
{
	if (i == -1)
		printf("malloc_error\n");
	else if (i == -2)
		printf("file open error\n");
	else if (i == -3)
		printf("file read error\n");
	else if (i == -4)
		printf("file close error\n");
	else if (i == -5)
		printf("gnl error\n");
	else if (i == -6)
		printf("map error\n");
		exit(1);
}

/*gnlを使用する*/
void read_map(t_data *data, char *file_name)
{
	int		fd;
	int		i;
	int		row;

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

/*ファイルの行数を返す*/
int count_read_row(char *file_name)
{
	int		fd;
	int		count;
	char buf[1];
	int		i;

	count = 1;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(-2);
	i = -2;
	while (1)
	{
		i = read(fd, buf, 1);
		if (i == 0)
			break;
		else if (i == -1)
			ft_error(-3);
		if (buf[0] == '\n')
			count++;
		i++;
	}
	if (close(fd) == -1)
		ft_error(-4);
	return count;
}




// error処理に関数
// イメージ void ft_error(func);
// funcの返り値はint型で、-1のときエラー
int main() {

	t_data	data;
	int		i;
	int		j;
	char	*file_name = "./maps/test.ber";

	init_data(&data);

	/*make_map*/
	data.row = count_read_row(file_name);
	data.map = malloc(sizeof(char *) * (data.row + 1));
	read_map(&data,file_name);

	/*check_map*/




    // 2次元配列の値を出力する
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%c ", data.map[i][j]);  // %c で文字を表示
        }
        printf("\n");
    }
    // メモリの解放
    for (int i = 0; i < ROW; i++) {
        free(data.map[i]);
    }
    free(data.map);


	return (0);

	/*make_window*/
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 50 * COL,
			50 * ROW, "Hello");

	t_img	img[5];

	img[0].img = mlx_xpm_file_to_image(data.mlx,
			"./img/snake.xpm", &img[0].width, &img[0].height);
	img[1].img = mlx_xpm_file_to_image(data.mlx,
			"./img/tooth.xpm", &img[1].width, &img[1].height);
	img[2].img = mlx_xpm_file_to_image(data.mlx,
			"./img/bacteria.xpm", &img[2].width, &img[2].height);
	img[3].img = mlx_xpm_file_to_image(data.mlx,
			"./img/trashBox2.xpm", &img[3].width, &img[3].height);
	img[4].img = mlx_xpm_file_to_image(data.mlx,
			"./img/dentist2.xpm", &img[4].width, &img[4].height);


		i = 0;
	while (i < ROW)
	{
		j = 0;
		while (j < COL)
		{
				if (data.map[i][j] == '1')
					mlx_put_image_to_window(data.mlx, data.win,
						img[1].img, j * 50, i * 50);
				else if (data.map[i][j] == 'C')
					mlx_put_image_to_window(data.mlx, data.win,
						img[2].img, j * 50, i * 50);
				else if (data.map[i][j] == 'P')
					mlx_put_image_to_window(data.mlx, data.win,
						img[4].img, j * 50, i * 50);
				else if (data.map[i][j] == 'E')
					mlx_put_image_to_window(data.mlx, data.win,
						img[3].img, j * 50, i * 50);

			j++;
		}
		i++;
	}
	

    // 2次元配列の値を出力する
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%c ", data.map[i][j]);  // %c で文字を表示
        }
        printf("\n");
    }
    // メモリの解放
    for (int i = 0; i < ROW; i++) {
        free(data.map[i]);
    }
    free(data.map);



    return (0);
}
