LPCRequireModule("Input")
LPCRequireModule("Rect")
LPCRequireModule("Entity")
LPCRequireModule("Color")
LPCRequireModule("Text")
LPCRequireModule("Physics")
LPCRequireModule("AnimatedImage")
LPCRequireModule("Vector2")
LPCRequireModule("Window")
LPCRequireModule("Camera")

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
	--Overriding physics module to test joystick motion
	rect = LPC.Rectf(100, 100, 32, 32)
	--Check if joystick is haptic
	if (LPC.Input.JoySupportsHaptic()) then
		print("Joy supports haptic")
	else
		print("No haptic support")
	end
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
	--[[
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
	]]
	--Testing joystick button input
	if (LPC.Input.GetJoyButton(0)) then
		print("Joy button 0 down")
	elseif (LPC.Input.GetJoyButton(1)) then
		print("Joy button 1 down")
	elseif (LPC.Input.GetJoyButton(2)) then
		print("Joy button 2 down")
	elseif (LPC.Input.GetJoyButton(3)) then
		print("Joy button 3 down")
	elseif (LPC.Input.GetJoyButton(4)) then
		print("Joy button 4 down")
	elseif (LPC.Input.GetJoyButton(5)) then
		print("Joy button 5 down")
	elseif (LPC.Input.GetJoyButton(6)) then
		print("Joy button 6 down")
	elseif (LPC.Input.GetJoyButton(7)) then
		print("Joy button 7 down")
	elseif (LPC.Input.GetJoyButton(8)) then
		print("Joy button 8 down")
	elseif (LPC.Input.GetJoyButton(9)) then
		print("Joy button 9 down")
	elseif (LPC.Input.GetJoyButton(10)) then
		print("Joy button 10 down")
	end
	if (not (LPC.Input.GetJoyHat(0) == LPC.Input.HAT_CENTERED)) then
		print("Joy hat position: " .. LPC.Input.GetJoyHat(0))
	end
end
--Use for movement
function Move(deltaT)
	--physics:Move(deltaT)
	local speed = 200
	rect.pos.x = rect.pos.x + LPC.Input.GetJoyAxis(0) * speed * deltaT
	rect.pos.y = rect.pos.y + LPC.Input.GetJoyAxis(1) * speed * deltaT
end
--Draw
function Draw(camera)
	--local pos = LPC.Math.FromSceneSpace(camera, physics:Box())
	--LPC.Window.Draw(img, pos, img:Clip(clipNum))
	--LPC.Window.Draw(animImg, pos)
	LPC.Window.Draw(animImg, rect)
	LPC.Window.Draw(text, textPos)
end