/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escaped.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:24:26 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/14 14:52:58 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		lex_state_escaped(t_lexer *lexer)
{
	lexer->in++;
	update_state(lexer, ST_GENERAL);
	return (1);
}
