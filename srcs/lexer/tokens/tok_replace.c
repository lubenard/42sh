/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 17:30:43 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/23 17:34:46 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

void	tok_replace(t_token *token, char *str)
{
	free(token->content);
	if (!str)
		str = ft_strdup("");
	token->content = str;
	token->len = ft_strlen(str);
}