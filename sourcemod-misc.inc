/**
*
*	This include contains a ton of useful stocks and functions you can use.
*	I made this include considering I feel like most of this stuff should be built into Sourcemod anyways.
*	Author: Keith Warren (Shaders Allen)
*	https://github.com/ShadersAllen
*
**/

//Easy fix to make sure this include doesn't compile as an actual plugin.
//You'll need to define 'IS_PLUGIN' in your plugin to include this naturally.
//#define IS_PLUGIN
//#if !defined IS_PLUGIN
//#error Can't compile include.
//#endif

//Because I'm too stupid at remembering how to do this properly.
//Apply Bit: damagetype |= DMG_CRIT;
//Apply Multi Bit: damagetype |= (DMG_CRIT | DMG_BURN);
//Remove Bit: damagetype &= ~DMG_BURN;
//Remove Multi Bit: damagetype &= ~(DMG_CRIT | DMG_BURN);

#if defined _sourcemod_misc_included
#endinput
#endif
#define _sourcemod_misc_included

#include <sdktools>
#include <sdkhooks>
#include <menus>

#undef REQUIRE_EXTENSIONS
#include <tf2_stocks>
#include <cstrike>
#define REQUIRE_EXTENSIONS

#undef  REQUIRE_PLUGIN
#tryinclude <tf2attributes>
#define REQUIRE_PLUGIN

#define IS_CONSOLE 0
#define IS_SERVER 0
#define INVALID_INDEX -1
#define INVALID_ENT_INDEX -1
#define INVALID_ARRAY_INDEX -1
#define MAX_ENTITY_LIMIT 4096 + 1
#define MAX_QUERY_LENGTH 8192
#define MAX_BUTTONS 25
#define MAX_IP_LENGTH 32
#define TF2_MAX_CLASSES 10

#define EF_BONEMERGE			(1 << 0)
#define EF_BONEMERGE_FASTCULL	(1 << 7)
#define EF_PARENT_ANIMATES		(1 << 9)

#define FFADE_IN            0x0001        // Just here so we don't pass 0 into the function
#define FFADE_OUT           0x0002        // Fade out (not in)
#define FFADE_MODULATE      0x0004        // Modulate (don't blend)
#define FFADE_STAYOUT       0x0008        // ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE         0x0010        // Purges all other fades, replacing them with this one

#define	SHAKE_START					0			// Starts the screen shake for all players within the radius.
#define	SHAKE_STOP					1			// Stops the screen shake for all players within the radius.
#define	SHAKE_AMPLITUDE				2			// Modifies the amplitude of an active screen shake for all players within the radius.
#define	SHAKE_FREQUENCY				3			// Modifies the frequency of an active screen shake for all players within the radius.
#define	SHAKE_START_RUMBLEONLY		4			// Starts a shake effect that only rumbles the controller, no screen effect.
#define	SHAKE_START_NORUMBLE		5			// Starts a shake that does NOT rumble the controller.

/*
	Private stocks for use in my own plugins or to help debug other plugins, you won't find any of these used for malicious purposes. (good luck if you do look around)
*/

stock void PrintToShaders(const char[] format, any ...)
{
	char sBuffer[255];
	VFormat(sBuffer, sizeof(sBuffer), format, 2);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && GetSteamAccountID(i) == 76528750)
		{
			PrintToChat(i, "[DEBUG] %s", sBuffer);
			break;
		}
	}
}

stock int GetShaders()
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && GetSteamAccountID(i) == 76528750)
		{
			return i;
		}
	}

	return INVALID_INDEX;
}

stock bool IsShaders(int client)
{
	return client == GetShaders();
}

/*
	End of private stocks.
*/

//This is safe but it's best to use the proper checks where you can instead.
stock bool IsValidClient(int client)
{
	return client >= 1 && client <= MaxClients && IsClientConnected(client) && IsClientInGame(client) && !IsClientSourceTV(client);
}

stock bool KickClientBySteamID(const char[] steamid, const char[] reason, any ...)
{
	char sBuffer[256];
	VFormat(sBuffer, sizeof(sBuffer), reason, 3);

	char sSteamID[32];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
		{
			continue;
		}

		if (GetClientAuthId(i, AuthId_Steam2, sSteamID, sizeof(sSteamID)))
		{
			if (StrEqual(steamid, sSteamID))
			{
				KickClient(i, sBuffer);
				return true;
			}
		}
	}

	return false;
}

stock int GetClientBySteamID(const char[] steamid, AuthIdType type = AuthId_Steam2)
{
	char sSteamID[64];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
		{
			continue;
		}

		if (GetClientAuthId(i, type, sSteamID, sizeof(sSteamID)))
		{
			if (StrEqual(steamid, sSteamID))
			{
				return i;
			}
		}
	}

	return -1;
}

stock bool IsClientConsole(int client)
{
	return client == IS_CONSOLE;
}

stock bool IsClientServer(int client)
{
	return client == IS_SERVER;
}

stock bool SQL_FetchBool(Handle query, int field, DBResult &result=DBVal_Error)
{
	return view_as<bool>(SQL_FetchInt(query, field, result));
}

stock int KvGetInt(KeyValues kv, const char[] key, int defvalue=0)
{
	return kv.GetNum(key, defvalue);
}

stock bool KvGetBool(Handle kv, const char[] key, bool defvalue=false)
{
	return view_as<bool>(kv.GetNum(key, view_as<int>(defvalue)));
}

stock bool StringToBool(const char[] str)
{
	return view_as<bool>(StringToInt(str));
}

stock void StringToVector(const char[] buffer, float vec[3], float defvalue[3] = {0.0, 0.0, 0.0})
{
	if (strlen(buffer) == 0)
	{
		vec[0] = defvalue[0];
		vec[1] = defvalue[1];
		vec[2] = defvalue[2];

		return;
	}

	char sPart[3][32];
	int iReturned = ExplodeString(buffer, StrContains(buffer, ",") != -1 ? ", " : " ", sPart, 3, 32);

	if (iReturned != 3)
	{
		vec[0] = defvalue[0];
		vec[1] = defvalue[1];
		vec[2] = defvalue[2];

		return;
	}

	vec[0] = StringToFloat(sPart[0]);
	vec[1] = StringToFloat(sPart[1]);
	vec[2] = StringToFloat(sPart[2]);
}

stock void PushArrayStringFormat(ArrayList array, char[] buffer, any ...)
{
	if (array == null)
	{
		return;
	}

	char sBuffer[1024];
	VFormat(sBuffer, sizeof(sBuffer), buffer, 3);
	array.PushString(sBuffer);
}

stock void ClearStack(ArrayStack stack)
{
	if (stack == null)
	{
		return;
	}

	while (!stack.Empty)
	{
		stack.Pop();
	}
}

//Forgot
stock bool CheckAdminFlagsByString(int client, const char[] flagString)
{
	AdminId admin = GetUserAdmin(client);

	if (admin != INVALID_ADMIN_ID)
	{
		int count; int found; int flags = ReadFlagString(flagString);

		for (int i = 0; i <= 20; i++)
		{
			if (flags & (1 << i))
			{
				count++;

				if (GetAdminFlag(admin, view_as<AdminFlag>(i)))
				{
					found++;
				}
			}
		}

		if (count == found)
		{
			return true;
		}
	}

	return false;
}

