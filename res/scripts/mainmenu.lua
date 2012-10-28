--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestEntity"
require "TestState"
require "TestInput"

function Init()
	print "\n--------Main Menu Init--------\n"
	e = Entity("../res/entities/npc.json")
	print ("Made entity: " .. e:name())
	--made = false
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	if Input.keyDown("q") and not made then
		--print "Q Pushed"
		--made = true
		--local quitButton = State.getEntity("quitbutton")
		--print "Got the entity"
		--print ("Looked up entity: " .. quitbutton:name())
		--quitButton:callFuncton("Test", 0)
	end
end
function RenderUpdate()
end