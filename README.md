# Flappy Bird
<img src="https://github.com/ghulam2545/flappy-bird/blob/master/out/out-1.PNG" width=400>  <img src="https://github.com/ghulam2545/flappy-bird/blob/master/out/out-2.PNG" width=400>


## Overview
"Flappy Bird is a mobile game developed by Vietnamese video game artist and programmer Dong Nguyen under his game development company Gears." (Wikipedia)<br>
This perticular game also inspired from similar flappy bird game. It has required functionality to work properly.You might interested to play in your spare and have fun.<br>

It includes:
1. Our main character flying bird.
2. Up and down obstacle texture (pipe).
3. Buttons to controll bird and restart the game.
4. Score count and hitting sound etc.


## Compilation
I have configured CMake with VSCode.
```
cmake -G "MinGW Makefiles" .
make
./flappy-bird.exe
```
## Dependency
Most parts are primitive c++ code and OOPs, also I have used SFML (An Open Source Library) for achieving window creation and other 2D rendering stuff.

<strong>SFML (https://www.sfml-dev.org/)
