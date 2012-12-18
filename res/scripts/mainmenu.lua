--require "Input"
--require "scripts/calltest.lua"

--Testing my Lua C modules
require "TestState"
require "TestVector2f"
require "TestEntity"
require "TestRectf"
require "TestPhysics"
require "TestMath"
require "TestCamera"

function Init()
	print "\n--------Main Menu Init--------\n"
	--[[
	quitButton = State.getEntity("quitbutton")
	print ("Main menu looked up entity: " .. quitButton:name())
	print ("Getting physics component")
	qBPhys = quitButton:physics()
	print ("quitbutton box: " .. qBPhys:box())
	print ("quitbutton position: " .. qBPhys:position())
	quitButton:callFunction("TestCall", 0, quitButton, qBPhys)
	quitButton:release()
	]]
	vA = Vector2f(0, 0)
	vB = Vector2f(0.5, 0.5)
	dist = Math.distance(vA, vB)
	print ("distance betw vA and vB:  " .. dist)
	
	clamped = Math.clamp(1, 0, 5)
	print ("clamped: " .. clamped)

	vC = Vector2f(1, 1)
	vCUnit = Math.normalize(vC)
	print ("vCUnit: " .. vCUnit)
	print ("vCUnit magnitude: " .. Math.magnitude(vCUnit))

	vLerp = Math.lerp(vA, vB, 0.5)
	print ("vLerp: " .. vLerp)

	vForw = Math.forwardVector(180.0)
	print ("vForw: " .. vForw)

	rA = Rectf(0, 0, 1, 1)
	rB = Rectf(0, 0, 1, 1)
	side = Math.rectNearRect(rA, rB, 0)
	print ("Near side: " .. side)
	if side == Math.RIGHT then
		print ("rA right side is nearest rB")
	end

	rectColl = Math.checkCollision(rA, rB)
	if rectColl then
		print "rA and rB are colliding!"
	else
		print "rA and rB aren't colliding"
	end

	print ("rA: " .. rA)
	print ("vB: " .. vB)
	vectColl = Math.checkCollision(vB, rA)
	if vectColl then
		print "vB is inside rA"
	else
		print "vB is outside rA"
	end

	print ("rA to scene: " .. Math.toSceneSpace(mCamera, rA))
	print ("rA from scene" .. Math.fromSceneSpace(mCamera, rA))

	print ("vA to scene: " .. Math.toSceneSpace(mCamera, vA))
	print ("vA from scene: " .. Math.fromSceneSpace(mCamera, vA))
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
	end
end
function RenderUpdate()
end
