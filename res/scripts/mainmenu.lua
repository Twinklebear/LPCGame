--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestVector2f"
require "TestRectf"
r = Rectf(10, 4, 32, 16)
v = r:pos()
print ("Made vector from r:pos(): " .. v:x() .. ", " .. v:y())
print ("r width, h: " .. r:w() .. ", " .. r:h())
v.x = 15
v.y = 14
r.pos = v
print ("now r:pos() " .. r:x() .. ", " .. r:y())

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