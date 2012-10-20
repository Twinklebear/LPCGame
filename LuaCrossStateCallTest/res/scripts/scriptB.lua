require "LuaRect"
require "LuaCScript"
--require "scripts/scriptA.lua"

print "Script B!"


print ("Silly enum: " .. LuaRect.ENUM)
r = LuaRect(3, 4, 2, 1)
print (r)
r2  = LuaRect(1, 2, 3, 4)
print (r2)


scriptA = LuaCScript.getScript("scriptA")
print ("Script B Printing sA name: " .. scriptA:name())
val = scriptA:callFunction("Test", 2, 1, r, r2)
print ("Returned: " .. val)
