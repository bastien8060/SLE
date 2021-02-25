# SLE - SlimLightEngine Project

SlimLightEngine Built with C++. Rendering + 3D Engine. Uses backward ray tracing. Communicate to UI/Output stream through socket. WIP.

## Disclaimers 

This project is not finished yet. It is a work in progress and needs a lot more work in order to be something functionnal.


## Installation

```
$ git clone https://github.com/bastien8060/SLE
$ cd SLE
$ cd builds
$ # run the build you want to run in this folder. The binaries are located here.
```

## Build

### Linux & Gnu/Linux

If you are running under Linux or GNU/Linux on an architecture or system that doesn't support the builds, then you can compile yourself the code with a single command. This may not apply to MacOS.

```
$ git clone https://github.com/bastien8060/SLE
$ cd SLE
$ ./build.sh
$ cd builds
$ # run the build you want to run in this folder. The binaries you just built are located here.
```

### Other OS
If you are running under another OS, then you can compile the code yourself with a C++ compiler. The file to compile is `main.cpp`.
In case you are running under any issues, feel free to post a new issue in the issues tab of this repository. We might be able to cross compile the code for your system or find a solution.

**Edit: Since last commit, Windows support has been temporarily dropped while a fix is being addressed to it. When it will work again, GNU/Linux and Windows will have two separate branches.**


## Usage/Demo
If you wish you can try a demo. Go ahead and compile the main.cpp script. Then launch it. There we go, the server is started! Now you can go ahead and run `viewer.py` which connects to the server by UDP. Make sure port number 6770 is free on your computer so the server can bind to it. You will also need to install the Pyxel module for python3. By default, viewer will draw a polygon, but you can change it with the SLE protocol.

### SLE Protocol

For this project, we made a custom protocol and a custom parser/interpreter. It is the SLE protocol. Here's how to use it:

`@[]` means we are going to draw/render something (eg. `polygon`, `circle`, `line`, `dot`)

`#[]` means we are setting some information about the environment. Only the screen size was thought about as of now, but we will eventually add support for lights/shadows etc...

Informations inside a `{}` are information telling what a shape is like, when combined with a draw action. With a Information action (`#[]`), it sets the value.

The protocol can be split and sent in bits. Then it can be effortlessly put back into a single request. To mark the end of the request, we send `@@@` at the end of a request or as another request.

When drawing circles two parameters are needed: `r` for radius and `c` for midpoint coordinates. For polygons one parameters are needed: `c` each points coordinates.

A basic example for valid requests is this:

```
@[polygon]{c:10,56|50,63|32,90;}
@[circle]{r:50;c:10,56;}
@@@
```

For now, the server only support parsing one request at a time.

#### By @Bastien8060 and @SBruh314
