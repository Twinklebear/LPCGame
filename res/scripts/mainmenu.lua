require "State"
require "Vector2f"
require "Rectf"
require "Math"
require "Camera"
require "Image"
require "Window"
require "Input"

mainmenu = {}

function mainmenu:Init()
	print "\n--------Main Menu Init--------\n"
	mainmenu.bkgnd = Image("../res/img/introback.png")
end
function mainmenu:Free()
	print "\n--------Main Menu Free--------\n"
end
function mainmenu:LogicUpdate()
	if Input.keyDown(Input.KEY_Q) then
		State.changeScene("quit")
	end
end
function mainmenu:RenderUpdate(camera)
	Window.draw(self.bkgnd, Math.fromSceneSpace(camera, camera:sceneBox()), camera:box())
end