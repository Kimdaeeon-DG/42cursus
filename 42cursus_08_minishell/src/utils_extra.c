/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:39 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:40 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_environment_vars(t_shell *msh, int *i, char **tmp)
{
	char	*content;
	int		key_size;
	int		content_size;

	key_size = ft_strchr(msh->environment.envp[*i], '=')  // 키의 사이즈 측정
		- msh->environment.envp[*i]; // 배열에서 =를 찾고 시작 주소만큼 빼줌 -> 길이를 알 수 있음
	content_size = ft_strlen(msh->environment.envp[*i]) - (key_size + 1); // 전체 길이에서 key_size + 1만큼 빼라. abc = 10 이면  " 10"의 길이 3
	content = ft_substr(msh->environment.envp[*i], key_size + 1, content_size); // 배열에서 key_size + 1 뒤부터, content_size만큼 추출해라
	tmp = (char **)malloc(sizeof(char *) * 3);
	tmp[0] = ft_substr(msh->environment.envp[*i], 0, key_size); // 환경변수 키 "PATH"
	tmp[1] = ft_strtrim(content, QUOTE_SET); //환경 변수의 값 "/usr/bin:/bin"
	tmp[2] = NULL; // 종료 표시
	free(content); // 메모리 해제
	return (tmp);
}

void	child_signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		signal(SIGINT, SIG_IGN); // 프로세스를 종료하지 않음. SIGINT를 무시함
	}
}

void	child_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 130;
		printf("\n");
		exit(g_exit); // 프로세스를 즉시 종료함
	}
}

void	clean_handler(t_shell *msh)
{
	if (msh->file_name && msh->file_name[0] != '\0')
	{
		unlink(msh->file_name);
		free(msh->file_name);
	}
	if (msh->ctrlc)
	{
		free(msh->tmp_cmd);
		msh->tmp_cmd = NULL;
	}
}
