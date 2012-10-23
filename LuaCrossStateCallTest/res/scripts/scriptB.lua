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

--[[
--Thrash the garbage collector to make sure __gc is called
for i = 1, 500 do
	local v3 = Vector2f(1, 1)
end
]]

v = v2 * v
print ("Result of v = v2 * v " .. v)

print ("Result of v / 10: " .. (v / 10))

--print ("Silly enum: " .. LuaRect.ENUM)
r = LuaRect(3, 4, 2, 1)
print ("I made a rect!: " .. r .. " YAY")
r.pos = Vector2f(5, 5)
print (r:pos())

--[[
scriptA = LuaCScript.getScript("scriptA")
r3 = scriptA:callFunction("Test", 1, r)
print "Returned: "
print (r3)
]]