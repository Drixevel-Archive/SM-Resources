//Pragma
#pragma semicolon 1
#pragma newdecls required

//Sourcemod Includes
#include <sourcemod>

//ConVars

//Globals

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
	//A public command that can be used in this case for everybody that types !test or /test into chat or 'sm_test' into console.
	//https://sm.alliedmods.net/new-api/console/RegConsoleCmd
	RegConsoleCmd("sm_test", Command_Execute_Callback, "Description of the command.");
	
	//Same as 'RegConsoleCmd' but is tied to an admin flag. We use the flag for bans here so only players with that flag can use this command.
	//Server operators can override the flag for this by putting the commands name 'sm_testadmin' into their overrides config.
	//https://wiki.alliedmods.net/Checking_Admin_Flags_(SourceMod_Scripting)
	//https://sm.alliedmods.net/new-api/console/RegAdminCmd
	RegAdminCmd("sm_testadmin", Command_Execute_Callback_Admin, ADMFLAG_BAN, "Description of the admin command.");
	
	//Arguments are defined for use in-game.
	RegConsoleCmd("sm_testarguments", Command_Arguments);
	RegConsoleCmd("sm_testargumentstring", Command_ArgumentString);
	
	//A command only the server console can use.
	//https://sm.alliedmods.net/new-api/console/RegServerCmd
	RegServerCmd("sm_servercommand", Command_ServerCommand, "Only for use on the server.");
}

public Action Command_Execute_Callback(int client, int args)
{
	//If client is 0 then this command was used in the server console.
	if (client == 0)
	{
		PrintToServer("You are the console.");
		return Plugin_Handled;
	}
	
	PrintToChat(client, "You are a player.");
	
	//Return handled for commands so the player doesn't get an unknown command error in-game.
	return Plugin_Handled;
}

public Action Command_Execute_Callback_Admin(int client, int args)
{
	//If client is 0 then this command was used in the server console.
	if (client == 0)
	{
		PrintToServer("You are the console.");
		return Plugin_Handled;
	}
	
	PrintToChat(client, "You are an admin that can ban people.");
	
	//Return handled for commands so the player doesn't get an unknown command error in-game.
	return Plugin_Handled;
}

public Action Command_Arguments(int client, int args)
{
	//No arguments were defined for this command.
	//We send a reply to tell the client that this command has to be used this way.
	//It's sometimes better to open up like a menu or functionality with default argument values and execute them here.
	if (args == 0)
	{
		//https://sm.alliedmods.net/new-api/console/GetCmdArg
		char command[32];
		GetCmdArg(0, command, sizeof(command));	//Argument 0 = command name itself
		ReplyToCommand(client, "[Usage] %s <arg1> <arg2> <arg3>", command);
		return Plugin_Handled;
	}
	
	//Get the 1st argument and save it as a string.
	char arg1[12];
	GetCmdArg(1, arg1, sizeof(arg1));
	int arg1_int = StringToInt(arg1);	//Turn it into an integer.
	
	//Turn the 2nd argument into a float.
	char arg2[12];
	GetCmdArg(2, arg2, sizeof(arg2));
	float arg2_float = StringToFloat(arg2);
	
	//Turn our 3rd argument into a string and leave it.
	char arg3[32];
	GetCmdArg(3, arg3, sizeof(arg3));
	
	ReplyToCommand(client, "arg1 = %i, arg2 = %f, arg3 = %s", arg1_int, arg2_float, arg3);
	
	return Plugin_Handled;
}

public Action Command_ArgumentString(int client, int args)
{
	//No arguments were defined for this command.
	//We send a reply to tell the client that this command has to be used this way.
	//It's sometimes better to open up like a menu or functionality with default argument values and execute them here.
	if (args == 0)
	{
		char command[32];
		GetCmdArg(0, command, sizeof(command));	//Argument 0 = command name itself
		ReplyToCommand(client, "[Usage] %s <arg>", command);
		return Plugin_Handled;
	}
	
	//We can get all of the contents past the command itself into a single string for single-arg usage.
	char arg[64];
	GetCmdArgString(arg, sizeof(arg));
	
	ReplyToCommand(client, "arg = %s", arg);
	
	return Plugin_Handled;
}

public Action Command_ServerCommand(int args)
{
	PrintToServer("This command is for server use only.");
	return Plugin_Handled;
}