#if defined _example_include_included
  #endinput
#endif
#define _example_include_included

////////////////////////////
//Globals


////////////////////////////
//Natives

//native float Native_Test();

////////////////////////////
//Forwards

//forward void Forward_Test(int client);


#if !defined REQUIRE_PLUGIN
public void __pl_example_include_SetNTVOptional()
{
	//MarkNativeAsOptional("Native_Test");
}
#endif

public SharedPlugin __pl_example_include =
{
	name = example_include",
	file = "example_include.smx",
#if defined REQUIRE_PLUGIN
	required = 1
#else
	required = 0
#endif
};