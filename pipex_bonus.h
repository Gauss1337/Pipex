/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:02:22 by ahakam            #+#    #+#             */
/*   Updated: 2022/03/24 21:29:33 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct l_fd
{
	int		fd[2];
	int		pipe;
	int		file1;
	int		file2;
	int		l;
	int		k;
	pid_t	id;
	char	*temp;
	char	*line;
	char	*delimiter;
	char	**cmd;
	char	**cmd2;
}	t_fd;

typedef struct l_par
{
	char	**htr;
	char	**ktr;
	char	*ptr;
	int		i;
}	t_par;

void	ft_close(int file1, int file2);
int		ft_strcmp_bonus(char *s1, char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *str, char c);
char	*ft_strjoin(char const *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	**comd(char **envp, char *argv);
char	**path(char **envp);
void	fk_free(char **strs);
void	here_doc(int argc, char **argv, char **envp);
void	ft_doc(char **argv, char **envp, int argc);
void	ft_inti_fd(char **argv, int *file1, int *file2, int argc);
#endif
