/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:20:34 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 14:52:58 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lex_state_quotes(t_lexer *lexer)
{
	if (*(lexer->in) == '\'' && lexer->state == ST_QUOTES
					&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		update_state(lexer, ST_GENERAL);
		lexer->in++;
	}
	else if (*(lexer->in) == '"' && lexer->state == ST_DQUOTES
					&& !is_escaped(lexer->pin, lexer->in - lexer->pin, 0))
	{
		update_state(lexer, ST_GENERAL);
		lexer->in++;
	}
	else if (*(lexer->in) == '\0')
		return (lexer->state == ST_QUOTES ? -2 : -3);
	else
		lexer->in++;
	return (1);
}