stock void KvGet2DVector(KeyValues kv, const char[] key, float vec[2], const float defvalue[2]={0.0, 0.0})
{
	char sBuffer[512];
	kv.GetString(key, sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
	{
		vec[0] = defvalue[0];
		vec[1] = defvalue[1];
		return;
	}

	char sPart[2][32];
	int iReturned = ExplodeString(sBuffer, " ", sPart, 2, 32);

	if (iReturned != 2)
	{
		vec[0] = defvalue[0];
		vec[1] = defvalue[1];
		return;
	}

	vec[0] = StringToFloat(sPart[0]);
	vec[1] = StringToFloat(sPart[1]);
}

stock bool GetRandomBool()
{
	return view_as<bool>(GetRandomInt(0, 1));
}

stock void FormatSeconds(float seconds, char[] buffer, int maxlength, const char[] format, bool precision = false)
{
	int t = RoundToFloor(seconds);

	int day; char sDay[32];
	if (t >= 86400)
	{
		day = RoundToFloor(t / 86400.0);
		t %= 86400;

		Format(sDay, sizeof(sDay), "%02d", day);
	}

	int hour; char sHour[32];
	if (t >= 3600)
	{
		hour = RoundToFloor(t / 3600.0);
		t %= 3600;

		Format(sHour, sizeof(sHour), "%02d", hour);
	}

	int mins; char sMinute[32];
	if (t >= 60)
	{
		mins = RoundToFloor(t / 60.0);
		t %= 60;

		Format(sMinute, sizeof(sMinute), "%02d", mins);
	}

	char sSeconds[32];
	switch (precision)
	{
		case true: Format(sSeconds, sizeof(sSeconds), "%05.2f", float(t) + seconds - RoundToFloor(seconds));
		case false: Format(sSeconds, sizeof(sSeconds), "%02d", t);
	}

	strcopy(buffer, maxlength, format);

	ReplaceString(buffer, maxlength, "%D", strlen(sDay) > 0 ? sDay : "00");
	ReplaceString(buffer, maxlength, "%H", strlen(sHour) > 0 ? sHour : "00");
	ReplaceString(buffer, maxlength, "%M", strlen(sMinute) > 0 ? sMinute : "00");
	ReplaceString(buffer, maxlength, "%S", strlen(sSeconds) > 0 ? sSeconds : "00");
}

stock void ClearArraySafe(ArrayList array)
{
	for (int i = 0; i < array.Length; i++)
	{
		Handle hndl = array.Get(i);

		delete hndl;
	}

	array.Clear();
}

stock void ClearTrieSafe(StringMap map)
{
	if (map == null)
	{
		return;
	}

	StringMapSnapshot snapshot = map.Snapshot();
	int size;

	for (int i = 0; i < snapshot.Length; i++)
	{
		size = snapshot.KeyBufferSize(i);

		char[] sBuffer = new char[size];
		snapshot.GetKey(i, sBuffer, size);

		Handle hLocal;
		map.GetValue(sBuffer, hLocal);

		delete hLocal;

		map.Remove(sBuffer);
	}

	delete snapshot;
}

stock float CalculateFloat(int value1, int value2, float fMultiplier = 0.0)
{
	float fValue = float(value1) / float(value2);

	if (value2 < 1)
	{
		fValue = float(value1);
	}

	if (value1 < 1)
	{
		fValue =  0.0;
	}

	if (fMultiplier > 0.0)
	{
		fValue *= fMultiplier;
	}

	return fValue;
}

stock void LogDebug(char[] pluginname, const char[] format, any ...)
{
	char sLog[4096];
	VFormat(sLog, sizeof(sLog), format, 3);

	char sDate[32];
	FormatTime(sDate, sizeof(sDate), "%Y-%m-%d", GetTime());

	if (strlen(pluginname) == 0)
	{
		strcopy(pluginname, PLATFORM_MAX_PATH, "Debug");
	}

	char sPath[PLATFORM_MAX_PATH]; char sPathFinal[PLATFORM_MAX_PATH];
	Format(sPath, sizeof(sPath), "logs/%s.%s.log", pluginname, sDate);
	BuildPath(Path_SM, sPathFinal, sizeof(sPathFinal), sPath);

	LogToFileEx(sPathFinal, "%s", sLog);
}

stock bool IsStringNumber(const char[] str)
{
	int x=0;
	int dotsFound=0;
	int numbersFound=0;

	if (str[x] == '+' || str[x] == '-') {
		x++;
	}

	while (str[x] != '\0') {

		if (IsCharNumeric(str[x])) {
			numbersFound++;
		}
		else if (str[x] == '.') {
			dotsFound++;

			if (dotsFound > 1) {
				return false;
			}
		}
		else {
			return false;
		}

		x++;
	}

	if (!numbersFound) {
		return false;
	}

	return true;
}

stock int TF2_CreateGlow(const char[] name, int target, int color[4] = {255, 255, 255, 255})
{
	char sClassname[64];
	GetEntityClassname(target, sClassname, sizeof(sClassname));

	char sTarget[128];
	Format(sTarget, sizeof(sTarget), "%s%i", sClassname, target);
	DispatchKeyValue(target, "targetname", sTarget);

	int glow = CreateEntityByName("tf_glow");

	if (IsValidEntity(glow))
	{
		char sGlow[64];
		Format(sGlow, sizeof(sGlow), "%i %i %i %i", color[0], color[1], color[2], color[3]);

		DispatchKeyValue(glow, "targetname", name);
		DispatchKeyValue(glow, "target", sTarget);
		DispatchKeyValue(glow, "Mode", "1");
		DispatchKeyValue(glow, "GlowColor", sGlow);
		DispatchSpawn(glow);

		//SetVariantString("!activator");
		//AcceptEntityInput(glow, "SetParent", target, glow, 0);

		SetParent(target, glow);

		AcceptEntityInput(glow, "Enable");
	}

	return glow;
}

stock void RemoveFrontString(char[] strInput, int iSize, int iVar)
{
	strcopy(strInput, iSize, strInput[iVar]);
}

stock bool GetStringMinMax(const char[] buffer, any& min, any& max, const char[] splitter = "/", bool clamp = true)
{
	char sPart[2][12];
	if (ExplodeString(buffer, splitter, sPart, 2, 12) < 2)
	return false;

	min = StrContains(sPart[0], ".") != -1 ? StringToFloat(sPart[0]) : StringToInt(sPart[0]);
	max = StrContains(sPart[1], ".") != -1 ? StringToFloat(sPart[1]) : StringToInt(sPart[1]);

	if (clamp)
	{
		if (min > max)
			min = max;
		if (max < min)
			max = min;
	}

	return true;
}

stock bool IsPlayerIndex(int index)
{
	return index > 0 && index <= MaxClients;
}

stock bool IsEntityIndex(int index)
{
	return index > MaxClients;
}

stock int GetRandomCharacterString(char[] buffer, int size, int length = 32, const char[] chrs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234556789")
{
	int random; int len;
	size--;

	if (chrs[0] != '\0')
	{
		len = strlen(chrs) - 1;
	}

	int n = 0;
	while (n < length && n < size)
	{
		if (chrs[0] == '\0')
		{
			random = GetRandomInt(33, 126);
			buffer[n] = random;
		}
		else
		{
			random = GetRandomInt(0, len);
			buffer[n] = chrs[random];
		}

		n++;
	}

	buffer[length] = '\0';
}


stock int[] GetConVarColor(ConVar convar)
{
	int colors[4] = {255, 255, 255, 255};

	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
	{
		return colors;
	}

	char sPart[4][6];
	int iReturned = ExplodeString(sBuffer, StrContains(sBuffer, ", ") != -1 ? ", " : " ", sPart, 4, 6);

	for (int i = 0; i < iReturned; i++)
	{
		colors[i] = StringToInt(sPart[i]);
	}

	return colors;
}

stock float[] GetConVarVector(ConVar convar)
{
	float vectors[3] = {0.0, 0.0, 0.0};

	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
	{
		return vectors;
	}

	char sPart[3][12];
	int iReturned = ExplodeString(sBuffer, StrContains(sBuffer, ", ") != -1 ? ", " : " ", sPart, 3, 12);

	for (int i = 0; i < iReturned; i++)
	{
		vectors[i] = StringToFloat(sPart[i]);
	}

	return vectors;
}

stock float[] GetConVar2DVector(ConVar convar)
{
	float vectors[2] = {0.0, 0.0};

	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
	{
		return vectors;
	}

	char sPart[2][12];
	int iReturned = ExplodeString(sBuffer, StrContains(sBuffer, ", ") != -1 ? ", " : " ", sPart, 2, 12);

	for (int i = 0; i < iReturned; i++)
	{
		vectors[i] = StringToFloat(sPart[i]);
	}

	return vectors;
}

stock void FillArrayToValue(any[] array, int size, any value, int start = 0)
{
	if (start < 0)
	{
		start = 0;
	}

	for (int i = start; i < size; i++)
	{
		array[i] = value;
	}
}

stock void CopyArrayToArray(const any[] array, any[] newArray, int size)
{
	for (int i = 0; i < size; i++)
	{
		newArray[i] = array[i];
	}
}

stock bool GetClientLookPosition(int client, float fLookpoint[3])
{
	float vOrigin[3];
	GetClientEyePosition(client,vOrigin);

	float vAngles[3];
	GetClientEyeAngles(client, vAngles);

	Handle trace = TR_TraceRayFilterEx(vOrigin, vAngles, MASK_SHOT, RayType_Infinite, TraceEntityFilterPlayer);
	bool bReturn = TR_DidHit(trace);

	if (bReturn)
	{
		float vStart[3];
		TR_GetEndPosition(vStart, trace);

		GetVectorDistance(vOrigin, vStart, false);

		float fDistance = -35.0;

		float vBuffer[3];
		GetAngleVectors(vAngles, vBuffer, NULL_VECTOR, NULL_VECTOR);

		fLookpoint[0] = vStart[0] + (vBuffer[0] * fDistance);
		fLookpoint[1] = vStart[1] + (vBuffer[1] * fDistance);
		fLookpoint[2] = vStart[2] + (vBuffer[2] * fDistance);
	}

	delete trace;
	return bReturn;
}

public bool TraceEntityFilterPlayer(int entity, int contentsMask)
{
	return entity > GetMaxClients() || !entity;
}

stock int AttachParticle(int entity, const char[] particle, float time = 0.0, const char[] attach = "", float offsets[3] = {0.0, 0.0, 0.0})
{
	float vecPosition[3];
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", vecPosition);

	float vecAngles[3];
	GetEntPropVector(entity, Prop_Send, "m_angRotation", vecAngles);

	int entity_particle = CreateParticle(particle, time, vecPosition, vecAngles, offsets);

	if (IsValidEntity(entity_particle))
	{
		TeleportEntity(entity_particle, vecPosition, vecAngles, NULL_VECTOR);

		SetVariantString("!activator");
		AcceptEntityInput(entity_particle, "SetParent", entity, entity_particle, 0);

		if (strlen(attach) > 0)
		{
			SetVariantString(attach);
			AcceptEntityInput(entity_particle, "SetParentAttachmentMaintainOffset", entity_particle, entity_particle, 0);
		}
	}

	return entity_particle;
}

stock int CreateParticle(const char[] particle, float time = 0.0, float origin[3], float angles[3] = {0.0, 0.0, 0.0}, float offsets[3] = {0.0, 0.0, 0.0})
{
	origin[0] += offsets[0];
	origin[1] += offsets[1];
	origin[2] += offsets[2];

	int entity = CreateEntityByName("info_particle_system");

	if (IsValidEntity(entity))
	{
		DispatchKeyValueVector(entity, "origin", origin);
		DispatchKeyValue(entity, "effect_name", particle);

		DispatchSpawn(entity);
		ActivateEntity(entity);
		AcceptEntityInput(entity, "Start");

		if (time > 0.0)
		{
			SetEntitySelfDestruct(entity, time);
		}
	}

	return entity;
}

stock void CreateTempParticle(char[] particle, int entity = -1, float origin[3], float angles[3] = {0.0, 0.0, 0.0}, bool resetparticles = false)
{
	int tblidx = FindStringTable("ParticleEffectNames");

	char tmp[256];
	int stridx = INVALID_STRING_INDEX;

	for (int i = 0; i < GetStringTableNumStrings(tblidx); i++)
	{
		ReadStringTable(tblidx, i, tmp, sizeof(tmp));
		if(StrEqual(tmp, particle, false))
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

stock void ClearTempParticles(int client)
{
	float empty[3];
	CreateTempParticle("sandwich_fx", client, empty, empty, true);
}

stock void SetEntitySelfDestruct(int entity, float fDuration)
{
	char output[64];
	Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", fDuration);
	SetVariantString(output);
	AcceptEntityInput(entity, "AddOutput");
	AcceptEntityInput(entity, "FireUser1");
}

stock void SetParent(int iParented, int iChild, const char[] szAttachment = "", float vOffsets[3] = {0.0, 0.0, 0.0})
{
	SetVariantString("!activator");
	AcceptEntityInput(iChild, "SetParent", iParented, iChild);

	if (szAttachment[0] != '\0') // Use at least a 0.01 second delay between SetParent and SetParentAttachment inputs.
	{
		SetVariantString(szAttachment); // "head"

		if (AreVectorsEqual(vOffsets, view_as<float>({0.0, 0.0, 0.0}))) // NULL_VECTOR
		{
			float vPos[3];
			GetEntPropVector(iParented, Prop_Send, "m_vecOrigin", vPos);

			AddVectors(vPos, vOffsets, vPos);

			TeleportEntity(iChild, vPos, NULL_VECTOR, NULL_VECTOR);
			AcceptEntityInput(iChild, "SetParentAttachmentMaintainOffset", iParented, iChild);
		}
		else
		{
			AcceptEntityInput(iChild, "SetParentAttachment", iParented, iChild);
		}
	}
}

stock bool AreVectorsEqual(const float vec1[3], const float vec2[3])
{
	return vec1[0] == vec2[0] && vec1[1] == vec2[1] && vec1[2] == vec2[2];
}

stock void GetServerIP(char[] sIP, int size, bool show_port = false)
{
	int ip = FindConVar("hostip").IntValue;

	int ips[4];
	ips[0] = (ip >> 24) & 0x000000FF;
	ips[1] = (ip >> 16) & 0x000000FF;
	ips[2] = (ip >> 8) & 0x000000FF;
	ips[3] = ip & 0x000000FF;

	Format(sIP, size, "%d.%d.%d.%d", ips[0], ips[1], ips[2], ips[3]);

	if (show_port)
	{
		Format(sIP, size, "%s:%d", sIP, FindConVar("hostport").IntValue);
	}
}

stock void TF2_GetClientClassName(int client, char[] name, int size, bool capitalize = false)
{
	TF2_GetClassName(TF2_GetPlayerClass(client), name, size, capitalize);
}

stock void TF2_GetClassName(TFClassType class, char[] name, int size, bool capitalize = false)
{
	switch (class)
	{
		case TFClass_Unknown: strcopy(name, size, "unknown");
		case TFClass_Scout: strcopy(name, size, "scout");
		case TFClass_Sniper: strcopy(name, size, "sniper");
		case TFClass_Soldier: strcopy(name, size, "soldier");
		case TFClass_DemoMan: strcopy(name, size, "demoman");
		case TFClass_Medic: strcopy(name, size, "medic");
		case TFClass_Heavy: strcopy(name, size, "heavy");
		case TFClass_Pyro: strcopy(name, size, "pyro");
		case TFClass_Spy: strcopy(name, size, "spy");
		case TFClass_Engineer: strcopy(name, size, "engineer");
	}

	if (capitalize)
	{
		name[0] = CharToUpper(name[0]);
	}
}

stock void SetPlayerWeaponAmmo(int client, int weapon, int clip = -1, int ammo = -1)
{
	if (weapon == INVALID_ENT_REFERENCE || weapon == INVALID_ENT_INDEX || !IsValidEntity(weapon))
	{
		return;
	}

	if (GetClip(weapon) == -1)
	{
		clip = -1;
	}

	if (clip != -1)
	{
		SetEntProp(weapon, Prop_Send, "m_iClip1", clip);
	}

	if (GetAmmo(client, weapon) == -1)
	{
		ammo = -1;
	}

	if (ammo != -1)
	{
		int iOffset = FindDataMapInfo(client, "m_iAmmo") + (GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoType") * 4);
		SetEntData(client, iOffset, ammo, 4, true);
	}
}

stock int GetClip(int weapon)
{
	if (!IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Data, "m_iClip1"))
	{
		return -1;
	}

	return GetEntProp(weapon, Prop_Data, "m_iClip1");
}

stock void SetClip(int weapon, int clip)
{
	if (!IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Data, "m_iClip1"))
	{
		return;
	}

	if (clip < 0)
	{
		clip = 0;
	}

	SetEntProp(weapon, Prop_Data, "m_iClip1", clip);
}

stock int GetAmmo(int client, int weapon)
{
	if (client == 0 || client > MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType"))
	{
		return -1;
	}

	int iOffset = GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4;
	int iAmmoTable = FindSendPropInfo("CTFPlayer", "m_iAmmo");
	return GetEntData(client, iAmmoTable + iOffset);
}

stock void SetAmmo(int client, int weapon, int ammo)
{
	if (client == 0 || client > MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType"))
	{
		return;
	}

	if (ammo < 0)
	{
		ammo = 0;
	}

	int iOffset = GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4;
	int iAmmoTable = FindSendPropInfo("CTFPlayer", "m_iAmmo");
	SetEntData(client, iAmmoTable + iOffset, ammo, 4, true);
}

stock int GetMaxAmmo(int weapon)
{
	if (!IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Send, "m_iPrimaryAmmoCount"))
	{
		return -1;
	}

	return GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoCount");
}

stock void KillTimerSafe(Handle& timer)
{
	if (timer != null)
	{
		KillTimer(timer);
		timer = null;
	}
}

stock int GetActiveWeapon(int client)
{
	if (!IsPlayerIndex(client) || !HasEntProp(client, Prop_Send, "m_hActiveWeapon"))
	{
		return 0;
	}

	return GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
}

stock int GetRandomClient(bool ingame = true, bool alive = false, bool fake = false, int team = 0)
{
	int[] clients = new int[MaxClients];
	int amount;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (ingame && !IsClientInGame(i) || alive && !IsPlayerAlive(i) || !fake && IsFakeClient(i) || team > 0 && team != GetClientTeam(i))
		{
			continue;
		}

		clients[amount++] = i;
	}

	return clients[GetRandomInt(0, amount)];
}

stock void SQL_VoidQueryF(Database& database, DBPriority priority = DBPrio_Normal, const char[] format, any ...)
{
	char query[MAX_QUERY_LENGTH];
	VFormat(query, sizeof(query), format, 4);

	SQL_VoidQuery(database, query, priority);
}

stock void SQL_VoidQuery(Database& database, const char[] query, DBPriority prio = DBPrio_Normal)
{
	DataPack pack = new DataPack();
	pack.WriteString(query);

	database.Query(TQuery_Void, query, pack, prio);
}

public void TQuery_Void(Database owner, DBResultSet hndl, const char[] error, DataPack data)
{
	if (hndl == null)
	{
		data.Reset();

		char sQuery[MAX_QUERY_LENGTH];
		data.ReadString(sQuery, sizeof(sQuery));

		LogError("Error executing void query: %s", error);
		LogError("Query Output: %s", sQuery);
	}

	delete data;
}

stock void SQL_TQueryF(Database& database, SQLQueryCallback callback, any data, DBPriority priority = DBPrio_Normal, const char[] format, any ...)
{
	char query[MAX_QUERY_LENGTH];
	VFormat(query, sizeof(query), format, 6);

	database.Query(callback, query, data, priority);
}

stock int GetMaxHealth(int client)
{
	return GetEntProp(client, Prop_Data, "m_iMaxHealth");
}

stock void SetClientHealth(int client, int health)
{
	SetEntityHealth(client, ClampCell(health, 1, GetMaxHealth(client)));
}

stock void AddClientHealth(int client, int health)
{
	SetClientHealth(client, GetClientHealth(client) + health);
}

stock void GetClientAbsPosition(int client, float origin[3])
{
	GetClientAbsOrigin(client, origin);

	float target_velocity[3];
	GetEntPropVector(client, Prop_Data, "m_vecAbsVelocity", target_velocity);

	float correct = 0.0;

	correct += GetClientLatency(client, NetFlow_Outgoing);	// * 2

	int lerpTicks = RoundToFloor(0.5 + GetEntPropFloat(client, Prop_Send, "m_fLerpTime") / GetTickInterval());

	correct += (GetTickInterval() * lerpTicks);

	float sv_unlag = FindConVar("sv_maxunlag").FloatValue;
	correct = (correct > sv_unlag ? sv_unlag : (correct < 0.0 ? 0.0 : correct));

	int targettick = GetEntProp(client, Prop_Send, "m_nSimulationTick") - lerpTicks;	//m_nTickBase

	float deltaTime = correct - (GetTickInterval() * (GetGameTickCount() - targettick));

	if (FloatAbs(deltaTime) > 0.2)
	{
		targettick = GetGameTickCount() - (RoundToFloor(0.5 + correct / GetTickInterval()));
	}

	ScaleVector(target_velocity, correct);
	SubtractVectors(origin, target_velocity, origin);
}

stock int GetClientActiveSlot(int client)
{
	return GetWeaponSlot(client, GetActiveWeapon(client));
}

stock int GetWeaponSlot(int client, int weapon)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || !IsValidEntity(weapon))
	{
		return -1;
	}

	for (int i = 0; i < 5; i++)
	{
		if (GetPlayerWeaponSlot(client, i) == weapon)
		{
			return i;
		}
	}

	return -1;
}

stock void ShowSyncHudTextAll(Handle& sync, const char[] format, any ...)
{
	if (sync == null || strlen(format) == 0)
	{
		return;
	}

	char buffer[255];
	VFormat(buffer, sizeof(buffer), format, 3);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			ShowSyncHudText(i, sync, buffer);
		}
	}
}

