# Swords Scrolls and Knuckles

![Swords Scrolls and Kuckles](https://img4.hostingpics.net/pics/717583Logo2.png "Swords Scrolls and Knuckles")

## Compilation

### Dependencies

Both Windows and Linux versions require the same dependencies:
 * Cmake (> 2.6)
 * Ogre 1.10
 * OIS (Generally presentend as a dependency of Ogre)
 * OpenAL
 * PyBind ( -> Python 2.7)

### Windows

To compile `Swords Scrolls and Knuckles` on a Windows NT system, open CMake and create a Visual Studio solution for the project.
You will maybe need to set some environment variables accordingly to your dependencies home directory.

### Linux

To compile `Swords Scrolls and Knuckles` on Unix-like system, open a terminal and type:

```bash
mkdir build && cd build
cmake ..
make
```

Now, you can play the game by typing `./ssk` from the project directory! :)
