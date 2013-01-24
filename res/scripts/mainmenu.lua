require "State"
require "Vector2f"
require "Rectf"
require "Math"
require "Camera"
require "Image"
require "Window"
require "Input"

function Init()
	print "\n--------Main Menu Init--------\n"
	bkgnd = Image("../res/img/introback.png")

	print ("State name: " .. State.name())
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