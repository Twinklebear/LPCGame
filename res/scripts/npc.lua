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
require "scripts/luaclass/entity.lua"

npc = class(Entity)

--Init the script
function npc:Init()
	self.img = AnimatedImage("../res/img/animtest.png")
	self.img:play("idle")
	self.physics = self.entity:physics()
end

function npc:Move(deltaT)
	--local speed = 200
	--rect.pos.x = rect.pos.x + LPC.Input.GetJoyAxis(0) * speed * deltaT
	--rect.pos.y = rect.pos.y + LPC.Input.GetJoyAxis(1) * speed * deltaT
	--This gives some odd behaviors
	local v = Vector2f(0, 0)
	v.x = Input.joyAxis(0)
	v.y = Input.joyAxis(1)
	--Set direction isn't implemented
	--physics:setDirection(v)
	--physics:move(deltaT)
end

function npc:Draw(camera)
	--With the changes made in the math class to std::weak_ptr<Camera>
	--We can no longer use the luabind library.
	--LPC.Window.Draw(img, LPC.Math.FromSceneSpace(camera, physics:Box()))
	Window.draw(self.img, Math.fromSceneSpace(camera, self.physics:box()))
end
