//Pragma
#pragma semicolon 1
#pragma newdecls required

//Defines
#define CHAT_TAG "[Tools]"
#define COLORED_CHAT_TAG "[Tools]"

//Sourcemod Includes
#include <sourcemod>
#include <sourcemod-misc>
#include <sourcemod-colors>
#include <adminmenu>

//Globals
EngineVersion game;
ArrayList g_Commands;
StringMap g_CachedTimes;

int g_iAmmo[MAX_ENTITY_LIMIT + 1];
int g_iClip[MAX_ENTITY_LIMIT + 1];

TopMenu hTopMenu;
bool g_SpewSounds;
bool g_SpewAmbients;
bool g_SpewEntities;

//entity tools
ArrayList g_OwnedEntities[MAXPLAYERS + 1];
int g_iTarget[MAXPLAYERS + 1] = {INVALID_ENT_REFERENCE, ...};

bool g_Locked;
ArrayList g_HookEvents;

public Plugin myinfo =
{
	name = "Server Tools",
	author = "Keith Warren (Drixevel)",
	description = "A simple set of admin tools that help with development or server moderation.",
	version = "1.0.0",
	url = "https://github.com/drixevel"
};

public void OnPluginStart()
{
	LoadTranslations("common.phrases");
	
	game = GetEngineVersion();

	g_Commands = new ArrayList(ByteCountToCells(128));
	g_CachedTimes = new StringMap();

	RegAdminCmd("sm_admintools", Command_ServerTools, ADMFLAG_SLAY, "List available commands under server tools.");
	RegAdminCmd("sm_servertools", Command_ServerTools, ADMFLAG_SLAY, "List available commands under server tools.");
	RegAdminCmd2("sm_teleport", Command_Teleport, ADMFLAG_SLAY, "Teleports yourself to other clients.");
	RegAdminCmd2("sm_bring", Command_Bring, ADMFLAG_SLAY, "Teleports clients to yourself.");
	RegAdminCmd2("sm_port", Command_Port, ADMFLAG_SLAY, "Teleports clients to your crosshair.");
	RegAdminCmd2("sm_sethealth", Command_SetHealth, ADMFLAG_SLAY, "Sets health on yourself or other clients.");
	RegAdminCmd2("sm_addhealth", Command_AddHealth, ADMFLAG_SLAY, "Add health on yourself or other clients.");
	RegAdminCmd2("sm_removehealth", Command_RemoveHealth, ADMFLAG_SLAY, "Remove health from yourself or other clients.");
	RegAdminCmd2("sm_setclass", Command_SetClass, ADMFLAG_SLAY, "Sets the class of yourself or other clients.");
	RegAdminCmd2("sm_setteam", Command_SetTeam, ADMFLAG_SLAY, "Sets the team of yourself or other clients.");
	RegAdminCmd2("sm_respawn", Command_Respawn, ADMFLAG_SLAY, "Respawn yourself or clients.");
	RegAdminCmd2("sm_regenerate", Command_Regenerate, ADMFLAG_SLAY, "Regenerate yourself or clients.");
	RegAdminCmd2("sm_refillammunition", Command_RefillAmunition, ADMFLAG_SLAY, "Refill your ammunition.");
	RegAdminCmd2("sm_refillclip", Command_RefillClip, ADMFLAG_SLAY, "Refill your clip.");
	RegAdminCmd2("sm_managebots", Command_ManageBots, ADMFLAG_SLAY, "Manage bots on the server.");
	RegAdminCmd2("sm_password", Command_Password, ADMFLAG_SLAY, "Set a password on the server or remove it.");
	RegAdminCmd("sm_setpassword", Command_Password, ADMFLAG_SLAY, "Set a password on the server or remove it.");
	RegAdminCmd2("sm_endround", Command_EndRound, ADMFLAG_SLAY, "Ends the current round.");
	RegAdminCmd2("sm_setcondition", Command_SetCondition, ADMFLAG_SLAY, "Sets a condition on yourself or other clients.");
	RegAdminCmd("sm_addcondition", Command_SetCondition, ADMFLAG_SLAY, "Adds a condition on yourself or other clients.");
	RegAdminCmd2("sm_removecondition", Command_RemoveCondition, ADMFLAG_SLAY, "Removes a condition from yourself or other clients.");
	RegAdminCmd2("sm_setubercharge", Command_SetUbercharge, ADMFLAG_SLAY, "Sets ubercharge on yourself or other clients.");
	RegAdminCmd2("sm_addubercharge", Command_AddUbercharge, ADMFLAG_SLAY, "Adds ubercharge to yourself or other clients.");
	RegAdminCmd2("sm_removeubercharge", Command_RemoveUbercharge, ADMFLAG_SLAY, "Adds ubercharge to yourself or other clients.");
	RegAdminCmd2("sm_setmetal", Command_SetMetal, ADMFLAG_SLAY, "Sets metal on yourself or other clients.");
	RegAdminCmd2("sm_addmetal", Command_AddMetal, ADMFLAG_SLAY, "Adds metal to yourself or other clients.");
	RegAdminCmd2("sm_removemetal", Command_RemoveMetal, ADMFLAG_SLAY, "Remove metal from yourself or other clients.");
	RegAdminCmd2("sm_settime", Command_SetTime, ADMFLAG_SLAY, "Sets time on the server.");
	RegAdminCmd2("sm_addtime", Command_AddTime, ADMFLAG_SLAY, "Adds time on the server.");
	RegAdminCmd2("sm_removetime", Command_RemoveTime, ADMFLAG_SLAY, "Remove time on the server.");
	RegAdminCmd2("sm_setcrits", Command_SetCrits, ADMFLAG_SLAY, "Sets crits on yourself or other clients.");
	RegAdminCmd2("sm_addcrits", Command_SetCrits, ADMFLAG_SLAY, "Adds crits on yourself or other clients.");
	RegAdminCmd2("sm_removecrits", Command_RemoveCrits, ADMFLAG_SLAY, "Removes crits from yourself or other clients.");
	RegAdminCmd2("sm_setgod", Command_SetGod, ADMFLAG_SLAY, "Sets godmode on yourself or other clients.");
	RegAdminCmd2("sm_setbuddha", Command_SetBuddha, ADMFLAG_SLAY, "Sets buddhamode on yourself or other clients.");
	RegAdminCmd2("sm_setmortal", Command_SetMortal, ADMFLAG_SLAY, "Sets mortality on yourself or other clients.");
	RegAdminCmd2("sm_stunplayer", Command_StunPlayer, ADMFLAG_SLAY, "Stuns either yourself or other clients.");
	RegAdminCmd2("sm_bleedplayer", Command_BleedPlayer, ADMFLAG_SLAY, "Bleeds either yourself or other clients.");
	RegAdminCmd2("sm_igniteplayer", Command_IgnitePlayer, ADMFLAG_SLAY, "Ignite either yourself or other clients.");
	RegAdminCmd2("sm_reloadmap", Command_ReloadMap, ADMFLAG_SLAY, "Reloads the current map.");
	RegAdminCmd2("sm_mapname", Command_MapName, ADMFLAG_SLAY, "Retrieves the name of the current map.");
	RegAdminCmd2("sm_reload", Command_Reload, ADMFLAG_SLAY, "Reload a certain plugin that's currently loaded.");
	RegAdminCmd2("sm_spawnsentry", Command_SpawnSentry, ADMFLAG_SLAY, "Spawn a sentry where you're looking.");
	RegAdminCmd2("sm_spawndispenser", Command_SpawnDispenser, ADMFLAG_SLAY, "Spawn a dispenser where you're looking.");
	RegAdminCmd2("sm_particle", Command_Particle, ADMFLAG_SLAY, "Spawn a particle where you're looking.");
	RegAdminCmd("sm_spawnparticle", Command_Particle, ADMFLAG_SLAY, "Spawn a particle where you're looking.");
	RegAdminCmd("sm_p", Command_Particle, ADMFLAG_SLAY, "Spawn a particle where you're looking.");
	RegAdminCmd2("sm_listparticles", Command_ListParticles, ADMFLAG_SLAY, "List particles by name and click on them to test them.");
	RegAdminCmd("sm_lp", Command_ListParticles, ADMFLAG_SLAY, "List particles by name and click on them to test them.");
	RegAdminCmd("sm_generateparticles", Command_GenerateParticles, ADMFLAG_SLAY, "Generates a list of particles under the addons/sourcemod/data/particles folder.");
	RegAdminCmd("sm_gp", Command_GenerateParticles, ADMFLAG_SLAY, "Generates a list of particles under the addons/sourcemod/data/particles folder.");
	RegAdminCmd2("sm_spewsounds", Command_SpewSounds, ADMFLAG_SLAY, "Logs all sounds played live into chat.");
	RegAdminCmd2("sm_spewambients", Command_SpewAmbients, ADMFLAG_SLAY, "Logs all ambient sounds played live into chat.");
	RegAdminCmd2("sm_spewentities", Command_SpewEntities, ADMFLAG_SLAY, "Logs all entities created live into chat.");
	RegAdminCmd2("sm_getentitymodel", Command_GetEntityModel, ADMFLAG_SLAY, "Gets the model of a certain entity if it has a model.");
	RegAdminCmd2("sm_setkillstreak", Command_SetKillstreak, ADMFLAG_SLAY, "Sets your current killstreak.");
	RegAdminCmd2("sm_lock", Command_Lock, ADMFLAG_SLAY, "Lock the server to admins only.");
	RegAdminCmd2("sm_lockserver", Command_Lock, ADMFLAG_SLAY, "Lock the server to admins only.");
	RegAdminCmd2("sm_createprop", Command_CreateProp, ADMFLAG_SLAY, "Create a dynamic prop entity.");
	RegAdminCmd2("sm_animateprop", Command_AnimateProp, ADMFLAG_SLAY, "Animate a dynamic prop entity.");
	RegAdminCmd2("sm_deleteprop", Command_DeleteProp, ADMFLAG_SLAY, "Delete a dynamic prop entity.");
	RegAdminCmd2("sm_debugevents", Command_DebugEvents, ADMFLAG_SLAY, "Easily debug events as they fire.");
	RegAdminCmd2("sm_setrendercolor", Command_SetRenderColor, ADMFLAG_SLAY, "Sets you current render color.");
	RegAdminCmd2("sm_setrenderfx", Command_SetRenderFx, ADMFLAG_SLAY, "Sets you current render fx.");
	RegAdminCmd2("sm_setrendermode", Command_SetRenderMode, ADMFLAG_SLAY, "Sets you current render mode.");
	
	//entity tools
	RegAdminCmd("sm_createentity", Command_CreateEntity, ADMFLAG_SLAY, "Create an entity.");
	RegAdminCmd("sm_dispatchkeyvalue", Command_DispatchKeyValue, ADMFLAG_SLAY, "Dispatch keyvalue on an entity.");
	RegAdminCmd("sm_dispatchkeyvaluefloat", Command_DispatchKeyValueFloat, ADMFLAG_SLAY, "Dispatch keyvalue float on an entity.");
	RegAdminCmd("sm_dispatchkeyvaluevector", Command_DispatchKeyValueVector, ADMFLAG_SLAY, "Dispatch keyvalue vector on an entity.");
	RegAdminCmd("sm_dispatchspawn", Command_DispatchSpawn, ADMFLAG_SLAY, "Dispatch spawn an entity.");
	RegAdminCmd("sm_acceptentityinput", Command_AcceptEntityInput, ADMFLAG_SLAY, "Send an input to an entity.");
	RegAdminCmd("sm_animate", Command_Animate, ADMFLAG_SLAY, "Send an animation input to an entity.");
	RegAdminCmd("sm_targetentity", Command_TargetEntity, ADMFLAG_SLAY, "Target an entity.");
	RegAdminCmd("sm_deleteentity", Command_DeleteEntity, ADMFLAG_SLAY, "Delete an entity.");
	RegAdminCmd("sm_listownedentities", Command_ListOwnedEntities, ADMFLAG_SLAY, "List all entities owned by you.");
	
	TopMenu topmenu;
	if (LibraryExists("adminmenu") && ((topmenu = GetAdminTopMenu()) != null))
		OnAdminMenuReady(topmenu);
		
	CreateTimer(1.0, Timer_CheckForUpdates, _, TIMER_REPEAT);
	g_HookEvents = new ArrayList(ByteCountToCells(256));
}

