# GDNativeSQL

A MariaDB/MySQL GDnative implementation

Instructions coming soon

##Requirements:
-x11 64bit (tested Ubuntu)

-Godot compiled from master, cpp-bindings and godot-headers from Oct 4th 2017

-MariaDB C/C++ Connector (tested) or MySQL C/C++ Connector (untested)


Godot code:

func _ready():
	var gdn = GDNative.new()

	gdn.library = load("res://lib/sqllib.tres")

	gdn.initialize()
	var s = "INSERT INTO Your_Table (Rowname) values (1), (2233242);"
	var a = gdn.call_native("standard_varcall", "sendstring", [s])
	gdn.terminate()
