--Init the script
function Init(object)
	print("Script Init")
	--Attempt to register a module
	--obj = object
	--io.output("test.log")
	--io.write("SCRIPT IS INIT!")
end
--Called each frame
function Update()
	if (LPC.Input.KeyDown(LPC.Input.KEY_R)) then
		print("R is pressed")
	end
	--io.write("SCRIPT IS UPDATE!")
	--print("Script Update")
end
--Use for movement
function Move(deltaT)
	--io.write("SCRIPT IS MOVE!")
	--print("Script Move")
end
--[[
function Draw()
	-- body
end
]]
