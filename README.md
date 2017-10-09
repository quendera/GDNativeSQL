# GDNativeSQL

A MariaDB/MySQL GDnative implementation

### Supported Features:
- mysql_real_query (MySQL/MariaDB docs https://mariadb.com/kb/en/library/mysql_real_query/);

To add more SQL features should be as easy as adding the C connector command to your 'gdsql.c' file before compiling the lib

### Requirements:
- x11 64bit (tested Ubuntu 16.04);
- Godot 3.0 and godot-headers (tested Oct 4th 2017)
- MariaDB C/C++ Connector 3.0.2 (tested) or MySQL C/C++ Connector (untested)
- Cmake and clang;

## Instructions:

1. Install MariaDB:
		sudo apt-get install mariadb-server

2. Install MariaDB C/C++ 3.0.2 connector and run cmake on the extracted tar.gz
		https://mariadb.com/kb/en/library/about-mariadb-connector-c/

3. Clone this repo into your desired folder;
		git clone https://github.com/quendera/GDNativeSQL
4. Clone godot-headers from master under [GDNativeSQL]:
		cd GDNativeSQL
		git clone https://github.com/GodotNativeTools/godot_headers

	Folder structure should look like this:

	[GDNativeSQL]
		├── godot-headers/
		├── lib/
		├── src/
			└── gdsql.c

5. Change the settings for your server in the gddsql.c file in line 82;

		mysql_real_connect(my, "your_server_IP", "server_user", "server_pw", "remote_db_name", 0, NULL, 0);

6. Compile your lib:

		cd GDNativeSQL
		clang -g -fPIC -c -std=c++11 src/gdsql.c -Igodot_headers -o src/gdsql_lib.os
		clang -g `mysql_config --cflags --libs` -shared src/gdsql_lib.os -o lib/gdsql_lib.so

7. Compile godot 3.0 from source
		cd MyGodotPath
		git clone https://github.com/godotengine/godot
		scons platform=x11

8. Open Godot and follow the steps to create GDNative library resource
		https://github.com/GodotNativeTools/godot_headers#create-gdnativelibrary-resource
and to attach your resource to a node

		https://github.com/GodotNativeTools/godot_headers#attaching-gdnativelibrary-to-a-node

9. Create a GDScript with the following code, save and run!

		func _ready():
			var gdn = GDNative.new()

			gdn.library = load("res://your_path_to_lib.tres")

			gdn.initialize()
			var s = "INSERT INTO Your_Table (Rowname) values (1), (2233242);"
			var a = gdn.call_native("standard_varcall", "sendstring", [s])
			gdn.terminate()

10. Success! 🎉
