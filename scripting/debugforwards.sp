//Pragma
#pragma semicolon 1
#pragma newdecls required

//Sourcemod Includes
#include <sourcemod>
#include <sourcemod-misc>

//Globals

public Plugin myinfo = 
{
	name = "debug start", 
	author = "Keith Warren (Shaders Allen)", 
	description = "Debugs servers on startup.", 
	version = "1.0.0", 
	url = "https://github.com/ShadersAllen"
};

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
	PrintToServer("AskPluginLoad2");
}

public void OnPluginStart()
{
	PrintToServer("OnPluginStart");
}

public void OnPluginPauseChange(bool pause)
{
	PrintToServer("OnPluginPauseChange");
}

public void OnPluginEnd()
{
	PrintToServer("OnPluginEnd");
}

public void OnConfigsExecuted()
{
	PrintToServer("OnPluginStart");
}

public void OnAllPluginsLoaded()
{
	PrintToServer("OnAllPluginsLoaded");
}

public void OnAutoConfigsBuffered()
{
	PrintToServer("OnAutoConfigsBuffered");
}

public void OnMapStart()
{
	PrintToServer("OnMapStart");
}

public void OnMapEnd()
{
	PrintToServer("OnMapEnd");
}

public void OnRebuildAdminCache(AdminCachePart part)
{
	PrintToServer("OnRebuildAdminCache");
}

public void OnAdminMenuCreated(Handle topmenu)
{
	PrintToServer("OnAdminMenuCreated");
}

public void OnAdminMenuReady(Handle topmenu)
{
	PrintToServer("OnAdminMenuReady");
}

public Action OnBanClient(int client, int time, int flags, const char[] reason, const char[] kick_message, const char[] command, any source)
{
	PrintToServer("OnBanClient");
}

public Action OnBanIdentity(const char[] identity, int time, int flags, const char[] reason, const char[] command, any source)
{
	PrintToServer("OnBanIdentity");
}

public Action OnRemoveBan(const char[] identity, int flags, const char[] command, any source)
{
	PrintToServer("OnRemoveBan");
}

public void BaseComm_OnClientGag(int client, bool gagState)
{
	PrintToServer("BaseComm_OnClientGag");
}

public void BaseComm_OnClientMute(int client, bool muteState)
{
	PrintToServer("BaseComm_OnClientMute");
}

public void OnClientCookiesCached(int client)
{
	PrintToServer("OnClientCookiesCached");
}

public void OnClientAuthorized(int client, const char[] auth)
{
	PrintToServer("OnClientAuthorized");
}

public Action OnClientCommand(int client, int args)
{
	PrintToServer("OnClientCommand");
}

public Action OnClientCommandKeyValues(int client, KeyValues kv)
{
	PrintToServer("OnClientCommandKeyValues");
}

public void OnClientCommandKeyValues_Post(int client, KeyValues kv)
{
	PrintToServer("OnClientCommandKeyValues_Post");
}

public bool OnClientConnect(int client, char[] rejectmsg, int maxlen)
{
	PrintToServer("OnClientConnect");
}

public void OnClientConnected(int client)
{
	PrintToServer("OnClientConnected");
}

public void OnClientDisconnect(int client)
{
	PrintToServer("OnClientDisconnect");
}

public void OnClientDisconnect_Post(int client)
{
	PrintToServer("OnClientDisconnect_Post");
}

public void OnClientPostAdminCheck(int client)
{
	PrintToServer("OnClientPostAdminCheck");
}

public void OnClientPostAdminFilter(int client)
{
	PrintToServer("OnClientPostAdminFilter");
}

public Action OnClientPreAdminCheck(int client)
{
	PrintToServer("OnClientPreAdminCheck");
}

public void OnClientPutInServer(int client)
{
	PrintToServer("OnClientPutInServer");
}

public void OnClientSettingsChanged(int client)
{
	PrintToServer("OnClientSettingsChanged");
}

public Action OnClientSayCommand(int client, const char[] command, const char[] sArgs)
{
	PrintToServer("OnClientSayCommand");
}

