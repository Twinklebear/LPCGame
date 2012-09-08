--Init the script
function Init(object)
	print("Test2 Init")
	--img = LPC.Window.LoadImage("../res/img/strip.png")
	--animImg = LPC.Window.LoadAnimatedImage("../res/img/animtest.png")
	animImg = LPC.AnimatedImage("../res/img/animtest.png")
	--Testing out text
	local col = LPC.Color(255, 255, 255)
	text = LPC.Text("Hello from Lua!", "../res/fonts/SourceSansPro-Regular.ttf",
		col, 30)
	textPos = LPC.Rectf(10, 10, 0, 0)
	--r = LPC.Rectf(80, 80, 32, 32)
	physics = object:GetPhysics()
	--Testing Rect::pos accessor
	--print("Rect x: " .. r.pos.x .. " y: " .. r.pos.y)
	--Testing some clip stuff
	clipNum = 0
end
function Free()
end
--Called each frame
function Update()
	--Playing with clips
	if (LPC.Input.KeyDown(LPC.Input.KEY_R) and animImg:Playing() == "idle") then
		--clipNum = clipNum + 1
		animImg:Play("run")
	elseif (LPC.Input.KeyDown(LPC.Input.KEY_R) and animImg:Playing() == "run") then
		animImg:Play("idle")
	end
	--Update animation
	animImg:Update();

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
	--LPC.Window.Draw(img, pos, img:Clip(clipNum))
	LPC.Window.Draw(animImg, pos)
	LPC.Window.Draw(text, textPos)
end