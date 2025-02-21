/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:37 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:38 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **str, int free_str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	if (free_str)
		free(str);
}

void	free_tokens(t_token *token)
{
	if (token->end)
	{
		free(token->end);
		token->end = NULL;
	}
	if (token->new)
	{
		free(token->new);
		token->new = NULL;
	}
	if (token->print)
	{
		free(token->print);
		token->print = NULL;
	}
	free(token);
}

void	print_error(char *msg, char *key, int exit_code)
{
	if (key)
	{
		if (msg)
			printf("%s: %s: %s\n", ERROR_TITLE, key, msg);
		else
			printf("%s: %s `%s'\n", ERROR_TITLE, ERROR_SYNTAX, key);
	}
	else
		printf("%s: %s\n", ERROR_TITLE, msg);
	g_exit = exit_code;
}

int	get_paths(t_shell *msh, char *tmp, int i)
{
	tmp = ft_strdup(get_envinroment_content(msh, "PATH", -1)); // key 값이 PATH인 content를 복사해서 tmp에 넣음
	if (!tmp)
		return (0);
	msh->paths = ft_split(tmp, ':'); // ':' 단위로 쪼갬.
	while (msh->paths && msh->paths[++i])
		msh->paths[i] = ft_strjoin(msh->paths[i], "/"); // 마지막 부분에 /를 붙임
	free(tmp);
	return (1);
}
/*
get_paths 예시
tmp = "/usr/local/bin:/usr/bin";

msh->paths = {
    "/usr/local/bin",
    "/usr/bin",
    NULL
};
strjoin 후
msh->paths = {
    "/usr/local/bin/",
    "/usr/bin/",
    NULL
};
*/


void	clean_exit(t_shell *msh, int mode)
{
	if (msh->paths)
		free_split(msh->paths, YES);
	free_split(msh->environment.key, YES);
	free_split(msh->environment.content, YES);
	free_split(msh->environment.key_tmp, YES);
	free(msh->user_input);
	free(msh->home);
	free(msh->oldpwd);
	if (mode == BUILTIN_EXIT)
		exit(EXIT_SUCCESS);
	else
		exit(g_exit);
}