void RegAdminCmd2(const char[] cmd, ConCmd callback, int adminflags, const char[] description = "", const char[] group = "", int flags = 0)
{
	RegAdminCmd(cmd, callback, adminflags, description, group, flags);
	g_Commands.PushString(cmd);
}

public Action Timer_CheckForUpdates(Handle timer)
{
	OnAllPluginsLoaded();
}

public void OnAllPluginsLoaded()
{
	char sPath[256];
	BuildPath(Path_SM, sPath, sizeof(sPath), "plugins/");

	if (g_CachedTimes.Size > 0)
	{
		Handle map = CreateTrieSnapshot(g_CachedTimes);
		
		int size; char sUnload[256];
		for (int i = 0; i < TrieSnapshotLength(map); i++)
		{
			size = TrieSnapshotKeyBufferSize(map, i);
			
			char[] sFile = new char[size + 1];
			GetTrieSnapshotKey(map, i, sFile, size + 1);
			
			strcopy(sUnload, sizeof(sUnload), sFile);
			ReplaceString(sUnload, size + 1, sPath, "");

			Handle plugin = FindPluginByFile(sUnload);

			if (plugin == null)
				g_CachedTimes.Remove(sFile);
		}

		delete map;
	}

	Handle iter = GetPluginIterator();
	while (MorePlugins(iter))
	{
		Handle plugin = ReadPlugin(iter);
		
		char sName[128];
		GetPluginInfo(plugin, PlInfo_Name, sName, sizeof(sName));
		
		char sFile[256];
		GetPluginFilename(plugin, sFile, sizeof(sFile));

		Format(sFile, sizeof(sFile), "%s%s", sPath, sFile);
		
		int current = GetFileTime(sFile, FileTime_LastChange);
		int iTime;

		if (g_CachedTimes.GetValue(sFile, iTime) && current > iTime)
		{
			char sReload[256];
			strcopy(sReload, sizeof(sReload), sFile);

			ReplaceString(sReload, sizeof(sReload), sPath, "", true);
			ReplaceString(sReload, sizeof(sReload), ".smx", "", true);
			
			ServerCommand("sm plugins reload %s", sReload);
			PrintToChatAll("Plugin '%s' has been reloaded.", sName);
			
			if (GetPluginStatus(FindPluginByFile(sReload)) != Plugin_Running)
				ServerCommand("sm plugins load %s", sReload); //Fixes an unloading issue.
			
			ServerCommand("sm_reload_translations %s", sReload); //Automatically reloads translations.
		}

		g_CachedTimes.SetValue(sFile, current);
	}

	delete iter;
}

public void OnMapStart()
{
	delete g_OwnedEntities[0];
	g_OwnedEntities[0] = new ArrayList();
	g_iTarget[0] = INVALID_ENT_REFERENCE;
}

public void OnMapEnd()
{
	delete g_OwnedEntities[0];
	g_iTarget[0] = INVALID_ENT_REFERENCE;
	g_Locked = false;
}

public void OnAdminMenuReady(Handle aTopMenu)
{
	TopMenu topmenu = TopMenu.FromHandle(aTopMenu);

	if (topmenu == hTopMenu)
		return;

	hTopMenu = topmenu;

	hTopMenu.AddCategory("sm_managebots", AdminMenu_BotCommands);
}

public void AdminMenu_BotCommands(TopMenu topmenu, TopMenuAction action, TopMenuObject topobj_id, int param, char[] buffer, int maxlength)
{
	if (action == TopMenuAction_DisplayOption)
		FormatEx(buffer, maxlength, "Bot Commands");
	else if (action == TopMenuAction_SelectOption)
		OpenManageBotsMenu(param);
}

public void OnClientConnected(int client)
{
	delete g_OwnedEntities[client];
	g_OwnedEntities[client] = new ArrayList();
	g_iTarget[client] = INVALID_ENT_REFERENCE;
}

public void OnClientDisconnect(int client)
{
	delete g_OwnedEntities[client];
	g_iTarget[client] = INVALID_ENT_REFERENCE;
}

public Action Command_ServerTools(int client, int args)
{
	if (IsClientConsole(client))
	{
		PrintToServer("%s You must be in-game to use this command.", CHAT_TAG);
		return Plugin_Handled;
	}

	ListCommands(client);
	return Plugin_Handled;
}

void ListCommands(int client)
{
	Panel panel = new Panel();
	panel.SetTitle("Server Tools:");

	char sCommand[128];
	for (int i = 0; i < g_Commands.Length; i++)
	{
		g_Commands.GetString(i, sCommand, sizeof(sCommand));
		ReplaceString(sCommand, sizeof(sCommand), "sm_", "!");
		panel.DrawText(sCommand);
	}

	panel.Send(client, PanelHandler_Commands, MENU_TIME_FOREVER);
	delete panel;
}

public int PanelHandler_Commands(Menu menu, MenuAction action, int param1, int param2)
{
	delete menu;
}

