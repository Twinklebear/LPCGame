require "Vector2"
require "LuaScript"

print "Script B!"

scriptA = LPC.LuaScript.GetScript("scriptA")
--vect = LPC.Vector2i(5, 4)
--test = "Some Test string"
--print (test)
--script:CallFunction("Test", 2, 5)
--val = GenericCall("Test", 1, 1, scriptA, scriptA:Name(), 5)
val = GenericCall("Test3", 3, 1, scriptA:Name(), 1, 2, "A String!")
print ("Got return val: " .. val)

--vector = LPC.Vector2i(10, 5)
--print ("Created v2: " .. vector.x .. ", " .. vector.y)
--GenericCall("TestVector", 1, 0, scriptA, scriptA:Name(), vector)