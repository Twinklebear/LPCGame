require "State"
require "scripts/button.lua"

playbutton = class(Button)

function playbutton:Init()
	self.super.entity = self.entity
	self.super:Init("Play")
end

function playbutton:OnClick()
	State.changeScene("gGame")
end
