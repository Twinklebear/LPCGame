require "LuaScript"
require "Vector2"

print "Script B!"

script = LPC.LuaScript.GetScript("scriptA")
--vect = LPC.Vector2i(5, 4)
script:CallFunction("Test", 2, 5)