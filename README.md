<h1 align="center">CViN</h1>
<p align="center">The C Visual Novel Engine</p>

## Features

* Multiplatform: Works on Windows, Mac OS X, and Linux! It is easiest to use on Linux.
* Simple: Reads a *.cvin file, which is a custom script format described below.
* Performant: Uses very little memory and is much lighter to run than other Visual Novel engines like RenPy

## How to set up

- You will require CMake to build this, alongside of SDL2, SDL2 Mixer, and SDL2 TTF libraries. These can be downloaded from your local package management repository using `sudo apt-get install libsdl2-2.0-0 libsdl2-dev libsdl2-image-2.0-0 libsdl2-image-dev libsdl2-mixer-2.0-0 libsdl2-mixer-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev`
- To compile, you will only need to run `cmake .` and `make` in the project directory.
- The final executable can be run in any directory structure which contains a game folder, and a game.cvin file. No command line options are needed.

## CVIN Custom Scripting

- CVIN scripts are a simplified visual novel language.
- The scripts are simple to read and understand and are "compiled" upon running CVIN.
- The compiled program is then immediately executed in the CVIN Virtual Machine, which produces the output.
- This scripting language is enough for most linear stories written by this system.
- In the future, the language may include multiple script files, embedded scripting languages like Lua, and the option to create labels and functions to jump to.

## Understanding CVIN Scripts

- CVIN Scripts are straightforward syntactically and semantically.
- All comments are full line comments - you cannot comment at the end of a line.
- These comments begin with `//`
- Variables are declared using the keyword `define` followed by the name of the variable then `as` a type.
- There are 4 primitive types:
    - `SPRITE` is a primitive which represents an image on screen. The image is specified by using the keyphrase `with FILE` and the filename in quotations.
    - `SOUND` is a primitive which contains a short-form WAV sound effect. The sound is specified by using the keyphrase `with FILE` and the filename in quotations.
    - `MUSIC` is a primitive which contains a long-form MP3 or MOD music. The music is specified by using the keyphrase `with FILE` and the filename in quotations.
    - `CHARACTER` is a primitive which contains a character's name and sprite. The image is specified by using the keyphrase `with SPRITE` and the sprite variable. The name is derived from the variable name - so all characters must be named via the variable name.
- Variables behave predictably and all variables are initialized in order of first occurrence. All variables are created at program initialization during the program's "compilation" phase.
- Commands or Statements are basic instructions held within a program.
- These execute from the top down in a file, ignoring variable declaration.
- There are 6 basic commands:
    - `exit` This command exits the program.
    - `show` This command shows a specified sprite or character (with attached sprite). It can be modified to include `as BG` to display as the background, or `at <x> <y>` to be placed at a location. This location is in floating point screen coordinates referring to the center of the image. The screen coordinates designate 0.0, 0.0 to be the top left of the screen.
    - `hide` This command hides a given sprite or character from the screen.
    - `play` This command plays a sound or music track. Music tracks will fade in and out, but sounds will not. Sounds have a 0.5 second buffer period to play.
    - `stop` This command stops a sound or music track. Music tracks will fade out, and sounds will cut.
    - `<Character> says` This command is applied after a character and is used to display dialog to the screen. Dialog WILL NOT move until a mouse click has been registered. There is approximately enough room on screen for a maximum of 4 sentences of medium length.
- With this information, you should be able to create and test out different scripts. Take a look at the `game.cvin` example.