public void OnClientSayCommand_Post(int client, const char[] command, const char[] sArgs)
{
	PrintToServer("OnClientSayCommand_Post");
}

public Action CS_OnBuyCommand(int client, const char[] weapon)
{
	PrintToServer("CS_OnBuyCommand");
}

public Action CS_OnCSWeaponDrop(int client, int weaponIndex)
{
	PrintToServer("CS_OnCSWeaponDrop");
}

public Action CS_OnGetWeaponPrice(int client, const char[] weapon, int& price)
{
	PrintToServer("CS_OnGetWeaponPrice");
}

public Action CS_OnTerminateRound(float& delay, CSRoundEndReason& reason)
{
	PrintToServer("CS_OnTerminateRound");
}

public Action OnLogAction(Handle source, Identity ident, int client, int target, const char[] message)
{
	PrintToServer("OnLogAction");
}

public void OnMapVoteStarted()
{
	PrintToServer("OnMapVoteStarted");
}

public void OnNominationRemoved(const char[] map, int owner)
{
	PrintToServer("OnNominationRemoved");
}

public void OnEntityCreated(int entity, const char[] classname)
{
	PrintToServer("OnEntityCreated");
}

public void OnEntityDestroyed(int entity)
{
	PrintToServer("OnEntityDestroyed");
}

public Action OnGetGameDescription(char gameDesc[64])
{
	PrintToServer("OnGetGameDescription");
}

public Action OnLevelInit(const char[] mapName, char mapEntities[2097152])
{
	PrintToServer("OnLevelInit");
}

public Action OnFileReceive(int client, const char[] sFile)
{
	PrintToServer("OnFileReceive");
}

public Action OnFileSend(int client, const char[] sFile)
{
	PrintToServer("OnFileSend");
}

public Action OnPlayerRunCmd(int client, int& buttons, int& impulse, float vel[3], float angles[3], int& weapon, int& subtype, int& cmdnum, int& tickcount, int& seed, int mouse[2])
{
	PrintToServer("OnPlayerRunCmd");
}

public void OnPlayerRunCmdPost(int client, int buttons, int impulse, const float vel[3], const float angles[3], int weapon, int subtype, int cmdnum, int tickcount, int seed, const int mouse[2])
{
	PrintToServer("OnPlayerRunCmdPost");
}

public bool OnClientFloodCheck(int client)
{
	PrintToServer("OnClientFloodCheck");
}

public void OnClientFloodResult(int client, bool blocked)
{
	PrintToServer("OnClientFloodResult");
}

public void OnGameFrame()
{
	PrintToServer("OnGameFrame");
}

public void OnLibraryAdded(const char[] name)
{
	PrintToServer("OnLibraryAdded");
}

public void OnLibraryRemoved(const char[] name)
{
	PrintToServer("OnLibraryRemoved");
}

public Action TF2_CalcIsAttackCritical(int client, int weapon, char[] weaponname, bool& result)
{
	PrintToServer("TF2_CalcIsAttackCritical");
}

public void TF2_OnConditionAdded(int client, TFCond condition)
{
	PrintToServer("TF2_OnConditionAdded");
}

public void TF2_OnConditionRemoved(int client, TFCond condition)
{
	PrintToServer("TF2_OnConditionRemoved");
}

public Action TF2_OnIsHolidayActive(TFHoliday holiday, bool& result)
{
	PrintToServer("TF2_OnIsHolidayActive");
}

public Action TF2_OnPlayerTeleport(int client, int teleporter, bool& result)
{
	PrintToServer("TF2_OnPlayerTeleport");
}

public void TF2_OnWaitingForPlayersEnd()
{
	PrintToServer("TF2_OnWaitingForPlayersEnd");
}

public void TF2_OnWaitingForPlayersStart()
{
	PrintToServer("TF2_OnWaitingForPlayersStart");
}

public void OnMapTimeLeftChanged()
{
	PrintToServer("OnMapTimeLeftChanged");
}
