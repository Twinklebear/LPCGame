Script:RequireModule("Input")

function TestCall()
	print("CallTest responding from function TestCall")
end
function CheckKey()
	if LPC.Input.KeyDown(LPC.Input.KEY_W) then
		print("Why ya gotta push w?")
	end
end