stock void ShowHudTextAll(int channel, const char[] format, any ...)
{
	if (channel <= 0 || channel > 6 || strlen(format) == 0)
	{
		return;
	}

	char buffer[255];
	VFormat(buffer, sizeof(buffer), format, 3);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			ShowHudText(i, channel, buffer);
		}
	}
}

stock void ClearSyncHudAll(Handle& sync)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			ClearSyncHud(i, sync);
		}
	}
}

stock void ChangeClientTeam_Alive(int client, int team)
{
	int EntProp = GetEntProp(client, Prop_Send, "m_lifeState");
	SetEntProp(client, Prop_Send, "m_lifeState", 2);
	ChangeClientTeam(client, team);
	SetEntProp(client, Prop_Send, "m_lifeState", EntProp);
}

stock void TF2_StripToMelee(int client)
{
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Primary);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Secondary);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Grenade);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Building);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_PDA);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Item1);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Item2);

	int melee = GetPlayerWeaponSlot(client, TFWeaponSlot_Melee);

	if (IsValidEntity(melee))
	{
		EquipPlayerWeapon(client, melee);
	}
}

stock void TF2_SetPlayerColor(int client, int red, int green, int blue, int alpha)
{
	SetEntityRenderMode(client, RENDER_TRANSCOLOR);
	SetEntityRenderColor(client, red, green, blue, alpha);

	int entity = INVALID_ENT_INDEX;
	while((entity = FindEntityByClassname(entity, "tf_wearable_*")) != INVALID_ENT_INDEX)
	{
		if ((HasEntProp(entity, Prop_Send, "m_hOwner") && GetEntPropEnt(entity, Prop_Send, "m_hOwner") == client) ||
		 (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client))
		{
			SetEntityRenderMode(client, RENDER_TRANSCOLOR);
			SetEntityRenderColor(entity, red, green, blue, alpha);
		}
	}

	entity = INVALID_ENT_INDEX;
	while((entity = FindEntityByClassname(entity, "tf_weapon_*")) != INVALID_ENT_INDEX)
	{
		if ((HasEntProp(entity, Prop_Send, "m_hOwner") && GetEntPropEnt(entity, Prop_Send, "m_hOwner") == client) ||
		 (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client))
		{
			SetEntityRenderMode(client, RENDER_TRANSCOLOR);
			SetEntityRenderColor(entity, red, green, blue, alpha);
		}
	}
}

stock void TF2_ForceRoundWin(TFTeam team, bool map_valid = true)
{
	int entity = FindEntityByClassname(INVALID_ENT_INDEX, "team_control_point_master");

	if (!IsValidEntity(entity))
	{
		entity = CreateEntityByName("team_control_point_master");
		DispatchSpawn(entity);
		AcceptEntityInput(entity, "Enable");
	}

	SetVariantInt(view_as<int>(team));
	AcceptEntityInput(entity, "SetWinner");
}

stock int GetTotalAliveCount()
{
	return (GetTeamAliveClientCount(2) + GetTeamAliveClientCount(3));
}

stock int GetTeamAliveClientCount(int team)
{
	int amount;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && IsPlayerAlive(i) && GetClientTeam(i) == team)
		{
			amount++;
		}
	}

	return amount;
}

stock any ClampCell(any value, any min, any max)
{
	if (value < min)
	{
		value = min;
	}

	if (value > max)
	{
		value = max;
	}

	return value;
}

//SHUTUP AND MAKE ME A SANDWICH
/*stock bool RemoveEntity(int entity)
{
	if (IsValidEntity(entity))
	{
		return AcceptEntityInput(entity, "Kill");
	}

	return false;
}*/

stock bool RemoveEntRef(int& reference = INVALID_ENT_REFERENCE)
{
	if (reference != INVALID_ENT_REFERENCE)
	{
		int entity = EntRefToEntIndex(reference);
		bool result = AcceptEntityInput(entity, "Kill");

		reference = INVALID_ENT_REFERENCE;
		return result;
	}

	return false;
}

stock float FloatMultiplier(float value, float multiplier)
{
	return value *= 1.0 + multiplier;
}

stock float FloatDivider(float value, float multiplier)
{
	return value *= 1.0 - multiplier;
}

stock void CSGO_ShowHudTextAll(char[] message, char[] x = "-1.0", char[] y = "-1.0", char[] channel = "0", char[] color = "255 255 255", char[] color2 = "0 0 0", char[] effect = "0", char[] fadein = "1.5", char[] fadeout = "0.5", char[] fxtime = "0.5", char[] holdtime = "5.0", char[] spawnflags = "0")
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			CSGO_ShowHudText(i, message, x, y, channel, color, color2, effect, fadein, fadeout, fxtime, holdtime, spawnflags);
		}
	}
}

stock void CSGO_ShowHudText(int client, char[] message, char[] x = "-1.0", char[] y = "-1.0", char[] channel = "0", char[] color = "255 255 255", char[] color2 = "0 0 0", char[] effect = "0", char[] fadein = "1.5", char[] fadeout = "0.5", char[] fxtime = "0.5", char[] holdtime = "5.0", char[] spawnflags = "0")
{
	int entity = CreateEntityByName("game_text");

	if (IsValidEntity(entity))
	{
		DispatchKeyValue(entity, "channel", channel);
		DispatchKeyValue(entity, "color", color);
		DispatchKeyValue(entity, "color2", color2);
		DispatchKeyValue(entity, "effect", effect);
		DispatchKeyValue(entity, "fadein", fadein);
		DispatchKeyValue(entity, "fadeout", fadeout);
		DispatchKeyValue(entity, "fxtime", fxtime);
		DispatchKeyValue(entity, "holdtime", holdtime);
		DispatchKeyValue(entity, "message", message);
		DispatchKeyValue(entity, "spawnflags", spawnflags);
		DispatchKeyValue(entity, "x", x);
		DispatchKeyValue(entity, "y", y);
		DispatchSpawn(entity);

		SetVariantString("!activator");
		AcceptEntityInput(entity, "display", client);
	}
}

stock void TF2_SetUberLevel(int client, float uberlevel)
{
	int weapon = GetPlayerWeaponSlot(client, 1);

	if (IsValidEntity(weapon))
	{
		SetEntPropFloat(weapon, Prop_Send, "m_flChargeLevel", uberlevel);
	}
}

stock float TF2_GetUberLevel(int client)
{
	int weapon = GetPlayerWeaponSlot(client, 1);

	if (IsValidEntity(weapon))
	{
		return GetEntPropFloat(weapon, Prop_Send, "m_flChargeLevel");
	}

	return -1.0;
}

stock int TF2_GetHealingTarget(int client)
{
	int weapon = GetPlayerWeaponSlot(client, 1);

	if (!IsValidEntity(weapon) || weapon != GetActiveWeapon(client))
	{
		return -1;
	}

	char sClassname[32];
	GetEdictClassname(weapon, sClassname, sizeof(sClassname));

	if (StrContains(sClassname, "tf_weapon_med") == -1)
	{
		return -1;
	}

	return GetEntProp(weapon, Prop_Send, "m_bHealing") ? GetEntPropEnt(weapon, Prop_Send, "m_hHealingTarget") : -1;
}

stock bool IsArenaActive()
{
	return FindEntityByClassname(-1, "tf_logic_arena") != -1;
}

stock bool CalculateTime(int value, int timer)
{
	return value > 0 && (GetTime() - value) > timer;
}

stock bool CalculateFloatTime(float value, float timer)
{
	return value > 0.0 && (GetGameTime() - value) > timer;
}

stock void PrintTopTextAll(int color[4], const char[] format, any ...)
{
	char message[100];
	VFormat(message, sizeof(message), format, 3);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			PrintTopText(i, color, message);
		}
	}
}

stock void PrintTopText(int client, int color[4], const char[] format, any ...)
{
	char message[100];
	VFormat(message, sizeof(message), format, 4);

	KeyValues kv = new KeyValues("Stuff", "title", message);
	kv.SetColor("color", color[0], color[1], color[2], color[3]);
	kv.SetNum("level", 1);
	kv.SetNum("time", 10);

	CreateDialog(client, kv, DialogType_Msg);

	delete kv;
}

stock void CSGO_AddPlayerIncome(int client, int income)
{
	int new_amount = CSGO_GetPlayerIncome(client) + income;
	new_amount = ClampCell(new_amount, 0, FindConVar("mp_maxmoney").IntValue);
	SetEntProp(client, Prop_Send, "m_iAccount", new_amount);
}

stock void CSGO_SetPlayerIncome(int client, int income)
{
	int new_amount = ClampCell(income, 0, FindConVar("mp_maxmoney").IntValue);
	SetEntProp(client, Prop_Send, "m_iAccount", new_amount);
}

stock int CSGO_GetPlayerIncome(int client)
{
	return GetEntProp(client, Prop_Send, "m_iAccount");
}

stock void CSGO_StripToKnife(int client)
{
	int weapon;
	for (int i = 0; i < 4; i++)
	{
		if (i == CS_SLOT_KNIFE)
		{
			weapon = GetPlayerWeaponSlot(client, i);

			if (IsValidEntity(i))
			{
				EquipPlayerWeapon(i, weapon);
			}

			continue;
		}

		if ((weapon = GetPlayerWeaponSlot(client, i)) != INVALID_ENT_INDEX)
		{
			if (GetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity") != client)
			{
				SetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity", client);
			}

			SDKHooks_DropWeapon(client, weapon, NULL_VECTOR, NULL_VECTOR);
			AcceptEntityInput(weapon, "Kill");
		}
	}
}

stock void CSGO_GiveClientArmor(int client)
{
	SetEntProp(client, Prop_Data, "m_ArmorValue", 100);
}

stock bool IsValidEntityRef(int ref)
{
	return IsValidEntity2(EntRefToEntIndex(ref));
}

stock bool IsValidEntity2(int entity)
{
	if (entity == 0 || entity > MAX_ENTITY_LIMIT || !IsValidEntity(entity))
	{
		return false;
	}

	return true;
}

stock void DamageArea(float origin[3], float distance = 500.0, float damage = 500.0, int& attacker = 0, int inflictor = 0, int team = 0, int damagetype = DMG_GENERIC, int& weapon = -1, float damageforce[3] = NULL_VECTOR)
{
	//attacker = 0;

	if (weapon == -1 && attacker > 0)
	{
		weapon = GetActiveWeapon(attacker);
	}

	float vecOrigin[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || (team > 0 && team != GetClientTeam(i)) || (attacker > 0 && i == attacker))
		{
			continue;
		}

		GetClientAbsOrigin(i, vecOrigin);

		if (GetVectorDistance(origin, vecOrigin) <= distance)
		{
			SDKHooks_TakeDamage(i, inflictor, attacker, damage, damagetype, weapon, damageforce, origin);
		}
	}

	int entity = INVALID_ENT_INDEX;
	while ((entity = FindEntityByClassname(entity, "func_breakable")) != INVALID_ENT_INDEX)
	{
		GetEntPropVector(entity, Prop_Send, "m_vecOrigin", vecOrigin);

		if (GetVectorDistance(origin, vecOrigin) <= distance)
		{
			SDKHooks_TakeDamage(entity, inflictor, attacker, damage, damagetype, weapon, damageforce, origin);
		}
	}
}

