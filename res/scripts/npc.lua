require "Entity"
require "Input"
require "Rect"
require "AnimatedImage"
require "Vector2"
require "Physics"
require "Window"
require "Camera"
require "Math"
require "Debug"

--Init the script
function Init()
	print "Test 2 init"
	img = LPC.AnimatedImage("../res/img/animtest.png")
	img:Play("idle")
	--rect = entity:Box()
	physics = entity:GetPhysics()
	LPC.Debug.Log("NPC Init: Debugging test!")
end
function Free()
	print "NPC Free"
end
--Called each frame
function Update()
end
--Use for movement
function Move(deltaT)
	--local speed = 200
	--rect.pos.x = rect.pos.x + LPC.Input.GetJoyAxis(0) * speed * deltaT
	--rect.pos.y = rect.pos.y + LPC.Input.GetJoyAxis(1) * speed * deltaT
	--This gives some odd behaviors
	local v = LPC.Vector2f(0, 0)
	v.x = LPC.Input.GetJoyAxis(0)
	v.y = LPC.Input.GetJoyAxis(1)
	physics:SetDirection(v)
	physics:Move(deltaT)
end
--Draw
function Draw(camera)
	--With the changes made in the math class to std::weak_ptr<Camera>
	--We can no longer use the luabind library.
	--LPC.Window.Draw(img, LPC.Math.FromSceneSpace(camera, physics:Box()))
	LPC.Window.Draw(img, physics:Box())
end