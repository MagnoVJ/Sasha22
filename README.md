# Sasha22
The idea of this software is to serve as a tool for rendering anything related to what today became common to call computer generated graphics. 
For exemple: 2D and 3D Primitives, Textured 3D Models, Graphs, Lighting, etc...
With every new functionality the hope is that the software becomes more and more powerful serving as a platform for creating all sorts of projects related to computer graphics.

It's being written primarly in C/C++ with OpenGL as graphics API.

![](https://github.com/MagnoVJ/Sasha22/blob/main/example1.jpg)

## How to run the Application
This application is compiled using the C/C++ compiler from Microsoft Visual Studio 2022. All you have to do to compile/execute it, is to install the Microsoft Visual Studio 2022 with the C/C++ module.

After that, use the Developer Command Prompt or PowerShell for VS 2022, navigate to the root project folder and type:
`msbuild.exe Sasha22.sln /property:Configuration=Debug /property:Platform=x64` for debug or
`msbuild.exe Sasha22.sln /property:Configuration=Release /property:Platform=x64` for release

Execute the application by calling: `./x64/Debug/Sasha22.exe` in your terminal.

This repository does not contain the graphic assets of the application.
