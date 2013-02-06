require "State"
require "Vector2f"
require "Rectf"
require "Math"
require "Camera"
require "Image"
require "Window"
require "Input"
require "Debug"
require "LuaScript"

function Init()
	print "\n--------Main Menu Init--------\n"
	bkgnd = Image("../res/img/introback.png")

	v = Vector2f(1, 2)
	print ("made v: " .. v)
	v.x = 5
	print ("set v: " .. v)
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	--Testing scene changing
	if Input.keyDown(Input.KEY_Q) then
		State.changeScene("quit")
	end
end
function RenderUpdate(camera)
	Window.draw(bkgnd, Math.fromSceneSpace(camera, camera:sceneBox()), camera:box())
end