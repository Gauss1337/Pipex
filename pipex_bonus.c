/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 20:00:37 by ahakam            #+#    #+#             */
/*   Updated: 2022/03/28 17:44:10 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close(int file1, int file2)
{
	if (file1 == -1)
	{
		perror("first file not found !");
		exit(1);
	}
	close(file1);
	close(file2);
}

void	ft_error(int dup)
{
	if (dup == -1)
	{
		perror ("duplication failed !");
		exit(1);
	}
}

void	ft_child_bonus(char **av1, char **envp)
{
	pid_t	id;
	int		fd[2];
	int		r;

	pipe(fd);
	id = fork();
	if (id == -1)
		perror("fork failed !");
	if (id)
	{
		r = dup2(fd[0], 0);
		ft_error(r);
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		close(fd[0]);
		r = dup2(fd[1], 1);
		ft_error(r);
		close(fd[1]);
		execve(av1[0], av1, envp);
		perror("execve failed <3");
		exit(1);
	}
}

void	ft_exec(int argc, t_fd *list, char **argv, char **envp)
{
	int	i;

	i = 3;
	while (i < argc - 2)
	{
		list->cmd = comd(envp, argv[i++]);
		ft_child_bonus(list->cmd, envp);
		fk_free(list->cmd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_fd	list;

	if (argc >= 5)
	{
		ft_doc(argv, envp, argc);
		ft_inti_fd(argv, &list.file1, &list.file2, argc);
		list.cmd = comd(envp, argv[2]);
		list.cmd2 = comd(envp, argv[argc - 2]);
		list.l = dup2(list.file1, 0);
		ft_error(list.l);
		list.k = dup2(list.file2, 1);
		ft_error(list.k);
		ft_child_bonus(list.cmd, envp);
		fk_free(list.cmd);
		ft_exec(argc, &list, argv, envp);
		ft_close(list.file1, list.file2);
		list.id = fork ();
		if (list.id == 0)
			execve(list.cmd2[0], list.cmd2, envp);
	}
	else
		perror("to many or few arguments !");
	close(0);
	while (wait(0) > 0)
		;
}
