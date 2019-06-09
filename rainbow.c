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

#include <stdio.h>
#include <string.h>

#define	CELL_PADDING 2
#define NUM_WIDTH 3

#define	WHITE_INK 15
#define BLACK_INK 0

#define BOLD "\e[1m"
#define DIM "\e[2m"
#define ITALIC "\e[3m"
#define UNDERLINE "\e[4m"
#define OFF "\e[0m"

void	print_cell(int color, int ink)
{
	printf("\e[48;5;%dm", color);
	printf("\e[38;5;%dm", ink);
	printf("%*c", CELL_PADDING, ' ');
	printf("%*d", NUM_WIDTH, color);
	printf("%*c", CELL_PADDING, ' ');
	printf(OFF);
}

void	two_blocks(int start)
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
			print_cell(start + i + (6 * j), (j < 2) ? WHITE_INK : BLACK_INK);
		for (int j = 11; j >= 6; --j)
			print_cell(start + i + (6 * j), (j < 8) ? WHITE_INK : BLACK_INK);
		printf("\n");
	}
}

void	rainbow(void)
{
	int	block_size = 36 * 2;
	two_blocks(16 + (block_size * 0));
	two_blocks(16 + (block_size * 1));
	two_blocks(16 + (block_size * 2));
}

#define GS_INK(x) (((x) >= 244) ? BLACK_INK : WHITE_INK)

void	boustrophedon_left(int start, int size)
{
	for (int i = 1; i <= size; ++i)
		print_cell(start + (size - i), GS_INK(start + (size - i)));
	printf("\n");
}

void	boustrophedon_right(int start, int size)
{
	for (int i = 0; i < size; ++i)
		print_cell(start + i, GS_INK(start + i));
	printf("\n");
}

void	grayscale(int n)
{
	int	row = (255 - 231) / n;

	int start = 232;
	for (int i = 0; (i * row) < (255 - 231); ++i)
	{
		if ((i + 1) % 2 == 0)
			boustrophedon_left(start, row);
		else
			boustrophedon_right(start, row);
		start += row;
	}
}

void	basic_16(void)
{
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			print_cell(j + (i * 8), (i == 0) ? WHITE_INK : BLACK_INK);
		}
		printf("\n");
	}
}

int main()
{
	printf(BOLD "0 to 15" OFF "\n");
	basic_16();
	printf(BOLD "16 to 231" OFF "\n");
	rainbow();
	printf(BOLD "323 to 255" OFF "\n");
	grayscale(3);
}
