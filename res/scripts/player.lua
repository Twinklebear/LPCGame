require "Entity"
require "Physics"
require "Rectf"
require "Vector2f"
require "Camera"
require "Color"
require "Timer"
require "Image"
require "Window"
require "Math"
require "State"
require "AnimatedImage"
require "Text"
require "Input"
require "Debug"

--Init the script
function Init()
	physics = entity:physics()
	--Load image
	playerImg = AnimatedImage("../res/img/walking.png")
	playerImg:play("idle-left")
end
function Free()
end
--Called each frame
function Update()
	--Read input
	local direction = -1
	--Horizontal motion
	if Input.keyDown(Input.KEY_A) then
		physics.horizDir = Math.LEFT
		direction = Math.LEFT
	elseif Input.keyDown(Input.KEY_D) then
		physics.horizDir = Math.RIGHT
		direction = Math.RIGHT
	else
		-- -1 corresponds to Physics::STOP
		physics.horizDir = -1
	end
	--Vertical motion
	if Input.keyDown(Input.KEY_W) then
		physics.vertDir = Math.UP
		direction = Math.UP
	elseif Input.keyDown(Input.KEY_S) then
		physics.vertDir = Math.DOWN
		direction = Math.DOWN
	else
		-- -1 corresponds to Physics::STOP
		physics.vertDir = -1
	end

	--Update animation
	UpdateAnimation(direction)
end
--Use for movement
function Move(deltaT)
	--physics:move(deltaT)
end
--Draw
function Draw(camera)
	--if not entity:IsUiElement() then
		--With the changes made in the math class to std::weak_ptr<Camera>
		--We can no longer use the luabind library.
		--LPC.Window.Draw(playerImg, LPC.Math.FromSceneSpace(camera, physics:Box()))
	--else
		Window.draw(playerImg, Math.fromSceneSpace(camera, physics:box()))
	--end
end
--Update player animation
function UpdateAnimation(direction)
	--Update animation
	playerImg:update()
	--Check for animation changes
	--Motion state isn't implemented as a lua lib
	--[[
	if physics:state() == MotionState.IDLE then
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
		if direction == LPC.Math.LEFT and playerImg:Playing() ~= "run-left" then
			playerImg:Play("run-left")
		elseif direction == LPC.Math.RIGHT and playerImg:Playing() ~= "run-right" then
			playerImg:Play("run-right")
		elseif direction == LPC.Math.UP and playerImg:Playing() ~= "run-up" then
			playerImg:Play("run-up")
		elseif direction == LPC.Math.DOWN and playerImg:Playing() ~= "run-down" then
			playerImg:Play("run-down")
		end
	end
	]]
end
function OnClick()
	print "Player clicked!"
	--Toggle rendering
	if not entity:render() then
		entity:render(true)
	else
		entity:render(false)
	end
	--Toggle ui status
	--We can't do this, because Drawing is done in the lua script
	--[[
	if not entity:IsUiElement() then
		entity:IsUiElement(true)
	else
		entity:IsUiElement(false)
	end
	]]
end