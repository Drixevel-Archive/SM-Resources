//Pragma
#pragma semicolon 1
#pragma newdecls required

//Includes
#include <sourcemod>

//Globals

//We define an array as 'ArrayList' to use the methodmaps allowed and give it a name.
ArrayList g_OurArray;

public Plugin myinfo = 
{
	name = "", 
	author = "", 
	description = "", 
	version = "1.0.0", 
	url = ""
};

public void OnPluginStart()
{
	//Learn more about ArrayLists here: https://sm.alliedmods.net/new-api/adt_array/ArrayList
	
	//We create our array whenever the plugin starts to use it throughout the plugin.
	//If you create it inside of a function in the plugin, you have to delete it otherwise you'll leak handles.
	g_OurArray = new ArrayList();
	
	//It's possible to set the default size per index of the array so we can set it to 3 for vectors.
	//Similar in this example: float vec[3];
	//Or...: int values[3];
	//g_OurArray = new ArrayList(3);
	
	//We can also store strings and we have access to an easy function which allows us set the size.
	//Similar in this example: char string[255];
	//g_OurArray = new ArrayList(ByteCountToCells(255));
	
	RegConsoleCmd("sm_addvalue", Command_AddValue);
}

public Action Command_AddValue(int client, int args)
{
	char sArgument[16];
	GetCmdArgString(sArgument, sizeof(sArgument));
	int value = StringToInt(sArgument);
	
	//We take a value and store it in the array with the ability to access it with the index.
	int index = g_OurArray.Push(value);
	
	//This returns the same value based on our index for use.
	value = g_OurArray.Get(index);
	
	//Check if our value is 0 or not.
	if (value == 0)
		PrintToChat(client, "Our value is 0, okay.");
	
	//We can also find the first sign of our value in the array and get the index if it exists.
	//If it doesn't exist, it'll return as -1.
	index = g_OurArray.FindValue(value);
	
	//Check if it's -1 and if it is, it's no longer in our array.
	if (index == -1)
		PrintToChat(client, "Value not found even though we just pushed it, weird bug.");
	
	//We can also set the index of the array manually if the array has that many storage slots used.
	g_OurArray.Set(index, value);
	
	//We can get the total amount of stored values in the array to check if it's empty or not.
	int size = g_OurArray.Length;
	
	//Check if the size is 0 and if it is, we have an empty array.
	if (size == 0)
		PrintToChat(client, "Our array is empty for some reason.");
	
	//We can get a random index and/or value from our array for use as well.
	//Each array starts with an index of 0 and increases as we store values in it.
	//We check the size and deduct it by 1 in order to offset the max allowed indexes since we start at 0 and 1 and the size returns the total.
	int random = GetRandomInt(0, size - 1);
	
	//Check if the random index we got is 0 or not.
	//We only have 1 value in our array currently so this is what it'll return no matter what.
	if (random == 0)
		PrintToChat(client, "We happen to get the first index of the array at random.");
	
	//Here's an example which gets the actual value from the array and not just the index to get the value from.
	//int random = g_OurArray.Get(GetRandomInt(0, size - 1));
	
	//Finally, we can clear all of our stored data in the array and start from scratch with the handle still being valid.
	g_OurArray.Clear();
	
	//If you create an array inside of a callback, you MUST delete it.
	//If you store handles in an array, you must also close those handles as well as this won't sufficiently close them all.
	//We don't do it here since we defined it globally for re-use.
	//delete g_OurArray;
	
	return Plugin_Handled;
}