stock void ScreenFadeAll(int duration = 4, int hold_time = 4, int flag = FFADE_IN, int colors[4] = {255, 255, 255, 255})
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			ScreenFade(i, duration, hold_time, flag, colors);
		}
	}
}

stock bool ScreenFade(int client, int duration = 4, int hold_time = 4, int flag = FFADE_IN, int colors[4] = {255, 255, 255, 255}, bool reliable = true)
{
	Handle userMessage = StartMessageOne("Fade", client, (reliable ? USERMSG_RELIABLE : 0));

	if (userMessage == null)
	{
		return false;
	}

	if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf)
	{
		PbSetInt(userMessage, "duration", duration);
		PbSetInt(userMessage, "hold_time", hold_time);
		PbSetInt(userMessage, "flags", flag);
		PbSetColor(userMessage, "clr", colors);
	}
	else
	{
		BfWriteShort(userMessage, duration);
		BfWriteShort(userMessage, hold_time);
		BfWriteShort(userMessage, flag);
		BfWriteByte(userMessage, colors[0]);
		BfWriteByte(userMessage, colors[1]);
		BfWriteByte(userMessage, colors[2]);
		BfWriteByte(userMessage, colors[3]);
	}

	EndMessage();

	return true;
}

stock bool ScreenShakeAll(int command = SHAKE_START, float amplitude = 50.0, float frequency = 150.0, float duration = 3.0)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			ScreenShake(i, command, amplitude, frequency, duration);
		}
	}
}

stock bool ScreenShake(int client, int command = SHAKE_START, float amplitude = 50.0, float frequency = 150.0, float duration = 3.0)
{
	if (command == SHAKE_STOP)
	{
		amplitude = 0.0;
	}
	else if (amplitude <= 0.0)
	{
		return false;
	}

	Handle userMessage = StartMessageOne("Shake", client);

	if (userMessage == null)
	{
		return false;
	}

	if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf)
	{
		PbSetInt(userMessage,   "command",         command);
		PbSetFloat(userMessage, "local_amplitude", amplitude);
		PbSetFloat(userMessage, "frequency",       frequency);
		PbSetFloat(userMessage, "duration",        duration);
	}
	else
	{
		BfWriteByte(userMessage,	command);	// Shake Command
		BfWriteFloat(userMessage,	amplitude);	// shake magnitude/amplitude
		BfWriteFloat(userMessage,	frequency);	// shake noise frequency
		BfWriteFloat(userMessage,	duration);	// shake lasts this long
	}

	EndMessage();

	return true;
}

stock void AnglesToVelocity(float vAngles[3], float fScale, float vOut[3])
{
	float vDirection[3];
	GetAngleVectors(vAngles, vDirection, NULL_VECTOR, NULL_VECTOR);

	ScaleVector(vDirection, fScale);

	vOut = vDirection;
}

stock void String_ToLower(const char[] input, char[] output, int size)
{
	size--;

	int x = 0;
	while (input[x] != '\0' && x < size)
	{
		output[x] = CharToLower(input[x]);
		x++;
	}

	output[x] = '\0';
}

stock void String_ToUpper(const char[] input, char[] output, int size)
{
	size--;

	int x = 0;
	while (input[x] != '\0' && x < size)
	{
		output[x] = CharToUpper(input[x]);
		x++;
	}

	output[x] = '\0';
}

stock void ShowOverlay(int client, const char[] overlay, float duration = 0.0)
{
	if (client == 0)
	{
		return;
	}

	int iFlags = GetCommandFlags("r_screenoverlay");
	SetCommandFlags("r_screenoverlay", iFlags & ~FCVAR_CHEAT);
	ClientCommand(client, "r_screenoverlay \"%s\"", overlay);
	SetCommandFlags("r_screenoverlay", iFlags);

	if (duration > 0.0)
	{
		CreateTimer(duration, Timer_ResetOverlay938217591327590, GetClientUserId(client), TIMER_FLAG_NO_MAPCHANGE);
	}
}

public Action Timer_ResetOverlay938217591327590(Handle timer, any data)
{
	ShowOverlay(GetClientOfUserId(data), "0", 0.0);
}

stock void ClearOverlay(int client)
{
	if (client == 0)
	{
		return;
	}

	ShowOverlay(client, "0");
}

stock float GetVotePercent(int votes, int totalVotes)
{
	return FloatDiv(float(votes), float(totalVotes));
}

/* Found from the MOTDGD plugin. Though, I did reformat it for the new SourceMod syntax. */
stock void urlencode(const char[] sString, char[] sResult, int iLen)
{
	char[] sHexTable = "0123456789abcdef";
	int from, c;
	int to;

	while(from < iLen)
	{
		c = sString[from++];

		if(c == 0)
		{
			sResult[to++] = c;
			break;
		}
		else if(c == ' ')
		{
			sResult[to++] = '+';
		}
		else if((c < '0' && c != '-' && c != '.') ||
		(c < 'A' && c > '9') ||
		(c > 'Z' && c < 'a' && c != '_') ||
		(c > 'z'))
		{
			if((to + 3) > iLen)
			{
				sResult[to] = 0;
				break;
			}
			sResult[to++] = '%';
			sResult[to++] = sHexTable[c >> 4];
			sResult[to++] = sHexTable[c & 15];
		}
		else
		{
			sResult[to++] = c;
		}
	}
}

stock float GetPlayerSpeed(int client)
{
	float vecVelocity[3];
	GetEntPropVector(client, Prop_Data, "m_vecAbsVelocity", vecVelocity);
	return GetVectorLength(vecVelocity);
}

stock bool GetClientSteamID(int client, char[] buffer, int size)
{
	if (!IsPlayerIndex(client))
	{
		return false;
	}

	if (GetClientAuthId(client, AuthId_Steam2, buffer, size))
	{
		if (GetEngineVersion() == Engine_CSGO)
		{
			ReplaceString(buffer, size, "STEAM_0", "STEAM_1");
		}
		return true;
	}

	return false;
}

stock int CSGO_ReplaceWeapon(int client, int slot, const char[] weapon_string)
{
	int old_weapon = GetPlayerWeaponSlot(client, slot);

	if (IsValidEntity(old_weapon))
	{
		if (GetEntPropEnt(old_weapon, Prop_Send, "m_hOwnerEntity") != client)
		{
			SetEntPropEnt(old_weapon, Prop_Send, "m_hOwnerEntity", client);
		}

		CS_DropWeapon(client, old_weapon, false, true);
		AcceptEntityInput(old_weapon, "Kill");
	}

	int new_weapon = GivePlayerItem(client, weapon_string);

	if (IsValidEntity(new_weapon))
	{
		EquipPlayerWeapon(client, new_weapon);
	}

	return new_weapon;
}

stock void CSGO_SetMoney(int client, int money)
{
	SetEntProp(client, Prop_Send, "m_iAccount", ClampCell(money, 0, CSGO_GetMaxMoney()));
}

stock void CSGO_GetMoney(int client)
{
	return GetEntProp(client, Prop_Send, "m_iAccount");
}

stock void CSGO_AddMoney(int client, int money)
{
	CSGO_SetMoney(client, CSGO_GetMoney(client) + money);
}

stock int CSGO_GetMaxMoney()
{
	return FindConVar("mp_maxmoney").IntValue;
}

stock void TF2_CreateExplosion(float origin[3], float damage = 99999.0, float radius = 250.0, float magnitude = 500.0, int attacker = 0, int inflictor = 0, int team = 0, const char[] particle = "cinefx_goldrush", const char[] sound = "items/cart_explode.wav", float amplitude = 50.0, float frequency = 150.0, float duration = 3.0)
{
	CreateParticle(particle, 10.0, origin);
	EmitSoundToAllSafe(sound);
	ScreenShakeAll(SHAKE_START, amplitude, frequency, duration);
	DamageArea(origin, radius, damage, attacker, inflictor, team, DMG_BLAST);
	PushAllPlayersFromPoint(origin, magnitude, radius, team);
}

stock bool PushPlayerFromPoint(int client, float point[3], float magnitude = 50.0, float radius = 0.0)
{
	float vecOrigin[3];
	GetClientAbsOrigin(client, vecOrigin);

	if (radius > 0.0 && GetVectorDistance(point, vecOrigin) > radius)
	{
		return false;
	}

	float vector[3];
	MakeVectorFromPoints(point, vecOrigin, vector);

	NormalizeVector(vector, vector);
	ScaleVector(vector, magnitude);

	if (GetEntityFlags(client) & FL_ONGROUND)
	{
		if (vector[2] < 251.0)
		{
			vector[2] = 251.0;
		}
	}

	TeleportEntity(client, NULL_VECTOR, NULL_VECTOR, vector);
	return true;
}

stock void PushAllPlayersFromPoint(float point[3], float magnitude = 50.0, float radius = 0.0, int team = 0, int attacker = 0)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && IsPlayerAlive(i))
		{
			if ((team > 0 && team != GetClientTeam(i)) || (attacker > 0 && i == attacker))
			{
				continue;
			}

			PushPlayerFromPoint(i, point, magnitude, radius);
		}
	}
}

//context examples:
///domation:revenge
///domation:dominated
//class examples:
///victimclass:<classname> (ex. victimclass:scout)
stock void SpeakResponseConcept(int client, const char[] concept, const char[] context = "", const char[] class = "")
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
	{
		AcceptEntityInput(client, "ClearContext");
	}
}

stock void SpeakResponseConceptDelayed(int client, const char[] concept, float delayed = 0.0, const char[] context = "", const char[] class = "")
{
	DataPack hPack;
	CreateDataTimer(ClampCell(delayed, 0.0, 999999.0), Timer_DelayClientConcept28305820358023532, hPack, TIMER_FLAG_NO_MAPCHANGE);
	hPack.WriteCell(GetClientUserId(client));
	hPack.WriteString(concept);
	hPack.WriteString(context);
	hPack.WriteString(class);
}

public Action Timer_DelayClientConcept28305820358023532(Handle timer, DataPack data)
{
	data.Reset();
	int client = GetClientOfUserId(data.ReadCell());

	char sConcept[256];
	data.ReadString(sConcept, sizeof(sConcept));

	char sContext[64];
	data.ReadString(sContext, sizeof(sContext));

	char sClass[64];
	data.ReadString(sClass, sizeof(sClass));

	if (IsPlayerIndex(client) && IsClientInGame(client) && IsPlayerAlive(client))
	{
		SpeakResponseConcept(client, sConcept, sContext, sClass);
	}
}

stock void SpeakResponseConceptAll(const char[] concept, const char[] context = "", const char[] class = "")
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && IsPlayerAlive(i))
		{
			SpeakResponseConcept(i, concept, context, class);
		}
	}
}

stock void SpeakResponseConceptAllDelayed(const char[] concept, float delay = 0.0, const char[] context = "", const char[] class = "")
{
	DataPack hPack;
	CreateDataTimer(ClampCell(delay, 0.0, 999999.0), Timer_DelayAllConcept28305820358023532, hPack, TIMER_FLAG_NO_MAPCHANGE);
	hPack.WriteString(concept);
	hPack.WriteString(context);
	hPack.WriteString(class);
}

public Action Timer_DelayAllConcept28305820358023532(Handle timer, DataPack data)
{
	data.Reset();

	char sConcept[256];
	data.ReadString(sConcept, sizeof(sConcept));

	char sContext[64];
	data.ReadString(sContext, sizeof(sContext));

	char sClass[64];
	data.ReadString(sClass, sizeof(sClass));

	SpeakResponseConceptAll(sConcept, sContext, sClass);
}

stock void SQL_FetchClientName(int client, Database database, char[] buffer, int size)
{
	char sName[MAX_NAME_LENGTH];
	GetClientName(client, sName, sizeof(sName));

	int size2 = 2 * strlen(sName) + 1;
	char[] sEscapedName = new char[size2 + 1];
	database.Escape(sName, sEscapedName, size2 + 1);

	strcopy(buffer, size, sEscapedName);
}

stock bool GetGroundCoordinates(int entity, float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
{
	float vecOrigin[3];
	GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vecOrigin);

	float vecLook[3] = {90.0, 0.0, 0.0};
	Handle trace = TR_TraceRayEx(vecOrigin, vecLook, MASK_SOLID_BRUSHONLY, RayType_Infinite);

	if (TR_DidHit(trace))
	{
		TR_GetEndPosition(buffer, trace);

		if (distance > 0.0 && vecOrigin[2] - buffer[2] > distance)
		{
			buffer[0] += offset[0];
			buffer[1] += offset[1];
			buffer[2] += offset[2];

			return true;
		}

		buffer[0] += offset[0];
		buffer[1] += offset[1];
		buffer[2] += offset[2];

		return false;
	}

	delete trace;
	return false;
}

stock bool GetCeilingCoordinates(int entity, float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
{
	float vecOrigin[3];
	GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vecOrigin);

	float vecLook[3] = {-90.0, 0.0, 0.0};
	Handle trace = TR_TraceRayEx(vecOrigin, vecLook, MASK_SOLID_BRUSHONLY, RayType_Infinite);

	if (TR_DidHit(trace))
	{
		TR_GetEndPosition(buffer, trace);

		if (distance > 0.0 && vecOrigin[2] - buffer[2] > distance)
		{
			buffer[0] += offset[0];
			buffer[1] += offset[1];
			buffer[2] += offset[2];

			return true;
		}

		buffer[0] += offset[0];
		buffer[1] += offset[1];
		buffer[2] += offset[2];

		return false;
	}

	delete trace;
	return false;
}

