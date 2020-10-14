/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mac <mac@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 23:31:18 by szakaria          #+#    #+#             */
/*   Updated: 2020/10/14 12:40:40 by ommadhi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include "includes/ft_readline.h"
# include "libft/libft.h"
# include "GTN/get_next_line.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/types.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

# define BUFF_SIZE 1024
# define NR_J 30

#define STATUS_RUNNING 0
#define STATUS_DONE 1
#define STATUS_SUSPENDED 2
#define STATUS_CONTINUED 3
#define STATUS_TERMINATED 4

#define COMMAND_EXTERNAL 0
#define COMMAND_EXIT 1
#define COMMAND_CD 2
#define COMMAND_JOBS 3
#define COMMAND_FG 4
#define COMMAND_BG 5
#define COMMAND_EXPORT 6
#define COMMAND_UNSET 7
#define COMMAND_SET 8
#define COMMAND_ECHO 9
#define COMMAND_TYPE 10
#define	COMMAND_ENV 11

#define BACK 0
#define FORE 1

typedef struct	s_env
{
	char			*name;
	char			*environ;
	int				flag;
	struct	s_env	*next;
}				t_env;

typedef struct	s_process
{
	char				*command;
    char				**argv;
    pid_t				pid;
    int					type;
    int					status;
	int					input;
	int					output;
	int					errorput;
    struct s_process	*next;
}				t_process;

typedef struct	s_job
{
	int				id;
    t_process		*process;
    char			*command;
    pid_t			pgid;
	int				mode;
	int				p_input;
	int				p_output;
	int				p;
}				t_job;

typedef struct	s_shell
{
	t_job	*job[NR_J + 1];
	t_env	*env;
}				t_shell;

typedef struct	s_some_norme
{
	char	c;
	char	count;
	int		b;
	char	*str;
}				t_some_norme;

//~/.norminette/norminette.rb

t_shell		*shell;
char		**STATUS_STRING;
char		**semicolon;
char		**and_and;
char		**or_or;
char		**the_jobs;
int			the_status;

t_job			*make_job(char *line, int mode);

t_env			*create_env(char **environ);
t_env			*create_next(char *environ);

void			trait(char *line, int mode);
void			init_shell();
void			exec_command(t_job **job, t_process **process);
void    		remove_job(int id);
void    		print_pgid_of_job(int id);
void			set_process_status(int pid, int status);
void    		print_job_status(int id);
void    		check_zombie();
void    		print_job_status(int id);
void			set_job_status(int id, int status);
void			execve_help(t_process **process, t_job **job,
				char *command, char *print);
void			help_to_fg(pid_t pid, int id);
void			free_2d(char **str);
void			free_job(t_job *job);
void			help_to_finish_the_pipe(char **line);
void			semicolon_parse(char *line);
void			help_to_exit(t_job *job);
void    		make_the_put(t_process **process, t_job **j);
void			pipe_execve(t_process *process, t_job *job);
void			close_pipe(t_process *process, t_job *job);
void			join_with_anything(char **line, int a, int i);
void			join_with_something(char **line, char *str, int a, int i);
void			join_with_anything2(char **line, char *str, int a, int i);
void			mini_mini_norme(char **line, char *str, int a, int i);
void			help_trait(t_job **j, t_process **process, int *count);
void			to_env(t_process *process);
void			back_or_fore(t_job **job, t_process **process);
void			to_type(t_process *process);
void			to_echo(t_process *process);
void			to_set(t_process *process);
void			to_unset(t_process *process, t_job *job);
void			to_export(t_process *process, t_job *job, char **argv);
void			add_pwd(t_process *process, t_job *job, char *str);
void			to_cd(t_process *process, t_job *job);
void			add_pwd(t_process *process, t_job *job, char *str);
int				test_dir(char *argv, t_process *process);
void			print_error_jump_options(char c, int error);
void			norme_to_cd(t_process *process, t_job *job, char **argv, int i);
void			help_setenv(char *command, t_env **list);
void			free_env_list(t_env *env);
void			help_unsetenv(char *command);
void			manage_variables2(t_env *save);
void			help_to_wait(t_job *j, int *status);
void			final_help(t_process **process, t_job **j, int *count);

char			*help_search_join(char *str, DIR *dir, char **print);
char			**make_2d_table(char *line);
char			**list_to_tab(t_env *env);
char			*ft_filter_quote(int i, char *cont);
char			**split_command(char *line, char s);
char			**split_and_and(char *line, char c);
char			**split_job(char *line);
char			*replace_with_env(char *line, t_env *env, int b);
char			*concate(char *path, char *str);
char			*replace_home(char *line, t_env *env);
char			*move_quote(char *line, int i);
char			*move_slash(char *line);
char			*filter_for_file(char *file, t_env *env);
char			*take_file(char **file, int *j);
char			**ls(char *path);
char			*check_env(char *str, t_env *env);
char			**mini_filter_h(char **str, t_env *env);
char			*check_if_exist(char *command, char **env);
char			*search_env(t_env *list);
char			*get_name(char *environ);
char			*get_environ(char *environ);
char			*check(char *str);
char			*search_home(t_env *list);
char			**manage_variables(char **argv, t_env **env);
char			**create_new_argv(char **argv, int i);
char			**help_re_null(t_env *save, t_env **env, char **argv);

int				insert_job(t_job *job);
int 			wait_for_job(int id, int wait_count);
int				get_command_type(char *command);
int				to_jobs(t_job *j);
int				to_fg(t_process *process, t_job *j);
int				to_bg(t_process *process, t_job *j);
int				put_error_not_found(int type);
int				search_last(void);
int				put_error_no_such(int type);
int				put_error_fg(int type);
int				trait_built(t_job *j, t_process *process);
int				search_no_espace(char *str);
int				print_and_of_number(char s, int count);
int				check_if_and_and(char **str, int i);
int				print_fu_redirect_error(void);
int				some_name(int *i, int *j, char *str, char c);
int				check_cursh(char *str);
int				check_line(char *line);
int				if_numeric(char *str);
int				help_check_if_and_and(char **str, int i);
int				print_error_num(char *file, int error);
int				trait_the_type(char *file, int out, int type,
				t_process **process);
int				redirect(t_process **process);
int				parse_to_two(char *file, int out, int type,
				t_process **process);
int				if_two(int out, int type, t_process **process);
int				if_three(char *file2, int out, int type, t_process **process);
int				if_four(char *file2, int out, int type, t_process **process);
int				help_type_one(char *file, int error);
int				print_p_d(char *file, int pipe);
int				error_type_three(char *file, int error);
int				help_redirect(char *file, char *line);
int				print_n_x(char *file, int pipe);
int				print_i_d(char *file, int pipe);
int				count_replace_env(char *line, int i, char c);
int				h_f_f(char *file2, t_process *process, int ifnot);
int				check_set(char *new);

#endif
