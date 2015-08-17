# Maze Generator
## Build & Run
To build maze generator you need `OpenGL` and `SDL2` installed in your system

build:

	mkdir build && cd build
	../configure
	make

run:
	
	cd src
	./maze

## Usage

Whether you run `./maze` you will be promted about maze settings.

	1) Width x Height: maze dimensions (how many cells it will have)
	2) Fullscreen: Do you want visualization be fullscreen? (note: it's better to set maze dimensions proportional to your screen size)

	If not fullscreen:
	2.1) Window width x height in pixels

	3) Start Point: Enter start point cell coordinates. Must be odd, greater then 0, but smaller then maze width/height
	4) Step Delay(msec): animation delay (vsync enabled by default, so 0 would be ok)
	5) Draw each x frame: draw each framescount % x == 0; must be >= 1. (1 is ok for little mazes, but can be too slow for big ones)

Note: by default exit point is down-left cell.

Once you entered all of these, window will be initialized.

Here are shortcuts to manage visualization process:

	G: start generation process
	S: once generation complete, start seekeng the way out
	
	UP: drop one more frame
	DOWN: drop one less frame
	
	LEFT: decrease animation delay
	RIGHT: increase animation delay

	TAB: stop process and promt maze settings (to terminal)
	ESC: end process and exit