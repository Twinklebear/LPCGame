A 2D Game Engine in C++
=======================

This is just a personal project where the goal is trying to get more experience with game engine design
and graphics programming.

The design of the engine is largely inspired by Unity3d, in that the aim is to use an Entity-Component based system and have a graphical scene editor where you can fiddle around and entities' have their behaviors defined by scripts attached to them, in this case Lua scripts since Lua's easy to embed.

## Building
To build the project you'll need Lua, I'm using 5.1 but more recent versions may be ok?, along with SDL2.0, which you may need to compile yourself. The JsonCPP library is included as the amalgamated version under src/external. If you 
encounter any issues feel free to ask or open an issue.

Note that if you plan to use msvc to compile the project you must use the November CTP compiler to have support for variadic templates. 

## Documentation/Reference:
- [Code](http://twinklebear.github.com/LPCGame/)
- [SDL 2.0](http://wiki.libsdl.org/moin.cgi/FrontPage)
- [Lua 5.1 Reference Manual](http://www.lua.org/manual/5.1/)
- [JsonCPP](http://jsoncpp.sourceforge.net/)
