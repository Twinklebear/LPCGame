require "State"
require "Vector2f"
require "Entity"
require "Rectf"
require "Physics"
require "Math"
require "Camera"
require "Image"
require "Window"
require "Input"
require "Color"
require "Timer"
require "AnimatedImage"

function Init()
	print "\n--------Main Menu Init--------\n"
	--[[
	animImg = AnimatedImage("../res/img/walking.png")
	animImg:play("run-right")
	drawPos = Rectf(0, 0, 64, 64)
	]]
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	--Testing scene changing
	if Input.keyDown(Input.KEY_Q) then
		State.changeScene("quit")
	end
	--animImg:update()
end
function RenderUpdate()
	--Window.draw(animImg, drawPos, 45, Vector2f(0, 0), Window.FLIP_VERTICAL)
end