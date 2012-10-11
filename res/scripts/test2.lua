require "Entity"
require "Input"
require "Rect"
require "AnimatedImage"
require "Vector2"
require "Window"
require "Camera"
require "Math"

--Init the script
function Init()
	print "Test 2 init"
	img = LPC.AnimatedImage("../res/img/animtest.png")
	img:Play("idle")
	rect = LPC.Rectf(50, 50, 32, 32)
end
function Free()
	--print "Will try to save animtest to a new file!"
	--img:Save("./testing.json")
	print "Will try to save this entity to ./testing.json"
	entity:Save("./testing.json")
end
--Called each frame
function Update()
end
--Use for movement
function Move(deltaT)
	local speed = 200
	rect.pos.x = rect.pos.x + LPC.Input.GetJoyAxis(0) * speed * deltaT
	rect.pos.y = rect.pos.y + LPC.Input.GetJoyAxis(1) * speed * deltaT
end
--Draw
function Draw(camera)
	LPC.Window.Draw(img, LPC.Math.FromSceneSpace(camera, rect))
end