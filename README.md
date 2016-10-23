sf2d wrapper for 3ds homebrew games
===================================

It's a simple shim library that should allow you to play sf2d homebrew games on your PC.
It also provides "emulation" for some functions provided by ctrulib.

Obviously, the game in question needs to have its source code available so it can be recompiled.
Also, pray so that your games in question does not use low-level GPU functions or else it will not work properly.

The library was tested against Memory3DS, a 3DS homebrew game by Omegadrien.
Memory3DS works quite well using this library.
This however isn't the case for all the other homebrew games... (like Minicraft3DS for example)

Text however is not displayed properly because SDL_ttf doesn't allow to change the size of a text
without closing/open a new font again. (which is ridiculous lol)


Some functions were also taken in part or directly from ctruilib and sf2dlib :
crtuilib has no license (i assume public domain ?) and sf2dlib is under the MIT license, copyright Sergi Granell (xerpi).