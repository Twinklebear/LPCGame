require "LuaRect"
require "LuaCScript"

print "Script B!"


print ("Silly enum: " .. LuaRect.ENUM)
r = LuaRect(3, 4, 2, 1)
print (r)
r:set(1, 2, 3, 4)
print (r)

--[[
scriptA = LuaCScript.getScript("scriptA")
print ("Script B Printing sA name: " .. scriptA:name())
val = scriptA:callFunction("Test", 1, 1, r)
print ("Returned: " .. val)
]]