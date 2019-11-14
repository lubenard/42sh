/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_completion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 12:43:39 by vsaltel           #+#    #+#             */
/*   Updated: 2019/11/14 20:24:35 by alagroy-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"

static t_list	*(*g_func_tab[4])(char *, t_shell *) =\
{
	NULL,
	compl_cmd,
	compl_file,
	compl_var,
};

static char	*find_compl_word(t_cursor_pos *pos)
{
	int		i;
	int		beg;

	beg = 0;
	i = pos->x_rel == pos->len_str ? pos->x_rel : pos->x_rel + 1;
	while (--i >= 0)
		if (ft_strchr(" |&<>'\"", pos->str[i]))
		{
			beg = i + 1;
			break ;
		}
		else if (pos->str[i] == '$')
		{
			beg = i;
			break ;
		}
	return (ft_strsub(pos->str, beg, pos->x_rel - beg));
}

void		termcaps_completion(char **str, t_cursor_pos *pos, t_shell *shell)
{
	int		mode;
	char	*compl;
	t_list	*compl_lst;

	if (pos->visual_mode || !str || !*str || !ft_strlen(*str))
		return ;
	if (!(mode = lite_parser(pos)))
		return ;
	if (!(compl = find_compl_word(pos)))
		return ;
	ft_printf("\ncompl: %s\n", compl);
	compl_lst = g_func_tab[mode](compl, shell);
	(void)shell;
	ft_strdel(&compl);
}
