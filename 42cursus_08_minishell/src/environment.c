/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:40:07 by daeekim           #+#    #+#             */
/*   Updated: 2025/02/19 17:03:25 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	key_content_malloc(t_envp *envp, int size)
{
	envp->key = malloc(sizeof(char *) * (size + 1));
	if (!envp->key)
		exit(EXIT_FAILURE);
	envp->content = malloc(sizeof(char *) * (size + 1));
	if (!envp->content)
		exit(EXIT_FAILURE);
}

// key값이 일치하는 항목의 content를 찾아서 리턴 
char	*get_envinroment_content(t_shell *msh, char *key, int i) 
{
	while (msh->environment.key[++i]) // 순차적으로 탐색
	{
		if (!ft_strcmp(msh->environment.key[i], key)) // key가 일치하면?
		{
			msh->environment.index = i; // 찾는 index = i임
			return (msh->environment.content[i]); // 찾은 content 리턴
		}
	}
	return (NULL);
}

void	get_envinroment_size(t_shell *msh, int i)
{
	while (msh->environment.envp[i])
		i++;
	msh->environment.size = i;
}

void	create_environment(t_shell *msh, char **envp, char **tmp, int i)
{
	msh->environment.envp = envp;
	get_envinroment_size(msh, 0); // 사이즈 측정
	key_content_malloc(&msh->environment, msh->environment.size); // 키와 값을 담을 공간 동적 할당
	while (msh->environment.envp[++i])
	{
		tmp = split_environment_vars(msh, &i, tmp); // tmp에 키와 값을 각각의 공간에 파싱
		msh->environment.key[i] = ft_strdup(tmp[0]); // tmp[0]에 키 넣기
		msh->environment.content[i] = ft_strdup(tmp[1]); // tmp[1]에 값 넣기
		free_split(tmp, YES); // 다 쓴 tmp 메모리 해제
		tmp = NULL; // NULL로 초기화
	}
	// 끝부분에 NULL
	msh->environment.key[i] = NULL; 
	msh->environment.content[i] = NULL;
	
	// 후속 연산 처리를 위해 임시 환경 변수 저장소 생성 및 초기화
	msh->environment.key_tmp = malloc(sizeof(char *) * (1)); 
	msh->environment.key_tmp[0] = NULL;
	msh->environment.size_tmp = 0;
}

void	set_environment_and_paths(t_shell *msh)
{
	g_exit = 0;
	msh->is_last_redirection = NO;
	msh->error_flag = NO;
	msh->has_flag_n = NO;
	msh->tokens = (char **) NULL;
	create_environment(msh, __environ, NULL, -1); // 환경변수를 파싱함
	get_paths(msh, NULL, -1); // 경로를 나누고 경로에 /를 붙임
	msh->home = ft_strdup(get_envinroment_content(msh, "HOME", -1)); // HOME이 key인 content 찾아서 넣음
	msh->oldpwd = ft_strdup(get_envinroment_content(msh, "OLDPWD", -1)); // OLDPWD가 key인 content를 찾아서 넣음
}
