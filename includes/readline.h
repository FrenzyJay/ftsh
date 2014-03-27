/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez <jibanez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:44:00 by jibanez           #+#    #+#             */
/*   Updated: 2014/03/27 19:47:06 by jibanez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_H
# define READLINE_H

typedef struct		s_env
{
	char			**env;
	int				size;
}					t_env;

typedef struct		s_hlst
{
	char			*cmd;
	int				clen;
	struct s_hlst	*next;
	struct s_hlst	*prev;
}					t_hlst;

typedef struct		s_entry
{
	struct s_hlst	*current;
	int				plen;
	int				cursor;
}					t_entry;

typedef struct		s_key_func
{
	unsigned int	key;
	void			(*f)(t_entry *);
}					t_key_func;

# define ESCAPE 27
# define UP 4283163
# define DOWN 4348699
# define LEFT 4479771
# define RIGHT 4414235
# define SPACE 32
# define RETURN 10
# define BACKSPACE 127
# define DELETE 2117294875
# define END 4610843
# define HOME 4741915
# define CTRL_A 1
# define CTRL_B 2
# define CTRL_D 4
# define CTRL_E 5
# define CTRL_L 12
# define CTRL_N 14

# define RADIX 128

char		*read_line(void);
void		raw_term_mode(void);
void		default_term_mode(void);
int			put_prompt(void);
char		*dynbuff(char *buff, int len, int add);
int			get_cols(void);
void		key_hook(unsigned int key, t_entry *user);
void		key_right(t_entry *user);
void		move_right(t_entry *user);
void		move_left(t_entry *user);
void		key_left(t_entry *user);
void		key_up(t_entry *user);
void		key_down(t_entry *user);
void		key_backspace(t_entry *user);
void		key_delete(t_entry *user);
void		key_end(t_entry *user);
void		key_home(t_entry *user);
void		key_next_word(t_entry *user);
void		key_prev_word(t_entry *user);
void		put_cmd(t_entry *user);
int			tputs_char(int c);
t_hlst		*hlst_new(char *cmd);
void		hlst_push_front(t_hlst **adlst, t_hlst *new);
void		hlst_push_back(t_hlst **adlst, t_hlst *new);
void		ft_destroy_hlst(t_hlst *historic);

#endif /* !READLINE_H */
