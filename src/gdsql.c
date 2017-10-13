#include <gdnative/gdnative.h>
#include <nativescript/godot_nativescript.h>

#include <mysql/mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *test_constructor(godot_object *obj, void *method_data) {
        printf("test.constructor()\n");
        return 0;
}

void test_destructor(godot_object *obj, void *method_data, void *user_data) {
        printf("test.destructor()\n");
}

/** func _ready() **/
godot_variant test_ready(godot_object *obj, void *method_data, void *user_data, int num_args, godot_variant **args) {
        godot_variant ret;
        godot_variant_new_nil(&ret);

        printf("_ready()\n");

        return ret;
}

/** Library entry point **/
void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
}

/** Library de-initialization **/
void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
}

/** Script entry (Registering all the classes and stuff) **/
void GDN_EXPORT godot_nativescript_init(void *desc) {
	printf("nativescript init\n");

	godot_instance_create_func create_func = {
		.create_func = &test_constructor,
                .method_data = 0,
                .free_func   = 0
        };

        godot_instance_destroy_func destroy_func = {
                .destroy_func = &test_destructor,
                .method_data  = 0,
                .free_func    = 0
        };

        godot_nativescript_register_class(desc, "SimpleClass", "Node", create_func, destroy_func);

        {
                godot_instance_method method = {
                        .method = &test_ready,
                        .method_data = 0,
                        .free_func = 0
                };

                godot_method_attributes attr = {
                        .rpc_type = GODOT_METHOD_RPC_MODE_DISABLED
                };

                godot_nativescript_register_method(desc, "SimpleClass", "_ready", attr, method);
        }
}


godot_variant GDN_EXPORT sendstring(void *data, godot_array *gd_query) {

godot_variant GDN_EXPORT sendstring(void *data, godot_array *gd_query) {

		const godot_int idx_ip = 1;
		godot_variant var_ip;
		var_ip = godot_array_get(gd_query, idx_ip);
		godot_string gds_ip = godot_variant_as_string(&var_ip);

		const godot_int idx_usr = 2;
		godot_variant var_usr;
		var_usr = godot_array_get(gd_query, idx_usr);
		godot_string gds_usr = godot_variant_as_string(&var_usr);

		const godot_int idx_pwd = 3;
		godot_variant var_pwd;
		var_pwd = godot_array_get(gd_query, idx_pwd);
		godot_string gds_pwd = godot_variant_as_string(&var_pwd);

		const godot_int idx_db = 4;
		godot_variant var_db;
		var_db = godot_array_get(gd_query, idx_db);
		godot_string gds_db = godot_variant_as_string(&var_db);

		const godot_int idx = 0;
		godot_variant ret;
		ret = godot_array_get(gd_query, idx);
		godot_string gd_string = godot_variant_as_string(&ret);

		char *c_query;
		int *c_query_length;
		godot_string_get_data(&gd_string, c_query, c_query_length);

		MYSQL *my = mysql_init(NULL);
		mysql_real_connect(my, "your_server_IP", "server_user", "server_pw", "remote_db_name", 0, NULL, 0);
		mysql_real_query(my, c_query, *c_query_length);
		mysql_close(my);
		return ret;
	
}
