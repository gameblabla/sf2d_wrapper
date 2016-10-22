sf2d wrapper for 3ds homebrew games
===================================

It's a simple shim library that should allow you to play sf2d homebrew games on your PC.
It also provides "emulation" for some functions provided by ctrulib.

Obviously, the game in question needs to have its source code available so it can be recompiled.
Also, pray so that your games in question does not use low-level GPU functions.

For now, it is a simple proof-of-concept but i'll try to work more on it to improve usability
and compatibility.

The library was tested against Memory3DS, a 3DS homebrew game by Omegadrien.
Since this game uses some ctrulib sound functions that are not yet supported, 
they had to be disabled but other than that, it worked out of the box.

Using this library, timer works correctly, touching works properly
and there are no graphical issues.
Text however is not displayed properly because SDL_ttf doesn't allow to change the size of a text
without closing/open a new font again. (which is ridiculous lol)