require "LuaRect"
require "LuaCScript"
require "Vector2f"

print "Script B!"

v = Vector2f(5, 4)
v2 = Vector2f(6, 5)
if v == v2 then
	print "v == v2"
else
	print "v != v2"
end
v = v * 10
print ("Result: " .. v)

--[[
print ("Silly enum: " .. LuaRect.ENUM)
r = LuaRect(3, 4, 2, 1)
print (r)
r2  = LuaRect(1, 2, 3, 4)
print (r2)
print (r2.type)


scriptA = LuaCScript.getScript("scriptA")
print ("Script B Printing sA name: " .. scriptA:name())
r3 = scriptA:callFunction("Test", 1, r, r2)
print "Returned: "
print (r3)
]]