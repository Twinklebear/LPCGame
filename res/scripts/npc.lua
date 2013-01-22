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

--Init the script
function Init()
	print "Test 2 init"
	img = AnimatedImage("../res/img/animtest.png")
	img:play("idle")
	--rect = entity:Box()
	physics = self:physics()
	Debug.log("NPC Init: Debugging test!")
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
	local v = Vector2f(0, 0)
	v.x = Input.GetJoyAxis(0)
	v.y = Input.GetJoyAxis(1)
	physics:setDirection(v)
	physics:move(deltaT)
end
--Draw
function Draw(camera)
	--With the changes made in the math class to std::weak_ptr<Camera>
	--We can no longer use the luabind library.
	--LPC.Window.Draw(img, LPC.Math.FromSceneSpace(camera, physics:Box()))
	Window.draw(img, Math.fromSceneSpace(camera, physics:Box()))
end