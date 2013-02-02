A 2D Game Engine in C++
=======================

This is just a personal project of mine where I'm trying to get more experience with game engine design
and graphics programming. My current focus is finishing up the Lua embedding, after which I'll work on dropping down to OpenGL for rendering (currently using SDL2), integrating Box2d and finishing the editor.

The main goal of the project is for me to get experience working on a large scale application and explore
areas of programming I'm interested in, but I'm always open to contributors who also want to learn.

The design of the engine is largely inspired by Unity3d, in that I aim to migrate to an Entity-Component based system and have a graphical scene editor where you can fiddle around and entities' have their behaviors 
defined by scripts attached to them, in this case Lua scripts since Lua's easy to embed.

## Building
To build the project you'll need the Lua 5.1 (headers & libs) along with SDL2.0, which you may need to compile yourself. The JsonCPP library is included as the amalgamated version under src/external. If you 
encounter any issues feel free to ask or open an issue.

## Documentation/Reference:
- [Code](http://twinklebear.github.com/LPCGame/)
- [SDL 2.0](http://wiki.libsdl.org/moin.cgi/FrontPage)
- [Lua 5.1 Reference Manual](http://www.lua.org/manual/5.1/)
- [JsonCPP](http://jsoncpp.sourceforge.net/)
