--require "Vector2"
--lets us use LuaRect.x as luaRect.x
--luaRect = require "LuaRect"
require "LuaRect"
require "LuaCScript"
--require "scripts/test.lua"

print "Script B!"

--tScript = LuaCScript.New("../res/scripts/test.lua")
--print "made tScript?"
--print ("Name of tScript: " .. tScript:Name())
scriptA = LuaCScript.GetScript("scriptA")
print "Got script?"
print ("Script B Printing sA name: " .. scriptA:Name())

--test = "Some Test string"
--print (test)
--script:CallFunction("Test", 2, 5)
--val = GenericCall("Test", 1, 1, scriptA, scriptA:Name(), 5)
--r = LuaRect.new()
--r:set(20, 30, 40, 50)
--val = GenericCall("Test3", 4, 1, scriptA:Name(), 1, 2, "A String!", r)
--print ("Got return val: " .. val)

--vector = LPC.Vector2i(10, 5)
--print ("Created v2: " .. vector.x .. ", " .. vector.y)
--GenericCall("TestVector", 1, 0, scriptA, scriptA:Name(), vector)