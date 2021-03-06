/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:08:59 by frossiny          #+#    #+#             */
/*   Updated: 2019/10/24 12:59:09 by frossiny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "variables.h"

int		par_type_name(t_parser *par)
{
	char	*content;
	char	*chr;

	content = par->tokens->content;
	if (par->can_var \
			&& (chr = ft_strchr(content, '='))
			&& var_is_key_valid(content, chr - content))
		par->tokens->type = TOKEN_ASSIGNMENT;
	else
		par->can_var = 0;
	par_next(par, 1);
	return (1);
}
