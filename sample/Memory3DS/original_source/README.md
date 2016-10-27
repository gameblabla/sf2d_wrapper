# Memory 3DS

A memory game for Nintendo 3DS.

Have fun playing this game!

---

Using sf2d, sftd and sfil. Music: Upbeat Cinematic Orchestra (2014), Akashic Records [SaReGaMa](https://www.jamendo.com/track/1143942/upbeat-cinematic-orchestra).

---

# Change the music and images

You can change images and the music. 
Images are loaded from sdmc:/3ds/data/Memory3DS/X.png, where X is the number of the png.
0.png is the back of the cards. 1.png, 2.png [...] 10.png are card pairs.
Format: PNG, 56*56 dimensions.

The music is loaded from sdmc:/3ds/data/Memory3DS/music.raw  Format: Mono, Sampling rate: 44100 Hz. Raw (header-less), signed 16-bit PCM.

# Compiling

You should have [portlibs](https://github.com/xerpi/3ds_portlibs) (including [sf2d](https://github.com/xerpi/sf2dlib), [sftd ](https://github.com/xerpi/sftdlib) and [sfil](https://github.com/xerpi/sfillib)) already installed to be able to compile this, [ctrulib](https://github.com/smealum/ctrulib) and [devKitPro](https://devkitpro.org/). Just run **make** and .3dsx/.cia build will come.

# Credits

* everyone who collaborated to ctrulib
* xerpi for sf2d, sftd and sfil
* BernardoGiordano for GUI-Template-for-3DS-homebrews
* SaReGaMa for the music
* and all others!