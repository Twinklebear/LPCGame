--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestVector2f"
require "TestRectf"

v1 = Vector2f(2, 3)
v2 = Vector2f(5, 6)

print ("v1: " .. v1 .. " \nv2: " .. v2)
print ("v1 / v2: " .. v1 / v2)
print ("v2 / v1: " .. v2 / v1)
print ("v1 * v2: " .. v1 * v2)
print ("v1 + v2: " .. v1 + v2)
print ("v1 - v2: " .. v1 - v2)

if v1 == v2 then
	print "v1 == v2"
else
	print "v1 != v2"
end

print ("v1 / 10: " .. v1 / 10)
print ("10 * v1: " .. 10 * v1)
print ("v1 * 10: " .. v1 * 10)

r = Rectf(0, 1, 10, 5)
r.pos = v1
print (r)

function Init()
	print "\n--------Main Menu Init--------\n"
--	if LPC.Input.JoystickAvailable() then
--		print "Joystick is available"
--	end
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
--	if LPC.Input.KeyDown(LPC.Input.KEY_Q) then
--		print "You pushed Q!"
--	end
--	CheckKey()
end
function RenderUpdate()
end