require "LuaRect"
require "LuaCScript"

print "Script B!"


print ("Silly enum: " .. LuaRect.ENUM)
r = LuaRect(3, 4, 2, 1)
print (r)
r2  = LuaRect(1, 2, 3, 4)
print (r2)


scriptA = LuaCScript.getScript("scriptA")
print ("Script B Printing sA name: " .. scriptA:name())
r3 = scriptA:callFunction("Test", 1, r, r2)
print "Returned: "
print (r3)
