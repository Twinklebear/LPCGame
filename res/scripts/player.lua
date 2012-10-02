LPCRequireModule("Rect")
LPCRequireModule("Entity")
LPCRequireModule("AnimatedImage")
LPCRequireModule("Window")
LPCRequireModule("Camera")
LPCRequireModule("Math")
LPCRequireModule("Input")
LPCRequireModule("Physics")
LPCRequireModule("MotionState")

--Init the script
function Init(object)
	--Get the object
	thisObj = object
	physics = thisObj:GetPhysics()
	--Load image
	playerImg = LPC.AnimatedImage("../res/img/walking.png")
	playerImg:Play("idle-left")
end
function Free()
end
--Called each frame
function Update()
	--Read input
	local direction = -1
	--Horizontal motion
	if LPC.Input.KeyDown(LPC.Input.KEY_H) then
		physics:SetHorizDir(LPC.Math.LEFT)
		direction = LPC.Math.LEFT
	elseif LPC.Input.KeyDown(LPC.Input.KEY_L) then
		physics:SetHorizDir(LPC.Math.RIGHT)
		direction = LPC.Math.RIGHT
	else
		physics:SetHorizDir(LPC.Physics.STOP)
	end
	--Vertical motion
	if LPC.Input.KeyDown(LPC.Input.KEY_J) then
		physics:SetVertDir(LPC.Math.UP)
		direction = LPC.Math.UP
	elseif LPC.Input.KeyDown(LPC.Input.KEY_K) then
		physics:SetVertDir(LPC.Math.DOWN)
		direction = LPC.Math.DOWN
	else
		physics:SetVertDir(LPC.Physics.STOP)
	end

	--Update animation
	UpdateAnimation(direction)
end
--Use for movement
function Move(deltaT)
	physics:Move(deltaT)
end
--Draw
function Draw(camera)
	LPC.Window.Draw(playerImg, LPC.Math.FromSceneSpace(camera, thisObj:Box()))
end
--Update player animation
function UpdateAnimation(direction)
	--Update animation
	playerImg:Update()
	--Check for animation changes
	if physics:State() == LPC.MotionState.IDLE then
		if playerImg:Playing() == "run-left" then
			playerImg:Play("idle-left")
		elseif playerImg:Playing() == "run-right" then
			playerImg:Play("idle-right")
		elseif playerImg:Playing() == "run-up" then
			playerImg:Play("idle-up")
		elseif playerImg:Playing() == "run-down" then
			playerImg:Play("idle-down")
		end
	elseif physics:State() == LPC.MotionState.RUNNING then
		if direction == LPC.Math.LEFT and not (playerImg:Playing() == "run-left") then
			playerImg:Play("run-left")
		elseif direction == LPC.Math.RIGHT and not (playerImg:Playing() == "run-right") then
			playerImg:Play("run-right")
		elseif direction == LPC.Math.UP and not (playerImg:Playing() == "run-up") then
			playerImg:Play("run-up")
		elseif direction == LPC.Math.DOWN and not (playerImg:Playing() == "run-down") then
			playerImg:Play("run-down")
		end
	end
end