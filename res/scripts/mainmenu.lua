--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestInput"

function Init()
	print "\n--------Main Menu Init--------\n"
	if Input.joystickAvailable() then
		print "joystickAvailable"
	end
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	if Input.keyDown(Input.KEY_Q) then
		print "Q down"
	end
	if Input.keyDown("w") then
		print "W down"
	end
	if Input.joyAxis(0) > 0 or Input.joyAxis(0) < 0 then
		print ("Joy axis 0: " .. Input.joyAxis(0))
	end
	if Input.joyAxis(1) > 0 or Input.joyAxis(1) < 0 then
		print ("Joy axis 1: " ..Input.joyAxis(1))
	end
	print (Input.joyHat(0))
end
function RenderUpdate()
end