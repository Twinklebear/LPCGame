--Init the script
function Init(object)
	print("Test2 Init")
	--img = LPC.Image("../res/images/npc.png")
	img = LPC.Window.LoadImage("../res/img/animtest.png")
	r = LPC.Rectf(80, 80, 32, 32)
	--Testing some clip stuff
	clipNum = 0
end
--Called each frame
function Update()
	if (LPC.Input.KeyDown(LPC.Input.KEY_R)) then
		clipNum = clipNum + 1
	end
	if (clipNum > 8) then
		clipNum = 0
	end
end
--Use for movement
function Move(deltaT)

end
--Draw
function Draw(camera)
	LPC.Window.Draw(img, r, img:Clip(clipNum))
end