--Init the script
function Init(object)
	print("Test2 Init")
	img = LPC.Image("../res/images/npc.png")
	r = LPC.Rectf(80, 80, 32, 32)
	print("Rect: x:" .. r:X() .. " y: " .. r:Y() .. " w: " .. r:W() .. " h: " .. r:H())
	--Attempt to register a module
	--obj = object
	--io.output("test.log")
	--io.write("SCRIPT IS INIT!")
end
--Called each frame
function Update()
	if (LPC.Input.KeyDown(LPC.Input.KEY_R)) then
		print("Test2 R is pressed")
	end
	--io.write("SCRIPT IS UPDATE!")
	--print("Script Update")
end
--Use for movement
function Move(deltaT)
	--io.write("SCRIPT IS MOVE!")
	--print("Script Move")
end
--Draw
function Draw(camera)
	--print ("Test2 Draw")
	LPC.Window.Draw(img, r)
end