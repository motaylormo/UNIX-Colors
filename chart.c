/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_printer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaylor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 11:13:49 by mtaylor           #+#    #+#             */
/*   Updated: 2019/06/09 11:13:50 by mtaylor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//https://misc.flogisoft.com/bash/tip_colors_and_formatting

#include <stdio.h>
#include <string.h>

#define	CELL_PADDING 3

#define	WHITE_INK 15
#define BLACK_INK 0

#define BOLD "\e[1m"
#define DIM "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define OFF "\e[0m"

void	print_cell(int color, int width, int ink)
{
	printf("\e[48;5;%dm", color);
	printf("\e[38;5;%dm", ink);
	printf("%*c", CELL_PADDING, ' ');
	printf("%*d", width, color);
	printf("%*c", CELL_PADDING, ' ');
	printf(OFF);
}

#define INDENT 17

static char	*names[] = {
	"black",
	"red",
	"green",
	"yellow",
	"blue",
	"magenta",
	"cyan",
	"white",
};

void	colors_16(void)
{
	printf("%*c", INDENT + 5, ' ');
	printf(BOLD "ANSI Colors" OFF "\n");
	printf("%*c ", INDENT, ' ');
	printf(ITALIC " %s   %s " OFF "\n", "normal", "bright");
	for (int i = 0; i < 8; ++i)
	{
		printf("%*s ", INDENT, names[i]);
		print_cell(i, 2, (i == 7) ? BLACK_INK : WHITE_INK);
		printf(" ");
		print_cell(i + 8, 2, (i == 0) ? WHITE_INK : BLACK_INK);
		printf("\n");
	}
}

#define BLANK ITALIC DIM UNDERLINE "number" OFF

void	colors_256(void)
{
	printf("%*c", ((9 * 6) - (int)strlen("256 Colors")) / 2, ' ');
	printf(BOLD "256 Colors" OFF "\n");
	printf("      Text: \"\\e[38;5;" BLANK "m\"\n");
	printf("Background: \"\\e[48;5;" BLANK "m\"\n");
	for (int i = 16; i < 256; ++i)
	{
		print_cell(i, 3,
			(((i - 16) / 18) % 2 == 1) ? BLACK_INK : WHITE_INK);
		if ((i - 15) % 6 == 0)
			printf("\n");
	}
}

int main()
{
	colors_16();
	printf("\n");
	colors_256();
}
