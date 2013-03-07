require "State"
require "scripts/button.lua"

quitbutton = class(Button)

function quitbutton:Init()
	self.super.entity = self.entity
	self.super:Init("Quit")
end

function quitbutton:OnClick()
	State.changeScene("quit")
end
