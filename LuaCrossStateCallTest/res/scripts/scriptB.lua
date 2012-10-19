require "LuaRect"
require "LuaCScript"

print "Script B!"

r = LuaRect.new(1, 2, 3, 4)
print "Made rect"
print ("r is " .. r:x() .. ", " .. r:y() .. ", " .. r:w() .. ", " .. r:h())
r.x = 10
print "Changed r.x"
print ("r is " .. r:x() .. ", " .. r:y() .. ", " .. r:w() .. ", " .. r:h())
print "Will try to print r.x"
print (r:accessor("x"))
print "Did i do it?"

--[[
scriptA = LuaCScript.getScript("scriptA")
print "Got script?"
print ("Script B Printing sA name: " .. scriptA:name())
val = scriptA:callFunction("Test", 1, 1, "", 5)
print ("Returned: " .. val)
--]]