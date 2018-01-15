/**
*
*	This include contains a ton of useful stocks and functions you can use.
*	I made this include considering I feel like most of this stuff should be built into Sourcemod anyways.
*	Author: Keith Warren (Sky Guardian)
*	https://github.com/SkyGuardian
*
**/

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

stock void PrintToSkyGuardian(const char[] format, any ...)
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

stock int GetSkyGuardian()
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

stock bool IsSkyGuardian(int client)
{
	return view_as<bool>(client == GetSkyGuardian());
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

		GetClientAuthId(i, AuthId_Steam2, sSteamID, sizeof(sSteamID));

		if (StrEqual(steamid, sSteamID))
		{
			KickClient(i, sBuffer);
			return true;
		}
	}

	return false;
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

stock int KvGetInt(Handle kv, const char[] key, int defvalue=0)
{
	return KvGetNum(kv, key, defvalue);
}

stock bool KvGetBool(Handle kv, const char[] key, bool defvalue=false)
{
	return view_as<bool>(KvGetNum(kv, key, view_as<int>(defvalue)));
}

stock bool StringToBool(const char[] str)
{
	return view_as<bool>(StringToInt(str));
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

stock void KvGet2DVector(Handle kv, const char[] key, float vec[2], const float defvalue[2]={0.0, 0.0})
{
	char sBuffer[512];
	KvGetString(kv, key, sBuffer, sizeof(sBuffer));

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

//https://github.com/50DKP/FF2-Official/blob/experimental/addons/sourcemod/scripting/freak_fortress_2.sp#L6051
stock int ParseFormula(const char[] formula, int defaultValue)
{
	if (!formula[0])
	{
		return defaultValue;
	}

	int size = 1;
	int matchingBrackets;
	for (int i; i <= strlen(formula); i++)
	{
		if (formula[i]=='(')
		{
			if (!matchingBrackets)
			{
				size++;
			}
			else
			{
				matchingBrackets--;
			}
		}
		else if (formula[i]==')')
		{
			matchingBrackets++;
		}
	}

	Handle sumArray = CreateArray(_, size);
	Handle _operator = CreateArray(_, size);
	int bracket;
	bool escapeCharacter;
	SetArrayCell(sumArray, 0, 0.0);
	SetArrayCell(_operator, bracket, Operator_None);

	char currentCharacter[2];
	char value[16];
	char variable[16];

	for (int i; i <= strlen(formula); i++)
	{
		currentCharacter[0] = formula[i];

		switch (currentCharacter[0])
		{
		case ' ', '\t':
			{
				continue;
			}
		case '(':
			{
				bracket++;
				SetArrayCell(sumArray, bracket, 0.0);
				SetArrayCell(_operator, bracket, Operator_None);
			}
		case ')':
			{
				OperateString(sumArray, bracket, value, sizeof(value), _operator);

				if (GetArrayCell(_operator, bracket) != Operator_None)
				{
					CloseHandle(sumArray);
					CloseHandle(_operator);
					return defaultValue;
				}

				if (--bracket < 0)
				{
					CloseHandle(sumArray);
					CloseHandle(_operator);
					return defaultValue;
				}

				Operate(sumArray, bracket, GetArrayCell(sumArray, bracket + 1), _operator);
			}
		case '\0':
			{
				OperateString(sumArray, bracket, value, sizeof(value), _operator);
			}
		case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.':
			{
				StrCat(value, sizeof(value), currentCharacter);
			}
		case '{':
			{
				escapeCharacter = true;
			}
		case '}':
			{
				if (!escapeCharacter)
				{
					CloseHandle(sumArray);
					CloseHandle(_operator);
					return defaultValue;
				}

				escapeCharacter = false;

				//custom variables - must be a float value
				if (StrEqual(variable, "custom", false))
				{
					Operate(sumArray, bracket, float(0.0), _operator);
				}
				else
				{
					CloseHandle(sumArray);
					CloseHandle(_operator);
					return defaultValue;
				}

				Format(variable, sizeof(variable), "");
			}
		case '+', '-', '*', '/', '^':
			{
				OperateString(sumArray, bracket, value, sizeof(value), _operator);

				switch (currentCharacter[0])
				{
				case '+':
					{
						SetArrayCell(_operator, bracket, Operator_Add);
					}
				case '-':
					{
						SetArrayCell(_operator, bracket, Operator_Subtract);
					}
				case '*':
					{
						SetArrayCell(_operator, bracket, Operator_Multiply);
					}
				case '/':
					{
						SetArrayCell(_operator, bracket, Operator_Divide);
					}
				case '^':
					{
						SetArrayCell(_operator, bracket, Operator_Exponent);
					}
				}
			}
		default:
			{
				if (escapeCharacter)
				{
					StrCat(variable, sizeof(variable), currentCharacter);
				}
				else
				{
					CloseHandle(sumArray);
					CloseHandle(_operator);
					return defaultValue;
				}
			}
		}
	}

	int result = RoundFloat(GetArrayCell(sumArray, 0));

	CloseHandle(sumArray);
	CloseHandle(_operator);

	if (result <= 0)
	{
		return defaultValue;
	}

	return result;
}

stock void Operate(Handle sumArray, int& bracket, float value, Handle _operator)
{
	float sum = GetArrayCell(sumArray, bracket);

	switch (GetArrayCell(_operator, bracket))
	{
	case Operator_Add:
		{
			SetArrayCell(sumArray, bracket, sum+value);
		}
	case Operator_Subtract:
		{
			SetArrayCell(sumArray, bracket, sum-value);
		}
	case Operator_Multiply:
		{
			SetArrayCell(sumArray, bracket, sum*value);
		}
	case Operator_Divide:
		{
			if (!value)
			{
				bracket = 0;
				return;
			}

			SetArrayCell(sumArray, bracket, sum/value);
		}
	case Operator_Exponent:
		{
			SetArrayCell(sumArray, bracket, Pow(sum, value));
		}
	default:
		{
			SetArrayCell(sumArray, bracket, value);
		}
	}

	SetArrayCell(_operator, bracket, Operator_None);
}

stock void OperateString(Handle sumArray, int& bracket, char[] value, int size, Handle _operator)
{
	if (strlen(value) > 0)
	{
		Operate(sumArray, bracket, StringToFloat(value), _operator);
		strcopy(value, size, "");
	}
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

stock void ClearArraySafe(Handle array)
{
	for (int i = 0; i < GetArraySize(array); i++)
	{
		Handle hndl = GetArrayCell(array, i);

		delete hndl;
	}

	ClearArray(array);
}

stock void ClearTrieSafe(Handle map)
{
	if (map == null)
	{
		return;
	}

	Handle snapshot = CreateTrieSnapshot(map);
	int size;

	for (int i = 0; i < TrieSnapshotLength(snapshot); i++)
	{
		size = TrieSnapshotKeyBufferSize(snapshot, i);

		char[] sBuffer = new char[size];
		GetTrieSnapshotKey(snapshot, i, sBuffer, size);

		Handle hLocal;
		GetTrieValue(map, sBuffer, hLocal);

		delete hLocal;

		RemoveFromTrie(map, sBuffer);
	}

	CloseHandle(snapshot);
}

stock void ShowWebPanel(int client, char[] title, char[] url)
{
	char sOpen[128];
	Format(sOpen, sizeof(sOpen), "javascript: var x = screen.width * 0.90;var y = screen.height * 0.90;window.open(\"%s\",\"scrollbars=yes, width='+x+',height='+y+'\");", url);
	ShowMOTDPanel(client, title, sOpen, MOTDPANEL_TYPE_URL);
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
		GetPluginFilename(null, pluginname, PLATFORM_MAX_PATH);
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
	return view_as<bool>(index > 0 && index <= MaxClients);
}

stock bool IsEntityIndex(int index)
{
	return view_as<bool>(index > MaxClients);
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


stock int[] GetConVarColor(Handle convar)
{
	int colors[4] = {255, 255, 255, 255};

	char sBuffer[128];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

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

stock float[] GetConVarVector(Handle convar)
{
	float vectors[3] = {0.0, 0.0, 0.0};

	char sBuffer[128];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

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

stock float[] GetConVar2DVector(Handle convar)
{
	float vectors[2] = {0.0, 0.0};

	char sBuffer[128];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

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

	CloseHandle(trace);
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
	int ip = GetConVarInt(FindConVar("hostip"));

	int ips[4];
	ips[0] = (ip >> 24) & 0x000000FF;
	ips[1] = (ip >> 16) & 0x000000FF;
	ips[2] = (ip >> 8) & 0x000000FF;
	ips[3] = ip & 0x000000FF;

	Format(sIP, size, "%d.%d.%d.%d", ips[0], ips[1], ips[2], ips[3]);

	if (show_port)
	{
		Format(sIP, size, "%s:%d", sIP, GetConVarInt(FindConVar("hostport")));
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
	if (weapon == INVALID_ENT_REFERENCE)
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
	return GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
}

stock int GetRandomClient(bool ingame = true, bool alive = false, bool nofake = false, int team = 0)
{
	int[] clients = new int[MaxClients];
	int amount;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (ingame && !IsClientInGame(i) || alive && !IsPlayerAlive(i) || nofake && IsFakeClient(i) || team > 0 && team != GetClientTeam(i))
		{
			continue;
		}

		clients[amount++] = i;
	}

	return clients[GetRandomInt(0, amount)];
}

stock void SQL_VoidQueryF(Handle& database, DBPriority priority = DBPrio_Normal, const char[] format, any ...)
{
	char query[MAX_QUERY_LENGTH];
	VFormat(query, sizeof(query), format, 4);

	SQL_VoidQuery(database, query, priority);
}

stock void SQL_VoidQuery(Handle& database, const char[] query, DBPriority prio = DBPrio_Normal)
{
	Handle pack = CreateDataPack();
	WritePackString(pack, query);

	SQL_TQuery(database, TQuery_Void, query, pack, prio);
}

public void TQuery_Void(Handle owner, Handle hndl, const char[] error, any data)
{
	if (hndl == null)
	{
		ResetPack(data);

		char sQuery[MAX_QUERY_LENGTH];
		ReadPackString(data, sQuery, sizeof(sQuery));

		LogError("Error executing void query: %s", error);
		LogError("Query Output: %s", sQuery);
	}

	CloseHandle(data);
}

stock void SQL_TQueryF(Handle& database, SQLTCallback callback, any data, DBPriority priority = DBPrio_Normal, const char[] format, any ...)
{
	char query[MAX_QUERY_LENGTH];
	VFormat(query, sizeof(query), format, 6);

	SQL_TQuery(database, callback, query, data, priority);
}

stock int TF2_GetPlayerMaxHealth(int client)
{
	return GetEntProp(GetPlayerResourceEntity(), Prop_Send, "m_iMaxHealth", _, client);
}

stock int GetMaxHealth(int client)
{
	return GetEntProp(client, Prop_Data, "m_iMaxHealth");
}

stock float[] GetClientAbsPosition(int client)
{
	float target_point[3];
	GetClientAbsOrigin(client, target_point);

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
	SubtractVectors(target_point, target_velocity, target_point);

	return target_point;
}

stock int GetClientActiveSlot(int client)
{
	return GetWeaponEntitySlot(client, GetActiveWeapon(client));
}

stock int GetWeaponEntitySlot(int client, int weapon)
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
		if (GetEntPropEnt(entity, Prop_Send, "m_hOwner") == client)
		{
			SetEntityRenderMode(client, RENDER_TRANSCOLOR);
			SetEntityRenderColor(entity, red, green, blue, alpha);
		}
	}

	entity = INVALID_ENT_INDEX;
	while((entity = FindEntityByClassname(entity, "tf_weapon_*")) != INVALID_ENT_INDEX)
	{
		if (GetEntPropEnt(entity, Prop_Send, "m_hOwner") == client)
		{
			SetEntityRenderMode(client, RENDER_TRANSCOLOR);
			SetEntityRenderColor(entity, red, green, blue, alpha);
		}
	}
}

stock void TF2_ForceRoundWin(TFTeam team)
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

stock int GetRandomPlayer(int team)
{
	int[] clients = new int[MaxClients];
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && IsPlayerAlive(i) && GetClientTeam(i) == team)
		{
			clients[count++] = i;
		}
	}

	return (count == 0) ? -1 : clients[GetRandomInt(0, count - 1)];
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

stock bool RemoveEntity(int entity)
{
	if (IsValidEntity(entity))
	{
		return AcceptEntityInput(entity, "Kill");
	}

	return false;
}

stock bool RemoveEntRef(int& reference = INVALID_ENT_REFERENCE)
{
	if (reference != INVALID_ENT_REFERENCE)
	{
		int entity = EntRefToEntIndex(reference);
		bool result = RemoveEntity(entity);

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

	if (!IsValidEntity(weapon) || weapon != GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon"))
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
	return view_as<bool>(value > 0 && GetTime() - value > timer);
}

stock bool CalculateFloatTime(float value, float timer)
{
	return view_as<bool>(value > 0.0 && GetGameTime() - value > timer);
}

stock bool EmitSoundToClientSafe(int client, char sample[PLATFORM_MAX_PATH], int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (!IsPlayerIndex(client) || !IsClientInGame(client) || IsFakeClient(client) || strlen(sample) == 0)
	{
		return false;
	}

	if (StrContains(sample, "sound/") == 0)
	{
		RemoveFrontString(sample, sizeof(sample), 6);
	}

	if (!IsSoundPrecached(sample))
	{
		PrecacheSound(sample);
	}

	if (IsSoundPrecached(sample))
	{
		EmitSoundToClient(client, sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
		return true;
	}

	return false;
}

stock bool EmitSoundToAllSafe(char sample[PLATFORM_MAX_PATH], int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (strlen(sample) == 0)
	{
		return false;
	}

	if (StrContains(sample, "sound/") == 0)
	{
		RemoveFrontString(sample, sizeof(sample), 6);
	}

	if (!IsSoundPrecached(sample))
	{
		PrecacheSound(sample);
	}

	if (IsSoundPrecached(sample))
	{
		EmitSoundToAll(sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
		return true;
	}

	return false;
}

stock void FakePrecacheSound(const char[] szPath)
{
	AddToStringTable(FindStringTable("soundprecache"), szPath);
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
	new_amount = ClampCell(new_amount, 0, GetConVarInt(FindConVar("mp_maxmoney")));
	SetEntProp(client, Prop_Send, "m_iAccount", new_amount);
}

stock void CSGO_SetPlayerIncome(int client, int income)
{
	int new_amount = ClampCell(income, 0, GetConVarInt(FindConVar("mp_maxmoney")));
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
			continue;
		}

		if ((weapon = GetPlayerWeaponSlot(client, i)) != INVALID_ENT_INDEX)
		{
			SDKHooks_DropWeapon(client, weapon, NULL_VECTOR, NULL_VECTOR);
			AcceptEntityInput(weapon, "Kill");
		}
	}
}

stock void CSGO_GiveClientArmor(int client)
{
	SetEntProp(client, Prop_Data, "m_ArmorValue", 100);
}

stock int PrepareModelConVar(ConVar convar, bool prefix = false, bool preload = false)
{
	if (convar == null)
	{
		return 0;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

	return PrepareModel(sBuffer, prefix, preload);
}

stock int PrepareModel(const char[] model, bool prefix = false, bool preload = false)
{
	if (strlen(model) == 0)
	{
		return 0;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	strcopy(sBuffer, sizeof(sBuffer), model);

	if (prefix)
	{
		Format(sBuffer, sizeof(sBuffer), "models/%s", sBuffer);
	}

	PrecacheModel(sBuffer, preload);

	return IsModelPrecached(sBuffer);
}

stock bool SetModelViaConVar(int entity, ConVar convar, bool prefix = false, bool preload = false)
{
	if (convar == null)
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

	return SetModel(entity, sBuffer, prefix, preload);
}

stock bool SetModel(int entity, const char[] model, bool prefix = false, bool preload = false)
{
	if (entity <= 0 || strlen(model) == 0)
	{
		return false;
	}

	if (PrepareModel(model, prefix, preload))
	{
		SetEntityModel(entity, model);
		return true;
	}

	return false;
}

stock bool PrepareSoundConVar(ConVar convar, bool preload = false)
{
	if (convar == null)
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

	return PrepareSound(sBuffer, preload);
}

stock bool PrepareSound(const char[] sound, bool preload = false)
{
	if (strlen(sound) == 0)
	{
		return false;
	}

	return PrecacheSound(sound, preload);
}

stock bool EmitSoundToClientViaConVar(int client, ConVar &convar, bool preload = false, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (!PrepareSoundConVar(convar, preload))
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

	return EmitSoundToClientSafe(client, sBuffer, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}

stock bool EmitSoundToAllViaConVar(ConVar convar, bool preload = false, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (!PrepareSoundConVar(convar, preload))
	{
		return false;
	}

	char sBuffer[PLATFORM_MAX_PATH];
	GetConVarString(convar, sBuffer, sizeof(sBuffer));

	return EmitSoundToAllSafe(sBuffer, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
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

stock void DamageArea(float origin[3], float distance = 500.0, int attacker = 0, int inflictor = 0, int team = 0, float damage = 500.0, int damagetype = 0, int weapon = INVALID_ENT_INDEX, float damageforce[3] = {0.0, 0.0, 0.0})
{
	if (weapon == INVALID_ENT_INDEX && attacker > 0)
	{
		weapon = GetActiveWeapon(attacker);
	}

	float vecOrigin[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || team > 0 && team != GetClientTeam(i) || attacker > 0 && i == attacker)
		{
			continue;
		}

		GetClientAbsOrigin(i, vecOrigin);

		if (GetVectorDistance(origin, vecOrigin) <= distance)
		{
			SDKHooks_TakeDamage(i, inflictor, attacker, damage, damagetype, weapon, damageforce, origin);
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

stock void ShowOverlay(int client, const char[] overlay, float duration)
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
	ShowOverlay(GetClientOfUserId(data), "", 0.0);
}

/*---------------------------------------------------------*/
//Menu stocks by Kisslick
/*---------------------------------------------------------*/
stock void PushMenuString(Handle hndl, const char[] id, const char[] data)
{
	AddMenuItem(hndl, id, data, ITEMDRAW_IGNORE);
}

stock void PushMenuCell(Handle hndl, const char[] id, int data)
{
	char DataString[64];
	IntToString(data, DataString, sizeof(DataString));
	AddMenuItem(hndl, id, DataString, ITEMDRAW_IGNORE);
}

stock void PushMenuFloat(Handle hndl, const char[] id, float data)
{
	char DataString[64];
	FloatToString(data, DataString, sizeof(DataString));
	AddMenuItem(hndl, id, DataString, ITEMDRAW_IGNORE);
}

stock bool GetMenuString(Handle hndl, const char[] id, char[] Buffer, int size)
{
	int ItemCount = GetMenuItemCount(hndl);
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		GetMenuItem(hndl, i, info, sizeof(info), _, data, sizeof(data));

		if (StrEqual(info, id)) {
			strcopy(Buffer, size, data);
			return true;
		}
	}
	return false;
}

stock int GetMenuCell(Handle hndl, const char[] id, int DefaultValue = 0)
{
	int ItemCount = GetMenuItemCount(hndl);
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		GetMenuItem(hndl, i, info, sizeof(info), _, data, sizeof(data));

		if (StrEqual(info, id))
		return StringToInt(data);
	}
	return DefaultValue;
}

stock float GetMenuFloat(Handle hndl, const char[] id, float DefaultValue = 0.0)
{
	int ItemCount = GetMenuItemCount(hndl);
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		GetMenuItem(hndl, i, info, sizeof(info), _, data, sizeof(data));

		if (StrEqual(info, id))
		return StringToFloat(data);
	}
	return DefaultValue;
}

stock void CopyMenuAny(Handle source, Handle dest, const char[] id)
{
	int ItemCount = GetMenuItemCount(source);
	char info[64]; char data[64];

	for (int i = 0; i < ItemCount; i++) {
		GetMenuItem(source, i, info, sizeof(info), _, data, sizeof(data));

		if (StrEqual(info, id))
		AddMenuItem(dest, id, data, ITEMDRAW_IGNORE);
	}
}

stock bool AddMenuItemFormat(Handle& menu, const char[] info, int style = ITEMDRAW_DEFAULT, const char[] format, any ...)
{
	char display[128];
	VFormat(display, sizeof(display), format, 5);

	return view_as<bool>(AddMenuItem(menu, info, display, style));
}
/*--------------------------------------------------------->*/
//TF2 Healing Stocks by Chdata
/*--------------------------------------------------------->*/

stock bool TF2_ReadyToOverheal(int client, int add = 0)
{
	return (add > 0) ? ((TF2_GetMaxHealth(client) - GetClientHealth(client)) < add) : (GetClientHealth(client) >= TF2_GetMaxHealth(client));
}

stock void TF2_AddPlayerHealth(int client, int add, float overheal = 1.5, bool additive = false, bool event = false)
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
	SetEventBool(hEvent, "sourcemod", true);
	SetEventInt(hEvent, "patient", iUserId);
	SetEventInt(hEvent, "healer", healer > 0 && IsClientInGame(healer) ? GetClientUserId(healer) : iUserId);
	SetEventInt(hEvent, "amount", health);
	FireEvent(hEvent);

	hEvent = CreateEvent("player_healonhit", true);
	SetEventBool(hEvent, "sourcemod", true);
	SetEventInt(hEvent, "amount", health);
	SetEventInt(hEvent, "entindex", patient);
	FireEvent(hEvent);
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