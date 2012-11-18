--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestState"
require "TestVector2f"
require "TestEntity"
require "TestRectf"
require "TestTimer"

function Init()
	print "\n--------Main Menu Init--------\n"
	quitButton = State.getEntity("quitbutton")
	print ("Main menu looked up entity: " .. quitButton:name())
	--quitButton = Entity("../res/entities/quitbutton.json")
	--Test call with a vector
	timer = Timer()
	timer:start()
	print ("Timer ticks: " .. timer:ticks())
	while timer:ticks() < 5 do
		print "mainmenu ticking"
	end
	ret = quitButton:callFunction("TestCall", 1, "howdy!", timer)
	print ("got back ret: " .. ret)
	print ("v1 still: " .. v1)
	quitButton:release()
	
	--print "Try to make a new entity"
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
	if Input.keyDown(Input.KEY_E) then
		print "Deleting entity npc"
	--	e:destroy()
	end
end
function RenderUpdate()
end
