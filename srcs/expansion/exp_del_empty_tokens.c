/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_del_empty_tokens.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:27:05 by frossiny          #+#    #+#             */
/*   Updated: 2020/02/14 14:40:11 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "expansion.h"

static void		check_redir(t_token *tok, t_cmd *cmd)
{
	t_redirect	*curr;

	curr = cmd->redir;
	while (curr)
	{
		if (curr->value == tok)
			curr->value = NULL;
		curr = curr->next;
	}
}

static t_token	*get_exe_token(t_token *exe)
{
	t_token		*prev;

	prev = NULL;
	while (tok_is_cmd_comp(exe))
	{
		if (prev && tok_is_redirection(prev))
		{
			prev = exe;
			exe = exe->next;
			continue ;
		}
		if (exe && exe->type == TOKEN_NAME)
			return (exe);
		prev = exe;
		exe = exe->next;
	}
	return (exe && exe->type == TOKEN_NAME ? exe : NULL);
}

t_token			*exp_del_empty_tokens(t_token *token, t_cmd *cmd)
{
	t_token	*prev;
	t_token	*curr;
	t_token	*next;

	exp_tok_clean(token);
	if (cmd->tokens == token)
		cmd->tokens = token->next;
	else if (cmd->tokens->next)
	{
		prev = NULL;
		curr = cmd->tokens->next;
		while (curr)
		{
			next = curr->next;
			if (curr == token)
				prev->next = token->next;
			curr = next;
		}
	}
	cmd->exe = get_exe_token(cmd->tokens);
	check_redir(token, cmd);
	next = token->next;
	tok_free(token);
	return (next);
}
