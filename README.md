# Snake
This is an implementation of the classic game 'snake' using ncurses for the
linux terminal

## Compilation
Enter repository directory and run

```
make
```

## Instructions
Run program with
```
./snake
```
### Controls
Control the snake with the arrow keys

p - pause game
### Runtime options
-c <color>: change color of snake

-s <speed>: choose speed value between 0-10(default 5)

-w        : Allow wrapping, snake will warp to opposite wall on collision

#### Note
If you have issues with screen flickering, try playing in a buffered terminal multiplexer such as GNU screen or tmux

## Screenshot
![snake](https://cloud.githubusercontent.com/assets/6550505/26068736/85014230-396c-11e7-8ff2-d364d33adbca.png)
