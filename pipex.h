/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:02:22 by ahakam            #+#    #+#             */
/*   Updated: 2022/03/28 17:25:19 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct l_fd
{
	int		fd[2];
	int		pipe;
	int		file1;
	int		file2;
	int		l;
	int		k;
	pid_t	id;
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

char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *str, char c);
char	*ft_strjoin(char const *s1, char *s2);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	**comd(char **envp, char *argv);
char	**path(char **envp);
void	fk_free(char **strs);
#endif
