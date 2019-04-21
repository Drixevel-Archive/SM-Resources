//Pragma
#pragma semicolon 1
#pragma newdecls required

//Sourcemod Includes
#include <sourcemod>
#include <sourcemod-misc>
#include <sourcemod-colors>

//Globals

public Plugin myinfo = 
{
	name = "[Sourcemod] Colors Test",
	author = "Keith Warren (Drixevel)",
	description = "Tests the sourcemod-colors include.",
	version = "1.0.0",
	url = "https://github.com/drixevel"
};

public void OnPluginStart()
{
	RegAdminCmd("sm_testcolors", Command_TestColors, ADMFLAG_ROOT);
	
	RegAdminCmd("sm_testcolors_printtochat", Command_Test_PrintToChat, ADMFLAG_ROOT);
	RegAdminCmd("sm_testcolors_printtochatex", Command_Test_PrintToChatEx, ADMFLAG_ROOT);
	
	RegAdminCmd("sm_testcolors_printtochatall", Command_Test_PrintToChatAll, ADMFLAG_ROOT);
	RegAdminCmd("sm_testcolors_printtochatallex", Command_Test_PrintToChatAllEx, ADMFLAG_ROOT);
	
	RegAdminCmd("sm_testcolors_printtochatteam", Command_Test_PrintToChatTeam, ADMFLAG_ROOT);
	RegAdminCmd("sm_testcolors_printtochatteamex", Command_Test_PrintToChatTeamEx, ADMFLAG_ROOT);
	
	RegAdminCmd("sm_testcolors_printtochatadmins", Command_Test_PrintToChatAdmins, ADMFLAG_ROOT);
	RegAdminCmd("sm_testcolors_printtochatadminsex", Command_Test_PrintToChatAdminsEx, ADMFLAG_ROOT);
	
	RegAdminCmd("sm_testcolors_replytocommand", Command_Test_ReplyToCommand, ADMFLAG_ROOT);
	
	RegAdminCmd("sm_testcolors_showactivity", Command_Test_ShowActivity, ADMFLAG_ROOT);
	RegAdminCmd("sm_testcolors_showactivityex", Command_Test_ShowActivityEx, ADMFLAG_ROOT);
	
	RegAdminCmd("sm_testcolors_showactivity2", Command_Test_ShowActivity2, ADMFLAG_ROOT);
}

public Action Command_TestColors(int client, int args)
{
	
	return Plugin_Handled;
}

public Action Command_Test_PrintToChat(int client, int args)
{
	char buffer[255];
	GetCmdArgString(buffer, sizeof(buffer));
	CPrintToChat(client, buffer);
	return Plugin_Handled;
}

public Action Command_Test_PrintToChatEx(int client, int args)
{
	char buffer[255];
	GetCmdArgString(buffer, sizeof(buffer));
	CPrintToChatEx(client, client, buffer);
	return Plugin_Handled;
}

public Action Command_Test_PrintToChatAll(int client, int args)
{
	char buffer[255];
	GetCmdArgString(buffer, sizeof(buffer));
	CPrintToChatAll(buffer);
	return Plugin_Handled;
}

public Action Command_Test_PrintToChatAllEx(int client, int args)
{
	char buffer[255];
	GetCmdArgString(buffer, sizeof(buffer));
	CPrintToChatAllEx(client, buffer);
	return Plugin_Handled;
}

public Action Command_Test_PrintToChatTeam(int client, int args)
{
	int team = GetCmdArgInt(1);
	
	char buffer[255];
	GetCmdArg(2, buffer, sizeof(buffer));
	
	CPrintToChatTeam(team, buffer);
	return Plugin_Handled;
}

public Action Command_Test_PrintToChatTeamEx(int client, int args)
{
	int team = GetCmdArgInt(1);
	
	char buffer[255];
	GetCmdArg(2, buffer, sizeof(buffer));
	
	CPrintToChatTeamEx(team, client, buffer);
	return Plugin_Handled;
}

public Action Command_Test_PrintToChatAdmins(int client, int args)
{
	char admin[255];
	GetCmdArg(1, admin, sizeof(admin));
	
	AdminFlag flag;
	if (!FindFlagByName(admin, flag))
		ThrowError("Error find admin group name.");
	
	int bitflags = FlagToBit(flag);
	
	char buffer[255];
	GetCmdArg(2, buffer, sizeof(buffer));
	
	CPrintToChatAdmins(bitflags, buffer);
	return Plugin_Handled;
}

public Action Command_Test_PrintToChatAdminsEx(int client, int args)
{
	char admin[255];
	GetCmdArg(1, admin, sizeof(admin));
	
	AdminFlag flag;
	if (!FindFlagByName(admin, flag))
		ThrowError("Error find admin group name.");
	
	int bitflags = FlagToBit(flag);
	
	char buffer[255];
	GetCmdArg(2, buffer, sizeof(buffer));
	
	CPrintToChatAdminsEx(bitflags, client, buffer);
	return Plugin_Handled;
}

public Action Command_Test_ReplyToCommand(int client, int args)
{
	char buffer[255];
	GetCmdArgString(buffer, sizeof(buffer));
	
	CReplyToCommand(client, buffer);
	return Plugin_Handled;
}

public Action Command_Test_ShowActivity(int client, int args)
{
	char buffer[255];
	GetCmdArgString(buffer, sizeof(buffer));
	
	CShowActivity(client, buffer);
	return Plugin_Handled;
}

public Action Command_Test_ShowActivityEx(int client, int args)
{
	char buffer[255];
	GetCmdArg(1, buffer, sizeof(buffer));
	
	char tag[255];
	GetCmdArg(2, tag, sizeof(tag));
	
	CShowActivityEx(client, tag, buffer);
	return Plugin_Handled;
}

public Action Command_Test_ShowActivity2(int client, int args)
{
	char buffer[255];
	GetCmdArg(1, buffer, sizeof(buffer));
	
	char tag[255];
	GetCmdArg(2, tag, sizeof(tag));
	
	CShowActivity2(client, tag, buffer);
	return Plugin_Handled;
}