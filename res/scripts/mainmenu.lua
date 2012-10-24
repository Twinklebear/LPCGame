--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestTimer"

timer = Timer()
timer:start()
if timer:started() then
	print "Timer started" 
	timer:pause()
else
	print "Timer stopped"
end

if timer:paused() then
	print "Timer paused" 
	timer:unpause()
else
	print "Timer running"
end
print ("# ticks: " .. timer:ticks())
print "Will wait 300ms"
while timer:ticks() < 300 do
end
print ("# ticks: " .. timer:ticks())

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