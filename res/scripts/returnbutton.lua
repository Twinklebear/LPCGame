require "State"
require "scripts/button.lua"

returnbutton = class(Button)

function returnbutton:Init()
	self.super.entity = self.entity
	--configure the box location
	local msg = ""
	if State.name() ~= "gGame" then
		self.entity:box():set(32, 625, 250, 50)
		msg = "Save & Quit"
	else
		msg = "Return"
	end

	self.super:Init("Return")
end

function returnbutton:Draw(camera)
	Window.draw(self.super.img, self.entity:box())
	Window.draw(self.super.text, self.super.textBox)
end

function returnbutton:OnClick()
	State.changeScene("mIntro")
end
