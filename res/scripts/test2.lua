Script:RequireModule("Input")
Script:RequireModule("Rect")
Script:RequireModule("Entity")
Script:RequireModule("Color")
Script:RequireModule("Text")
Script:RequireModule("Physics")
Script:RequireModule("AnimatedImage")
Script:RequireModule("Vector2")
Script:RequireModule("Window")
Script:RequireModule("Camera")
Script:RequireModule("Math")

--Init the script
function Init()
	print("Test2 Init")
	--Get the object
	animImg = LPC.AnimatedImage("../res/img/animtest.png")
	animImg:Play("idle")
	--Testing out text
	local col = LPC.Color(255, 255, 255)
	text = LPC.Text("Hello from Lua!", "../res/fonts/SourceSansPro-Regular.ttf",
		col, 30)
	textPos = LPC.Rectf(10, 10, 0, 0)
	--Overriding physics module to test joystick motion
	rect = entity:Box()
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
	local speed = 200
	rect.pos.x = rect.pos.x + LPC.Input.GetJoyAxis(0) * speed * deltaT
	rect.pos.y = rect.pos.y + LPC.Input.GetJoyAxis(1) * speed * deltaT
end
--Draw
function Draw(camera)
	LPC.Window.Draw(animImg, LPC.Math.FromSceneSpace(camera, rect))
	LPC.Window.Draw(text, textPos)
end