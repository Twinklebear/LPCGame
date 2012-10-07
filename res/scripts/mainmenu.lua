--require 'AnimatedImage'
--RequireModule("AnimatedImage")
Script:RequireModule("Input")
--We must use dofile as the file is not in Lua's search path
dofile("../res/scripts/calltest.lua")

function Init()
	--print("Lua search path: " .. package.path)
	print("state init")
	if LPC.Input.JoystickAvailable() then
		print("Joystick is available")
	end
	--Test.TestFunc()
	TestCall()
end
function Free()
	print("state free")
end
function LogicUpdate()
	if LPC.Input.KeyDown(LPC.Input.KEY_Q) then
		print ("You pushed Q! Why would you do that?")
	end
	CheckKey()
	--print("state logic update")
end
function RenderUpdate()
	--print("state render update")
end