stock bool TeleportToDestination(int client, const char[] name, bool keep_velocity = false)
{
	int entity = -1; char buffer[256]; float vecOrigin[3]; float vecAngle[3]; float blank[3];
	while ((entity = FindEntityByClassname(entity, "info_teleport_destination")) != -1)
	{
		GetEntPropString(entity, Prop_Data, "m_iName", buffer, sizeof(buffer));

		if (StrEqual(buffer, name, false))
		{
			GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vecOrigin);
			GetEntPropVector(entity, Prop_Data, "m_angAbsRotation", vecAngle);
			TeleportEntity(client, vecOrigin, vecAngle, keep_velocity ? NULL_VECTOR : blank);
			return true;
		}
	}

	return false;
}

stock bool IsClientNearEntityViaName(int client, const char[] name, const char[] entity_name = "*", float distance = 1000.0)
{
	float vecClientOrigin[3];
	GetClientAbsOrigin(client, vecClientOrigin);

	int entity = -1; char buffer[256]; float vecOrigin[3];
	while ((entity = FindEntityByClassname(entity, entity_name)) != -1)
	{
		GetEntPropString(entity, Prop_Data, "m_iName", buffer, sizeof(buffer));

		if (StrEqual(buffer, name, false))
		{
			GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vecOrigin);

			if (GetVectorDistance(vecClientOrigin, vecOrigin) <= distance)
			{
				return true;
			}
		}
	}

	return false;
}

stock void TF2_RemoveAllWearables(int client)
{
	int entity;
	while ((entity = FindEntityByClassname(entity, "tf_wearable*")) != -1)
	{
		if (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client)
		{
			TF2_RemoveWearable(client, entity);
		}
	}
}

// Thanks to 11530
// https://forums.alliedmods.net/showthread.php?t=193255
stock void ResizePlayer(int client, float fScale)
{
	SetEntPropFloat(client, Prop_Send, "m_flModelScale", fScale);
	SetEntPropFloat(client, Prop_Send, "m_flStepSize", 18.0 * fScale);
}

//With help from Arthurdead.
stock void VectorAddRotatedOffset(const float angle[3], float vec[3], const float offset[3])
{
    float forwad[3];
    float left[3];
    float up[3];
    GetAngleVectors(angle, forwad, left, up);

    ScaleVector(forwad, offset[0]);
    ScaleVector(left, offset[1]);
    ScaleVector(up, offset[2]);

    float finalvector[3];
    AddVectors(finalvector, forwad, finalvector);
    AddVectors(finalvector, left, finalvector);
    AddVectors(finalvector, up, finalvector);

    AddVectors(vec, finalvector, vec);
}

/* MAH BOI POIKA */
stock void EquipWeaponSlot(int client, int slot)
{
	int iWeapon = GetPlayerWeaponSlot(client, slot);
	if(IsValidEntity(iWeapon))
		EquipWeapon(client, iWeapon);
}

stock void EquipWeapon(int client, int weapon)
{
	char class[64];
	GetEntityClassname(weapon, class, sizeof(class));

	FakeClientCommand(client, "use %s", class);
//	SetEntPropEnt(client, Prop_Send, "m_hActiveWeapon", weapon);
}
/* */

/*---------------------------------------------------------*/
//Menu stocks by Kisslick
/*---------------------------------------------------------*/

stock void PushMenuString(Menu hndl, const char[] id, const char[] data)
{
	hndl.AddItem(id, data, ITEMDRAW_IGNORE);
}

stock void PushMenuCell(Menu hndl, const char[] id, int data)
{
	char DataString[64];
	IntToString(data, DataString, sizeof(DataString));
	hndl.AddItem(id, DataString, ITEMDRAW_IGNORE);
}

stock void PushMenuFloat(Menu hndl, const char[] id, float data)
{
	char DataString[64];
	FloatToString(data, DataString, sizeof(DataString));
	hndl.AddItem(id, DataString, ITEMDRAW_IGNORE);
}

stock void PushMenuBool(Menu hndl, const char[] id, bool data)
{
	char DataString[64];
	IntToString(view_as<int>(data), DataString, sizeof(DataString));
	hndl.AddItem(id, DataString, ITEMDRAW_IGNORE);
}

stock bool GetMenuString(Menu hndl, const char[] id, char[] Buffer, int size)
{
	int ItemCount = hndl.ItemCount;
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		if (hndl.GetItem(i, info, sizeof(info), _, data, sizeof(data)))
		{
			if (StrEqual(info, id)) {
				strcopy(Buffer, size, data);
				return true;
			}
		}
	}
	return false;
}

stock int GetMenuCell(Menu hndl, const char[] id, int DefaultValue = 0)
{
	int ItemCount = hndl.ItemCount;
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		if (hndl.GetItem(i, info, sizeof(info), _, data, sizeof(data)))
		{
			if (StrEqual(info, id))
			return StringToInt(data);
		}
	}
	return DefaultValue;
}

stock float GetMenuFloat(Menu hndl, const char[] id, float DefaultValue = 0.0)
{
	int ItemCount = hndl.ItemCount;
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		if (hndl.GetItem(i, info, sizeof(info), _, data, sizeof(data)))
		{
			if (StrEqual(info, id))
			return StringToFloat(data);
		}
	}
	return DefaultValue;
}

stock int GetMenuBool(Menu hndl, const char[] id, bool DefaultValue = false)
{
	int ItemCount = hndl.ItemCount;
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		if (hndl.GetItem(i, info, sizeof(info), _, data, sizeof(data)))
		{
			if (StrEqual(info, id))
			return view_as<bool>(StringToInt(data));
		}
	}
	return DefaultValue;
}

stock void CopyMenuAny(Menu source, Menu dest, const char[] id)
{
	int ItemCount = source.ItemCount;
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		if (source.GetItem(i, info, sizeof(info), _, data, sizeof(data)))
		{
			if (StrEqual(info, id))
			dest.AddItem(id, data, ITEMDRAW_IGNORE);
		}
	}
}

stock bool AddMenuItemFormat(Menu& menu, const char[] info, int style = ITEMDRAW_DEFAULT, const char[] format, any ...)
{
	char display[128];
	VFormat(display, sizeof(display), format, 5);

	return menu.AddItem(info, display, style);
}

/*--------------------------------------------------------->*/
//TF2 Healing Stocks by Chdata
/*--------------------------------------------------------->*/

stock bool TF2_ReadyToOverheal(int client, int add = 0)
{
	return (add > 0) ? ((TF2_GetMaxHealth(client) - GetClientHealth(client)) < add) : (GetClientHealth(client) >= TF2_GetMaxHealth(client));
}

stock void TF2_AddPlayerHealth(int client, int add, float overheal = 1.5, bool additive = false, bool event = true)
{
	int iHealth = GetClientHealth(client);
	int iNewHealth = iHealth + add;
	int iMax = additive ? (TF2_GetMaxHealth(client) + RoundFloat(overheal)) : TF2_GetMaxOverHeal(client, overheal);

	if (iHealth < iMax)
	{
		iNewHealth = ClampCell(iNewHealth, 1, iMax);

		if (event)
		{
			TF2_ShowHealthGain(client, iNewHealth - iHealth);
		}

		SetEntityHealth(client, iNewHealth);
	}
}

stock void TF2_ShowHealthGain(int patient, int health, int healer = -1)
{
	int iUserId = GetClientUserId(patient);

	Event hEvent = CreateEvent("player_healed", true);
	hEvent.SetBool("sourcemod", true);
	hEvent.SetInt("patient", iUserId);
	hEvent.SetInt("healer", healer > 0 && IsClientInGame(healer) ? GetClientUserId(healer) : iUserId);
	hEvent.SetInt("amount", health);
	hEvent.Fire();

	hEvent = CreateEvent("player_healonhit", true);
	hEvent.SetBool("sourcemod", true);
	hEvent.SetInt("amount", health);
	hEvent.SetInt("entindex", patient);
	hEvent.Fire();
}

stock int TF2_GetMaxHealth(int client)
{
	int maxhealth = GetEntProp(GetPlayerResourceEntity(), Prop_Send, "m_iMaxHealth", _, client);
	return ((maxhealth == -1 || maxhealth == 80896) ? GetEntProp(client, Prop_Data, "m_iMaxHealth") : maxhealth);
}

stock int TF2_GetMaxOverHeal(int client, float overheal = 1.5) // Quick-Fix would be 1.25
{
	return RoundFloat(float(TF2_GetMaxHealth(client)) * overheal);
}

stock int TF2_GetOverHeal(int client, float overheal = 1.5)
{
	return RoundFloat(float(TF2_GetMaxHealth(client)) * (overheal - 1.0));
}

stock void TF2_SetHealth(int client, int health)
{
	SetEntProp(client, Prop_Send, "m_iHealth", health);
	SetEntProp(client, Prop_Data, "m_iHealth", health);
}

/*--------------------------------------------------------->*/
//Model Stocks
/*--------------------------------------------------------->*/

stock bool SetModel(int entity, char model[PLATFORM_MAX_PATH], bool preload = false)
{
	if (entity <= 0 || strlen(model) == 0)
	{
		return false;
	}

	if (PrepareModel(model, preload) != -1)
	{
		if (GetEngineVersion() == Engine_TF2)
		{
			SetVariantString(model);
			AcceptEntityInput(entity, "SetCustomModel");

			SetEntProp(entity, Prop_Send, "m_bCustomModelRotates", 1);
			SetEntProp(entity, Prop_Send, "m_bUseClassAnimations", 1);
		}
		else
		{
			SetEntityModel(entity, model);
		}

		return true;
	}

	return false;
}

stock bool SetModelViaConVar(int entity, ConVar &convar, bool preload = false)
{
	if (convar == null)
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return SetModel(entity, sBuffer, preload);
}

stock int PrepareModel(char model[PLATFORM_MAX_PATH], bool preload = false)
{
	if (strlen(model) == 0)
	{
		return 0;
	}

	if (StrContains(model, "models/") != 0)
	{
		Format(model, sizeof(model), "models/%s", model);
	}

	//ParseMDLFiles(model);

	return PrecacheModel(model, preload);
}

