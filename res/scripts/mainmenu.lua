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
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	if Input.keyDown(Input.KEY_Q) then
		State.changeScene("quit")
	end
end
function RenderUpdate(camera)
	Window.draw(bkgnd, Math.fromSceneSpace(camera, camera:sceneBox()), camera:box())
end
function RefTest(hi)
	print ("RefTest called with: " .. hi)
end

--Testing reference of table fields and calling self functions
testTable = {}
testTable.name = "Jim"
function testTable:speak()
	print ("This is table with name: " .. self.name .. " speaking")
end