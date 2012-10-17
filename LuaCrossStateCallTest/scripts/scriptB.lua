require "LuaScript"
print "Script B!"

script = LPC.LuaScript.GetScript("scriptA")
script:CallFunction("Test")