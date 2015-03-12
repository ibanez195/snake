#include <ncurses.h>
#include <time.h>
#include <stdlib.h>


typedef struct
{
	int y;
	int x;
}cell;

// TODO: slithering over scoreboard writes over text there fix dat
int main(int argc, char* argv[])
{

	int direction = 2;
	int size = 3;
	cell food = {10,10};
	bool grow = false;
	bool lose = false;

	// set up speed by looking at arguments
	int speed;
	int delay;
	if(argc > 1){
		speed = atoi(argv[1]);
		if(speed > 10){
			speed = 10;
		}
		delay = 100-(10*(speed-1));
	}else{
		delay = 60;
	}

	initscr();
	cbreak();
	noecho();
	curs_set(0); // Hide cursor
	nodelay(stdscr, TRUE); // Don't wait for keypresses with getch()
	start_color();
	use_default_colors();
	init_pair(1, COLOR_WHITE, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);

	mvaddch(food.y, food.x, '*');

	// Allocate memory for snake cell array
	cell* snake = malloc(size*sizeof(cell));
	snake[0] = (cell){1,3};
	snake[1] = (cell){1,2};
	snake[2] = (cell){1,1};

	attron(COLOR_PAIR(1));
	mvaddch(snake[0].y, snake[0].x, '*');	
	mvaddch(snake[1].y, snake[1].x, '*');	
	mvaddch(snake[2].y, snake[2].x, '*');	
	attroff(COLOR_PAIR(1));

	int i;
	for(i=0; i < LINES; i++)
	{
		attron(COLOR_PAIR(2));
		mvprintw(0, 0, "%0*s", COLS, " ");
		attroff(COLOR_PAIR(2));
	}

	attron(COLOR_PAIR(2));
	mvprintw(0, 0, "Score: %d", size-3);
	attroff(COLOR_PAIR(2));

	while(true)
	{

		if(lose)
		{
			mvprintw(LINES/2,(COLS/2)-8,"You suck and lose");
			break;
		}
		// Detect collision with food and put it in a new place
		if(snake[0].y == food.y && snake[0].x == food.x)
		{
			grow = true;
			bool valid = false;
			while(!valid)
			{
				valid = true;
				int newX = rand() % COLS;
				// LINES-1 and newY++ are to make sure the top row is left clear
				int newY = rand() % (LINES-1);
				newY++;

				food = (cell){newY,newX};

				int i = 0;
				for(i;i<size;i++)
				{
					if(snake[0].y == food.y && snake[i].x == food.x)
					{
						valid = false;
					}
				}
			}
			mvaddch(food.y, food.x, '*');
		}
		// arrow keys return 3 characters when using getch()
		// \033, [, and a letter A-D indicating which key
		// this skips the first two characters
		if(getch() == '\033')
		{
			// ignore character '[]'
			getch();
			switch(getch())
			{
				case 'A':
					if(direction != 1)
						direction = 0;
					break;
				case 'B':
					if(direction != 0)
						direction = 1;
					break;
				case 'C':
					if(direction != 3)
						direction = 2;
					break;
				case 'D':
					if(direction != 2)
						direction = 3;
					break;
			}
		}
		if(!grow)
		{
			// Draw over trailing character
			mvaddch(snake[size-1].y, snake[size-1].x, ' ');
			int i=size-1;
			// Shift all cells except the first up one position
			for(i;i>0;i--)
			{
				snake[i].x = snake[i-1].x;	
				snake[i].y = snake[i-1].y;	
			}
			// Use direction to change position of front cell
			switch(direction)
			{
				case 0:
					snake[0].y--;
					break;
				case 1:
					snake[0].y++;
					break;
				case 2:
					snake[0].x++;
					break;
				case 3:
					snake[0].x--;
					break;
			}
			// Draw new leading character
			attron(COLOR_PAIR(1));
			mvaddch(snake[0].y, snake[0].x, '*');
			attroff(COLOR_PAIR(1));
		}else{
			// Increase size and realloc memory for snake
			size++;
			cell *temp = realloc(snake, size*sizeof(cell));	

			attron(COLOR_PAIR(2));
			mvprintw(0, 0, "Score: %d", size-3);
			attroff(COLOR_PAIR(2));

			// Check that reallocation was successful
			if(temp!=NULL)
			{
				snake = temp;
			}else{
				free(snake);
				mvprintw(20,20,"Error allocating memory to temp");
				return 1;
			}

			// Shift all cells except the first up one position
			int i=size-1;
			for(i; i>0; i--)
			{
				snake[i] = snake[i-1];
			}

			// Use direction to change position of front cell
			switch(direction)
			{
				case 0:
					snake[0].y--;
					break;
				case 1:
					snake[0].y++;
					break;
				case 2:
					snake[0].x++;
					break;
				case 3:
					snake[0].x--;
					break;
			}
			// Draw new character reset growth
			attron(COLOR_PAIR(1));
			mvaddch(snake[0].y, snake[0].x, '*');
			attroff(COLOR_PAIR(1));
			grow = false;
		}	

		// do collision detection
		if(snake[0].y >= LINES || snake[0].y < 1 || snake[0].x >= COLS || snake[0].x < 0)
		{
			lose = true;
		}else{
			int a = 1;
			for(a;a<size;a++)
			{
				if(snake[0].x == snake[a].x && snake[0].y == snake[a].y)
				{
					lose = true;
					break;
				}
			}
		}
		
		refresh();
		usleep(delay*1000);
	}
	nodelay(stdscr, FALSE);

	getch();
	endwin();
}
