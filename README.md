# Pixel Drawer 
Simpe pixel art maker tool using GLES2. Works on Ubuntu with X11 without specifying a toolchain. Ported to iMX6 yocto/wayland
The goal of this project was to practice creating and porting an openGLESv2 app from x86_64/X11 to ARVv7/Wayland on an evaluation board used in automotive industry.

<p float="left">
  <img src="https://github.com/balinth0rvath/pixel-drawer/blob/master/misc/pixel.png" width="200" />
  <img src="https://github.com/balinth0rvath/pixel-drawer/blob/master/misc/pixel2.png" width="200" /> 
</p>

## The target<br/>
BD-SL-i.MX6 [Sabre Lite](https://boundarydevices.com/wiki/bd-sl-imx6/)
## Toolchain<br/>
Yocto Poky 2.5.3 Sumo was used to generate SD image and SDK. 
[More about it](https://boundarydevices.com/wiki/yocto-for-nitrogen6/). <br/>
Distro fslc-xwayland was used, it is mandatory to get cross compile succeded. 
## Compile to host<br/>
Compilation can be done by simply calling cmake and then make from the folder of CMakelists.txt  
Before compiling, make sure the following libs are installed:
* X11
* EGL
* GLESv2
#### Compile steps
```sh
$ mkdir _build
$ cd _build
$ cmake ..
$ make
```
## Cross compile to iMX6<br/>
CMake is used to cross compiling. SDK must be under /opt/fslc-xwayland/2.5.3
Before compiling, make sure the following libs are installed:
* wayland-client
* EGL
* GLESv2
* wayland-egl
#### Compile steps
```sh
$ mkdir _build
$ cd _build
$ cmake .. -DTARGET_SDK=IMX6 
$ make
```
