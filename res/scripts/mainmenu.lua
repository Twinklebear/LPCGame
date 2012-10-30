--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestEntity"
require "TestState"
require "TestInput"
require "TestTimer"

function Init()
	print "\n--------Main Menu Init--------\n"
	quitButton = State.getEntity("quitbutton")
	print "Got the entity?"
	print ("Looked up entity main menu: " .. quitButton:name())

	timer = Timer()
	timer:start()
	print ("Timer ticks: " .. timer:ticks())

	result = quitButton:callFunction("Test", 1, timer)
	print ("Got result: " .. result)
	--Try to make a new entity
	--e = Entity("../res/entities/npc.json")
	--print ("Made entity: " .. e:name())
end
function Free()
	print "\n--------Main Menu Free--------\n"
end
function LogicUpdate()
	--Testing scene changing
	if Input.keyDown(Input.KEY_Q) then
		print "QUITTING"
		State.changeScene("quit")
	end
end
function RenderUpdate()
end