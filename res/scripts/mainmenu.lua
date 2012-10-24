--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestColor"

c1 = Color(140, 200, 10)
c2 = Color(150, 210, 20)
c2.r = 140
c2.g = 55
c2.b = 10
if c1 == c2 then
	print (c1 .. " == " .. c2)
else
	print (c1 .. " != " .. c2)
end

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