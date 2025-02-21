/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daeekim <daeekim@student.42gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:40:23 by daeekim           #+#    #+#             */
/*   Updated: 2025/02/19 16:40:25 by daeekim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

int	main(void)
{
	t_shell	msh;

	set_environment_and_paths(&msh);
	while (1)
	{
		msh.fdin = STDIN_FILENO; // 표준 입력 설정
		msh.fdout = STDOUT_FILENO; // 표준 출력 설정
		get_user_input(&msh, NULL); // 유저가 입력하는 값 처리
		if (msh.user_input)
		{
			if (ft_strlen(msh.user_input) && is_valid_input(msh.user_input, 0) // 유효성 체크
				&& !have_only_spaces(msh.user_input, -1)) // 공백만 있는지 체크
			{
				parse_input(&msh, msh.user_input, -1); // 파싱함
				if (first_cmd_valid(&msh) && redirections_are_valid(&msh, -1)) // cmds, redirections 유효성 체크
					commands_manager(&msh, -1);
				free_split(msh.cmds, NO);
			}
			free(msh.user_input);
		}
		else
			set_signal(EXIT, &msh);
	}
}