public Action Command_Teleport(int client, int args)
{
	if (IsClientConsole(client))
	{
		PrintToServer("%s You must be in-game to use this command.", CHAT_TAG);
		return Plugin_Handled;
	}

	if (args == 0)
	{
		CPrintToChat(client, "%s You must specify a target to teleport to.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (!IsPlayerAlive(client))
	{
		CPrintToChat(client, "%s You must be alive to use this command.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int target = FindTarget(client, sTarget, false, true);

	if (!IsPlayerIndex(target) || !IsClientConnected(target) || !IsClientInGame(target))
	{
		CPrintToChat(client, "%s Invalid target specified, please try again.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (!IsPlayerAlive(target))
	{
		CPrintToChat(client, "%s %N isn't currently alive.", COLORED_CHAT_TAG, target);
		return Plugin_Handled;
	}

	float vecOrigin[3];
	GetClientAbsOrigin(target, vecOrigin);

	float vecAngles[3];
	GetClientAbsAngles(target, vecAngles);

	TeleportEntity(client, vecOrigin, vecAngles, NULL_VECTOR);

	CPrintToChat(target, "%s %N teleported themselves to you.", COLORED_CHAT_TAG, client);
	CPrintToChat(client, "%s You have teleported yourself to %N.", COLORED_CHAT_TAG, target);

	return Plugin_Handled;
}

public Action Command_Bring(int client, int args)
{
	if (IsClientConsole(client))
	{
		PrintToServer("%s You must be in-game to use this command.", CHAT_TAG);
		return Plugin_Handled;
	}

	if (args == 0)
	{
		CPrintToChat(client, "%s You must specify a target to bring.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (!IsPlayerAlive(client))
	{
		CPrintToChat(client, "%s You must be alive to use this command.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	float vecOrigin[3];
	GetClientAbsOrigin(client, vecOrigin);

	float vecAngles[3];
	GetClientAbsAngles(client, vecAngles);

	for (int i = 0; i < targets; i++)
	{
		TeleportEntity(targets_list[i], vecOrigin, vecAngles, NULL_VECTOR);
		CPrintToChat(targets_list[i], "%s You have been teleported to %N.", COLORED_CHAT_TAG, client);
	}

	CPrintToChat(client, "%s You have teleported %s to you.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_Port(int client, int args)
{
	if (IsClientConsole(client))
	{
		PrintToServer("%s You must be in-game to use this command.", CHAT_TAG);
		return Plugin_Handled;
	}

	if (args == 0)
	{
		CPrintToChat(client, "%s You must specify a target to port.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (!IsPlayerAlive(client))
	{
		CPrintToChat(client, "%s You must be alive to use this command.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	float vecOrigin[3];
	GetClientCrosshairOrigin(client, vecOrigin);

	for (int i = 0; i < targets; i++)
	{
		TeleportEntity(targets_list[i], vecOrigin, NULL_VECTOR, NULL_VECTOR);
		CPrintToChat(targets_list[i], "%s You have been ported by %N.", COLORED_CHAT_TAG, client);
	}

	CPrintToChat(client, "%s You have ported %s to your look position.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_SetHealth(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set their health.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sHealth[12];
	GetCmdArg(2, sHealth, sizeof(sHealth));
	int health = ClampCell(StringToInt(sHealth), 1, 999999);

	for (int i = 0; i < targets; i++)
	{
		TF2_SetPlayerHealth(targets_list[i], health);
		CPrintToChat(targets_list[i], "%s Your health has been set to %i by %N.", COLORED_CHAT_TAG, health, client);
	}

	CReplyToCommand(client, "%s You have set the health of %s to %i.", COLORED_CHAT_TAG, sTargetName, health);

	return Plugin_Handled;
}

public Action Command_AddHealth(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to add to their health.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sHealth[12];
	GetCmdArg(2, sHealth, sizeof(sHealth));
	int health = ClampCell(StringToInt(sHealth), 1, 999999);

	for (int i = 0; i < targets; i++)
	{
		TF2_AddPlayerHealth(targets_list[i], health);
		CPrintToChat(targets_list[i], "%s Your health has been increased by %i by %N.", COLORED_CHAT_TAG, health, client);
	}

	CReplyToCommand(client, "%s You have increased the health of %s by %i.", COLORED_CHAT_TAG, sTargetName, health);

	return Plugin_Handled;
}

public Action Command_RemoveHealth(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to deduct from their health.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sHealth[12];
	GetCmdArg(2, sHealth, sizeof(sHealth));
	int health = ClampCell(StringToInt(sHealth), 1, 999999);

	for (int i = 0; i < targets; i++)
	{
		TF2_RemovePlayerHealth(targets_list[i], health);
		CPrintToChat(targets_list[i], "%s Your health has been deducted by %i by %N.", COLORED_CHAT_TAG, health, client);
	}

	CReplyToCommand(client, "%s You have deducted health of %s by %i.", COLORED_CHAT_TAG, sTargetName, health);

	return Plugin_Handled;
}

public Action Command_SetClass(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set their class.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	else if (args == 1)
	{
		CReplyToCommand(client, "%s You must specify a class to set.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	else if (game != Engine_TF2)
	{
		CReplyToCommand(client, "%s This command is for Team Fortress 2 only.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sClass[32];
	GetCmdArg(2, sClass, sizeof(sClass));
	TFClassType class = IsStringNumeric(sClass) ? view_as<TFClassType>(StringToInt(sClass)) : TF2_GetClass(sClass);

	if (class == TFClass_Unknown)
	{
		CReplyToCommand(client, "%s You have specified an invalid class.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sClassName[32];
	TF2_GetClassName(class, sClassName, sizeof(sClassName));

	for (int i = 0; i < targets; i++)
	{
		TF2_SetPlayerClass(targets_list[i], class, false, true);
		TF2_RegeneratePlayer(targets_list[i]);
		CPrintToChat(targets_list[i], "%s Your class has been set to %s by %N.", COLORED_CHAT_TAG, sClassName, client);
	}

	CReplyToCommand(client, "%s You have set the class of %s to %s.", COLORED_CHAT_TAG, sTargetName, sClassName);

	return Plugin_Handled;
}

public Action Command_SetTeam(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set their team.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	else if (args == 1)
	{
		CReplyToCommand(client, "%s You must specify a team to set.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sTeam[32];
	GetCmdArg(2, sTeam, sizeof(sTeam));
 	int team = StringToInt(sTeam);

	if (team < 1 || team > 3)
	{
		CReplyToCommand(client, "%s You have specified an invalid team.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTeamName[32];
	GetTeamName(team, sTeamName, sizeof(sTeamName));

	for (int i = 0; i < targets; i++)
	{
		switch (game)
		{
			case Engine_TF2:
			{
				TF2_ChangeClientTeam(targets_list[i], view_as<TFTeam>(team));
				TF2_RegeneratePlayer(targets_list[i]);
			}
			
			case Engine_CSS, Engine_CSGO:
			{
				CS_SwitchTeam(targets_list[i], team);
				CS_UpdateClientModel(targets_list[i]);
			}
			default: ChangeClientTeam(targets_list[i], team);
		}
		
		CPrintToChat(targets_list[i], "%s Your team has been set to %s by %N.", COLORED_CHAT_TAG, sTeamName, client);
	}

	CReplyToCommand(client, "%s You have set the team of %s to %s.", COLORED_CHAT_TAG, sTargetName, sTeamName);

	return Plugin_Handled;
}

public Action Command_Respawn(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to respawn.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_CONNECTED, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		switch (game)
		{
			case Engine_TF2: TF2_RespawnPlayer(targets_list[i]);
			case Engine_CSS, Engine_CSGO: CS_RespawnPlayer(targets_list[i]);
		}
		
		CPrintToChat(targets_list[i], "%s Your have been respawned by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have respawned %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_Regenerate(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to regenerate.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_RegeneratePlayer(targets_list[i]);
		CPrintToChat(targets_list[i], "%s Your have been regenerated by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have regenerated %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_RefillAmunition(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to refill their ammunition.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	int weapon2;
	for (int i = 0; i < targets; i++)
	{
		for (int x = 0; x < TF_MAX_SLOTS; x++)
		{
			if ((weapon2 = GetPlayerWeaponSlot(targets_list[i], i)) != INVALID_ENT_INDEX && IsValidEntity(weapon2) && g_iAmmo[weapon2] > 0)
				SetAmmo(targets_list[i], weapon2, g_iAmmo[weapon2]);
		}

		CPrintToChat(targets_list[i], "%s Your weapons ammunitions have been refilled by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have refilled the ammunition ammo for %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_RefillClip(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to refill their clip.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	int weapon2;
	for (int i = 0; i < targets; i++)
	{
		for (int x = 0; x < TF_MAX_SLOTS; x++)
		{
			if ((weapon2 = GetPlayerWeaponSlot(targets_list[i], i)) != INVALID_ENT_INDEX && IsValidEntity(weapon2) && g_iClip[weapon2] > 0)
				SetClip(weapon2, g_iClip[weapon2]);
		}

		CPrintToChat(targets_list[i], "%s Your weapons clips have been refilled by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have refilled the clip ammo for %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public void TF2Items_OnGiveNamedItem_Post(int client, char[] classname, int itemDefinitionIndex, int itemLevel, int itemQuality, int entityIndex)
{
	if (StrContains(classname, "tf_weapon") != 0)
		return;

	DataPack pack;
	CreateDataTimer(0.2, Timer_CacheValues, pack, TIMER_FLAG_NO_MAPCHANGE);
	pack.WriteCell(GetClientUserId(client));
	pack.WriteCell(EntIndexToEntRef(entityIndex));
}

public Action Timer_CacheValues(Handle timer, DataPack data)
{
	data.Reset();
	int client = GetClientOfUserId(data.ReadCell());
	int entity = EntRefToEntIndex(data.ReadCell());

	if (IsPlayerIndex(client) && IsValidEntity(entity))
	{
		g_iAmmo[entity] = GetAmmo(client, entity);
		g_iClip[entity] = GetClip(entity);
	}
}

public void OnEntityDestroyed(int entity)
{
	if (!IsEntityIndex(entity))
		return;

	g_iAmmo[entity] = 0;
	g_iClip[entity] = 0;
}

public Action Command_ManageBots(int client, int args)
{
	if (IsClientConsole(client))
	{
		PrintToServer("%s You must be in-game to use this command.", CHAT_TAG);
		return Plugin_Handled;
	}

	OpenManageBotsMenu(client);
	return Plugin_Handled;
}

void OpenManageBotsMenu(int client)
{
	Menu menu = new Menu(MenuHandler_ManageBots);
	menu.SetTitle("[Tools] Manage Bots:");

	menu.AddItem("spawn", "Spawn a bot");
	menu.AddItem("remove", "Remove a bot");
	menu.AddItem("class", "Set bot class");
	menu.AddItem("team", "Switch bot team");
	menu.AddItem("move", "Toggle bot movement");
	menu.AddItem("quota", "Update bot quota");

	menu.Display(client, MENU_TIME_FOREVER);
}

public int MenuHandler_ManageBots(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sInfo[32];
			menu.GetItem(param2, sInfo, sizeof(sInfo));

			if (StrEqual(sInfo, "spawn"))
			{
				CPrintToChatAll("%s %N has spawned a bot.", COLORED_CHAT_TAG, param1);
				ServerCommand("tf_bot_add");

				OpenManageBotsMenu(param1);
			}
			else if (StrEqual(sInfo, "remove"))
			{
				int target = GetClientAimTarget(param1, true);

				if (!IsPlayerIndex(target) || !IsFakeClient(target))
				{
					CPrintToChat(param1, "%s Please aim your crosshair at a valid bot.", COLORED_CHAT_TAG);
					OpenManageBotsMenu(param1);
					return;
				}

				CPrintToChatAll("%s %N has kicked the bot %N.", COLORED_CHAT_TAG, param1, target);
				ServerCommand("tf_bot_kick \"%N\"", target);

				OpenManageBotsMenu(param1);
			}
			else if (StrEqual(sInfo, "class"))
			{
				int target = GetClientAimTarget(param1, true);

				if (!IsPlayerIndex(target) || !IsFakeClient(target))
				{
					CPrintToChat(param1, "%s Please aim your crosshair at a valid bot.", COLORED_CHAT_TAG);
					OpenManageBotsMenu(param1);
					return;
				}

				OpenSetBotClassMenu(param1, target);
			}
			else if (StrEqual(sInfo, "team"))
			{
				int target = GetClientAimTarget(param1, true);

				if (!IsPlayerIndex(target) || !IsFakeClient(target))
				{
					CPrintToChat(param1, "%s Please aim your crosshair at a valid bot.", COLORED_CHAT_TAG);
					OpenManageBotsMenu(param1);
					return;
				}

				OpenSetBotTeamMenu(param1, target);
			}
			else if (StrEqual(sInfo, "move"))
			{
				ConVar blind = FindConVar("nb_blind");
				SetConVarFlag(blind, false, FCVAR_CHEAT);
				blind.SetBool(!blind.BoolValue);
				SetConVarFlag(blind, true, FCVAR_CHEAT);

				CPrintToChatAll("%s %N has toggled bot movement %s.", COLORED_CHAT_TAG, param1, !blind.BoolValue ? "on" : "off");

				OpenManageBotsMenu(param1);
			}
			else if (StrEqual(sInfo, "quota"))
				OpenSetBotQuotaMenu(param1);
		}

		case MenuAction_End:
		{
			delete menu;
		}
	}
}

void OpenSetBotClassMenu(int client, int target)
{
	Menu menu = new Menu(MenuHandler_SetBotClass);
	menu.SetTitle("[Tools] Pick a class for %N:", target);

	menu.AddItem("1", "Scout");
	menu.AddItem("3", "Soldier");
	menu.AddItem("7", "Pyro");
	menu.AddItem("4", "DemoMan");
	menu.AddItem("6", "Heavy");
	menu.AddItem("9", "Engineer");
	menu.AddItem("5", "Medic");
	menu.AddItem("2", "Sniper");
	menu.AddItem("8", "Spy");

	PushMenuInt(menu, "target", target);

	menu.ExitBackButton = true;
	menu.Display(client, MENU_TIME_FOREVER);
}

public int MenuHandler_SetBotClass(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sInfo[32];
			menu.GetItem(param2, sInfo, sizeof(sInfo));

			int target = GetMenuInt(menu, "target");
			TFClassType class = view_as<TFClassType>(StringToInt(sInfo));

			if (!IsPlayerIndex(target) || !IsFakeClient(target))
			{
				CPrintToChat(param1, "%s Bot is no longer valid.", COLORED_CHAT_TAG);
				OpenManageBotsMenu(param1);
				return;
			}

			TF2_SetPlayerClass(target, class);
			TF2_RegeneratePlayer(target);

			OpenSetBotClassMenu(param1, target);
		}

		case MenuAction_Cancel:
		{
			if (param2 == MenuCancel_ExitBack)
				OpenManageBotsMenu(param1);
		}

		case MenuAction_End:
			delete menu;
	}
}

void OpenSetBotTeamMenu(int client, int target)
{
	Menu menu = new Menu(MenuHandler_SetBotTeam);
	menu.SetTitle("[Tools] Pick a team for %N:", target);

	menu.AddItem("2", "Red");
	menu.AddItem("3", "Blue");

	PushMenuInt(menu, "target", target);

	menu.ExitBackButton = true;
	menu.Display(client, MENU_TIME_FOREVER);
}

public int MenuHandler_SetBotTeam(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sInfo[32];
			menu.GetItem(param2, sInfo, sizeof(sInfo));

			int target = GetMenuInt(menu, "target");
			TFTeam team = view_as<TFTeam>(StringToInt(sInfo));

			if (!IsPlayerIndex(target) || !IsFakeClient(target))
			{
				CPrintToChat(param1, "%s Bot is no longer valid.", COLORED_CHAT_TAG);
				OpenManageBotsMenu(param1);
				return;
			}

			TF2_ChangeClientTeam(target, team);
			TF2_RespawnPlayer(target);

			OpenSetBotTeamMenu(param1, target);
		}

		case MenuAction_Cancel:
		{
			if (param2 == MenuCancel_ExitBack)
				OpenManageBotsMenu(param1);
		}

		case MenuAction_End:
			delete menu;
	}
}

void OpenSetBotQuotaMenu(int client)
{
	Menu menu = new Menu(MenuHandler_SetBotQuota);
	menu.SetTitle("[Tools] Set the curren bot quota:");

	menu.AddItem("0", "Zero");
	menu.AddItem("6", "Six");
	menu.AddItem("12", "Twelve");
	menu.AddItem("18", "Eighteen");
	menu.AddItem("24", "Twenty-Four");
	menu.AddItem("30", "Thirty");

	menu.ExitBackButton = true;
	menu.Display(client, MENU_TIME_FOREVER);
}

public int MenuHandler_SetBotQuota(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sInfo[12];
			menu.GetItem(param2, sInfo, sizeof(sInfo));

			ServerCommand("tf_bot_quota %i", StringToInt(sInfo));

			OpenSetBotQuotaMenu(param1);
		}

		case MenuAction_Cancel:
		{
			if (param2 == MenuCancel_ExitBack)
				OpenManageBotsMenu(param1);
		}

		case MenuAction_End:
		{
			delete menu;
		}
	}
}

public Action Command_Password(int client, int args)
{
	ConVar password = FindConVar("sv_password");

	char sPassword[256];
	password.GetString(sPassword, sizeof(sPassword));

	if (args == 0)
	{
		if (strlen(sPassword) == 0)
		{
			CReplyToCommand(client, "%s No password is currently set on the server, it's unlocked.", COLORED_CHAT_TAG);
			return Plugin_Handled;
		}

		password.SetString("");
		CPrintToChatAll("%s %N has removed the password unlocking the server.", COLORED_CHAT_TAG, client);

		return Plugin_Handled;
	}

	char sNewPassword[256];
	GetCmdArgString(sNewPassword, sizeof(sNewPassword));

	if (strlen(sNewPassword) == 0)
	{
		CReplyToCommand(client, "%s You must specify a password in order to set it.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (strlen(sNewPassword) < 6)
	{
		CReplyToCommand(client, "%s The new password requires more than or equal to 6 characters.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (strlen(sNewPassword) > 256)
	{
		CReplyToCommand(client, "%s The new password requires less than or equal to 256 characters.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	password.SetString(sPassword);

	CPrintToChatAll("%s %N has set a password on the server locking it.", COLORED_CHAT_TAG, client);
	CReplyToCommand(client, "%s You have set the server password locking it to %s.", COLORED_CHAT_TAG);

	return Plugin_Handled;
}

public Action Command_EndRound(int client, int args)
{
	TFTeam team = TFTeam_Unassigned;

	if (args > 0)
	{
		char sTeam[12];
		GetCmdArgString(sTeam, sizeof(sTeam));
		team = view_as<TFTeam>(StringToInt(sTeam));
	}

	TF2_ForceRoundWin(team);
	CPrintToChatAll("%s %N has ended the current round.", COLORED_CHAT_TAG, client);

	return Plugin_Handled;
}

public Action Command_SetCondition(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to add a condition to.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	else if (args == 1)
	{
		CReplyToCommand(client, "%s You must specify a condition to set.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sCondition[12];
	GetCmdArg(2, sCondition, sizeof(sCondition));
	TFCond condition = view_as<TFCond>(StringToInt(sCondition));

	if (view_as<int>(condition) < 0 || view_as<int>(condition) > 118)
	{
		CReplyToCommand(client, "%s You have specified an invalid condition.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	float time = TFCondDuration_Infinite;

	if (args >= 2)
	{
		char sTime[12];
		GetCmdArg(3, sTime, sizeof(sTime));

		time = StringToFloat(sTime);

		if (time < TFCondDuration_Infinite)
		{
			CReplyToCommand(client, "%s You have specified an invalid time.", COLORED_CHAT_TAG);
			return Plugin_Handled;
		}
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_AddCondition(targets_list[i], condition, time, client);
		CPrintToChat(targets_list[i], "%s Your have gained a new condition from %N for %.2f seconds.", COLORED_CHAT_TAG, client, time);
	}

	CReplyToCommand(client, "%s You have set a new condition on %s for %.2f seconds.", COLORED_CHAT_TAG, sTargetName, time);

	return Plugin_Handled;
}

public Action Command_RemoveCondition(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to remove a condition from.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	else if (args == 1)
	{
		CReplyToCommand(client, "%s You must specify a condition to remove.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sCondition[12];
	GetCmdArg(2, sCondition, sizeof(sCondition));
	TFCond condition = view_as<TFCond>(StringToInt(sCondition));

	if (view_as<int>(condition) < 0 || view_as<int>(condition) > 118)
	{
		CReplyToCommand(client, "%s You have specified an invalid condition.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		if (TF2_IsPlayerInCondition(targets_list[i], condition))
			continue;

		TF2_RemoveCondition(targets_list[i], condition);
		CPrintToChat(targets_list[i], "%s Your have been stripped of a condition by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have been stripped of a condition by %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_SetUbercharge(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set their ubercharge.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sUbercharge[12];
	GetCmdArg(2, sUbercharge, sizeof(sUbercharge));
	float uber = ClampCell(StringToFloat(sUbercharge), 1.0, 999999.0);

	for (int i = 0; i < targets; i++)
	{
		if (TF2_GetPlayerClass(targets_list[i]) != TFClass_Medic)
			continue;

		TF2_SetUberLevel(targets_list[i], uber);
		CPrintToChat(targets_list[i], "%s Your ubercharge has been set to %.2f by %N.", COLORED_CHAT_TAG, uber, client);
	}

	CReplyToCommand(client, "%s You have set the ubercharge of %s to %.2f.", COLORED_CHAT_TAG, sTargetName, uber);

	return Plugin_Handled;
}

public Action Command_AddUbercharge(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to add to their ubercharge.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sUbercharge[12];
	GetCmdArg(2, sUbercharge, sizeof(sUbercharge));
	float uber = ClampCell(StringToFloat(sUbercharge), 1.0, 999999.0);

	for (int i = 0; i < targets; i++)
	{
		if (TF2_GetPlayerClass(targets_list[i]) != TFClass_Medic)
			continue;

		TF2_AddUberLevel(targets_list[i], uber);
		CPrintToChat(targets_list[i], "%s Your ubercharge has been increased by %.2f by %N.", COLORED_CHAT_TAG, uber, client);
	}

	CReplyToCommand(client, "%s You have increased the ubercharge of %s by %.2f.", COLORED_CHAT_TAG, sTargetName, uber);

	return Plugin_Handled;
}

public Action Command_RemoveUbercharge(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to deduct from their ubercharge.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sUbercharge[12];
	GetCmdArg(2, sUbercharge, sizeof(sUbercharge));
	float uber = ClampCell(StringToFloat(sUbercharge), 1.0, 999999.0);

	for (int i = 0; i < targets; i++)
	{
		if (TF2_GetPlayerClass(targets_list[i]) != TFClass_Medic)
			continue;

		TF2_RemoveUberLevel(targets_list[i], uber);
		CPrintToChat(targets_list[i], "%s Your ubercharge has been deducted by %.2f by %N.", COLORED_CHAT_TAG, uber, client);
	}

	CReplyToCommand(client, "%s You have deducted ubercharge of %s by %.2f.", COLORED_CHAT_TAG, sTargetName, uber);

	return Plugin_Handled;
}

public Action Command_SetMetal(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set their metal.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sMetal[12];
	GetCmdArg(2, sMetal, sizeof(sMetal));
	int metal = ClampCell(StringToInt(sMetal), 1, 999999);

	for (int i = 0; i < targets; i++)
	{
		if (TF2_GetPlayerClass(targets_list[i]) != TFClass_Engineer)
			continue;

		TF2_SetMetal(targets_list[i], metal);
		CPrintToChat(targets_list[i], "%s Your metal has been set to %i by %N.", COLORED_CHAT_TAG, metal, client);
	}

	CReplyToCommand(client, "%s You have set the metal of %s to %i.", COLORED_CHAT_TAG, sTargetName, metal);

	return Plugin_Handled;
}

public Action Command_AddMetal(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to add to their metal.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sMetal[12];
	GetCmdArg(2, sMetal, sizeof(sMetal));
	int metal = ClampCell(StringToInt(sMetal), 1, 999999);

	for (int i = 0; i < targets; i++)
	{
		if (TF2_GetPlayerClass(targets_list[i]) != TFClass_Engineer)
			continue;

		TF2_AddMetal(targets_list[i], metal);
		CPrintToChat(targets_list[i], "%s Your metal has been increased by %i by %N.", COLORED_CHAT_TAG, metal, client);
	}

	CReplyToCommand(client, "%s You have increased the metal of %s by %i.", COLORED_CHAT_TAG, sTargetName, metal);

	return Plugin_Handled;
}

public Action Command_RemoveMetal(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to deduct from their metal.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	char sMetal[12];
	GetCmdArg(2, sMetal, sizeof(sMetal));
	int metal = ClampCell(StringToInt(sMetal), 1, 999999);

	for (int i = 0; i < targets; i++)
	{
		if (TF2_GetPlayerClass(targets_list[i]) != TFClass_Engineer)
			continue;

		TF2_RemoveMetal(targets_list[i], metal);
		CPrintToChat(targets_list[i], "%s Your metal has been deducted by %i by %N.", COLORED_CHAT_TAG, metal, client);
	}

	CReplyToCommand(client, "%s You have deducted metal of %s by %i.", COLORED_CHAT_TAG, sTargetName, metal);

	return Plugin_Handled;
}

public Action Command_SetTime(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a time to set.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTime[12];
	GetCmdArg(1, sTime, sizeof(sTime));
	int time = StringToInt(sTime);

	int entity = FindEntityByClassname(-1, "team_round_timer");

	if (IsValidEntity(entity))
	{
		SetVariantInt(time);
		AcceptEntityInput(entity, "SetTime");
	}
	else
	{
		ConVar timelimit = FindConVar("mp_timelimit");
		SetConVarFloat(timelimit, StringToFloat(sTime) / 60);
		delete timelimit;
	}

	CPrintToChatAll("%s %N has set the time to %i.", COLORED_CHAT_TAG, client, time);

	return Plugin_Handled;
}

public Action Command_AddTime(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a time to add to it.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTime[12];
	GetCmdArg(1, sTime, sizeof(sTime));
	int time = StringToInt(sTime);

	int entity = FindEntityByClassname(-1, "team_round_timer");

	if (IsValidEntity(entity))
	{
		char sMap[32];
		GetCurrentMap(sMap, sizeof(sMap));

		if (strncmp(sMap, "pl_", 3) == 0)
		{
			char sBuffer[32];
			Format(sBuffer, sizeof(sBuffer), "0 %i", time);

			SetVariantString(sBuffer);
			AcceptEntityInput(entity, "AddTeamTime");
		}
		else
		{
			SetVariantInt(time);
			AcceptEntityInput(entity, "AddTime");
		}
	}
	else
	{
		ConVar timelimit = FindConVar("mp_timelimit");
		SetConVarFloat(timelimit, timelimit.FloatValue + (StringToFloat(sTime) / 60));
		delete timelimit;
	}

	CPrintToChatAll("%s %N has added time to %i.", COLORED_CHAT_TAG, client, time);

	return Plugin_Handled;
}

public Action Command_RemoveTime(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a time to removed from.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTime[12];
	GetCmdArg(1, sTime, sizeof(sTime));
	int time = StringToInt(sTime);

	int entity = FindEntityByClassname(-1, "team_round_timer");

	if (IsValidEntity(entity))
	{
		char sMap[32];
		GetCurrentMap(sMap, sizeof(sMap));

		if (strncmp(sMap, "pl_", 3) == 0)
		{
			char sBuffer[32];
			Format(sBuffer, sizeof(sBuffer), "0 %i", time);

			SetVariantString(sBuffer);
			AcceptEntityInput(entity, "RemoveTeamTime");
		}
		else
		{
			SetVariantInt(time);
			AcceptEntityInput(entity, "RemoveTime");
		}
	}
	else
	{
		ConVar timelimit = FindConVar("mp_timelimit");
		SetConVarFloat(timelimit, timelimit.FloatValue - (StringToFloat(sTime) / 60));
		delete timelimit;
	}

	CPrintToChatAll("%s %N has removed time from %i.", COLORED_CHAT_TAG, client, time);

	return Plugin_Handled;
}

public Action Command_SetCrits(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set crits on.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	float time = TFCondDuration_Infinite;

	if (args >= 1)
	{
		char sTime[12];
		GetCmdArg(2, sTime, sizeof(sTime));

		time = StringToFloat(sTime);

		if (time < TFCondDuration_Infinite)
		{
			CReplyToCommand(client, "%s You have specified an invalid time.", COLORED_CHAT_TAG);
			return Plugin_Handled;
		}
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_AddCondition(targets_list[i], TFCond_CritOnWin, time, client);
		CPrintToChat(targets_list[i], "%s Your have gained crits from %N for %.2f seconds.", COLORED_CHAT_TAG, client, time);
	}

	CReplyToCommand(client, "%s You have set crits on %s for %.2f seconds.", COLORED_CHAT_TAG, sTargetName, time);

	return Plugin_Handled;
}

public Action Command_RemoveCrits(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to remove crits from.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		if (TF2_IsPlayerInCondition(targets_list[i], TFCond_CritOnWin))
			continue;

		TF2_RemoveCondition(targets_list[i], TFCond_CritOnWin);
		CPrintToChat(targets_list[i], "%s Your have been stripped of crits by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have stripped crits from %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_SetGod(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set godmode on.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_SetGodmode(targets_list[i], TFGod_God);
		CPrintToChat(targets_list[i], "%s Your have been set to godmode by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have set godmode on %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_SetBuddha(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set buddhamode on.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_SetGodmode(targets_list[i], TFGod_Buddha);
		CPrintToChat(targets_list[i], "%s Your have been set to buddhamode by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have set buddhamode on %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_SetMortal(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to set mortalmode on.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_SetGodmode(targets_list[i], TFGod_Mortal);
		CPrintToChat(targets_list[i], "%s Your have been set to mortalmode by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have set mortalmode on %s.", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_StunPlayer(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to stun.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	float time = 7.0;

	if (args >= 2)
	{
		char sTime[12];
		GetCmdArg(2, sTime, sizeof(sTime));

		time = StringToFloat(sTime);

		if (time < 0.0)
		{
			CReplyToCommand(client, "%s You have specified an invalid time.", COLORED_CHAT_TAG);
			return Plugin_Handled;
		}
	}

	float slowdown = 0.8;

	if (args >= 3)
	{
		char sSlowdown[12];
		GetCmdArg(3, sSlowdown, sizeof(sSlowdown));

		slowdown = StringToFloat(sSlowdown);

		if (slowdown < 0.0 || slowdown > 1.00)
		{
			CReplyToCommand(client, "%s You have specified an invalid slowdown.", COLORED_CHAT_TAG);
			return Plugin_Handled;
		}
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_StunPlayer(targets_list[i], time, slowdown, TF_STUNFLAGS_SMALLBONK, client);
		CPrintToChat(targets_list[i], "%s Your have been stunned by %N  for %.2f seconds.", COLORED_CHAT_TAG, client, time);
	}

	CReplyToCommand(client, "%s You have stunned %s  for %.2f seconds.", COLORED_CHAT_TAG, sTargetName, time);

	return Plugin_Handled;
}

public Action Command_BleedPlayer(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to bleed.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	float time = 10.0;

	if (args >= 2)
	{
		char sTime[12];
		GetCmdArg(2, sTime, sizeof(sTime));

		time = StringToFloat(sTime);

		if (time < 0.0)
		{
			CReplyToCommand(client, "%s You have specified an invalid time.", COLORED_CHAT_TAG);
			return Plugin_Handled;
		}
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_MakeBleed(targets_list[i], client, time);
		CPrintToChat(targets_list[i], "%s Your have been cut by %N  for %.2f seconds.", COLORED_CHAT_TAG, client, time);
	}

	CReplyToCommand(client, "%s You have cut %s  for %.2f seconds.", COLORED_CHAT_TAG, sTargetName, time);

	return Plugin_Handled;
}

public Action Command_IgnitePlayer(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a target to ignite.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(1, sTarget, sizeof(sTarget));

	int targets_list[MAXPLAYERS];
	char sTargetName[MAX_TARGET_LENGTH];
	bool tn_is_ml;

	int targets = ProcessTargetString(sTarget, client, targets_list, sizeof(targets_list), COMMAND_FILTER_ALIVE, sTargetName, sizeof(sTargetName), tn_is_ml);

	if (targets == COMMAND_TARGET_NONE)
	{
		ReplyToTargetError(client, COMMAND_TARGET_NONE);
		return Plugin_Handled;
	}

	for (int i = 0; i < targets; i++)
	{
		TF2_IgnitePlayer(targets_list[i], client);
		CPrintToChat(targets_list[i], "%s Your have been ignited by %N.", COLORED_CHAT_TAG, client);
	}

	CReplyToCommand(client, "%s You have ignited %s", COLORED_CHAT_TAG, sTargetName);

	return Plugin_Handled;
}

public Action Command_ReloadMap(int client, int args)
{
	char sCurrentMap[MAX_MAP_NAME_LENGTH];
	GetCurrentMap(sCurrentMap, sizeof(sCurrentMap));
	ServerCommand("sm_map %s", sCurrentMap);

	char sMap[MAX_MAP_NAME_LENGTH];
	GetMapName(sMap, sizeof(sMap));
	CPrintToChatAll("%s %N has initiated a map reload.", COLORED_CHAT_TAG, client);

	return Plugin_Handled;
}

public Action Command_MapName(int client, int args)
{
	char sCurrentMap[MAX_MAP_NAME_LENGTH];
	GetCurrentMap(sCurrentMap, sizeof(sCurrentMap));

	char sMap[MAX_MAP_NAME_LENGTH];
	GetMapDisplayName(sCurrentMap, sMap, sizeof(sMap));

	if (StrContains(sCurrentMap, "workshop/", false) == 0)
		CReplyToCommand(client, "%s Name: %s [%s]", COLORED_CHAT_TAG, sMap, sCurrentMap);
	else
		CReplyToCommand(client, "%s Name: %s", COLORED_CHAT_TAG, sCurrentMap);

	return Plugin_Handled;
}

public Action Command_Reload(int client, int args)
{
	if (IsClientConsole(client))
	{
		CReplyToCommand(client, "[SM] %t", "Command is in-game only");
		return Plugin_Handled;
	}

	Menu menu = new Menu(MenuHandler_Reload);
	menu.SetTitle("Reload a plugin:");

	Handle iter = GetPluginIterator();
	
	char sName[128]; char sFile[256];
	while (MorePlugins(iter))
	{
		Handle plugin = ReadPlugin(iter);

		GetPluginInfo(plugin, PlInfo_Name, sName, sizeof(sName));
		GetPluginFilename(plugin, sFile, sizeof(sFile));
		PrintToChat(client, sName);

		menu.AddItem(sFile, sName);
	}

	delete iter;
	
	menu.Display(client, MENU_TIME_FOREVER);
	return Plugin_Handled;
}

public int MenuHandler_Reload(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sFile[256]; char sName[128];
			GetMenuItem(menu, param2, sFile, sizeof(sFile), _, sName, sizeof(sName));
			ServerCommand("sm plugins reload %s", sFile);
			PrintToChat(param1, "Plugin '%s' has been reloaded.", sName);
			Command_Reload(param1, 0);
		}
		case MenuAction_End:
			delete menu;
	}
}

public Action Command_SpawnSentry(int client, int args)
{
	if (args == 0)
	{
		char sCommand[32];
		GetCommandName(sCommand, sizeof(sCommand));
		CReplyToCommand(client, "%s Usage: %s <target> <team> <level> <mini> <disposable>", COLORED_CHAT_TAG, sCommand);
		return Plugin_Handled;
	}

	float vecOrigin[3];
	if (!GetClientCrosshairOrigin(client, vecOrigin))
	{
		CReplyToCommand(client, "%s Invalid look position.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	float vecAngles[3];
	GetClientAbsAngles(client, vecAngles);

	int target = GetCmdArgTarget(client, 1, false, false);

	if (target == -1)
		target = client;

	TFTeam team = view_as<TFTeam>(GetCmdArgInt(2));
	int level = GetCmdArgInt(3);
	bool mini = GetCmdArgBool(4);
	bool disposable = GetCmdArgBool(5);

	TF2_SpawnSentry(target, vecOrigin, vecAngles, team, level, mini, disposable);
	return Plugin_Handled;
}

public Action Command_SpawnDispenser(int client, int args)
{
	if (args == 0)
	{
		char sCommand[32];
		GetCommandName(sCommand, sizeof(sCommand));
		CReplyToCommand(client, "%s Usage: %s <target> <team> <level>", COLORED_CHAT_TAG, sCommand);
		return Plugin_Handled;
	}

	float vecOrigin[3];
	if (!GetClientCrosshairOrigin(client, vecOrigin))
	{
		CReplyToCommand(client, "%s Invalid look position.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	float vecAngles[3];
	GetClientAbsAngles(client, vecAngles);

	int target = GetCmdArgTarget(client, 1, false, false);

	if (target == -1)
		target = client;

	TFTeam team = view_as<TFTeam>(GetCmdArgInt(2));
	int level = GetCmdArgInt(3);

	TF2_SpawnDispenser(target, vecOrigin, vecAngles, team, level);
	return Plugin_Handled;
}

public Action Command_SpawnTeleporter(int client, int args)
{
	if (args == 0)
	{
		char sCommand[32];
		GetCommandName(sCommand, sizeof(sCommand));
		CReplyToCommand(client, "%s Usage: %s <target> <team> <level> <mode>", COLORED_CHAT_TAG, sCommand);
		return Plugin_Handled;
	}

	float vecOrigin[3];
	if (!GetClientCrosshairOrigin(client, vecOrigin))
	{
		CReplyToCommand(client, "%s Invalid look position.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	float vecAngles[3];
	GetClientAbsAngles(client, vecAngles);

	int target = GetCmdArgTarget(client, 1, false, false);

	if (target == -1)
		target = client;

	TFTeam team = view_as<TFTeam>(GetCmdArgInt(2));
	int level = GetCmdArgInt(3);
	TFObjectMode mode = view_as<TFObjectMode>(GetCmdArgInt(4));

	TF2_SpawnTeleporter(target, vecOrigin, vecAngles, team, level, mode);
	return Plugin_Handled;
}

public Action Command_Particle(int client, int args)
{
	if (args == 0)
	{
		char sCommand[64];
		GetCommandName(sCommand, sizeof(sCommand));
		CReplyToCommand(client, "%s Usage: %s <target> <team> <level> <mode>", COLORED_CHAT_TAG, sCommand);
		return Plugin_Handled;
	}
	
	char sParticle[64];
	GetCmdArg(1, sParticle, sizeof(sParticle));
	
	float time = GetCmdArgFloat(2);
	
	if (time <= 0.0)
		time = 2.0;
	
	float vecOrigin[3];
	GetClientCrosshairOrigin(client, vecOrigin);
	
	CreateParticle(sParticle, time, vecOrigin);
	CReplyToCommand(client, "%s Particle %s has been spawned for %.2f second(s).", COLORED_CHAT_TAG, sParticle, time);
	
	return Plugin_Handled;
}

public Action Command_ListParticles(int client, int args)
{
	int item = GetCmdArgInt(1);
	ListParticles(client, item);
	return Plugin_Handled;
}

void ListParticles(int client, int item)
{
	int tblidx = FindStringTable("ParticleEffectNames");
	
	if (tblidx == INVALID_STRING_TABLE)
	{
		CReplyToCommand(client, "Could not find string table: ParticleEffectNames");
		return;
	}
	
	Menu menu = new Menu(MenuHandler_Particles);
	menu.SetTitle("Available particles:");
	
	char sParticle[256];
	for (int i = 0; i < GetStringTableNumStrings(tblidx); i++)
	{
		ReadStringTable(tblidx, i, sParticle, sizeof(sParticle));
		menu.AddItem(sParticle, sParticle);
	}
	
	menu.DisplayAt(client, item, MENU_TIME_FOREVER);
}

public int MenuHandler_Particles(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sParticle[256];
			menu.GetItem(param2, sParticle, sizeof(sParticle));
			
			float vecOrigin[3];
			GetClientCrosshairOrigin(param1, vecOrigin);
			
			CreateParticle(sParticle, 2.0, vecOrigin);
			CReplyToCommand(param1, "%s Particle %s has been spawned for 2.0 seconds.", COLORED_CHAT_TAG, sParticle);
			
			ListParticles(param1, param2);
		}
		case MenuAction_End:
			delete menu;
	}
}

public Action Command_GenerateParticles(int client, int args)
{
	char sPath[PLATFORM_MAX_PATH];
	BuildPath(Path_SM, sPath, sizeof(sPath), "data/particles/");
	
	if (!DirExists(sPath))
	{
		CreateDirectory(sPath, 511);
		
		if (!DirExists(sPath))
		{
			CReplyToCommand(client, "%s Error finding and creating directory: %s", COLORED_CHAT_TAG, sPath);
			return Plugin_Handled;
		}
	}
	
	char sGame[32];
	GetGameFolderName(sGame, sizeof(sGame));
	
	BuildPath(Path_SM, sPath, sizeof(sPath), "data/particles/%s.txt", sGame);
	
	File file = OpenFile(sPath, "w");
	
	if (file == null)
	{
		CReplyToCommand(client, "%s Error opening up file for writing: %s", COLORED_CHAT_TAG, sPath);
		return Plugin_Handled;
	}
	
	int tblidx = FindStringTable("ParticleEffectNames");
	
	if (tblidx == INVALID_STRING_TABLE)
	{
		CReplyToCommand(client, "%s Could not find string table: ParticleEffectNames", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	
	char name[256];
	for (int i = 0; i < GetStringTableNumStrings(tblidx); i++)
	{
		ReadStringTable(tblidx, i, name, sizeof(name));
		file.WriteLine(name);
	}
	
	delete file;
	CReplyToCommand(client, "%s Particles file generated successfully for %s at: %s", COLORED_CHAT_TAG, sGame, sPath);
	
	return Plugin_Handled;
}

public Action Command_SpewSounds(int client, int args)
{
	g_SpewSounds = !g_SpewSounds;
	CReplyToCommand(client, "%s Spew Sounds: %s", COLORED_CHAT_TAG, g_SpewSounds ? "ON" : "OFF");
	
	if (g_SpewSounds)
		AddNormalSoundHook(SpewSounds);
	else
		RemoveNormalSoundHook(SpewSounds);
	
	return Plugin_Handled;
}

public Action SpewSounds(int clients[MAXPLAYERS], int &numClients, char sample[PLATFORM_MAX_PATH], int &entity, int &channel, float &volume, int &level, int &pitch, int &flags, char soundEntry[PLATFORM_MAX_PATH], int &seed)
{
	CPrintToChatAll("[SpewSounds] -: %s", sample);
}

public Action Command_SpewAmbients(int client, int args)
{
	g_SpewAmbients = !g_SpewAmbients;
	CReplyToCommand(client, "%s Spew Ambients: %s", COLORED_CHAT_TAG, g_SpewAmbients ? "ON" : "OFF");
	
	if (g_SpewAmbients)
		AddAmbientSoundHook(SpewAmbients);
	else
		RemoveAmbientSoundHook(SpewAmbients);
	
	return Plugin_Handled;
}

public Action SpewAmbients(char sample[PLATFORM_MAX_PATH], int &entity, float &volume, int &level, int &pitch, float pos[3], int &flags, float &delay)
{
	CPrintToChatAll("[SpewAmbients] -: %s", sample);
}

public Action Command_SpewEntities(int client, int args)
{
	g_SpewEntities = !g_SpewEntities;
	CReplyToCommand(client, "%s Spew Entities: %s", COLORED_CHAT_TAG, g_SpewEntities ? "ON" : "OFF");
	
	return Plugin_Handled;
}

public void OnEntityCreated(int entity, const char[] classname)
{
	if (g_SpewEntities)
		CPrintToChatAll("[SpewEntities] -%i: %s", entity, classname);
}

public Action Command_GetEntityModel(int client, int args)
{
	int target = GetClientAimTarget(client, false);
	
	if (!IsValidEntity(target))
	{
		CPrintToChat(client, "%s Target not found, please aim your crosshair at the entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	
	if (!HasEntProp(target, Prop_Data, "m_ModelName"))
	{
		CPrintToChat(client, "%s Target doesn't have a valid model.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}
	
	char sModel[PLATFORM_MAX_PATH];
	GetEntPropString(target, Prop_Data, "m_ModelName", sModel, sizeof(sModel));
	CPrintToChat(client, "%s Model Found: %s", COLORED_CHAT_TAG, sModel);
	
	return Plugin_Handled;
}

public Action Command_SetKillstreak(int client, int args)
{
	int value = GetCmdArgInt(1);
	TF2_SetKillstreak(client, value);
	CPrintToChat(client, "%s Killstreak set to: %i", COLORED_CHAT_TAG, value);
	return Plugin_Handled;
}

public Action Command_CreateEntity(int client, int args)
{
	if (args == 0)
	{
		CReplyToCommand(client, "%s You must specify a classname.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sClassname[64];
	GetCmdArg(1, sClassname, sizeof(sClassname));

	if (args == 1)
	{
		CReplyToCommand(client, "%s You must specify an entity name for reference.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sName[64];
	GetCmdArg(2, sName, sizeof(sName));

	int entity = CreateEntityByName(sClassname);

	if (!IsValidEntity(entity))
	{
		CReplyToCommand(client, "%s Unknown error while creating entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (!DispatchKeyValue(entity, "targetname", sName))
	{
		CReplyToCommand(client, "%s Error while setting entity classname to '%s'.", COLORED_CHAT_TAG, sName);
		AcceptEntityInput(entity, "Kill");
		return Plugin_Handled;
	}

	CReplyToCommand(client, "%s '%s' entity created with the index '%i'.", COLORED_CHAT_TAG, sClassname, entity);

	g_OwnedEntities[client].Push(EntIndexToEntRef(entity));
	CReplyToCommand(client, "%s Entity '%i' is now under ownership of you.", COLORED_CHAT_TAG, entity);

	g_iTarget[client] = EntIndexToEntRef(entity);
	CReplyToCommand(client, "%s Entity '%s' is now targetted by you.", COLORED_CHAT_TAG, sName);

	return Plugin_Handled;
}

public Action Command_DispatchKeyValue(int client, int args)
{
	if (args < 2)
	{
		CReplyToCommand(client, "%s You must input at least 2 arguments for the key and the value.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (g_iTarget[client] == INVALID_ENT_REFERENCE)
	{
		CReplyToCommand(client, "%s You aren't currently targeting an entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	int entity = EntRefToEntIndex(g_iTarget[client]);

	if (!IsValidEntity(entity) || entity < 1)
	{
		CReplyToCommand(client, "%s Entity is no longer valid.", COLORED_CHAT_TAG);
		g_iTarget[client] = INVALID_ENT_REFERENCE;
		return Plugin_Handled;
	}

	char sKeyName[64];
	GetCmdArg(1, sKeyName, sizeof(sKeyName));

	char sValue[PLATFORM_MAX_PATH];
	GetCmdArg(2, sValue, sizeof(sValue));

	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));

	DispatchKeyValue(entity, sKeyName, sValue);
	CReplyToCommand(client, "%s Targetted entity '%s' is now dispatch keyvalue '%s' for '%s'.", COLORED_CHAT_TAG, strlen(sName) > 0 ? sName : "N/A", sKeyName, sValue);

	return Plugin_Handled;
}

public Action Command_DispatchKeyValueFloat(int client, int args)
{
	if (args < 2)
	{
		CReplyToCommand(client, "%s You must input at least 2 arguments for the key and the value.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (g_iTarget[client] == INVALID_ENT_REFERENCE)
	{
		CReplyToCommand(client, "%s You aren't currently targeting an entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	int entity = EntRefToEntIndex(g_iTarget[client]);

	if (!IsValidEntity(entity) || entity < 1)
	{
		CReplyToCommand(client, "%s Entity is no longer valid.", COLORED_CHAT_TAG);
		g_iTarget[client] = INVALID_ENT_REFERENCE;
		return Plugin_Handled;
	}

	char sKeyName[64];
	GetCmdArg(1, sKeyName, sizeof(sKeyName));

	char sValue[PLATFORM_MAX_PATH];
	GetCmdArg(2, sValue, sizeof(sValue));
	float fValue = StringToFloat(sValue);

	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));

	DispatchKeyValueFloat(entity, sKeyName, fValue);
	CReplyToCommand(client, "%s Targetted entity '%s' is now dispatch keyvalue '%s' for '%.2f'.", COLORED_CHAT_TAG, strlen(sName) > 0 ? sName : "N/A", sKeyName, fValue);

	return Plugin_Handled;
}

public Action Command_DispatchKeyValueVector(int client, int args)
{
	if (args < 2)
	{
		CReplyToCommand(client, "%s You must input at least 2 arguments for the key and the value.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	if (g_iTarget[client] == INVALID_ENT_REFERENCE)
	{
		CReplyToCommand(client, "%s You aren't currently targeting an entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	int entity = EntRefToEntIndex(g_iTarget[client]);

	if (!IsValidEntity(entity) || entity < 1)
	{
		CReplyToCommand(client, "%s Entity is no longer valid.", COLORED_CHAT_TAG);
		g_iTarget[client] = INVALID_ENT_REFERENCE;
		return Plugin_Handled;
	}

	char sKeyName[64];
	GetCmdArg(1, sKeyName, sizeof(sKeyName));

	char sValue[PLATFORM_MAX_PATH];
	GetCmdArg(2, sValue, sizeof(sValue));

	float vecValue[3];
	StringToVector(sValue, vecValue);

	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));

	DispatchKeyValueVector(entity, sKeyName, vecValue);
	CReplyToCommand(client, "%s Targetted entity '%s' is now dispatch keyvalue '%s' for '%.2f/%.2f/%.2f'.", COLORED_CHAT_TAG, strlen(sName) > 0 ? sName : "N/A", sKeyName, vecValue[0], vecValue[1], vecValue[2]);

	return Plugin_Handled;
}

public Action Command_DispatchSpawn(int client, int args)
{
	if (g_iTarget[client] == INVALID_ENT_REFERENCE)
	{
		CReplyToCommand(client, "%s You aren't currently targeting an entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	int entity = EntRefToEntIndex(g_iTarget[client]);

	if (!IsValidEntity(entity) || entity < 1)
	{
		CReplyToCommand(client, "%s Entity is no longer valid.", COLORED_CHAT_TAG);
		g_iTarget[client] = INVALID_ENT_REFERENCE;
		return Plugin_Handled;
	}

	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));

	DispatchSpawn(entity);
	CReplyToCommand(client, "%s Targetted entity '%s' is now dispatch spawned.", COLORED_CHAT_TAG, strlen(sName) > 0 ? sName : "N/A");

	return Plugin_Handled;
}

public Action Command_AcceptEntityInput(int client, int args)
{
	if (g_iTarget[client] == INVALID_ENT_REFERENCE)
	{
		CReplyToCommand(client, "%s You aren't currently targeting an entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	int entity = EntRefToEntIndex(g_iTarget[client]);

	if (!IsValidEntity(entity) || entity < 1)
	{
		CReplyToCommand(client, "%s Entity is no longer valid.", COLORED_CHAT_TAG);
		g_iTarget[client] = INVALID_ENT_REFERENCE;
		return Plugin_Handled;
	}
	
	char sInput[64];
	GetCmdArg(1, sInput, sizeof(sInput));
	
	char sVariantType[64];
	GetCmdArg(2, sVariantType, sizeof(sVariantType));
	
	char sVariant[64];
	GetCmdArg(3, sVariant, sizeof(sVariant));
	
	if (strlen(sVariantType) > 0 && strlen(sVariant) > 0)
	{
		if (StrEqual(sVariantType, "string", false))
			SetVariantString(sVariant);
	}
	
	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));

	AcceptEntityInput(entity, sInput);
	CReplyToCommand(client, "%s Targetted entity '%s' input '%s' sent.", COLORED_CHAT_TAG, strlen(sName) > 0 ? sName : "N/A", sInput);

	return Plugin_Handled;
}

public Action Command_Animate(int client, int args)
{
	if (g_iTarget[client] == INVALID_ENT_REFERENCE)
	{
		CReplyToCommand(client, "%s You aren't currently targeting an entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	int entity = EntRefToEntIndex(g_iTarget[client]);

	if (!IsValidEntity(entity) || entity < 1)
	{
		CReplyToCommand(client, "%s Entity is no longer valid.", COLORED_CHAT_TAG);
		g_iTarget[client] = INVALID_ENT_REFERENCE;
		return Plugin_Handled;
	}
	
	char sAnimation[64];
	GetCmdArg(1, sAnimation, sizeof(sAnimation));
	
	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));
	
	SetVariantString(sAnimation);
	AcceptEntityInput(entity, "SetAnimation");
	CReplyToCommand(client, "%s Targetted entity '%s' animation '%s' set.", COLORED_CHAT_TAG, strlen(sName) > 0 ? sName : "N/A", sAnimation);

	return Plugin_Handled;
}

public Action Command_TargetEntity(int client, int args)
{
	int entity = GetClientAimTarget(client, false);

	if (!IsValidEntity(entity))
	{
		CReplyToCommand(client, "%s You aren't aiming at a valid entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));

	g_iTarget[client] = EntIndexToEntRef(entity);
	CReplyToCommand(client, "%s Entity '%s' is now targetted by you.", COLORED_CHAT_TAG, sName);

	return Plugin_Handled;
}

public Action Command_DeleteEntity(int client, int args)
{
	if (g_iTarget[client] == INVALID_ENT_REFERENCE)
	{
		CReplyToCommand(client, "%s You aren't currently targeting an entity.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	int entity = EntRefToEntIndex(g_iTarget[client]);

	if (!IsValidEntity(entity) || entity < 1)
	{
		CReplyToCommand(client, "%s Entity is no longer valid.", COLORED_CHAT_TAG);
		g_iTarget[client] = INVALID_ENT_REFERENCE;
		return Plugin_Handled;
	}

	char sName[64];
	GetEntityName(entity, sName, sizeof(sName));

	AcceptEntityInput(entity, "Kill");
	g_iTarget[client] = INVALID_ENT_REFERENCE;
	CReplyToCommand(client, "%s Targetted entity '%s' is now deleted.", COLORED_CHAT_TAG, strlen(sName) > 0 ? sName : "N/A");

	return Plugin_Handled;
}

public Action Command_ListOwnedEntities(int client, int args)
{
	int owned = g_OwnedEntities[client].Length;

	if (owned == 0)
	{
		CReplyToCommand(client, "%s You currently don't own any entities.", COLORED_CHAT_TAG);
		return Plugin_Handled;
	}

	Menu menu = new Menu(MenuHandler_ListOwnedEntities);
	menu.SetTitle("Owned Entities:");

	int reference; int entity; char sName[64]; char sIndex[12];
	for (int i = 0; i < owned; i++)
	{
		reference = g_OwnedEntities[client].Get(i);
		entity = EntRefToEntIndex(reference);

		if (!IsValidEntity(entity))
		{
			g_OwnedEntities[client].Erase(i);
			continue;
		}

		IntToString(i, sIndex, sizeof(sIndex));
		GetEntityName(entity, sName, sizeof(sName));

		if (strlen(sName) == 0)
		{
			GetEntityClassname(entity, sName, sizeof(sName));
		}

		if (reference == g_iTarget[client])
		{
			Format(sName, sizeof(sName), "(T)%s", sName);
		}

		menu.AddItem(sIndex, sName, (reference == g_iTarget[client]) ? ITEMDRAW_DISABLED : ITEMDRAW_DEFAULT);
	}

	menu.Display(client, 20);

	return Plugin_Handled;
}

public int MenuHandler_ListOwnedEntities(Menu menu, MenuAction action, int param1, int param2)
{
	switch (action)
	{
		case MenuAction_Select:
		{
			char sIndex[12]; char sName[64];
			menu.GetItem(param2, sIndex, sizeof(sIndex), _, sName, sizeof(sName));
			int index = StringToInt(sIndex);

			int entity = EntRefToEntIndex(g_OwnedEntities[param1].Get(index));

			if (!IsValidEntity(entity))
			{
				g_OwnedEntities[param1].Erase(index);
				Command_ListOwnedEntities(param1, 0);
				return;
			}

			g_iTarget[param1] = EntIndexToEntRef(entity);
			CReplyToCommand(param1, "%s Entity '%s' is now targetted by you.", COLORED_CHAT_TAG, sName);
			Command_ListOwnedEntities(param1, 0);
		}

		case MenuAction_End:
		{
			delete menu;
		}
	}
}

public Action Command_Lock(int client, int args)
{
	ToggleLock(client);
	return Plugin_Handled;
}

void ToggleLock(int client)
{
	g_Locked = !g_Locked;
	CPrintToChatAll(g_Locked ? "Server is now locked to admins by %N." : "Server is now unlocked by %N.", client);
}

public bool OnClientConnect(int client, char[] rejectmsg, int maxlen)
{
	if (g_Locked && CheckCommandAccess(client, "", ADMFLAG_GENERIC, true))
	{
		strcopy(rejectmsg, maxlen, "Server is currently locked, you cannot access it.");
		return false;
	}
	
	return true;
}

public Action Command_CreateProp(int client, int args)
{
	float vecOrigin[3];
	GetClientCrosshairOrigin(client, vecOrigin);
	
	char sModel[PLATFORM_MAX_PATH];
	GetCmdArgString(sModel, sizeof(sModel));
	
	if (strlen(sModel) > 0 && GetEngineVersion() == Engine_TF2)
		PrecacheModel(sModel);
	
	CreateProp(sModel, vecOrigin);
	CPrintToChat(client, "Prop '%s' has been spawned.");
	
	return Plugin_Handled;
}

public Action Command_AnimateProp(int client, int args)
{
	int target = GetNearestEntity(client, "prop_dynamic");
	
	if (!IsValidEntity(target))
	{
		CPrintToChat(client, "No target has been found.");
		return Plugin_Handled;
	}
	
	char sClassname[32];
	GetEntityClassname(target, sClassname, sizeof(sClassname));
	
	if (StrContains(sClassname, "prop_dynamic") != 0)
	{
		CPrintToChat(client, "Target is not a dynamic prop entity.");
		return Plugin_Handled;
	}
	
	char sAnimation[32];
	GetCmdArgString(sAnimation, sizeof(sAnimation));
	
	if (strlen(sAnimation) == 0)
	{
		CPrintToChat(client, "Invalid animation input, please specify one.");
		return Plugin_Handled;
	}
	
	bool success = AnimateEntity(target, sAnimation);
	CPrintToChat(client, "Animation '%s' has been sent to the target %s.", sAnimation, success ? "successfully" : "unsuccessfully");
	
	return Plugin_Handled;
}

public Action Command_DeleteProp(int client, int args)
{
	int target = GetNearestEntity(client, "prop_dynamic");
	
	if (!IsValidEntity(target))
	{
		CPrintToChat(client, "No target has been found.");
		return Plugin_Handled;
	}
	
	char sClassname[32];
	GetEntityClassname(target, sClassname, sizeof(sClassname));
	
	if (StrContains(sClassname, "prop_dynamic") != 0)
	{
		CPrintToChat(client, "Target is not a dynamic prop entity.");
		return Plugin_Handled;
	}
	
	bool success = DeleteEntity(target);
	CPrintToChat(client, "Prop has been deleted %s.", success ? "successfully" : "unsuccessfully");
	
	return Plugin_Handled;
}

public Action Command_DebugEvents(int client, int args)
{
	if (g_HookEvents.Length > 0)
	{
		char sName[256];
		for (int i = 0; i < g_HookEvents.Length; i++)
		{
			g_HookEvents.GetString(i, sName, sizeof(sName));
			UnhookEvent(sName, Event_Debug);
		}
		
		g_HookEvents.Clear();
		CReplyToCommand(client, "Event debugging: OFF");
		
		return Plugin_Handled;
	}
	
	char sPath[PLATFORM_MAX_PATH];
	FormatEx(sPath, sizeof(sPath), "resource/modevents.res");
	
	KeyValues kv = new KeyValues("ModEvents");
	
	if (!kv.ImportFromFile(sPath))
	{
		delete kv;
		CPrintToChat(client, "Error finding file: %s", sPath);
		return Plugin_Handled;
	}
	
	if (!kv.GotoFirstSubKey())
	{
		delete kv;
		CPrintToChat(client, "Error parsing file: %s", sPath);
		return Plugin_Handled;
	}
	
	char sName[256];
	do
	{
		kv.GetSectionName(sName, sizeof(sName));
		HookEventEx(sName, Event_Debug);
		g_HookEvents.PushString(sName);
	}
	while (kv.GotoNextKey());
	
	delete kv;
	CReplyToCommand(client, "Event %i debugging: ON", g_HookEvents.Length);
	
	return Plugin_Handled;
}

public void Event_Debug(Event event, const char[] name, bool dontBroadcast)
{
	PrintToConsoleAll("[EVENT DEBUGGING] FIRED: %s", name);
}

public Action Command_SetRenderColor(int client, int args)
{
	int red = GetCmdArgInt(1);
	int green = GetCmdArgInt(2);
	int blue = GetCmdArgInt(3);
	int alpha = GetCmdArgInt(4);
	
	SetEntityRenderColor(client, red, green, blue, alpha);
	CPrintToChat(client, "%s Render color set to '%i/%i/%i/%i'.", COLORED_CHAT_TAG, red, green, blue, alpha);
	
	return Plugin_Handled;
}

public Action Command_SetRenderFx(int client, int args)
{
	char sArg[64];
	GetCmdArgString(sArg, sizeof(sArg));
	
	SetEntityRenderFx(client, GetRenderFxByName(sArg));
	CPrintToChat(client, "%s Render fx set to '%s'.", COLORED_CHAT_TAG, sArg);
	
	return Plugin_Handled;
}

public Action Command_SetRenderMode(int client, int args)
{
	char sArg[64];
	GetCmdArgString(sArg, sizeof(sArg));
	
	SetEntityRenderMode(client, GetRenderModeByName(sArg));
	CPrintToChat(client, "%s Render mode set to '%s'.", COLORED_CHAT_TAG, sArg);
	
	return Plugin_Handled;
}