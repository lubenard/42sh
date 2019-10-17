/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 12:12:12 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/17 16:32:22 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	lexer_free(t_lexer *lexer)
{
	tok_destroy(lexer->tokens);
	lexer->tokens = NULL;
	lexer->size = 0;
	update_state(lexer, ST_GENERAL);
}
