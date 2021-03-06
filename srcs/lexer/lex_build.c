/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 15:28:04 by vsaltel           #+#    #+#             */
/*   Updated: 2020/02/17 16:49:11 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"
#include "shell.h"
#include "structs.h"
#include "lexer.h"
#include "history.h"

static void		init_bslash_error(char **input, char **ninput)
{
	char	*tmp;

	if ((*input)[ft_strlen(*input) - 1] == '\\')
	{
		tmp = ft_strndup(*input, ft_strlen(*input) - 1);
		free(*input);
		*input = tmp;
	}
	g_ignore_signals = 1;
	*ninput = NULL;
}

int				bslash_error(char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	init_bslash_error(input, &ninput);
	while (!ninput || ft_strequ(ninput, "\\"))
	{
		free(ninput);
		if (!(ret = get_input(0, &ninput, &g_shell)))
		{
			if (g_ignore_signals)
			{
				g_ignore_signals = 0;
				return (2);
			}
			return (258);
		}
	}
	if (ninput)
	{
		tmp = ft_strjoinf(*input, ninput);
		*input = tmp;
	}
	g_ignore_signals = 0;
	return (0);
}

int				not_closed_error(char **input, int ret)
{
	char	*ninput;
	char	*tmp;

	g_ignore_signals = 1;
	if (!(ret = get_input(0, &ninput, &g_shell)))
	{
		if (g_ignore_signals)
		{
			ft_dprintf(2, "42sh: unexpected EOF\n");
			g_ignore_signals = 0;
			return (2);
		}
		return (258);
	}
	tmp = ft_strjoint(*input, "\n", ninput);
	free(*input);
	free(ninput);
	*input = tmp;
	g_ignore_signals = 0;
	return (0);
}

int				lex_build(t_shell *shell, char **input)
{
	int			ret;

	ret = 0;
	shell->lexer.size = 0;
	while ((ret = lex(*input, &(shell->lexer))) < 1)
	{
		lexer_free(&(shell->lexer));
		if (ret > -2)
			return (ret);
		else if (ret == -2 && (ret = not_closed_error(input, ret)))
			return (ret);
		else if (ret == -3 && (ret = bslash_error(input, ret)))
			return (ret);
	}
	return (ret);
}

int				lex_loop(t_shell *shell, char **input, int history)
{
	int			ret;

	ret = 0;
	if (isatty(0) && (ret = histo_expansion(shell, input)))
		return (0);
	if ((ret = lex_build(shell, input)) != 1)
		return (ret);
	if (isatty(0))
		history ? add_to_history(*input, &(shell->history)) : 0;
	if ((ret = alias_exec(shell)))
		return (ret);
	return (1);
}
