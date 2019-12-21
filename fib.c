/* Author : Youssef Dahab
File name: fib.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

#define I(x, y) im[x + (y) * w]

typedef enum
{
	up,
	down,
	left,
	right
}direction;

int draw(int x, int y, direction dir, int step, int w, int h, RGB *im, RGB c);

int fib(int n, int x, int y, int step, RGB bc, RGB fc, int w, int h, RGB *image)
{
	/* calculate the nth fibonacci number fn. Ex: the 12th fibonacci in the 
        fibonacci sequence is 144 */

        unsigned long int fn_minus_2, fn_minus_1 = 0, fn = 1;
	int i;

	for (i = 1; i < n; i++)
	{
		fn_minus_2 = fn_minus_1;
		fn_minus_1 = fn;
		fn = fn_minus_2 + fn_minus_1;
	}

	/* #################################################################################### */

	/* Ex: So now I now that the fiboacci word (string) is 
        of length 144 so I allocate memory of size 144 + 1 ('\0') to store the 
        fibonacci word (string) in */

	char *nth_fib_word = malloc(1 + sizeof(char) * fn);
	if (nth_fib_word == NULL) return 0;

	nth_fib_word[0] = '0';
	nth_fib_word[1] = '1';	/* Now I have f3 which is '01' */

	/* Ex of how loop works: I already have f3, currently at f4 (thats why I start at j = 4) 
	and want to compute f5. The length of the previous word (f3) is 2. So I loop 2 times 
	appending each character of f3 to the end of f4 to get f5 */

	int prev_len = 1;
	int j;

	for (i = 4; i <= n; i++) 
	{
		for (j = 0; j < prev_len; j++) 
			*(nth_fib_word + strlen(nth_fib_word)) = *(nth_fib_word + j);

		prev_len = strlen(nth_fib_word) - prev_len;
	}

	nth_fib_word[fn + 1] = '\0';

	/* #################################################################################### */

	/* Set the screen background color */
	for (i = 0; i < w * h; i++) image[i] = bc; 


	int k;			/* position k */
	direction dir = up;	/* initially go up */


	for (i = 0, k = 1; i < fn; i++, k++)
	{
		if (y * w + x > w * h || y * w + x < 0) 
		{
			printf("Coordinates outside image window\n");
			return 0;
		}

		draw(x, y, dir, step, w, h, image, fc);
		
		if (nth_fib_word[i] == '0')
		{
			if (k % 2 == 0)
			{
				if (dir == up)
				{
					y += step;
					dir = left;
				}

				else if (dir == left)
				{
					x -= step;
					dir = down;
				}

				else if (dir == down)
				{
					y -= step;
					dir = right;
				}

				else /* if (dir == right)*/
				{
					x += step;
					dir = up;
				}
			}

			else
			{
				if (dir == up)
				{
					y += step;
					dir = right;
				} 
				
				else if (dir == right)
				{
					x += step;
					dir = down;
				}

				else if (dir == down)
				{
					y -= step;
					dir = left;
				}

				else /* if (dir == left) */
				{
					x -= step;
					dir = up;
				}
			}
		}

		else
		{
			if (dir == right) x += step;
			else if (dir == left) x -= step;
			else if (dir == up) y += step;
			else /*if (dir == down)*/ y -= step;
		}	
	}

	return fn;
}

int draw(int x, int y, direction dir, int step, int w, int h, RGB *im, RGB c)
{
	int j;

	if (dir == up)
	{
		for (j = 0; j < step; j++)
		{
			if ((y + j) * w + x > w * h || (y + j) * w + x < 0) return 0;
			I(x, y + j) = c;							/* im[(y + j) * w + x]= c; */
		}
	}

	if (dir == down)
	{
		for (j = 0; j < step; j++)
		{
			if ((y - j) * w + x > w * h || (y - j) * w + x < 0) return 0;
			I(x, y - j) = c;							/* im[(y - j) * w + x]= c; */
		}
	}

	if (dir == right)
	{
		for (j = 0; j < step; j++)
		{
			if (y * w + (x + j) > w * h || y * w + (x + j) < 0) return 0;
			I(x + j, y) = c;							/* im[y * w + (x + j)]= c; */
		}
	}

	if (dir == left)
		for (j = 0; j < step; j++)
		{
			if (y * w + (x - j) > w * h || y * w + (x - j) < 0) return 0;
			I(x - j, y) = c;							/* im[y * w + (x - j)]= c; */
		}

	return 0;
}

