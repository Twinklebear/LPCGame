--Script:RequireModule("Input")
print("CallTest.lua attempting to require input")
require "Input"
print("CallTest continuing")

function TestCall()
	print("CallTest responding from function TestCall")
end
function CheckKey()
	if LPC.Input.KeyDown(LPC.Input.KEY_W) then
		print("Why ya gotta push w?")
	end
end