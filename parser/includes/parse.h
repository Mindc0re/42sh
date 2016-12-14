#ifndef PARSE_H
# define PARSE_H

# include "../libft/libft.h"
# include "get_next_line.h"
# include <sys/types.h>
# include <dirent.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>

# define SEMICOLON 	1
# define AND 		2
# define OR 		3
# define PIPE 		4
# define LESS 		5
# define MORE 		6
# define DBLESS 	7
# define DBMORE 	8
# define COMMAND	9

extern char			**environ;

typedef struct 		s_tree
{
	int				type;
	char			*content;
	struct s_tree	*left;
	struct s_tree	*right;
} 					t_tree;

typedef struct		s_all
{
	char			*line;
	char			*epured;
	char			*cmd;
	char			*cmd1;
	char			*cmd2;
	char			*cmd1_path;
	char			*cmd2_path;
	char			**path;
	char			**lines;
	char			**envcpy;
}					t_all;

void	get_cmds(t_all *all, char *command1, char *command2);
int		get_path_for_pipe(t_all *all, t_tree *tree);
void	free_tree(t_tree *tree);
void	free_tab(char **tab);
void	parse(t_tree *tree);
int		isallspace(char *str);
char	*epur_str(char *str);
int		dotcoma(t_tree *tree);
char	*search(char *src, char *str1, char *str2);
t_tree		*create_node(void);
int		and_or(t_tree *tree);
char	*search2(char *src, char *str1, char *str2, char *str3);
int		redirections(t_tree *tree);
void	pipe_tree(t_tree *tree, char *chr, int len);
void	dbless_tree(t_tree *tree, char *chr, int len);
void	dbmore_tree(t_tree *tree, char *chr, int len);
void	less_tree(t_tree *tree, char *chr, int len);
void	more_tree(t_tree *tree, char *chr, int len);
void	exec_tree(t_all *all, t_tree *tree);
void	get_path(t_all *all);
int		find_cmd_path(t_all *all, int i, char *cmd);
void	accessfork(t_all *all, struct stat sb, char *cmd);
void	exec_fork(t_all *all, char *cmd);
int		count_words(char *str);
void	get_cmd(t_all *all, char *command);
void	try_pipe(t_all *all, t_tree *tree);
void	exec_pipe(char **output, char **input, t_all *all);

#endif