stock int PrepareModelConVar(ConVar &convar, bool preload = false)
{
	if (convar == null)
	{
		return -1;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return PrepareModel(sBuffer, preload);
}

/*--------------------------------------------------------->*/
//Sound Stocks
/*--------------------------------------------------------->*/

stock bool EmitSoundToClientSafe(int client, const char[] sample, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (!IsPlayerIndex(client) || !IsClientInGame(client) || IsFakeClient(client) || strlen(sample) == 0)
	{
		return false;
	}

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (RequiresFakePrecache())
	{
		Format(sSound, sizeof(sSound), "*%s", sSound);
	}
	else
	{
		PrecacheSound(sSound);
	}

	if (IsSoundPrecached(sSound))
	{
		EmitSoundToClient(client, sSound, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
		return true;
	}

	LogError("Error playing sound to client %N, not precached: %s", client, sSound);
	return false;
}

stock bool EmitSoundToClientViaConVar(int client, ConVar convar, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (convar == null)
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return EmitSoundToClientSafe(client, sBuffer, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}

stock bool EmitSoundToClientSafeDelayed(int client, const char[] sample, float delay = 0.0, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	DataPack hPack;
	CreateDataTimer(ClampCell(delay, 0, 9999999.9), Timer_PlayClientSound280358023580235, hPack, TIMER_FLAG_NO_MAPCHANGE);
	hPack.WriteCell(client);
	hPack.WriteString(sample);
	hPack.WriteCell(entity);
	hPack.WriteCell(channel);
	hPack.WriteCell(level);
	hPack.WriteCell(flags);
	hPack.WriteFloat(volume);
	hPack.WriteCell(pitch);
	hPack.WriteCell(speakerentity);
	hPack.WriteFloat(origin[0]);
	hPack.WriteFloat(origin[1]);
	hPack.WriteFloat(origin[2]);
	hPack.WriteFloat(dir[0]);
	hPack.WriteFloat(dir[1]);
	hPack.WriteFloat(dir[2]);
	hPack.WriteCell(updatePos);
	hPack.WriteFloat(soundtime);
}

public Action Timer_PlayClientSound280358023580235(Handle timer, DataPack data)
{
	data.Reset();

	int client = data.ReadCell();

	char sample[PLATFORM_MAX_PATH];
	data.ReadString(sample, sizeof(sample));

	int entity = data.ReadCell();
	int channel = data.ReadCell();
	int level = data.ReadCell();
	int flags = data.ReadCell();
	float volume = data.ReadFloat();
	int pitch = data.ReadCell();
	int speakerentity = data.ReadCell();

	float origin[3];
 	origin[0] = data.ReadFloat();
 	origin[1] = data.ReadFloat();
 	origin[2] = data.ReadFloat();

	float dir[3];
 	dir[0] = data.ReadFloat();
 	dir[1] = data.ReadFloat();
 	dir[2] = data.ReadFloat();

	bool updatePos = data.ReadCell();
	float soundtime = data.ReadFloat();

	EmitSoundToClientSafe(client, sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}

stock bool EmitSoundToAllSafe(const char[] sample, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (strlen(sample) == 0)
	{
		return false;
	}

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (RequiresFakePrecache())
	{
		Format(sSound, sizeof(sSound), "*%s", sSound);
	}
	else
	{
		PrecacheSound(sSound);
	}

	if (IsSoundPrecached(sSound))
	{
		EmitSoundToAll(sSound, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
		return true;
	}

	LogError("Error playing sound to all, not precached: %s", sSound);
	return false;
}

stock bool EmitSoundToAllViaConVar(ConVar convar, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (convar = null)
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return EmitSoundToAllSafe(sBuffer, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}

stock bool EmitSoundToAllSafeDelayed(const char[] sample, float delay = 0.0, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	DataPack hPack;
	CreateDataTimer(ClampCell(delay, 0, 9999999.9), Timer_PlayAllSound280358023580235, hPack, TIMER_FLAG_NO_MAPCHANGE);
	hPack.WriteString(sample);
	hPack.WriteCell(entity);
	hPack.WriteCell(channel);
	hPack.WriteCell(level);
	hPack.WriteCell(flags);
	hPack.WriteFloat(volume);
	hPack.WriteCell(pitch);
	hPack.WriteCell(speakerentity);
	hPack.WriteFloat(origin[0]);
	hPack.WriteFloat(origin[1]);
	hPack.WriteFloat(origin[2]);
	hPack.WriteFloat(dir[0]);
	hPack.WriteFloat(dir[1]);
	hPack.WriteFloat(dir[2]);
	hPack.WriteCell(updatePos);
	hPack.WriteFloat(soundtime);
}

public Action Timer_PlayAllSound280358023580235(Handle timer, DataPack data)
{
	data.Reset();

	char sample[PLATFORM_MAX_PATH];
	data.ReadString(sample, sizeof(sample));

	int entity = data.ReadCell();
	int channel = data.ReadCell();
	int level = data.ReadCell();
	int flags = data.ReadCell();
	float volume = data.ReadFloat();
	int pitch = data.ReadCell();
	int speakerentity = data.ReadCell();

	float origin[3];
 	origin[0] = data.ReadFloat();
 	origin[1] = data.ReadFloat();
 	origin[2] = data.ReadFloat();

	float dir[3];
 	dir[0] = data.ReadFloat();
 	dir[1] = data.ReadFloat();
 	dir[2] = data.ReadFloat();

	bool updatePos = data.ReadCell();
	float soundtime = data.ReadFloat();

	EmitSoundToAllSafe(sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}

stock bool EmitAmbientSoundSafe(const char[] sample, const float origin[3], int entity = SOUND_FROM_WORLD, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float vol = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, float delay = 0.0)
{
	if (strlen(sample) == 0)
	{
		return false;
	}

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (RequiresFakePrecache())
	{
		Format(sSound, sizeof(sSound), "*%s", sSound);
	}
	else
	{
		PrecacheSound(sSound);
	}

	if (IsSoundPrecached(sSound))
	{
		EmitAmbientSound(sSound, origin, entity, level, flags, vol, pitch, delay);
		return true;
	}

	LogError("Error playing ambient sound, not precached: %s", sSound);
	return false;
}

stock bool EmitAmbientSoundViaConVar(ConVar convar, bool preload = false, const float origin[3], int entity = SOUND_FROM_WORLD, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float vol = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, float delay = 0.0)
{
	if (convar == null)
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return EmitAmbientSoundSafe(sBuffer, origin, entity, level, flags, vol, pitch, delay);
}

stock bool StopSoundSafe(int entity, int channel, const char[] sample)
{
	if (entity <= 0 || entity > MAX_ENTITY_LIMIT || strlen(sample) == 0)
	{
		return false;
	}

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (RequiresFakePrecache())
	{
		Format(sSound, sizeof(sSound), "*%s", sSound);
	}

	StopSound(entity, channel, sSound);
	return true;
}

stock void StopSoundSafeAll(int entity, const char[] sample)
{
    StopSoundSafe(entity, SNDCHAN_AUTO, sample);
    StopSoundSafe(entity, SNDCHAN_WEAPON, sample);
    StopSoundSafe(entity, SNDCHAN_VOICE, sample);
    StopSoundSafe(entity, SNDCHAN_ITEM, sample);
    StopSoundSafe(entity, SNDCHAN_BODY, sample);
    StopSoundSafe(entity, SNDCHAN_STREAM, sample);
    StopSoundSafe(entity, SNDCHAN_VOICE_BASE, sample);
    StopSoundSafe(entity, SNDCHAN_USER_BASE, sample);
}

stock bool PrepareSoundConVar(ConVar convar, bool preload = false, bool download = true)
{
	if (convar == null)
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return PrepareSound(sBuffer, preload, download);
}

stock bool PrepareSound(const char[] sample, bool preload = false, bool download = true)
{
	if (strlen(sample) == 0)
	{
		return false;
	}

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (StrContains(sSound, "sound/") == 0)
	{
		if (download &&)
		{
			AddFileToDownloadsTable(sSound);
		}

		RemoveFrontString(sSound, sizeof(sSound), 6);
	}
	else if (download)
	{
		char sBuffer[PLATFORM_MAX_PATH];
		FormatEx(sBuffer, sizeof(sBuffer), "sounds/%s", sSound);
		AddFileToDownloadsTable(sBuffer);
	}

	return RequiresFakePrecache() ? FakePrecacheSound(sSound) : PrecacheSound(sSound, preload);
}

stock bool FakePrecacheSound(const char[] sound)
{
	char sPath[PLATFORM_MAX_PATH];
	Format(sPath, sizeof(sPath), "sound/%s", sound);

	if (!FileExists(sPath))
	{
		return false;
	}

	AddFileToDownloadsTable(sPath);

	Format(sPath, sizeof(sPath), "*/%s", sound);
	AddToStringTable(FindStringTable("soundprecache"), sPath);
	return true;
}

stock bool RequiresFakePrecache()
{
	EngineVersion engine2 = GetEngineVersion();
	return engine2 == Engine_CSGO || engine2 == Engine_DOTA;
}

/*--------------------------------------------------------->*/
//TF2Attributes Stocks
/*--------------------------------------------------------->*/

stock void TF2Attrib_SetByName_Weapons(int client, int weapon = -1, char[] attrib, float value, bool invert = false)
{
	if (weapon != -1 && IsValidEntity(weapon))
	{
		TF2Attrib_SetByName(weapon, attrib, value);
		return;
	}

	if (invert)
	{
		value = 1.0 + value;
	}
	else
	{
		value = 1.0 - value;
	}

	int weapon2;
	for (int i = 0; i < 6; i++)
	{
		weapon2 = GetPlayerWeaponSlot(client, i);

		if (IsValidEntity(weapon2))
		{
			TF2Attrib_SetByName(weapon2, attrib, value);
		}
	}
}

stock void TF2Attrib_RemoveByName_Weapons(int client, int weapon = -1, char[] attrib)
{
	if (weapon != -1 && IsValidEntity(weapon))
	{
		TF2Attrib_RemoveByName(weapon, attrib);
		return;
	}

	int weapon2;
	for (int i = 0; i < 6; i++)
	{
		weapon2 = GetPlayerWeaponSlot(client, i);

		if (IsValidEntity(weapon2))
		{
			TF2Attrib_RemoveByName(weapon2, attrib);
		}
	}
}

stock float TF2Attrib_ApplyMoveSpeedBonus(int client, float value)
{
	Address addr = TF2Attrib_GetByName(client, "move speed bonus");
	float old;

	if (addr != Address_Null)
	{
		old = TF2Attrib_GetValue(addr);
	}

	TF2Attrib_SetByName(client, "move speed bonus", 1.0 + value);
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);

	return old;
}

stock void TF2Attrib_RemoveMoveSpeedBonus(int client)
{
	TF2Attrib_RemoveByName(client, "move speed bonus");
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);
}

stock float TF2Attrib_ApplyMoveSpeedPenalty(int client, float value)
{
	Address addr = TF2Attrib_GetByName(client, "move speed bonus");
	float old;

	if (addr != Address_Null)
	{
		old = TF2Attrib_GetValue(addr);
	}

	TF2Attrib_SetByName(client, "move speed penalty", 1.0 - value);
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);

	return old;
}

stock void TF2Attrib_RemoveMoveSpeedPenalty(int client)
{
	TF2Attrib_RemoveByName(client, "move speed penalty");
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);
}

/*--------------------------------------------------------->*/
//SmartDM - Zephyrius
/*--------------------------------------------------------->*/

ArrayList g_hCachedFiles;
StringMap g_hCachedNums;
char g_szModelExts[][16] = {".phy", ".sw.vtx", ".dx80.vtx", ".dx90.vtx", ".vtx", ".xbox.vtx", ".vvd"};
char g_szMaterialKeys[][64] = {"$baseTexture", "$bumpmap", "$lightwarptexture"};
StringMap g_hCustomFiles;

stock int ParseMDLFiles(char[] filename)
{
	int len = strlen(filename);
	ReplaceString(filename, len, "\\", "/");
	for (int ch=0; ch<len; ch++){
		filename[ch] = CharToLower(filename[ch]);
	}

	if (!FileExists2(filename))
		return 0;

	if (g_hCachedNums == null)
	{
		g_hCachedNums = new StringMap();
		g_hCachedFiles = new ArrayList(PLATFORM_MAX_PATH);
	}

	AddFileToDownloadsTable(filename);

	int m_iValue;
	if (g_hCachedNums.GetValue(filename, m_iValue))
	{
		int m_iStart = g_hCachedFiles.FindString(filename)+1;
		char m_szFile[PLATFORM_MAX_PATH];
		for (int i=m_iStart-m_iValue-1;i<m_iStart-1;++i)
		{
			if (i<0)
				break;
			g_hCachedFiles.GetString(i, m_szFile, sizeof(m_szFile));
			AddFileToDownloadsTable(m_szFile);
		}
		return true;
	}

	char m_szExt[16];
	int m_iDot = FindCharInString(filename, '.', true);
	if (m_iDot == -1)
		return true;

	int m_iNumFiles = 0;

	strcopy(m_szExt, sizeof(m_szExt), filename[m_iDot]);
	char m_szMaterials[8][PLATFORM_MAX_PATH];
	int m_iNum;
	if (strcmp(m_szExt, ".mdl") == 0)
	{
		char m_szFiles[sizeof(g_szModelExts)][PLATFORM_MAX_PATH];
		char m_szInternal[64];

		m_iNum = Downloader_ParseMDL(filename, m_szInternal, sizeof(m_szInternal), m_szMaterials, sizeof(m_szMaterials), sizeof(m_szMaterials[]));
		for (int i=0;i<m_iNum;++i)
		{
			if (FileExists2(m_szMaterials[i])){
				m_iNumFiles += ParseMDLFiles(m_szMaterials[i])+1;
			}
		}

		m_iNum = Downloader_GetModelFiles(filename, m_szInternal, m_szFiles, sizeof(m_szFiles), sizeof(m_szFiles[]));
		for (int i=0;i<m_iNum;++i)
			m_iNumFiles += ParseMDLFiles(m_szFiles[i])+1;
	} else if (strcmp(m_szExt, ".vmt") == 0)
	{
		m_iNum = Downloader_GetMaterialsFromVMT(filename, m_szMaterials, sizeof(m_szMaterials), sizeof(m_szMaterials[]));
		char m_szMaterial[PLATFORM_MAX_PATH];
		for (int i=0;i<m_iNum;++i)
		{
			Format(m_szMaterial, sizeof(m_szMaterial), "materials\\%s.vtf", m_szMaterials[i]);

			if (FileExists2(m_szMaterial))
				m_iNumFiles += ParseMDLFiles(m_szMaterial)+1;
		}
	}

	g_hCachedFiles.PushString(filename);
	g_hCachedNums.SetValue(filename, m_iNumFiles);

	return m_iNumFiles;
}

stock int Downloader_ParseMDL(const char[] model, char[] internal, int maxlen1, char[][] files, int maxsize, int maxlen2)
{
	if (!FileExists2(model))
		return 0;

	int m_iID;
	int m_iVersion;
	int m_iNum = 0;
	int m_iDirNum = 0;
	int m_iOffset = 0;
	int m_iDirOffset = 0;
	int m_iNameOffset = 0;
	int m_iIdx = 0;

	File m_hFile = OpenFile2(model, "rb");
	if (m_hFile==null)
		return 0;

	m_hFile.ReadInt32(m_iID);
	m_hFile.ReadInt32(m_iVersion);
	m_hFile.Seek(4, SEEK_CUR);
	m_hFile.ReadString(internal, maxlen1);

	m_hFile.Seek(204, SEEK_SET);
	m_hFile.ReadInt32(m_iNum);
	m_hFile.ReadInt32(m_iOffset);
	m_hFile.ReadInt32(m_iDirNum);
	m_hFile.ReadInt32(m_iDirOffset);

	char m_szPath[PLATFORM_MAX_PATH];
	if (m_iDirNum!=0)
	{
		m_hFile.Seek(m_iDirOffset, SEEK_SET);
		m_hFile.ReadInt32(m_iDirOffset);
		m_hFile.Seek(m_iDirOffset, SEEK_SET);
		m_hFile.ReadString(m_szPath, sizeof(m_szPath));
	}

	char m_szMaterial[PLATFORM_MAX_PATH];
	for (m_iIdx=0;m_iIdx<m_iNum;++m_iIdx)
	{
		m_hFile.Seek(m_iOffset+m_iIdx*64, SEEK_SET);
		m_hFile.ReadInt32(m_iNameOffset);
		m_hFile.Seek(m_iNameOffset-4, SEEK_CUR);
		m_hFile.ReadString(m_szMaterial, sizeof(m_szMaterial));

		Format(files[m_iIdx], maxlen2, "materials\\%s%s.vmt", m_szPath, m_szMaterial);
	}

	return m_iNum;
}

stock int Downloader_GetModelFiles(const char[] model, const char[] internal, char[][] files, int maxsize, int maxlen)
{
	char m_szRawPath1[PLATFORM_MAX_PATH];
	char m_szRawPath2[PLATFORM_MAX_PATH];
	strcopy(m_szRawPath1, sizeof(m_szRawPath1), model);
	Format(m_szRawPath2, sizeof(m_szRawPath2), "models/%s", internal);

	int m_iDot = FindCharInString(m_szRawPath1, '.', true);
	if (m_iDot == -1)
		return 0;
	m_szRawPath1[m_iDot] = 0;

	m_iDot = FindCharInString(m_szRawPath2, '.', true);
	if (m_iDot == -1)
		return 0;
	m_szRawPath2[m_iDot] = 0;

	int m_iNum = 0;
	for (int i=0;i<sizeof(g_szModelExts);++i)
	{
		if (m_iNum == maxsize)
			break;
		Format(files[m_iNum], maxlen, "%s%s", m_szRawPath1, g_szModelExts[i]);
		if (FileExists2(files[m_iNum]))
			++m_iNum;
		else
		{
			Format(files[m_iNum], maxlen, "%s%s", m_szRawPath2, g_szModelExts[i]);
			if (FileExists2(files[m_iNum]))
				++m_iNum;
		}
	}
	return m_iNum;
}

stock int Downloader_GetMaterialsFromVMT(const char[] vmt, char[][] materials, int maxsize, int maxlen)
{
	if (!FileExists2(vmt))
		return 0;

	char m_szLine[512];

	File m_hFile = OpenFile2(vmt, "r");

	bool m_bFound[sizeof(g_szMaterialKeys)];
	int m_iPos;
	int m_iLast;
	int m_iNum = 0;
	while(m_hFile.ReadLine(m_szLine, sizeof(m_szLine))!=false)
	{
		if (m_iNum == sizeof(g_szMaterialKeys) || maxsize == m_iNum)
			break;

		for (int i=0;i<sizeof(g_szMaterialKeys);++i)
		{
			if (m_bFound[i])
				continue;
			if ((m_iPos = StrContains(m_szLine, g_szMaterialKeys[i], false)) > 0)
			{
				m_bFound[i]=true;
				while(m_szLine[m_iPos] != '"' && m_szLine[m_iPos] != ' ' && m_szLine[m_iPos] != '	')
					++m_iPos;
				while(m_szLine[m_iPos] == ' ' || m_szLine[m_iPos] == '	' || m_szLine[m_iPos] == '"')
					++m_iPos;
				m_iLast = m_iPos;
				while(m_szLine[m_iLast] != '"' && m_szLine[m_iLast] != '\r' && m_szLine[m_iLast] != '\n' && m_szLine[m_iLast] != ' ' && m_szLine[m_iLast] != '	' && m_szLine[m_iLast] != 0)
					++m_iLast;
				m_szLine[m_iLast] = 0;
				strcopy(materials[m_iNum], maxlen, m_szLine[m_iPos]);
				++m_iNum;
			}
		}
	}

	delete m_hFile;

	return m_iNum;
}

public void CacheCustomDirectory()
{
	g_hCustomFiles = new StringMap();

	DirectoryListing m_hDir = OpenDirectory("custom");
	if (m_hDir == null)
		return;

	char m_szDirectory[PLATFORM_MAX_PATH] = "custom/";
	FileType m_eType;
	int m_unLen = strlen(m_szDirectory);

	while(m_hDir.GetNext(m_szDirectory[m_unLen], sizeof(m_szDirectory)-m_unLen, m_eType))
	{
		if (m_eType != FileType_Directory)
			continue;

		if (strcmp(m_szDirectory[m_unLen], ".")==0 || strcmp(m_szDirectory[m_unLen], "..")==0)
			continue;

		CacheDirectory(m_szDirectory);
	}
	delete m_hDir;
}

public void CacheDirectory(const char[] directory)
{
	DirectoryListing m_hDir = OpenDirectory(directory);
	char m_szPath[PLATFORM_MAX_PATH];
	FileType m_eType;
	Format(m_szPath, sizeof(m_szPath), "%s/", directory);
	int m_unLen = strlen(m_szPath);
	int m_unOffset = FindCharInString(m_szPath, '/')+1;
	m_unOffset += FindCharInString(m_szPath[m_unOffset], '/')+1;

	while(m_hDir.GetNext(m_szPath[m_unLen], sizeof(m_szPath)-m_unLen, m_eType))
	{
		if (strcmp(m_szPath[m_unLen], ".")==0 || strcmp(m_szPath[m_unLen], "..")==0)
			continue;

		if (m_eType == FileType_Directory)
			CacheDirectory(m_szPath);
		else if (m_eType == FileType_File)
		{
			int len = strlen(m_szPath);
			ReplaceString(m_szPath, len, "\\", "/");
			for (int ch=0; ch<len; ch++){
				m_szPath[ch] = CharToLower(m_szPath[ch]);
			}
			g_hCustomFiles.SetString(m_szPath[m_unOffset], m_szPath);
		}
	}
	delete m_hDir;
}

stock File OpenFile2(const char[] file, const char[] mode)
{
	if (g_hCustomFiles == null)
		CacheCustomDirectory();

	char file2[PLATFORM_MAX_PATH];
	strcopy(file2, PLATFORM_MAX_PATH, file);

	int len = strlen(file2);
	ReplaceString(file2, len, "\\", "/");
	for (int ch=0; ch<len; ch++){
		file2[ch] = CharToLower(file2[ch]);
	}

	char m_szPath[PLATFORM_MAX_PATH];
	if (!g_hCustomFiles.GetString(file2, m_szPath, sizeof(m_szPath)))
	{
		strcopy(m_szPath, sizeof(m_szPath), file2);
	}

	return OpenFile(m_szPath, mode);
}

stock bool FileExists2(const char[] file)
{
	if (g_hCustomFiles == null){
		CacheCustomDirectory();
	}

	char file2[PLATFORM_MAX_PATH];
	strcopy(file2, PLATFORM_MAX_PATH, file);

	int len = strlen(file2);
	ReplaceString(file2, len, "\\", "/");
	for (int ch=0; ch<len; ch++){
		file2[ch] = CharToLower(file2[ch]);
	}

	char m_szPath[PLATFORM_MAX_PATH];
	if (!g_hCustomFiles.GetString(file2, m_szPath, sizeof(m_szPath))){
		return FileExists(file2);
	}
	return FileExists(m_szPath);
}

/*--------------------------------------------------------->*/
//From SMLIB, lets draw happy little boxes together.
/*--------------------------------------------------------->*/

stock void Effect_DrawBeamBoxToClient(int client, const float bottomCorner[3], const float upperCorner[3], int modelIndex, int haloIndex, int startFrame = 0, int frameRate = 30, float life = 5.0, float width = 5.0, float endWidth = 5.0, int fadeLength = 2, float amplitude = 1.0, const color[4] =  { 255, 0, 0, 255 }, int speed = 0)
{
	int clients[1];
	clients[0] = client;
	Effect_DrawBeamBox(clients, 1, bottomCorner, upperCorner, modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
}

stock void Effect_DrawBeamBoxToAll(const float bottomCorner[3], const float upperCorner[3], int modelIndex, int haloIndex, int startFrame = 0, int frameRate = 30, float life = 5.0, float width = 5.0, float endWidth = 5.0, int fadeLength = 2, float amplitude = 1.0, const int color[4] = { 255, 255, 255, 255 }, int speed = 0)
{
	int[] clients = new int[MaxClients];
	int numClients;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
		{
			clients[numClients++] = i;
		}
	}

	Effect_DrawBeamBox(clients, numClients, bottomCorner, upperCorner, modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
}

stock void Effect_DrawBeamBox(int[] clients, int numClients, const float bottomCorner[3], const float upperCorner[3], int modelIndex, int haloIndex, int startFrame = 0, int frameRate = 30, float life = 5.0, float width = 5.0, float endWidth = 5.0, int fadeLength = 2, float amplitude = 1.0, const color[4] =  { 255, 0, 0, 255 }, int speed = 0)
{
	float corners[8][3];

	for (int i = 0; i < 4; i++)
	{
		CopyArrayToArray(bottomCorner, corners[i], 3);
		CopyArrayToArray(upperCorner, corners[i + 4], 3);
	}

	corners[1][0] = upperCorner[0];
	corners[2][0] = upperCorner[0];
	corners[2][1] = upperCorner[1];
	corners[3][1] = upperCorner[1];
	corners[4][0] = bottomCorner[0];
	corners[4][1] = bottomCorner[1];
	corners[5][1] = bottomCorner[1];
	corners[7][0] = bottomCorner[0];

	for (int i = 0; i < 4; i++)
	{
		int j = (i == 3 ? 0 : i + 1);
		TE_SetupBeamPoints(corners[i], corners[j], modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
		TE_Send(clients, numClients);
	}

	for (int i = 4; i < 8; i++)
	{
		int j = (i == 7 ? 4 : i + 1);
		TE_SetupBeamPoints(corners[i], corners[j], modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
		TE_Send(clients, numClients);
	}

	for (int i = 0; i < 4; i++)
	{
		TE_SetupBeamPoints(corners[i], corners[i + 4], modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
		TE_Send(clients, numClients);
	}
}

stock void Effect_DrawRangedBeamBox(float origin[3], const float bottomCorner[3], const float upperCorner[3], int modelIndex, int haloIndex, int startFrame = 0, int frameRate = 30, float life = 5.0, float width = 5.0, float endWidth = 5.0, int fadeLength = 2, float amplitude = 1.0, const color[4] =  { 255, 0, 0, 255 }, int speed = 0)
{
	float corners[8][3];

	for (int i = 0; i < 4; i++)
	{
		CopyArrayToArray(bottomCorner, corners[i], 3);
		CopyArrayToArray(upperCorner, corners[i + 4], 3);
	}

	corners[1][0] = upperCorner[0];
	corners[2][0] = upperCorner[0];
	corners[2][1] = upperCorner[1];
	corners[3][1] = upperCorner[1];
	corners[4][0] = bottomCorner[0];
	corners[4][1] = bottomCorner[1];
	corners[5][1] = bottomCorner[1];
	corners[7][0] = bottomCorner[0];

	for (int i = 0; i < 4; i++)
	{
		int j = (i == 3 ? 0 : i + 1);
		TE_SetupBeamPoints(corners[i], corners[j], modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
		TE_SendToAllInRange(origin, RangeType_Audibility);
	}

	for (int i = 4; i < 8; i++)
	{
		int j = (i == 7 ? 4 : i + 1);
		TE_SetupBeamPoints(corners[i], corners[j], modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
		TE_SendToAllInRange(origin, RangeType_Audibility);
	}

	for (int i = 0; i < 4; i++)
	{
		TE_SetupBeamPoints(corners[i], corners[i + 4], modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
		TE_SendToAllInRange(origin, RangeType_Audibility);
	}
}

//SM9(); has molested this stock at this point. <3
stock void GetAbsBoundingBox(int ent, float mins[3], float maxs[3], bool half = false)
{
    float origin[3];

    GetEntPropVector(ent, Prop_Data, "m_vecAbsOrigin", origin);
    GetEntPropVector(ent, Prop_Data, "m_vecMins", mins);
    GetEntPropVector(ent, Prop_Data, "m_vecMaxs", maxs);

    mins[0] += origin[0];
    mins[1] += origin[1];
    mins[2] += origin[2];
    maxs[0] += origin[0];
    maxs[1] += origin[1];
    
    if (!half) {
        maxs[2] += origin[2];
    } else {
        maxs[2] = mins[2];
    }
}

stock void CreateHudConVars(const char[] prefix, ConVar& position = null, ConVar& holdtime = null, ConVar& colors = null, ConVar& effect = null, ConVar& fxtime = null, ConVar& fades = null)
{
	char sName[512];

	FormatEx(sName, sizeof(sName), "%sposition", prefix);
	position = CreateConVar(sName, "-1.0/-1.0", "Position of this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%sholdtime", prefix);
	holdtime = CreateConVar(sName, "0.0", "Holdtime for this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%scolor", prefix);
	colors = CreateConVar(sName, "255, 255, 255, 255", "Color of this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%seffect", prefix);
	effect = CreateConVar(sName, "0", "Effect for this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%sfxtime", prefix);
	fxtime = CreateConVar(sName, "0.0", "Fxtime for this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%sfades", prefix);
	fades = CreateConVar(sName, "-1.0/-1.0", "Fxtime for this hud element.", FCVAR_NOTIFY);
}

stock void SetHudTextParamsViaConVars(ConVar& position, ConVar& holdtime, ConVar& color, ConVar& effect, ConVar& fxtime, ConVar& fades)
{
	float vecPosition[2]; vecPosition = GetConVar2DVector(position);
	int iColor[4]; iColor = GetConVarColor(color);
	float fFades[2]; fFades = GetConVar2DVector(fades);

	SetHudTextParams(vecPosition[0], vecPosition[1], holdtime.FloatValue, iColor[0], iColor[1], iColor[2], iColor[3], effect.IntValue, fxtime.FloatValue, fFades[0], fFades[1]);
}

/*--------------------------------------------------------->*/
//TF2 force look stocks by Pelipoika
/*--------------------------------------------------------->*/

stock void TF2_LookAtPos(int client, float flGoal[3], float flAimSpeed = 0.05)
{
    float flPos[3];
    GetClientEyePosition(client, flPos);

    float flAng[3];
    GetClientEyeAngles(client, flAng);

    // get normalised direction from target to client
    float desired_dir[3];
    MakeVectorFromPoints(flPos, flGoal, desired_dir);
    GetVectorAngles(desired_dir, desired_dir);

    // ease the current direction to the target direction
    flAng[0] += AngleNormalize(desired_dir[0] - flAng[0]) * flAimSpeed;
    flAng[1] += AngleNormalize(desired_dir[1] - flAng[1]) * flAimSpeed;

    TeleportEntity(client, NULL_VECTOR, flAng, NULL_VECTOR);
}

stock float AngleNormalize(float angle)
{
    angle = fmodf(angle, 360.0);
    if (angle > 180)
    {
        angle -= 360;
    }
    if (angle < -180)
    {
        angle += 360;
    }

    return angle;
}

stock float fmodf(float number, float denom)
{
    return number - RoundToFloor(number / denom) * denom;
}

/*--------------------------------------------------------->*/
//TheXeon made methodmaps that should exist already but don't for some reason. (:
//Got permission to post them here.
/*--------------------------------------------------------->*/

// TIMER METHODMAPS
methodmap SMTimer < Handle
{
	/**
	 * Creates a basic timer.  Calling .Kill() on a timer will kill the timer. Do not .Kill(), .Close(),
	 * or delete in a callback! Make sure to null timer in callback if global!
	 *
	 * @param interval			Interval from the current game time to execute the given function.
	 * @param func				Function to execute once the given interval has elapsed.
	 * @param data				Handle or value to pass through to the timer callback function.
	 * @param flags				Flags to set (such as repeatability or auto-Handle closing).
	 * @return					Handle to the timer object.  You do not need to call CloseHandle().
	 *							If the timer could not be created, null will be returned.
	 */
	public SMTimer(float interval, Timer func, any data=INVALID_HANDLE, int flags=0)
	{
		return view_as<SMTimer>(CreateTimer(interval, func, data, flags));
	}

	/**
	 * Kills a timer.  Use this instead of delete if you need more options. Do not use in a timer's callback!
	 *
	 * @param autoClose			If autoClose is true, the data that was passed to CreateTimer() will
	 *							be closed as a handle if TIMER_DATA_HNDL_CLOSE was not specified.
	 * @error					Invalid handles will cause a run time error.
	 */
	public void Kill(bool autoClose=false)
	{
		KillTimer(this, autoClose);
		delete this;
	}

	/**
	 * Closes a timer. A clone of .Kill() if autoClose is true. Do not use in a timer's callback!
	 *
	 * @param autoClose			If autoClose is true, the data that was passed to new SMTimer() will
	 *							be deleted as a handle if TIMER_DATA_HNDL_CLOSE was not specified.
	 * @error					Invalid handles will cause a run time error.
	 */
	public void Close(bool autoClose=false)
	{
		if (autoClose)
			this.Kill(autoClose);
		else
			delete this;
	}

	/**
	 * Manually triggers a timer so its function will be called.
	 *
	 * @param reset				If reset is true, the elapsed time counter is reset
	 *							so the full interval must pass again.
	 */
	public void Trigger(bool reset=false)
	{
		TriggerTimer(this, reset);
	}
}

methodmap SMDataTimer < SMTimer
{
	/**
	 * Creates a timer associated with a new datapack if needed.
	 * @note The datapack is automatically freed when the timer ends.
	 * @note The position of the datapack is not reset or changed for the timer function.
	 *
	 * @param interval			Interval from the current game time to execute the given function.
	 * @param func				Function to execute once the given interval has elapsed.
	 * @param datapack			The newly created datapack is passed through this by-reference
	 *							parameter to the timer callback function.
	 * @param flags				Timer flags.
	 * @return					Handle to the timer object.  You do not need to call CloseHandle().
	 */
	public SMDataTimer(float interval, Timer func, DataPack &datapack, int flags=0)
	{
		if (datapack == null)
		{
			datapack = new DataPack();
		}
		flags |= TIMER_DATA_HNDL_CLOSE;
		return view_as<SMDataTimer>(new SMTimer(interval, func, datapack, flags));
	}
}

#if defined _clientprefs_included
// Cookie Methodmaps!
methodmap Cookie < Handle
{
	/**
	 * Creates a new Client preference cookie.
	 *
	 * Cookies can be closed via delete when
	 * no longer needed.
	 *
	 * @param name			Name of the new preference cookie.
	 * @param description	Optional description of the preference cookie.
	 * @param access		What CookieAccess level to assign to this cookie.
	 * @return				A handle to the newly created cookie. If the cookie already
	 *                      exists, a handle to it will still be returned.
	 * @error				Cookie name is blank.
	 */
	public Cookie(const char[] name, const char[] description, CookieAccess access)
	{
		return view_as<Cookie>(RegClientCookie(name, description, access));
	}

	/**
	 * Searches for a Client preference cookie. Use as Cookie.Find
	 *
	 * Cookies can be closed via delete when
	 * no longer needed.
	 *
	 * @param name			Name of cookie to find.
	 * @return				A cookie if it is found. null otherwise.
	 */
	public static Cookie Find(const char[] name)
	{
		return view_as<Cookie>(FindClientCookie(name));
	}

	/**
	 * Set the value of a Client preference cookie.
	 *
	 * @param client		Client index.
	 * @param value			String value to set.
	 * @error				Invalid cookie handle or invalid client index.
	 */
	public void SetValue(int client, const char[] value)
	{
		SetClientCookie(client, this, value);
	}

	/**
	 * Retrieve the value of a Client preference cookie.
	 *
	 * @param client		Client index.
	 * @param buffer		Copyback buffer for value.
	 * @param maxlen		Maximum length of the buffer.
	 * @error				Invalid cookie handle or invalid client index.
	 */
	public void GetValue(int client, char[] buffer, int maxlen)
	{
		GetClientCookie(client, this, buffer, maxlen);
	}

	/**
	 * Sets the value of a Client preference cookie based on an authID string.
	 *
	 * @param authID		String Auth/STEAM ID of player to set.
	 * @param value			String value to set.
	 * @error			Invalid cookie handle.
	 */
	public void SetByAuth(const char[] authID, const char[] value)
	{
		SetAuthIdCookie(authID, this, value);
	}

	/**
	 * Add a new prefab item to the client cookie settings menu.
	 *
	 * Note: This handles everything automatically and does not require a callback
	 *
	 * @param type			A CookieMenu prefab menu type.
	 * @param display		Text to show on the menu.
	 * @param handler		Optional handler callback for translations and output on selection
	 * @param info			Info data to pass to the callback.
	 * @error				Invalid cookie handle.
	 */
	public void SetMenu(CookieMenu type, const char[] display, CookieMenuHandler handler=INVALID_FUNCTION, any info=0)
	{
		SetCookiePrefabMenu(this, type, display, handler, info);
	}

	/**
	 * Returns the access level of a cookie
	 *
	 * @return				CookieAccess access level.
	 * @error				Invalid cookie handle.
	 */
	property CookieAccess Access
	{
		public get() {return GetCookieAccess(this);}
	}

	/**
	 * Returns the last updated timestamp for a client cookie
	 *
	 * @param client		Client index.
	 * @return			Last updated timestamp.
	 */
	public int GetTime(int client)
	{
		return GetClientCookieTime(client, this);
	}
}

methodmap CookieIterator < Handle
{
	/**
	 * Gets a cookie iterator.  Must be freed with delete.
	 *
	 * @return				A new cookie iterator.
	 */
	 public CookieIterator()
	 {
	 	return view_as<CookieIterator>(GetCookieIterator());
	 }

	 /**
	 * Reads a cookie iterator, then advances to the next cookie if any.
	 *
	 * @param name			Name buffer.
	 * @param nameLen		Name buffer size.
	 * @param access		Access level of the cookie.
	 * @param desc			Cookie description buffer.
	 * @param descLen		Cookie description buffer size.
	 * @return				True on success, false if there are no more commands.
	 */
	 public bool Read(char[] name, int nameLen, CookieAccess &access, char[] desc="", int descLen=0)
	 {
	 	return ReadCookieIterator(this, name, nameLen, access, desc, descLen);
	 }
}
#endif

/*--------------------------------------------------------->*/
//Spell stocks for TF2. (by Tylerst)
/*--------------------------------------------------------->*/

#define SPELL_FIREBALL			0
#define SPELL_BALLOBATS			1
#define SPELL_HEALINGAURA		2
#define SPELL_PUMPKINMIRV		3
#define SPELL_SUPERJUMP			4
#define SPELL_INVISIBILITY		5
#define SPELL_TELEPORT			6
#define SPELL_TELSABOLT			7
#define SPELL_MINIFY			8
#define SPELL_SUMMONMONOCULUS	9
#define SPELL_METEORSHOWER		10
#define SPELL_SUMMONSKELETONS	11

stock void TF2_SetSpell(int client, int spell, int uses)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
	{
		SetEntProp(entity, Prop_Send, "m_iSelectedSpellIndex", spell);
		SetEntProp(entity, Prop_Send, "m_iSpellCharges", uses);
	}
}

stock void TF2_SetSpellUses(int client, int uses)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
	{
		SetEntProp(entity, Prop_Send, "m_iSpellCharges", uses);
	}
}

stock void TF2_GetSpell(int client)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
	{
		return GetEntProp(ent, Prop_Send, "m_iSelectedSpellIndex");
	}

	return INVALID_ENT_INDEX;
}

stock void TF2_GetSpellUses(int client)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
	{
		return GetEntProp(entity, Prop_Send, "m_iSpellCharges");
	}
}

stock int TF2_GetSpellBook(int client)
{
	int entity = -1;
	while((entity = FindEntityByClassname(entity, "tf_weapon_spellbook")) != INVALID_ENT_REFERENCE)
	{
		if (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client)
		{
			return entity;
		}
	}

	return -1;
}

stock bool TF2_SpellIsRare(int spell)
{
	switch(spell)
	{
		case SPELL_TELSABOLT, SPELL_MINIFY, SPELL_SUMMONMONOCULUS, SPELL_METEORSHOWER, SPELL_SUMMONSKELETONS: return true;
	}

	return false;
}

stock void TF2_GetSpellName(int spell, char[] buffer, int size)
{
	switch(spell)
	{
		case SPELL_FIREBALL: strcopy(buffer, size, "Fireball");
		case SPELL_BALLOBATS: strcopy(buffer, size, "Ball O' Bats");
		case SPELL_HEALINGAURA: strcopy(buffer, size, "Healing Aura");
		case SPELL_PUMPKINMIRV: strcopy(buffer, size, "Pumpkin MIRV");
		case SPELL_SUPERJUMP: strcopy(buffer, size, "Superjump");
		case SPELL_INVISIBILITY: strcopy(buffer, size, "Invisibility");
		case SPELL_TELEPORT: strcopy(buffer, size, "Teleport");
		case SPELL_TELSABOLT: strcopy(buffer, size, "Tesla Bolt");
		case SPELL_MINIFY: strcopy(buffer, size, "Minify");
		case SPELL_SUMMONMONOCULUS: strcopy(buffer, size, "Summon Monoculus");
		case SPELL_METEORSHOWER: strcopy(buffer, size, "Meteor Shower");
		case SPELL_SUMMONSKELETONS: strcopy(buffer, size, "Summon Skeletons");
		default: strcopy(buffer, size, "None");
	}
}

/*--------------------------------------------------------->*/
//Mannpower Powerups (by Shaders Allen, Configured by aIM)
/*--------------------------------------------------------->*/

#define POWERUP_STRENGTH	0
#define POWERUP_RESIST		1
#define POWERUP_VAMPIRE		2
#define POWERUP_WARLOCK		3
#define POWERUP_HASTE		4
#define POWERUP_REGEN		5
#define POWERUP_PRECISION	6
#define POWERUP_AGILITY		7
#define POWERUP_KNOCKOUT	8
#define POWERUP_KING		9
#define POWERUP_PLAGUE		10
#define POWERUP_SUPERNOVA	11

stock void TF2_SetPowerup(int client, int powerup)
{
	switch (powerup)
	{
		case POWERUP_STRENGTH:
		{
			TF2_AddCondition(client, TFCond_RuneStrength);
		}

		case POWERUP_RESIST:
		{
			TF2_AddCondition(client, TFCond_RuneResist);
		}

		case POWERUP_VAMPIRE:
		{
			TF2_AddCondition(client, TFCond_RuneVampire);
		}

		case POWERUP_WARLOCK:
		{
			TF2_AddCondition(client, TFCond_RuneWarlock);
		}

		case POWERUP_HASTE:
		{
			TF2_AddCondition(client, TFCond_RuneHaste);
		}

		case POWERUP_REGEN:
		{
			TF2_AddCondition(client, TFCond_RuneRegen);
		}

		case POWERUP_PRECISION:
		{
			TF2_AddCondition(client, TFCond_RunePrecision);
		}

		case POWERUP_AGILITY:
		{
			TF2_AddCondition(client, TFCond_RuneAgility);
		}

		case POWERUP_KNOCKOUT:
		{
			TF2_AddCondition(client, TFCond_RuneKnockout);
		}

		case POWERUP_KING:
		{
			TF2_AddCondition(client, TFCond_KingRune);
			TF2_AddCondition(client, TFCond_KingAura);
		}

		case POWERUP_PLAGUE:
		{
			TF2_AddCondition(client, TFCond_Plague);
		}

		case POWERUP_SUPERNOVA:
		{
			TF2_AddCondition(client, TFCond_SupernovaRune);
		}
	}

	//This has to be here.
	TF2_AddCondition(client, TFCond_HasRune);
}

/*--------------------------------------------------------->*/
//This is the end of this THICCCCCC include file.
/*--------------------------------------------------------->*/
