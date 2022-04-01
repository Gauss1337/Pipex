/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahakam <ahakam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:15:57 by ahakam            #+#    #+#             */
/*   Updated: 2022/03/28 18:24:30 by ahakam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fk_free(char **strs)
{
	int	k;

	k = 0;
	while (strs[k])
	{
		free (strs[k]);
		k++;
	}
	free (strs);
}

char	**path(char **envp)
{
	char	*htr;
	int		i;

	htr = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != 0)
			htr = ft_strnstr(envp[i], "PATH=", 5);
		i++;
	}
	if (htr == NULL)
	{
		perror("PATH not found");
		exit(127);
	}
	return (ft_split(htr, ':'));
}

char	**comd(char **envp, char *argv)
{
	t_par	list;

	list.i = -1;
	list.htr = path(envp);
	list.ktr = ft_split(argv, ' ');
	if (!list.ktr || !list.htr)
		return (NULL);
	while (list.htr[++(list.i)] != NULL)
	{
		list.ptr = ft_strjoin(list.htr[list.i], list.ktr[0]);
		if (!list.ptr)
			return (NULL);
		if (access(list.ptr, X_OK) == 0)
		{
			free(list.ktr[0]);
			fk_free(list.htr);
			list.ktr[0] = ft_strdup(list.ptr);
			free(list.ptr);
			return (list.ktr);
		}
		free(list.ptr);
	}
	fk_free(list.htr);
	return (list.ktr);
}
