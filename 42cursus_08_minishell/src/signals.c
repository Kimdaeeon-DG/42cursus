/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:31 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:32 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int sig)
{
	g_exit = 130;
	ft_putchar('\n');
	(void)sig;
}

void	back_slash(int sig)
{
	g_exit = 131;
	printf("Quit (core dumped)\n");
	(void)sig;
}

void	reset_prompt(int sg)
{
	g_exit = 130;
	ft_putchar('\n');
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sg;
}

void	set_signal(int sg, t_shell *msh) // heredoc 관련 시그널 설정
{
	if (sg == STOP_RESTORE) // 기본 쉘 상태로 복구
	{
		signal(SIGINT, reset_prompt); // ctrl + c 누르면 프롬프트 재설정(리셋)
		signal(SIGQUIT, SIG_IGN); // ctrl + \ 는 무시하여 코어 덤프 방지
	}
	if (sg == STOP_QUIT) // 일반적인 종료
	{
		signal(SIGINT, ctrl_c); // ctrl + c 발생 시  ctrl_c() 실행
		signal(SIGQUIT, back_slash); // ctrl + \ 발생 시 back_slash() 실행
	}
	if (sg == EXIT) // 쉘 종료
	{
		printf("exit\n");
		clean_exit(msh, BUILTIN_EXIT); // 해당 함수를 호출하여 쉘 종료
	}
	if (sg == HEREDOC) // 히어독 모드면
		signal(SIGINT, child_signal_handler); // ctrl + c 발생 시 child_signal_handler 실행
	if (sg == HEREDOC_PAUSE) // 히어독의 다른 처리
		signal(SIGINT, child_signal_handler2); // ctrl + c 발생 시 child_signal_handler2 실행
}
