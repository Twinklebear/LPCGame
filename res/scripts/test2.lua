--Init the script
function Init(object)
	print("Test2 Init")
	--img = LPC.Image("../res/images/npc.png")
	img = LPC.Window.LoadImage("../res/img/animtest.png")
	--r = LPC.Rectf(80, 80, 32, 32)
	physics = object:GetPhysics()
	--Testing Rect::pos accessor
	--print("Rect x: " .. r.pos.x .. " y: " .. r.pos.y)
	--Testing some clip stuff
	clipNum = 0
end
--Called each frame
function Update()
	--Playing with clips
	if (LPC.Input.KeyDown(LPC.Input.KEY_R)) then
		clipNum = clipNum + 1
	end
	if (clipNum > 8) then
		clipNum = 0
	end
	--Testing motion
	if (LPC.Input.KeyDown(LPC.Input.KEY_UP)) then
		physics:SetVertDir(LPC.Math.UP)
	elseif (LPC.Input.KeyDown(LPC.Input.KEY_DOWN)) then
		physics:SetVertDir(LPC.Math.DOWN)
	else
		physics:SetVertDir(LPC.Physics.STOP)
	end
	if (LPC.Input.KeyDown(LPC.Input.KEY_RIGHT)) then
		physics:SetHorizDir(LPC.Math.RIGHT)
	elseif (LPC.Input.KeyDown(LPC.Input.KEY_LEFT)) then
		physics:SetHorizDir(LPC.Math.LEFT)
	else
		physics:SetHorizDir(LPC.Physics.STOP)
	end
end
--Use for movement
function Move(deltaT)
	physics:Move(deltaT)
end
--Draw
function Draw(camera)
	local pos = LPC.Math.FromSceneSpace(camera, physics:Box())
	LPC.Window.Draw(img, pos, img:Clip(clipNum))
end