require "LuaScript"
require "Vector2"

print "Script B!"

scriptA = LPC.LuaScript.GetScript("scriptA")
print ("Script name: " .. scriptA:Name() .. " file: " .. scriptA:File())
--vect = LPC.Vector2i(5, 4)
--test = "Some Test string"
--print (test)
--script:CallFunction("Test", 2, 5)
GenericCall("Test", 1, 0, scriptA, scriptA:Name(), 5)