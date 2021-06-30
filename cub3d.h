/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Amber <Amber@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/05 17:16:47 by Amber         #+#    #+#                 */
/*   Updated: 2020/06/22 19:06:11 by avan-dam      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct		s_sto
{
	long int		r[3];
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	int				f[3];
	int				c[3];
	int				row;
	char			*map;
	char			**split;
	char			**copy;
	int				tilesize;
	unsigned int	floorcolor;
	unsigned int	ceilingcolor;
	int				save;
	char			*error;
}					t_sto;

typedef struct		s_sprite
{
	float			*z_buf;
	int				**sprites;
	int				numbsprite;
	float			x;
	float			y;
	double			inv_det;
	double			trans_x;
	double			trans_y;
	int				screen_x;
	int				height;
	int				draw_start_y;
	int				draw_end_y;
	int				width;
	int				draw_start_x;
	int				draw_end_x;
	int				stripe;
	int				*order;
	void			*img;
	char			*addr;
	unsigned int	colour_save;
	float			v;
}					t_sprite;

typedef struct		s_data {
	void			*mlx;
	void			*mlx_win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				bits_per_pixel1;
	int				bits_per_pixel2;
	int				bits_per_pixel3;
	int				bits_per_pixel4;
	int				bits_per_pixel5;
	int				line_length;
	int				line_length1;
	int				line_length2;
	int				line_length3;
	int				line_length4;
	int				line_length5;
	int				endian;
	int				endian2;
	int				color;
	unsigned int	color_sprite;
	void			*texture1;
	char			*addrtexture1;
	void			*texture2;
	char			*addrtexture2;
	void			*texture3;
	char			*addrtexture3;
	void			*texture4;
	char			*addrtexture4;
	void			*sprite;
	char			*addrsprite;
	int				img_width1;
	int				img_height1;
	int				img_width2;
	int				img_height2;
	int				img_width3;
	int				img_height3;
	int				img_width4;
	int				img_height4;
	int				img_width5;
	int				img_height5;
	int				good_width;
	int				good_height;
	void			*goodtex;
	char			*goodaddrtex;
	int				goodline_length;
	int				good_bits_pixel;
	float			wall_x;
	float			tex_step;
	int				line_height;
	int				tex_x;
	int				tex_y;
	float			tex_pos;
}					t_data;

typedef struct		s_ray
{
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
	float			camera_x;
	float			ray_dir_x;
	float			ray_dir_y;
	float			w;
	float			pos_y;
	float			pos_x;
	float			map_x;
	float			map_y;
	float			step_x;
	float			step_y;
	float			sidedist_x;
	float			sidedist_y;
	float			deltadist_x;
	float			deltadist_y;
	float			perpwalldist;
	int				side;
	int				color;
}					t_ray;

typedef struct		s_move
{
	int				up;
	int				down;
	int				rotate_left;
	int				rotate_right;
	int				move_left;
	int				move_right;
	int				counter;
}					t_move;

typedef struct		s_master
{
	t_ray			ray;
	t_data			img;
	t_sto			mys;
	t_move			move;
	t_sprite		sp;
}					t_master;

int					main(int argc, char **argv);
int					ft_error(t_sto *mys);
void				ft_putstr(char *s);
void				ft_zero_struct(t_sto *mys);
void				ft_more_zero(t_sto *mys);
int					ft_find_info(t_sto *mys, int fd);
int					free_storage(char **storage, t_sto *mys);
int					error_text(t_sto *mys, char *error, int i);
int					ft_error(t_sto *mys);
int					ft_next_steps(t_sto *mys);
int					check_liney(char *line, t_sto *mys);
int					ft_more_checks(char *line, t_sto *mys);
int					check_negatives(t_sto *mys);
int					ft_strcmp(const char *s1, const char *s2);
int					floor_ceiling_colour(char *line, t_sto *mys, char c, int j);
int					ft_floor_ceiling_fill(t_sto *mys, char c, int j, int numb);
int					sprite_path(char *line, t_sto *mys);
int					fill_texture(char *line, t_sto *mys);
int					ft_texture_correct(char *line, t_sto *mys, char *texture);
int					fill_res(char *line, t_sto *mys, int i, int j);
int					ft_find_map(char *line, t_sto *mys);
int					check_map_characters(char *map, t_sto *mys);
char				*ft_strjoin_cub3d(char const *s1, char const *s2);
int					ft_split_cub3d(char const *s, char c, t_sto *mys);
char				*ft_strdup(const char *s1);
int					ft_strlen(const char *s);
int					ft_check_if_map_valid(t_sto *mys);
int					ft_duplicate_map(t_sto *mys);
int					ft_free_copy(t_sto *mys, int i);
int					ft_check_lines(t_sto *mys, int x, int y);
int					ft_more_map_valid(char **split, int x, int y);
int					start_char(t_sto *mys, int x, int y, int p);
void				ft_floodfill(t_sto *mys, int x, int y);
int					start_raycastin(t_sto *mys);
void				check_resize(t_master *big);
void				ft_sort_big_struct(t_master *big, t_sto *mys);
int					ft_load_texture(t_master *big);
int					keywhere(t_master *big);
int					keyrelease(int keycode, t_master *big);
int					keypress(int keycode, t_master *big);
int					ft_movedown(t_master *big);
int					ft_moveup(t_master *big);
int					ft_rotate_right(t_master *big);
int					ft_rotate_left(t_master *big);
int					ft_move_right(t_master *big);
int					ft_move_left(t_master *big);
void				ft_zero_t_move(t_move *move);
void				ft_zero_tdata(t_data *img);
void				ft_zero_tdata_more(t_data *img);
void				ft_zero_tdata_more_more(t_data *img);
int					ft_looping(t_master *big);
void				ft_wall_height(t_master *big, int x);
void				ft_texturing(t_master *big, int start, int end, int x);
void				ver_dot(int x, int y, t_master *big);
void				ft_find_out_side(t_master *big);
void				ft_more_side(t_master *big);
void				ft_find_me_color(t_master *big, int y, int x);
void				ft_find_variables(t_master *big, int x);
void				ft_find_sidedist(t_master *big);
void				ft_dda(t_master *big);
void				ft_draw_ceiling(t_master *big, int y, int x, char *dst);
void				ft_draw_floor(t_master *big, int y2, int x, char *dst);
int					start_pos(t_master *big, int y, int x);
void				ft_fill_ray(t_master *big, int x, int y);
void				ft_fill_plane(t_master *big);
void				ft_zero_tray(t_ray *ray);
int					closeme(int keycode, t_master *big);
int					exit_program(t_master *big);
unsigned int		create_trgb(int t, int r, int g, int b);
void				find_ceiling_floor_hx(t_sto *mys);
void				ft_store_sprite(t_master *big);
void				ft_numb_sprites(t_master *big);
int					ft_sprite_put(t_master *big, int i);
int					ft_load_sprite(t_master *big);
int					sort_sprites(float *sprite_dist, int numb, t_master *big);
void				ft_find_me_sprite_color(t_master *big, int tex_x, int y);
void				ver_dot_sprite(int x, int y, t_master *big);
void				sprite_working(t_master *big);
void				ft_zero_sprite_struct(t_sprite *sprite, int i);
void				start_value_sprite(t_master *big);
void				ft_zero_all(t_master *big);
char				*ft_substr(char *s, int start, int len);
int					ft_start_save(t_master *big);
void				ft_bitheader(t_master *big);
void				ft_bitheader(t_master *big);
void				ft_putpixeldata(t_master *big);
void				ft_find_me_color_save(t_master *big, int y, int x);

#endif
