# Heart of the Alien
Heart of the Alien port for Vita. Based on the 1.2.2. version created by Gil Megidish .

# Change log

v1.2.2
---------
    
- Initial port of Reminiscence game.

- Fix fullscreen mode.

- Fix button mapping

# Requirements
A Vita system with Henkaku installed to run homebrew.

Install the vpk file in your Vita

Put the original data files in the folder **ux0:data/SOMO00003/DATA**

Original files can be downloaded in serveral sites, for example:

`https://github.com/ytmytm/beos-heartofthealien`

#Button configuration

To control your character, you may use either set of cursor keys.
        Moreover, here are extra keys available:

        Z                      shoot, keep down in order to run
        X                      use your whip
        C                      jump
        F5                     quicksave (1 slot)
        F7                     quickload
        ESC                    leave game, or skip animation


Arrow Keys:     move Alien

Left stick:     move Alien

X:              shoot, keep down in order to run

O :             jump

□ :             use your whip

Start:          exit

Select:         acelerate motion


# How to compile

You need the vitasdk installed and SDL libraries to compile this game. I used this commit:

https://github.com/Cpasjuste/SDL-Vita/commit/361262981e260bceb8a0f63195d80b778aa5e141

Simply, launch the commnad:

`make`

#Enchancements

Feel free to create new issues and pull request to enchance this fantastic game.

# Credits

Gil Megidish  for the PC version.

# Thanks to

Xerpi for the SDL2 port for Vita. (https://github.com/xerpi)

Cpasjuste for solving some issues of SDL2 port. (https://github.com/Cpasjuste)

# Original version

Original version: http://hota.sourceforge.net/
