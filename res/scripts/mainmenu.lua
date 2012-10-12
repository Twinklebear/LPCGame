require "Input"
require "scripts/calltest.lua"

function Init()
	print "\n--------Main Menu Init--------\n"
	if LPC.Input.JoystickAvailable() then
		print "Joystick is available"
	end
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	if LPC.Input.KeyDown(LPC.Input.KEY_Q) then
		print "You pushed Q!"
	end
	CheckKey()
end
function RenderUpdate()
end