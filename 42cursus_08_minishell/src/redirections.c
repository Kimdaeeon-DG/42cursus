/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jupyo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:03:30 by jupyo             #+#    #+#             */
/*   Updated: 2025/02/19 17:03:31 by jupyo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_command(int i, char **file)
{
	char	*tmp;

	tmp = ft_strdup("");
	while (file[++i])
	{
		if (ft_strlen(tmp) > 0) // ex)  
			tmp = ft_strjoin(tmp, " ");
		tmp = ft_strjoin(tmp, file[i]);
	}
	/* ex)
	file[0] = "ls";
	file[1] = "-l";
	file[2] = "file.txt";
	저거 하고 나면
	tmp = "ls -l file.txt"
	*/
	return (tmp);
}

char	**double_redirect_in(t_shell *msh, char **file, int i) // <<(Heredoc) 처리 함수
{
	pid_t	pid;

	file = ft_split2(&msh->cmds[i][2], SPC); // 공백 단위로 잘라서 넣음
	pid = fork(); // 0 -> 자식 프로세스에서 반환, 양수(자식 PID) -> 부모 프로세스에서 반환, 음수(-1) -> 실패
	if (pid < 0)
		print_error(ERROR_FORK, NULL, 127);
	else if (pid == 0) // 자식 프로세스
	{
		set_signal(HEREDOC, msh); // heredoc 관련 시그널 설정
		start_heredoc(file[0], msh); // heredoc 기능 처리
		exit(g_exit);
	}
	else // 부모 프로세스
	{
		set_signal(HEREDOC_PAUSE, msh); // HEREDOC_PAUSE로 시그널 설정
		wait(NULL); // 자식 프로세스 끝날 때까지 기다림
	}
	if (g_exit == 130) // ctrl + c로 종료
		msh->ctrlc = YES;
	msh->fdin = open(file[0], O_RDONLY | O_CREAT, 0777);
	msh->file_name = ft_strdup(file[0]); // 파일 이름 복사
	msh->is_append++; // heredoc 사용 표시
	return (file);
}

void	redirect_in(t_shell *msh, int i, char **file, char *tmp)
{
	if (msh->cmds[i][0] == '<') // '<'일 때
	{
		if (msh->cmds[i][1] == '<') // "<<" 일 때
			file = double_redirect_in(msh, file, i); // "<<" 처리함
		else
		{
			file = ft_split2(&msh->cmds[i][1], SPC); // 공백 단위로 단어 자름
			msh->fdin = open(file[0], O_RDONLY, 0777);
			if (msh->fdin == -1 && !msh->file_error)
				msh->file_error = ft_strdup(file[0]);
		}
		tmp = ft_strtrim(msh->tmp_cmd, SPC);
		if ((i == 0 && file[1]) || msh->parse.id == 1
			|| (tmp[0] == '|' && ft_strlen(tmp) == 1))
		{
			free(msh->tmp_cmd);
			msh->tmp_cmd = new_command(0, file); // 여러 문자열을 합쳐서 새로운 명령어 문자열 생성
		}
		free (tmp);
		msh->is_last_redirection = NO;
		free_split(file, YES);
	}
}

void	redirect_out(t_shell *msh, int i, char *file)
{
	if (msh->cmds[i] && msh->cmds[i][0] == '>') // ">"면?
	{
		if (msh->fdout != STDOUT_FILENO) // 표준 출력이 아니면?
			close(msh->fdout); // 파일 디스크립터 닫음.
		if (msh->cmds[i] && msh->cmds[i][1] == '>') // ">>"면?
		{
			file = ft_strtrim(&msh->cmds[i][2], SPC);
			msh->fdout = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
			// 쓰기 전용으로 열고 | 파일이 없다면 생성 | 기존 파일이 있으면 파일 끝에 추가. 권한 777
		}
		else
		{
			file = ft_strtrim(&msh->cmds[i][1], SPC);
			msh->fdout = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			// 쓰기 전용으로 열고 | 파일이 없다면 생성 | 기존 파일이 있으면 지우고 새로 씀. 권한 777
		}
		free(file);
		msh->is_last_redirection = YES;
		if (msh->parse.id == 1)
		{
			free (msh->tmp_cmd);
			msh->tmp_cmd = NULL;
		}
	}
}
