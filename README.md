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
snake [-c color] [-s speed] [-w]
```
### Controls
Control the snake with the arrow keys

p - pause game
### Runtime options
-c <color>: change color of snake

-s <speed>: choose speed value between 0-10(default 5)

-w        : Allow wrapping, snake will warp to opposite wall on collision

## Screenshot
![snake](https://cloud.githubusercontent.com/assets/6550505/26068736/85014230-396c-11e7-8ff2-d364d33adbca.png)
