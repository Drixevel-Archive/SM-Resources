/**
*   _____                                              _        __  __ _
*  / ____|                                            | |      |  \/  (_)         
* | (___   ___  _   _ _ __ ___ ___ _ __ ___   ___   __| |______| \  / |_ ___  ___ 
*  \___ \ / _ \| | | | '__/ __/ _ \ '_ ` _ \ / _ \ / _` |______| |\/| | / __|/ __|
*  ____) | (_) | |_| | | | (_|  __/ | | | | | (_) | (_| |      | |  | | \__ \ (__ 
* |_____/ \___/ \__,_|_|  \___\___|_| |_| |_|\___/ \__,_|      |_|  |_|_|___/\___|
*                                                                                
*	This include contains a ton of useful stocks and functions you can use.
*	I made this include considering I feel like most of this stuff should be built into Sourcemod anyways.
*	Author: Keith Warren (Drixevel)
*	https://github.com/Drixevel
*
*	NOTE: The best way to use this include is to copy and paste into your projects manually.
*	Credits: Pelipoika, SM9();, TheXeon
**/

//Examples on how to update bitwise operators:
//Apply Bit: bitbuffer |= BIT_1;
//Apply Multi Bit: bitbuffer |= (BIT_1 | BIT_2);
//Remove Bit: bitbuffer &= ~BIT_2;
//Remove Multi Bit: bitbuffer &= ~(BIT_1 | BIT_2);
//
//Example on how to update damage code to add falloff:
//Damage = MaxDmg - (Range - StartFalloff) / (EndFalloff - StartFalloff) * (MaxDmg - MinDmg)

#if defined _misc_sm_included
#endinput
#endif
#define _misc_sm_included

#tryinclude <sdktools>
#tryinclude <sdkhooks>
#tryinclude <regex>
#tryinclude <clientprefs>

#undef REQUIRE_EXTENSIONS
#tryinclude <steamworks>
#define REQUIRE_EXTENSIONS

#define IS_CONSOLE 0
#define IS_SERVER 0

#define INVALID_INDEX -1
#define INVALID_ENT_INDEX -1
#define INVALID_ARRAY_INDEX -1

#define MAX_ENTITY_LIMIT 4096
#define MAX_QUERY_LENGTH 8192
#define MAX_BUTTONS 25
#define MAX_IP_LENGTH 64
#define MAX_MAP_NAME_LENGTH 64
#define MAX_FLAGS_LENGTH 21
#define MAX_STEAMID_LENGTH 64
#define MAX_ENTITY_CLASSNAME_LENGTH 32
#define MAX_PARTICLE_NAME_LENGTH 32
#define MAX_COMMAND_NAME_LENGTH 255

#define EF_BONEMERGE	(1 << 0)
#define EF_BONEMERGE_FASTCULL	(1 << 7)
#define EF_PARENT_ANIMATES	(1 << 9)
#define EF_NOSHADOW		16
#define EF_NOINTERP		8

#define FFADE_IN	0x0001			// Just here so we don't pass 0 into the function
#define FFADE_OUT	0x0002			// Fade out (not in)
#define FFADE_MODULATE	0x0004		// Modulate (don't blend)
#define FFADE_STAYOUT	0x0008		// ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE	0x0010			// Purges all other fades, replacing them with this one

#define	SHAKE_START 0				// Starts the screen shake for all players within the radius.
#define	SHAKE_STOP 1				// Stops the screen shake for all players within the radius.
#define	SHAKE_AMPLITUDE 2			// Modifies the amplitude of an active screen shake for all players within the radius.
#define	SHAKE_FREQUENCY 3			// Modifies the frequency of an active screen shake for all players within the radius.
#define	SHAKE_START_RUMBLEONLY 4	// Starts a shake effect that only rumbles the controller, no screen effect.
#define	SHAKE_START_NORUMBLE 5		// Starts a shake that does NOT rumble the controller.

//Hex Colors ( Should be used as characters and not strings, ala %c or {1:c} )
#define WHITE 0x01
#define DARKRED 0x02
#define PURPLE 0x03
#define GREEN 0x04
#define MOSSGREEN 0x05
#define LIMEGREEN 0x06
#define RED 0x07
#define GRAY 0x08
#define YELLOW 0x09
#define DARKGREY 0x0A
#define BLUE 0x0B
#define DARKBLUE 0x0C
#define LIGHTBLUE 0x0D
#define PINK 0x0E
#define LIGHTRED 0x0F

/*
* Checks whether a client is valid or not.
*
* client	Client index.
*
* return	True if valid, false otherwise.
*/
stock bool IsValidClient(int client)
{
	return client > 0 && client <= MaxClients && IsClientConnected(client) && IsClientInGame(client) && !IsClientSourceTV(client);
}

/*
* Stops the timer and sets it to null.
*
* return	N/A
*/
stock bool StopTimer(Handle& timer)
{
	if (timer != null)
	{
		KillTimer(timer);
		timer = null;
		return true;
	}
	
	return false;
}

/*
* Kicks a client based on the specified SteamID on the server if they exist.
*
* steamid	Steamid to check for based on the authtype.
* authtype	Authtype to check for.
* reason	Reason to give the client being kicked.
* ...		Format arguments for the reaso.
*
* return	True if found and kicked, false otherwise.
*/
stock bool KickClientBySteamID(const char[] steamid, AuthIdType authtype = AuthId_Engine, const char[] reason, any ...)
{
	if (strlen(steamid) == 0)
		return false;
	
	char sBuffer[256];
	VFormat(sBuffer, sizeof(sBuffer), reason, 4);

	char sSteamID[32];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i) || !GetClientAuthId(i, authtype, sSteamID, sizeof(sSteamID)) || !StrEqual(steamid, sSteamID))
			continue;

		KickClient(i, sBuffer);
		return true;
	}

	return false;
}

/*
* Retrieves a client with a specific steamid on the server if they exist.
*
* steamid	Steamid to check for based on the authtype.
* authtype	Authtype to check for.
*
* return	Client index if found, -1 if not found.
*/
stock int GetClientBySteamID(const char[] steamid, AuthIdType authtype = AuthId_Engine)
{
	if (strlen(steamid) == 0)
		return -1;
	
	char sSteamID[64];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i) || !GetClientAuthId(i, authtype, sSteamID, sizeof(sSteamID)) || !StrEqual(steamid, sSteamID))
			continue;

		return i;
	}

	return -1;
}

/*
* Retrieves a client with a specific accountid on the server if they exist.
* AccountIDs are one of the most consistent ways of tracking specific player accounts.
*
* accountid	AccountID to search for.
*
* return	Client index if found, -1 if not found.
*/
stock int GetClientByAccountID(int accountid)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i) || GetSteamAccountID(i) != accountid)
			continue;

		return i;
	}

	return -1;
}

/*
* Retrieves a client with a specific ip address on the server if they exist.
*
* ip		IP address to search for.
*
* return	Client index if found, -1 if not found.
*/
stock int GetClientByIP(const char[] ip)
{
	char sBuffer[16];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;
		
		GetClientIP(i, sBuffer, sizeof(sBuffer));
		
		if (StrEqual(ip, sBuffer))
			return i;
	}

	return -1;
}

/*
* Checks the players steamid based on the auth type.
*
* client	Client index.
* steamid	SteamID to check.
* auth		Auth type to check.
*
* return	True if they have the steamid, false otherwise.
*/
stock bool HasSteamID(int client, const char[] steamid, AuthIdType auth = AuthId_Steam2)
{
	if (!IsClientAuthorized(client) || IsFakeClient(client))
		return false;
	
	char buffer[64];
	if (!GetClientAuthId(client, auth, buffer, sizeof(buffer)))
		return false;
	
	return StrEqual(buffer, steamid, false);
}

/*
* Checks whether or not the client is console or not. (Same as IsClientConsole)
* You can easily just add checks to make sure client is more than 0 if you use this for error checking.
* I use this sometimes for things like replies to console specifically.
*
* client	Client index.
*
* return	True if client is console, false otherwise.
*/
stock bool IsClientServer(int client)
{
	return client == 0;
}

/*
* Converts a string to a boolean.
* Fixes the ugly workaround it's actually doing.
*
* str	String to convert.
*
* return	Boolean version.
*/
stock bool StringToBool(const char[] str)
{
	return view_as<bool>(StringToInt(str));
}

/*
* Converts a string to a 3D vector.
* Fixes the ugly workaround it's actually doing.
*
* explode	String to convert to 3D vectors.
* buffer	Buffer to store values in.
* defaultvector	Default values if the string is malformed.
*
* return	True if converted successfully, false otherwise.
*/
stock bool StringToVector(const char[] explode, float buffer[3], float defaultvector[3] = {0.0, 0.0, 0.0})
{
	if (strlen(explode) == 0)
	{
		buffer[0] = defaultvector[0]; buffer[1] = defaultvector[1]; buffer[2] = defaultvector[2];
		return false;
	}

	char sPart[3][32];
	int iReturned = ExplodeString(explode, StrContains(explode, ", ") != -1 ? ", " : " ", sPart, 3, 32);

	if (iReturned != 3)
	{
		buffer[0] = defaultvector[0]; buffer[1] = defaultvector[1]; buffer[2] = defaultvector[2];
		return false;
	}

	buffer[0] = StringToFloat(sPart[0]); buffer[1] = StringToFloat(sPart[1]); buffer[2] = StringToFloat(sPart[2]);
	return true;
}

/*
* Converts a string to a 2D vector.
* Fixes the ugly workaround it's actually doing.
*
* explode	String to convert to 3D vectors.
* buffer	Buffer to store values in.
* defaultvector	Default values if the string is malformed.
*
* return	True if converted successfully, false otherwise.
*/
stock bool StringToVector2D(const char[] explode, float buffer[2], float defaultvector[2] = {0.0, 0.0})
{
	if (strlen(explode) == 0)
	{
		buffer[0] = defaultvector[0]; buffer[1] = defaultvector[1];
		return false;
	}

	char sPart[2][32];
	int iReturned = ExplodeString(explode, StrContains(explode, ", ") != -1 ? ", " : " ", sPart, 2, 32);

	if (iReturned != 2)
	{
		buffer[0] = defaultvector[0]; buffer[1] = defaultvector[1];
		return false;
	}

	buffer[0] = StringToFloat(sPart[0]); buffer[1] = StringToFloat(sPart[1]);
	return true;
}

/*
* Converts a string to a color vector.
* Fixes the ugly workaround it's actually doing.
*
* explode	String to convert a color vector.
* buffer	Buffer to store values in.
* defaultvector	Default values if the string is malformed.
*
* return	True if converted successfully, false otherwise.
*/
stock bool StringToColor(const char[] explode, int buffer[4], int defaultvalues[4] = {255, 255, 255, 255})
{
	if (strlen(explode) == 0)
	{
		buffer[0] = defaultvalues[0]; buffer[1] = defaultvalues[1]; buffer[2] = defaultvalues[2]; buffer[3] = defaultvalues[3];
		return false;
	}

	char sPart[4][32];
	int iReturned = ExplodeString(explode, StrContains(explode, ",") != -1 ? ", " : " ", sPart, 4, 32);

	if (iReturned != 4)
	{
		buffer[0] = defaultvalues[0]; buffer[1] = defaultvalues[1]; buffer[2] = defaultvalues[2]; buffer[3] = defaultvalues[3];
		return false;
	}

	buffer[0] = StringToInt(sPart[0]); buffer[1] = StringToInt(sPart[1]); buffer[2] = StringToInt(sPart[2]); buffer[3] = StringToInt(sPart[3]);
	return true;
}

/*
* Same as array.PushString/PushArrayString but with a formatting parameter.
*
* array		Array handle to push.
* format	Format buffer to use.
* ...		Parameters to use.
*
* return	Index used in the array, -1 otherwise.
*/
stock int PushArrayStringFormat(ArrayList array, char[] format, any ...)
{
	if (array == null)
		return -1;
	
	char sBuffer[1024];
	VFormat(sBuffer, sizeof(sBuffer), format, 3);
	return array.PushString(sBuffer);
}

/*
* Clears the ArrayStack handles data.
* Apparently there isn't a native one.
*
* stack		ArrayStack handle to push.
*
* return	True if successfully emptied, false otherwise.
*/
stock bool ClearStack(ArrayStack stack)
{
	if (stack == null)
		return false;

	while (!stack.Empty)
		stack.Pop();
		
	return true;
}

/*
* Prints a specific file on the server to console.
* Mostly used to debug error logs but it can be used for anything.
*
* client	Client index.
* path		Path to the file.
*
* return	True if file is found and shown, false otherwise.
*/
stock bool PrintFileToConsole(int client, const char[] path)
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

/*
* Checks if a client has specific flags or not.
* This is mostly deprecated though, might as well use CheckCommandAccess with ReadFlagString instead.
* CheckCommandAccess(client, "", ReadFlagString(flags), true);
*
* client	Client index.
* flags		Flags to check for.
*
* return	True if client has flags, false otherwise.
*/
//Forgot
//Lost but not forgotten.
stock bool CheckAdminFlagsByString(int client, const char[] flags)
{
	if (client == 0 || IsFakeClient(client) || strlen(flags) == 0)
		return false;

	AdminId admin = GetUserAdmin(client);

	if (admin != INVALID_ADMIN_ID)
	{
		int count; int found; int flags = ReadFlagString(flags);

		for (int i = 0; i <= 20; i++)
		{
			if (flags & (1 << i))
			{
				count++;

				if (GetAdminFlag(admin, view_as<AdminFlag>(i)))
					found++;
			}
		}

		if (count == found)
			return true;
	}

	return false;
}

/*
* Returns a random boolean between true or false.
*
* return	True or false.
*/
stock bool GetRandomBool()
{
	return view_as<bool>(GetRandomInt(0, 1));
}

/*
* Sends an input to the entity if it's valid.
* Also checks if the world is trying to be killed due to faulty checks.
*
* dest		Destination entity.
* input		Input to send.
* activator	Activator sending the input.
* caller	Caller sending the input.
* outputid	Outputid to send the input.
*
* return	True if successful, false otherwise.
*/
stock bool AcceptEntityInputSafe(int dest, const char[] input, int activator = -1, int caller = -1, int outputid = 0)
{
	if (!IsValidEntity(dest) || dest < 1 && StrEqual(input, "kill", false))
		return false;
	
	return AcceptEntityInput(dest, input, activator, caller, outputid);
}

/*
* Same as AddFileToDownloadsTable except as a format buffer.
*
* format	Format buffer.
* ...		Parameters to use.
*
* return	True if successful, false otherwise.
*/
stock bool AddFileToDownloadsTableEx(const char[] format, any ...)
{
	if (strlen(format) == 0)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	VFormat(sBuffer, sizeof(sBuffer), format, 2);

	AddFileToDownloadsTable(sBuffer);
	return true;
}

/*
* Format seconds into a formatted string to display neatly.
* This function can largely be edited to fit whatever needs, it's hard to make a solid stock for every necessity.
*
* seconds	Seconds to convert.
* buffer	Buffer to store the results.
* maxlength	Length of the buffer.
* format	Format string to reference to reference and save in the buffer.
* precision	Whether to use precise milliseconds alongside the normal display of seconds. (Useful for precise timers)
*
* return	N/A
*/
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

/*
* Clears all indexes from an array that have the specified value.
*
* array		Array handle.
* value		Value to clear.
*
* return	N/A
*/
stock void ClearValueFromArray(ArrayList array, any value)
{
	if (array == null || array.FindValue(value) == -1)
		return;
	
	int index;
	while ((index = array.FindValue(value)) != -1)
		array.Erase(index);
}

/*
* Clears an array of all indexes regardless if handles exist or not.
* Clearing the array normally won't kill the handles saved as well.
*
* array		Array handle.
*
* return	True if cleared, false otherwise.
*/
stock bool ClearArraySafe(ArrayList array)
{
	if (array == null)
		return false;
	
	for (int i = 0; i < array.Length; i++)
	{
		Handle hndl = array.Get(i);
		delete hndl;
	}

	array.Clear();
	return true;
}

/*
* Clears a stringmap of all indexes regardless if handles exist or not.
* Clearing the stringmap normally won't kill the handles saved as well.
*
* map		StringMap handle.
*
* return	True if cleared, false otherwise.
*/
stock bool ClearTrieSafe(StringMap map)
{
	if (map == null)
		return false;

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
	return true;
}

stock void SteamWorks_SetHTTPRequestGetOrPostParameterInt(Handle hHandle, const char[] sName, int value)
{
	char sValue[256];
	IntToString(value, sValue, sizeof(sValue));
	SteamWorks_SetHTTPRequestGetOrPostParameter(hHandle, sName, sValue);
}

stock float CalculateFloat(int value1, int value2, float fMultiplier = 0.0)
{
	float fValue = float(value1) / float(value2);

	if (value2 < 1)
		fValue = float(value1);

	if (value1 < 1)
		fValue =  0.0;

	if (fMultiplier > 0.0)
		fValue *= fMultiplier;

	return fValue;
}

stock void LogDebug(char[] name, const char[] format, any ...)
{
	char sLog[4096];
	VFormat(sLog, sizeof(sLog), format, 3);

	char sDate[32];
	FormatTime(sDate, sizeof(sDate), "%Y-%m-%d", GetTime());

	if (strlen(name) == 0)
		strcopy(name, PLATFORM_MAX_PATH, "Debug");

	char sPath[PLATFORM_MAX_PATH]; char sPathFinal[PLATFORM_MAX_PATH];
	Format(sPath, sizeof(sPath), "logs/%s.%s.log", name, sDate);
	BuildPath(Path_SM, sPathFinal, sizeof(sPathFinal), sPath);

	LogToFileEx(sPathFinal, "%s", sLog);
}

stock bool IsStringNumeric(const char[] str)
{
	int x = 0;
	int dotsFound = 0;
	int numbersFound = 0;

	if (str[x] == '+' || str[x] == '-')
		x++;

	while (str[x] != '\0')
	{
		if (IsCharNumeric(str[x]))
			numbersFound++;
		else if (str[x] == '.')
		{
			dotsFound++;

			if (dotsFound > 1)
				return false;
		}
		else
			return false;

		x++;
	}

	return numbersFound > 0;
}

stock void StripCharactersPre(char[] buffer, int size, int position)
{
	strcopy(buffer, size, buffer[position]);
}

stock void StripCharactersPost(char[] buffer, int position)
{
	buffer[position] = '\0';
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

stock bool IsEntityWorld(int index)
{
	return index == 0;
}

stock int GetRandomString(char[] buffer, int size, int length = 32, const char[] chrs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234556789")
{
	int random; int len;
	size--;

	if (chrs[0] != '\0')
		len = strlen(chrs) - 1;

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

stock void FillArrayToValue(any[] array, int size, any value, int start = 0)
{
	if (start < 0)
		start = 0;

	for (int i = start; i < size; i++)
		array[i] = value;
}

stock void CopyArrayToArray(const any[] array, any[] newArray, int size)
{
	for (int i = 0; i < size; i++)
		newArray[i] = array[i];
}

stock bool GetClientLookOrigin(int client, float pOrigin[3], bool filter_players = true, float distance = 35.0)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client))
		return false;

	float vOrigin[3];
	GetClientEyePosition(client,vOrigin);

	float vAngles[3];
	GetClientEyeAngles(client, vAngles);

	Handle trace = TR_TraceRayFilterEx(vOrigin, vAngles, MASK_SHOT, RayType_Infinite, filter_players ? TraceEntityFilterPlayer : TraceEntityFilterNone, client);
	bool bReturn = TR_DidHit(trace);

	if (bReturn)
	{
		float vStart[3];
		TR_GetEndPosition(vStart, trace);

		float vBuffer[3];
		GetAngleVectors(vAngles, vBuffer, NULL_VECTOR, NULL_VECTOR);

		pOrigin[0] = vStart[0] + (vBuffer[0] * -distance);
		pOrigin[1] = vStart[1] + (vBuffer[1] * -distance);
		pOrigin[2] = vStart[2] + (vBuffer[2] * -distance);
	}

	delete trace;
	return bReturn;
}

stock bool IsPlayerStuck(int client)
{
	float vecMin[3];
	GetEntPropVector(client, Prop_Send, "m_vecMins", vecMin);
	
	float vecMax[3];
	GetEntPropVector(client, Prop_Send, "m_vecMaxs", vecMax);
	
	float vecOrigin[3];
	GetEntPropVector(client, Prop_Send, "m_vecOrigin", vecOrigin);
	
	TR_TraceHullFilter(vecOrigin, vecOrigin, vecMin, vecMax, MASK_SOLID, TraceEntityFilterNone, client);
	return (TR_DidHit());
}

public bool TraceEntityFilterPlayer(int entity, int contentsMask, any data)
{
	return entity > MaxClients || !entity;
}

public bool TraceEntityFilterNone(int entity, int contentsMask, any data)
{
	return entity != data;
}

stock bool IsEntityInSightRange(int client, int entity, float angle = 90.0, float distance = 0.0, bool heightcheck = true, bool negativeangle = false)
{
	if (angle > 360.0 || angle < 0.0)
		angle = 180.0;
	
	float anglevector[3];
	GetClientEyeAngles(client, anglevector);
	
	anglevector[0] = anglevector[2] = 0.0;
	
	GetAngleVectors(anglevector, anglevector, NULL_VECTOR, NULL_VECTOR);
	NormalizeVector(anglevector, anglevector);
	
	if (negativeangle)
		NegateVector(anglevector);
	
	float clientpos[3];
	GetClientAbsOrigin(client, clientpos);
	
	float targetpos[3];
	
	if (HasEntProp(entity, Prop_Data, "m_vecAbsOrigin"))
		GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", targetpos);
	else
		GetClientAbsOrigin(entity, targetpos);
	
	float resultdistance;
	if (heightcheck && distance > 0)
		resultdistance = GetVectorDistance(clientpos, targetpos);
	
	clientpos[2] = targetpos[2] = 0.0;
	
	float targetvector[3];
	MakeVectorFromPoints(clientpos, targetpos, targetvector);
	NormalizeVector(targetvector, targetvector);
	
	float resultangle = RadToDeg(ArcCosine(GetVectorDotProduct(targetvector, anglevector)));
	
	if (resultangle <= angle / 2)	
	{
		if(distance > 0)
		{
			if(!heightcheck)
				resultdistance = GetVectorDistance(clientpos, targetpos);
			if(distance >= resultdistance)
				return true;
			else
				return false;
		}
		else
			return true;
	}
	else
		return false;
}

stock int TE_LookupParticle(const char[] name)
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
	
	return stridx;
}

stock void TE_Particle(char[] name, float origin[3], int entity = -1, float angles[3] = {0.0, 0.0, 0.0}, bool resetparticles = false)
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

stock void TE_ParticleByID(int stridx, float origin[3], int entity = -1, float angles[3] = {0.0, 0.0, 0.0}, bool resetparticles = false)
{
	if (stridx == INVALID_STRING_INDEX)
		return;

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

stock int AttachParticle(int entity, const char[] name, float time = 0.0, const char[] attach = "", float angles[3] = {0.0, 0.0, 0.0}, float offsets[3] = {0.0, 0.0, 0.0})
{
	float origin[3];
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", origin);
	
	origin[0] += offsets[0];
	origin[1] += offsets[1];
	origin[2] += offsets[2];

	int particle = CreateEntityByName("info_particle_system");

	if (IsValidEntity(particle))
	{
		DispatchKeyValueVector(particle, "origin", origin);
		DispatchKeyValueVector(particle, "angles", angles);
		DispatchKeyValue(particle, "effect_name", name);

		DispatchSpawn(particle);
		ActivateEntity(particle);
		AcceptEntityInput(particle, "Start");

		if (time > 0.0)
		{
			char output[64];
			Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", time);
			SetVariantString(output);
			AcceptEntityInput(particle, "AddOutput");
			AcceptEntityInput(particle, "FireUser1");
		}
		
		SetVariantString("!activator");
		AcceptEntityInput(particle, "SetParent", entity, particle, 0);

		if (strlen(attach) > 0)
		{
			SetVariantString(attach);
			AcceptEntityInput(particle, "SetParentAttachmentMaintainOffset", particle, particle, 0);
		}
	}

	return particle;
}

stock int CreateParticle(const char[] name, float origin[3], float time = 0.0, float angles[3] = {0.0, 0.0, 0.0}, float offsets[3] = {0.0, 0.0, 0.0})
{
	if (strlen(name) == 0)
		return -1;

	origin[0] += offsets[0];
	origin[1] += offsets[1];
	origin[2] += offsets[2];

	int entity = CreateEntityByName("info_particle_system");

	if (IsValidEntity(entity))
	{
		DispatchKeyValueVector(entity, "origin", origin);
		DispatchKeyValueVector(entity, "angles", angles);
		DispatchKeyValue(entity, "effect_name", name);

		DispatchSpawn(entity);
		ActivateEntity(entity);
		AcceptEntityInput(entity, "Start");

		if (time > 0.0)
		{
			char output[64];
			Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", time);
			SetVariantString(output);
			AcceptEntityInput(entity, "AddOutput");
			AcceptEntityInput(entity, "FireUser1");
		}
	}

	return entity;
}

stock void SetEntitySelfDestruct(int entity, float duration)
{
	char output[64];
	Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", duration);
	SetVariantString(output);
	AcceptEntityInput(entity, "AddOutput");
	AcceptEntityInput(entity, "FireUser1");
}

stock void PrecacheParticle(const char[] particle)
{
	if (!IsValidEntity(0))
		return;
	
	int entity = -1;
	
	if ((entity = CreateEntityByName("info_particle_system")) == -1)
		return;
	
	char sName[32];
	GetEntPropString(0, Prop_Data, "m_iName", sName, sizeof(sName));
	
	DispatchKeyValue(entity, "parentname", sName);
	DispatchKeyValue(entity, "effect_name", particle);
	DispatchSpawn(entity);
	
	SetVariantString(sName);
	AcceptEntityInput(entity, "SetParent", 0, 0, 0);
	
	ActivateEntity(entity);
	AcceptEntityInput(entity, "start");
	
	char output[64];
	Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", 0.1);
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
			AcceptEntityInput(iChild, "SetParentAttachment", iParented, iChild);
	}
}

stock bool AreVectorsEqual(const float vec1[3], const float vec2[3])
{
	return vec1[0] == vec2[0] && vec1[1] == vec2[1] && vec1[2] == vec2[2];
}

stock void GetServerIP(char[] buffer, int size, bool showport = false)
{
	int ip = FindConVar("hostip").IntValue;

	int ips[4];
	ips[0] = (ip >> 24) & 0x000000FF;
	ips[1] = (ip >> 16) & 0x000000FF;
	ips[2] = (ip >> 8) & 0x000000FF;
	ips[3] = ip & 0x000000FF;

	Format(buffer, size, "%d.%d.%d.%d", ips[0], ips[1], ips[2], ips[3]);

	if (showport)
		Format(buffer, size, "%s:%d", buffer, FindConVar("hostport").IntValue);
}

stock bool SetPlayerWeaponAmmo(int client, int weapon, int clip = -1, int ammo = -1)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon))
		return false;

	if (GetClip(weapon) == -1)
		clip = -1;

	if (clip > -1)
		SetEntProp(weapon, Prop_Send, "m_iClip1", clip);

	if (GetAmmo(client, weapon) == -1)
		ammo = -1;
	
	if (ammo > -1)
	{
		int iOffset = FindDataMapInfo(client, "m_iAmmo") + (GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoType") * 4);
		SetEntData(client, iOffset, ammo, 4, true);
	}

	return true;
}

stock int GetClip(int weapon)
{
	if (weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Data, "m_iClip1"))
		return -1;

	return GetEntProp(weapon, Prop_Data, "m_iClip1");
}

stock bool SetClip(int weapon, int clip)
{
	if (weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Data, "m_iClip1"))
		return false;

	if (clip < 0)
		clip = 0;

	SetEntProp(weapon, Prop_Data, "m_iClip1", clip);
	return true;
}

stock int GetAmmo(int client, int weapon)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType"))
		return -1;

	int iOffset = GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4;
	int iAmmoTable = FindSendPropInfo("CTFPlayer", "m_iAmmo");
	return GetEntData(client, iAmmoTable + iOffset);
}

stock bool SetAmmo(int client, int weapon, int ammo)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType"))
		return false;

	if (ammo < 0)
		ammo = 0;
	
	SetEntData(client, FindSendPropInfo("CTFPlayer", "m_iAmmo") + (GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4), ammo, 4, true);
	return true;
}

stock bool AddAmmo(int client, int weapon, int ammo)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType"))
		return false;

	if (ammo < 0)
		ammo = 0;
		
	int iOffset = GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4;
	int iAmmoTable = FindSendPropInfo("CTFPlayer", "m_iAmmo");
	int current = GetEntData(client, iAmmoTable + iOffset);
	
	int set = ammo + current;
	int max = GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoCount");
	
	if (set > max)
		set = max;
	
	SetEntData(client, FindSendPropInfo("CTFPlayer", "m_iAmmo") + (GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4), set, 4, true);
	return true;
}

stock bool StripAmmo(int client, int weapon, int ammo)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType"))
		return false;

	if (ammo < 0)
		ammo = 0;
		
	int iOffset = GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4;
	int iAmmoTable = FindSendPropInfo("CTFPlayer", "m_iAmmo");
	int current = GetEntData(client, iAmmoTable + iOffset);
	
	int set = ammo - current;
	
	if (set < 0)
		set = 0;
	
	SetEntData(client, FindSendPropInfo("CTFPlayer", "m_iAmmo") + (GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4), set, 4, true);
	return true;
}

stock int GetMaxAmmo(int weapon)
{
	if (weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Data, "m_iPrimaryAmmoCount"))
		return -1;

	return GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoCount");
}

stock void RefillAmmo(int client, int weapon)
{
	int max = GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoCount");
	SetEntData(client, FindSendPropInfo("CTFPlayer", "m_iAmmo") + (GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4), max, 4, true);
}

stock void RefillWeapons(int client)
{
	int weapon; int max;
	for (int i = 0; i < 5; i++)
	{
		weapon = GetPlayerWeaponSlot(client, i);
		
		if (!IsValidEntity(weapon))
			continue;
		
		max = GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoCount");
		SetEntData(i, FindSendPropInfo("CTFPlayer", "m_iAmmo") + (GetEntProp(weapon, Prop_Send, "m_iPrimaryAmmoType", 1) * 4), max, 4, true);
	}
}

stock int GetActiveWeapon(int client)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || !HasEntProp(client, Prop_Send, "m_hActiveWeapon"))
		return -1;

	return GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
}

stock int GetActiveWeaponIndex(int client)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || !HasEntProp(client, Prop_Send, "m_hActiveWeapon"))
		return -1;
	
	int weapon = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
	
	if (!IsValidEntity(weapon))
		return -1;
	
	return GetEntProp(weapon, Prop_Send, "m_iItemDefinitionIndex");
}

stock int GetActiveWeaponSlot(int client)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client))
		return -1;
	
	int weapon = GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
	
	if (weapon == 0 || weapon < MaxClients || !IsValidEntity(weapon))
		return -1;
	
	for (int i = 0; i < 5; i++)
	{
		if (GetPlayerWeaponSlot(client, i) != weapon)
			continue;

		return i;
	}

	return -1;
}

stock int GetWeaponSlot(int client, int weapon)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || weapon == 0 || weapon < MaxClients || !IsValidEntity(weapon))
		return -1;

	for (int i = 0; i < 5; i++)
	{
		if (GetPlayerWeaponSlot(client, i) != weapon)
			continue;

		return i;
	}

	return -1;
}

stock int GetWeaponIndex(int weapon)
{
	return GetEntProp(weapon, Prop_Send, "m_iItemDefinitionIndex");
}

stock int GetItemIndex(int item)
{
	return GetEntProp(item, Prop_Send, "m_iItemDefinitionIndex");
}

stock int GetWeaponIndexBySlot(int client, int slot)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client))
		return -1;

	int weapon = GetPlayerWeaponSlot(client, slot);
	
	if (!IsValidEntity(weapon))
		return -1;

	return GetEntProp(weapon, Prop_Send, "m_iItemDefinitionIndex");
}

stock bool HasWeapon(int client, const char[] entity, bool caseSensitive = true)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client))
		return false;
	
	int weapon; char class[32];
	for (int i = 0; i < 5; i++)
	{
		weapon = GetPlayerWeaponSlot(client, i);
		
		if (!IsValidEntity(weapon))
			continue;
		
		GetEntityClassname(weapon, class, sizeof(class));
		
		if (StrEqual(class, entity, caseSensitive))
			return true;
	}
	
	return false;
}

stock int GetWeapon(int client, const char[] entity, bool caseSensitive = true)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client))
		return -1;
	
	int weapon; char class[32];
	for (int i = 0; i < 5; i++)
	{
		weapon = GetPlayerWeaponSlot(client, i);
		
		if (!IsValidEntity(weapon))
			continue;
		
		GetEntityClassname(weapon, class, sizeof(class));
		
		if (StrEqual(class, entity, caseSensitive))
			return weapon;
	}
	
	return -1;
}

stock bool IsValidHex(const char[] strHex)
{
	if (strlen(strHex) != 6)
		return false;
	
	Handle g_hRegexHex = CompileRegex("([A-Fa-f0-9]{6})");
	int captures = MatchRegex(g_hRegexHex, strHex);
	
	if (strlen(strHex) == 6 && captures > 0)
		return true;
	
	return false;
}

stock int GetRandomClient(bool ingame = true, bool alive = false, bool fake = false, int team = 0)
{
	int[] clients = new int[MaxClients];
	int amount;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (ingame && !IsClientInGame(i) || alive && !IsPlayerAlive(i) || !fake && IsFakeClient(i) || team > 0 && team != GetClientTeam(i))
			continue;

		clients[amount++] = i;
	}

	return (amount == 0) ? -1 : clients[GetRandomInt(0, amount - 1)];
}

stock int GetSlotIDFromName(const char[] name)
{
	if (StrEqual(name, "primary", false))
		return 0;
	else if (StrEqual(name, "secondary", false))
		return 1;
	else if (StrEqual(name, "melee", false) || StrEqual(name, "knife", false))
		return 2;
	else if (StrEqual(name, "grenade", false))
		return 3;
	
	switch (GetEngineVersion())
	{
		case Engine_CSGO, Engine_CSS:
		{
			if (StrEqual(name, "c4", false))
				return 4;
		}
		case Engine_TF2:
		{
			if (StrEqual(name, "building", false))
				return 4;
			else if (StrEqual(name, "pda", false))
				return 5;
			else if (StrEqual(name, "item1", false))
				return 6;
			else if (StrEqual(name, "item2", false))
				return 7;
		}
		
	}
	
	return -1;
}

stock bool ShowSyncHudTextAll(Handle& sync, const char[] format, any ...)
{
	if (sync == null || strlen(format) == 0)
		return false;

	char buffer[255];
	VFormat(buffer, sizeof(buffer), format, 3);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;

		ShowSyncHudText(i, sync, buffer);
	}

	return true;
}

stock bool ShowHudTextAll(int channel, const char[] format, any ...)
{
	if (channel <= 0 || channel > 6 || strlen(format) == 0)
		return false;

	char buffer[255];
	VFormat(buffer, sizeof(buffer), format, 3);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;

		ShowHudText(i, channel, buffer);
	}

	return true;
}

stock void ClearSyncHudAll(Handle& sync)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;

		ClearSyncHud(i, sync);
	}
}

stock bool ChangeClientTeam_Alive(int client, int team)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || team < 2 || team > 3)
		return false;

	int lifestate = GetEntProp(client, Prop_Send, "m_lifeState");
	SetEntProp(client, Prop_Send, "m_lifeState", 2);
	ChangeClientTeam(client, team);
	SetEntProp(client, Prop_Send, "m_lifeState", lifestate);
	
	return true;
}

stock int GetClientAbsCount()
{
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsClientSourceTV(i))
			continue;

		count++;
	}

	return count;
}

stock int GetTeamAbsCount(int team)
{
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsClientSourceTV(i) || GetClientTeam(i) != team)
			continue;

		count++;
	}

	return count;
}

stock int GetClientAliveCount()
{
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsClientSourceTV(i) || !IsPlayerAlive(i))
			continue;

		count++;
	}

	return count;
}

stock int GetTeamAliveCount(int team)
{
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsClientSourceTV(i) || !IsPlayerAlive(i) || GetClientTeam(i) != team)
			continue;

		count++;
	}

	return count;
}

stock int GetClientDeadCount()
{
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsClientSourceTV(i) || IsPlayerAlive(i))
			continue;

		count++;
	}

	return count;
}

stock int GetTeamDeadCount(int team)
{
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsClientSourceTV(i) || IsPlayerAlive(i) || GetClientTeam(i) != team)
			continue;

		count++;
	}

	return count;
}

stock int GetBothTeamCount()
{
	int count;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsClientSourceTV(i) || GetClientTeam(i) != 2 || GetClientTeam(i) != 3)
			continue;

		count++;
	}

	return count;
}

stock int GetClientsNearEntity(int entity, float distance = 1000.0, int team = 0, bool fake = true)
{
	int count;

	float vecOrigin1[3];
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", vecOrigin1);

	float vecOrigin2[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || (team > 0 && team != GetClientTeam(i)) || (!fake && IsFakeClient(i)))
			continue;

		GetClientAbsOrigin(i, vecOrigin2);

		if (GetVectorDistance(vecOrigin1, vecOrigin2) > distance)
			continue;

		count++;
	}

	return count;
}

stock any ClampCell(any value, any min, any max)
{
	if (value < min)
		value = min;

	if (value > max)
		value = max;

	return value;
}

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

stock float FloatDivider(float value, float divider)
{
	return value *= 1.0 - divider;
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
	
	KeyValues kv = new KeyValues("Stuff", "title", message);
	kv.SetColor("color", color[0], color[1], color[2], color[3]);
	kv.SetNum("level", 1);
	kv.SetNum("time", 10);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;
		
		CreateDialog(i, kv, DialogType_Msg);
	}
	
	delete kv;
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

//You can skip using these if you set 'sv_hudhint_sound' to 0 on your server.
//I like to keep it on and selectively choose when to not use the sound so it can also be an alert.
stock void PrintSilentHintAll(const char[] format, any ...)
{
	char message[255];
	VFormat(message, sizeof(message), format, 2);
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;
		
		PrintHintText(i, message);
		StopSound(i, SNDCHAN_STATIC, "UI/hint.wav");
	}
}

stock void PrintSilentHint(int client, const char[] format, any ...)
{
	char message[255];
	VFormat(message, sizeof(message), format, 3);
	PrintHintText(client, message);
	StopSound(client, SNDCHAN_STATIC, "UI/hint.wav");
}

enum ErrorCode
{
	Error_Unknown,
	Error_SQLDisconnected,
	Error_SQLInvalidResults,
	Error_InvalidTarget
}

stock bool SendClientError(int client, ErrorCode error_code, char[] format = "", any ...)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || IsFakeClient(client))
		return false;
	
	char sBuffer[255];
	VFormat(sBuffer, sizeof(sBuffer), format, 4);
	
	if (strlen(sBuffer) == 0)
	{
		switch (error_code)
		{
			case Error_SQLDisconnected: strcopy(sBuffer, sizeof(sBuffer), "Not Connected");
			case Error_SQLInvalidResults: strcopy(sBuffer, sizeof(sBuffer), "Invalid database results.");
			case Error_InvalidTarget: strcopy(sBuffer, sizeof(sBuffer), "Target not found.");
			default: strcopy(sBuffer, sizeof(sBuffer), "Unknown Error");
		}
	}
	
	ReplyToCommand(client, "Error Reported: %s [ERROR CODE: %i]", sBuffer, error_code);
	return true;
}

//WARNING: Don't call this inside of the 'player_death' event, it'll crash. (May also apply to some OnTakeDamage hooks as well)
stock void DamageRadius(float origin[3], float distance = 500.0, float damage = 500.0, int attacker = 0, int inflictor = 0, int damagetype = DMG_GENERIC, int weapon = -1, float damageforce[3] = NULL_VECTOR)
{
	if (distance <= 0.0 || damage <= 0.0)
		return;

	float vecOrigin[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || (attacker > 0 && i == attacker))
			continue;

		GetClientAbsOrigin(i, vecOrigin);
		
		if (GetVectorDistance(origin, vecOrigin) > distance)
			continue;

		SDKHooks_TakeDamage(i, inflictor, attacker, damage, damagetype, weapon, damageforce, origin);
	}

	int entity = -1;
	while ((entity = FindEntityByClassname(entity, "*")) != -1)
	{
		if (!HasEntProp(entity, Prop_Send, "m_vecOrigin") || entity < MaxClients)
			continue;

		GetEntPropVector(entity, Prop_Send, "m_vecOrigin", vecOrigin);

		if (GetVectorDistance(origin, vecOrigin) > distance)
			continue;

		SDKHooks_TakeDamage(entity, inflictor, attacker, damage, damagetype, weapon, damageforce, origin);
	}
}

stock void DamagePlayersInRadius(float origin[3], float distance = 500.0, float damage = 500.0, int attacker = 0, int inflictor = 0, int damagetype = DMG_GENERIC, int weapon = -1, float damageforce[3] = NULL_VECTOR)
{
	if (distance <= 0.0 || damage <= 0.0)
		return;

	float vecOrigin[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || (attacker > 0 && i == attacker))
			continue;

		GetClientAbsOrigin(i, vecOrigin);
		
		if (GetVectorDistance(origin, vecOrigin) > distance)
			continue;

		SDKHooks_TakeDamage(i, inflictor, attacker, damage, damagetype, weapon, damageforce, origin);
	}
}

stock void DamageRadiusWithFalloff(float origin[3], float distance = 500.0, float min_damage = 10.0, float max_damage = 50.0, int attacker = 0, int inflictor = 0, int damagetype = DMG_GENERIC, int weapon = -1, float damageforce[3] = NULL_VECTOR)
{
	if (distance <= 0.0)
		return;

	float vecOrigin[3]; float actualdistance; float tempdamage;
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || (attacker > 0 && i == attacker))
			continue;

		GetClientAbsOrigin(i, vecOrigin);
		
		actualdistance = GetVectorDistance(origin, vecOrigin);
		if (actualdistance > distance)
			continue;
		
		tempdamage = max_damage - (actualdistance - 0.0) / (distance - 0.0) * (max_damage - min_damage);

		SDKHooks_TakeDamage(i, inflictor, attacker, tempdamage, damagetype, weapon, damageforce, origin);
	}
}

stock void ScreenFadeAll(int duration = 4, int hold_time = 4, int flag = FFADE_IN, int colors[4] = {255, 255, 255, 255}, bool reliable = true)
{
	bool pb = GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf;
	Handle userMessage;
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
		
		userMessage = StartMessageOne("Fade", i, (reliable ? USERMSG_RELIABLE : 0));

		if (userMessage == null)
			continue;

		if (pb)
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
	}
}

stock bool ScreenFade(int client, int duration = 4, int hold_time = 4, int flag = FFADE_IN, int colors[4] = {255, 255, 255, 255}, bool reliable = true)
{
	Handle userMessage = StartMessageOne("Fade", client, (reliable ? USERMSG_RELIABLE : 0));

	if (userMessage == null)
		return false;

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

stock bool ScreenShakeAll(int command = SHAKE_START, float amplitude = 50.0, float frequency = 150.0, float duration = 3.0, float distance = 0.0, float origin[3] = NULL_VECTOR)
{
	if (amplitude <= 0.0)
		return false;
		
	if (command == SHAKE_STOP)
		amplitude = 0.0;
	
	bool pb = GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf;
	
	Handle userMessage; float vecOrigin[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;
		
		GetClientAbsOrigin(i, vecOrigin);
			
		if (distance > 0.0 && GetVectorDistance(origin, vecOrigin) > distance)
			continue;
		
		userMessage = StartMessageOne("Shake", i);

		if (pb)
		{
			PbSetInt(userMessage, "command", command);
			PbSetFloat(userMessage, "local_amplitude", amplitude);
			PbSetFloat(userMessage, "frequency", frequency);
			PbSetFloat(userMessage, "duration", duration);
		}
		else
		{
			BfWriteByte(userMessage, command);		// Shake Command
			BfWriteFloat(userMessage, amplitude);	// shake magnitude/amplitude
			BfWriteFloat(userMessage, frequency);	// shake noise frequency
			BfWriteFloat(userMessage, duration);	// shake lasts this long
		}

		EndMessage();
	}
	
	return true;
}

stock bool ScreenShake(int client, int command = SHAKE_START, float amplitude = 50.0, float frequency = 150.0, float duration = 3.0)
{
	if (amplitude <= 0.0)
		return false;
		
	if (command == SHAKE_STOP)
		amplitude = 0.0;

	Handle userMessage = StartMessageOne("Shake", client);

	if (userMessage == null)
		return false;

	if (GetFeatureStatus(FeatureType_Native, "GetUserMessageType") == FeatureStatus_Available && GetUserMessageType() == UM_Protobuf)
	{
		PbSetInt(userMessage, "command", command);
		PbSetFloat(userMessage, "local_amplitude", amplitude);
		PbSetFloat(userMessage, "frequency", frequency);
		PbSetFloat(userMessage, "duration", duration);
	}
	else
	{
		BfWriteByte(userMessage, command);		// Shake Command
		BfWriteFloat(userMessage, amplitude);	// shake magnitude/amplitude
		BfWriteFloat(userMessage, frequency);	// shake noise frequency
		BfWriteFloat(userMessage, duration);	// shake lasts this long
	}

	EndMessage();
	return true;
}

#define DIR_FORWARD			(1<<0)
#define DIR_BACKWARD		(1<<1)
#define DIR_LEFT			(1<<2)
#define DIR_RIGHT			(1<<3)
#define DIR_UP				(1<<4)
#define DIR_DOWN			(1<<5)

//25.0 = ideal z_offset for TF2.
stock void KnockbackClient(int client, float scale = 50.0, int dir = DIR_BACKWARD, float z_offset = 25.0)
{
	float vecAngles[3];
	GetClientEyeAngles(client, vecAngles);
	
	float pResults[3];
	if ((dir & DIR_FORWARD) == DIR_FORWARD || (dir & DIR_BACKWARD) == DIR_BACKWARD)
		GetAngleVectors(vecAngles, pResults, NULL_VECTOR, NULL_VECTOR);
	else if ((dir & DIR_LEFT) == DIR_LEFT || (dir & DIR_RIGHT) == DIR_RIGHT)
		GetAngleVectors(vecAngles, NULL_VECTOR, pResults, NULL_VECTOR);
	if ((dir & DIR_UP) == DIR_UP || (dir & DIR_DOWN) == DIR_DOWN)
		GetAngleVectors(vecAngles, NULL_VECTOR, NULL_VECTOR, pResults);
	
	ScaleVector(pResults, scale);
	
	if ((dir & DIR_FORWARD) != DIR_FORWARD && (dir & DIR_BACKWARD) != DIR_BACKWARD || (dir & DIR_RIGHT) != DIR_RIGHT && (dir & DIR_LEFT) != DIR_LEFT)
		NegateVector(pResults);
	
	float vecOrigin[3];
	if (z_offset > 0.0)
	{
		GetClientAbsOrigin(client, vecOrigin);
		vecOrigin[2] += z_offset;
	}

	TeleportEntity(client, (z_offset > 0.0 ? vecOrigin : NULL_VECTOR), NULL_VECTOR, pResults);
}

stock void BlinkClient(int client, float distance = 35.0)
{
	float vecOrigin[3];
	GetClientAbsOrigin(client, vecOrigin);

	float vecPosition[3];
	GetClientCrosshairOrigin(client, vecPosition, true, distance);
	
	TeleportEntity(client, vecPosition, NULL_VECTOR, NULL_VECTOR);
	
	if (IsPlayerStuck(client))
		TeleportEntity(client, vecOrigin, NULL_VECTOR, NULL_VECTOR);
}

stock void AnglesToVelocity(const float pAngles[3], float pScale, float pResults[3])
{
	GetAngleVectors(pAngles, pResults, NULL_VECTOR, NULL_VECTOR);
	ScaleVector(pResults, pScale);
}

stock void TeleportTo(int client, int target)
{
	float vecOrigin[3];
	GetClientAbsOrigin(target, vecOrigin);
	
	float vecAngles[3];
	GetClientAbsAngles(target, vecAngles);
	
	TeleportEntity(client, vecOrigin, vecAngles, NULL_VECTOR);
}

stock void strtolower(const char[] input, char[] output, int size)
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

stock void strtoupper(const char[] input, char[] output, int size)
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

stock bool isstrnum(const char[] buffer)
{
	int x; int dotsFound; int numbersFound;

	if (buffer[x] == '+' || buffer[x] == '-')
		x++;

	while (buffer[x] != '\0')
	{

		if (IsCharNumeric(buffer[x]))
			numbersFound++;
		else if (buffer[x] == '.') {
			dotsFound++;

			if (dotsFound > 1)
				return false;
		}
		else
			return false;

		x++;
	}

	return numbersFound > 0;
}

stock void ShowOverlay(int client, const char[] overlay, float duration = 0.0)
{
	if (client == 0 || client > MaxClients)
		return;

	int iFlags = GetCommandFlags("r_screenoverlay");
	SetCommandFlags("r_screenoverlay", iFlags & ~FCVAR_CHEAT);
	ClientCommand(client, "r_screenoverlay \"%s\"", overlay);
	SetCommandFlags("r_screenoverlay", iFlags);

	if (duration > 0.0)
		CreateTimer(duration, __Timer_ResetOverlay, GetClientUserId(client), TIMER_FLAG_NO_MAPCHANGE);
}

public Action __Timer_ResetOverlay(Handle timer, any data)
{
	ShowOverlay(GetClientOfUserId(data), "0", 0.0);
}

stock void ClearOverlay(int client)
{
	if (client == 0 || client > MaxClients)
		return;

	int iFlags = GetCommandFlags("r_screenoverlay");
	SetCommandFlags("r_screenoverlay", iFlags & ~FCVAR_CHEAT);
	ClientCommand(client, "r_screenoverlay \"0\"");
	SetCommandFlags("r_screenoverlay", iFlags);
}

stock float GetVotePercent(int votes, int totalVotes)
{
	return FloatDiv(float(votes), float(totalVotes));
}

/* Found from the MOTDGD plugin. Though, I did reformat it for the new SourceMod syntax. */
stock void EncodeURL(const char[] sString, char[] sResult, int iLen)
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
		else if((c < '0' && c != '-' && c != '.') || (c < 'A' && c > '9') || (c > 'Z' && c < 'a' && c != '_') || (c > 'z'))
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
	if (client == 0 || client > MaxClients)
		return false;

	if (GetClientAuthId(client, AuthId_Steam2, buffer, size))
	{
		if (GetEngineVersion() == Engine_CSGO)
			ReplaceString(buffer, size, "STEAM_0", "STEAM_1");

		return true;
	}

	return false;
}

stock bool PushPlayerFromPoint(int client, float point[3], float magnitude = 50.0, float radius = 0.0)
{
	if (magnitude <= 0.0)
		return false;

	float vecOrigin[3];
	GetClientAbsOrigin(client, vecOrigin);

	if (radius > 0.0 && GetVectorDistance(point, vecOrigin) > radius)
		return false;

	float vector[3];
	MakeVectorFromPoints(point, vecOrigin, vector);

	NormalizeVector(vector, vector);
	ScaleVector(vector, magnitude);

	if (GetEntityFlags(client) & FL_ONGROUND && vector[2] < 251.0)
		vector[2] = 251.0;

	TeleportEntity(client, NULL_VECTOR, NULL_VECTOR, vector);
	return true;
}

stock bool PushPlayersFromPoint(float point[3], float magnitude = 50.0, float radius = 0.0, int team = 0, int attacker = 0)
{
	if (magnitude <= 0.0)
		return false;

	float vecOrigin[3]; float vector[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || (team > 0 && team != GetClientTeam(i)) || (attacker > 0 && i == attacker))
			continue;

		GetClientAbsOrigin(i, vecOrigin);

		if (radius > 0.0 && GetVectorDistance(point, vecOrigin) > radius)
			continue;

		MakeVectorFromPoints(point, vecOrigin, vector);

		NormalizeVector(vector, vector);
		ScaleVector(vector, magnitude);

		if (GetEntityFlags(i) & FL_ONGROUND && vector[2] < 251.0)
			vector[2] = 251.0;

		TeleportEntity(i, NULL_VECTOR, NULL_VECTOR, vector);
	}

	return true;
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
		AcceptEntityInput(client, "ClearContext");
}

stock void SpeakResponseConceptDelayed(int client, const char[] concept, float delayed = 0.0, const char[] context = "", const char[] class = "")
{
	if (delayed < 0.0)
		delayed = 0.0;
	
	DataPack hPack;
	CreateDataTimer(delayed, __Timer_DelayClientConcept, hPack, TIMER_FLAG_NO_MAPCHANGE);
	hPack.WriteCell(GetClientUserId(client));
	hPack.WriteString(concept);
	hPack.WriteString(context);
	hPack.WriteString(class);
}

public Action __Timer_DelayClientConcept(Handle timer, DataPack data)
{
	data.Reset();
	int client = GetClientOfUserId(data.ReadCell());

	char sConcept[256];
	data.ReadString(sConcept, sizeof(sConcept));

	char sContext[64];
	data.ReadString(sContext, sizeof(sContext));

	char sClass[64];
	data.ReadString(sClass, sizeof(sClass));

	if (client > 0 && IsClientInGame(client) && IsPlayerAlive(client))
		SpeakResponseConcept(client, sConcept, sContext, sClass);
}

stock void SpeakResponseConceptAll(const char[] concept, const char[] context = "", const char[] class = "")
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && IsPlayerAlive(i))
			SpeakResponseConcept(i, concept, context, class);
	}
}

stock void SpeakResponseConceptAllDelayed(const char[] concept, float delayed = 0.0, const char[] context = "", const char[] class = "")
{
	if (delayed < 0.0)
		delayed = 0.0;
	
	DataPack hPack;
	CreateDataTimer(delayed, __Timer_DelayAllConcept, hPack, TIMER_FLAG_NO_MAPCHANGE);
	hPack.WriteString(concept);
	hPack.WriteString(context);
	hPack.WriteString(class);
}

public Action __Timer_DelayAllConcept(Handle timer, DataPack data)
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

stock bool GetGroundCoordinates(float start[3], float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
{
	float vecLook[3] = {90.0, 0.0, 0.0};
	Handle trace = TR_TraceRayFilterEx(start, vecLook, MASK_SOLID_BRUSHONLY, RayType_Infinite, ___TraceEntityFilter_NoPlayers);

	if (TR_DidHit(trace))
	{
		TR_GetEndPosition(buffer, trace);
		delete trace;
		
		buffer[0] += offset[0]; buffer[1] += offset[1]; buffer[2] += offset[2];
		return (distance > 0.0 && start[2] - buffer[2] > distance);
	}

	delete trace;
	return false;
}

stock bool GetCeilingCoordinates(float start[3], float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
{
	float vecLook[3] = {-90.0, 0.0, 0.0};
	Handle trace = TR_TraceRayFilterEx(start, vecLook, MASK_SOLID_BRUSHONLY, RayType_Infinite, ___TraceEntityFilter_NoPlayers);

	if (TR_DidHit(trace))
	{
		TR_GetEndPosition(buffer, trace);
		delete trace;
		
		buffer[0] += offset[0]; buffer[1] += offset[1]; buffer[2] += offset[2];
		return (distance > 0.0 && start[2] - buffer[2] > distance);
	}

	delete trace;
	return false;
}

stock bool GetEntGroundCoordinates(int entity, float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
{
	float vecOrigin[3];
	GetEntPropVector(entity, Prop_Data, "m_vecOrigin", vecOrigin);

	float vecLook[3] = {90.0, 0.0, 0.0};
	Handle trace = TR_TraceRayFilterEx(vecOrigin, vecLook, MASK_SOLID_BRUSHONLY, RayType_Infinite, ___TraceEntityFilter_NoPlayers);

	if (TR_DidHit(trace))
	{
		TR_GetEndPosition(buffer, trace);
		delete trace;
		
		buffer[0] += offset[0]; buffer[1] += offset[1]; buffer[2] += offset[2];
		return (distance > 0.0 && vecOrigin[2] - buffer[2] > distance);
	}

	delete trace;
	return false;
}

stock bool GetEntCeilingCoordinates(int entity, float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
{
	float vecOrigin[3];
	GetEntPropVector(entity, Prop_Data, "m_vecOrigin", vecOrigin);

	float vecLook[3] = {-90.0, 0.0, 0.0};
	Handle trace = TR_TraceRayFilterEx(vecOrigin, vecLook, MASK_SOLID_BRUSHONLY, RayType_Infinite, ___TraceEntityFilter_NoPlayers);

	if (TR_DidHit(trace))
	{
		TR_GetEndPosition(buffer, trace);
		delete trace;
		
		buffer[0] += offset[0]; buffer[1] += offset[1]; buffer[2] += offset[2];
		return (distance > 0.0 && vecOrigin[2] - buffer[2] > distance);
	}

	delete trace;
	return false;
}

public bool ___TraceEntityFilter_NoPlayers(int entity, int contentsMask, any data)
{
	return entity > MaxClients;
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
				return true;
		}
	}

	return false;
}

//With help from Arthurdead.
stock void VectorAddRotatedOffset(const float angle[3], float buffer[3], const float offset[3])
{
    float vecForward[3]; float vecLeft[3]; float vecUp[3];
    GetAngleVectors(angle, vecForward, vecLeft, vecUp);

    ScaleVector(vecForward, offset[0]);
    ScaleVector(vecLeft, offset[1]);
    ScaleVector(vecUp, offset[2]);

    float vecAdd[3];
    AddVectors(vecAdd, vecForward, vecAdd);
    AddVectors(vecAdd, vecLeft, vecAdd);
    AddVectors(vecAdd, vecUp, vecAdd);

    AddVectors(buffer, vecAdd, buffer);
}

//By Boikinov
stock void RotateYaw(float angles[3], float degree)
{
	float direction[3], normal[3];
	GetAngleVectors(angles, direction, NULL_VECTOR, normal);

	float sin = Sine(degree * 0.01745328);     // Pi/180
	float cos = Cosine(degree * 0.01745328);
	float a = normal[0] * sin;
	float b = normal[1] * sin;
	float c = normal[2] * sin;
	float x = direction[2] * b + direction[0] * cos - direction[1] * c;
	float y = direction[0] * c + direction[1] * cos - direction[2] * a;
	float z = direction[1] * a + direction[2] * cos - direction[0] * b;
	direction[0] = x; direction[1] = y; direction[2] = z;

	GetVectorAngles(direction, angles);

	float up[3];
	GetVectorVectors(direction, NULL_VECTOR, up);

	float roll = GetAngleBetweenVectors(up, normal, direction);
	angles[2] += roll;
}

//By Boikinov
stock float GetAngleBetweenVectors(const float vector1[3], const float vector2[3], const float direction[3])
{
	float direction_n[3];
	NormalizeVector(direction, direction_n);
	
	float vector1_n[3];
	NormalizeVector(vector1, vector1_n);
	
	float vector2_n[3];
	NormalizeVector(vector2, vector2_n);
	float degree = ArcCosine(GetVectorDotProduct(vector1_n, vector2_n)) * 57.29577951;   // 180/Pi
    
	float cross[3];
	GetVectorCrossProduct(vector1_n, vector2_n, cross);
	
	if (GetVectorDotProduct(cross, direction_n) < 0.0)
		degree *= -1.0;

	return degree;
}  

stock void GetMapName(char[] buffer, int size)
{
	GetCurrentMap(buffer, size);
	GetMapDisplayName(buffer, buffer, size);
}

stock bool IsCurrentMap(const char[] buffer, bool casesensitive = false)
{
	char map[64];
	GetCurrentMap(map, sizeof(map));
	GetMapDisplayName(map, map, sizeof(map));
	
	return StrEqual(buffer, map, casesensitive);
}

stock bool CreateFile(const char[] buffer)
{
	if (strlen(buffer) == 0)
		return false;

	char path[PLATFORM_MAX_PATH];
	BuildPath(Path_SM, path, sizeof(path), buffer);

	if (!FileExists(path))
	{
		File file = OpenFile(path, "w");
		delete file;
	}

	return true;
}

stock int[] GetNearestPlayers(int entity, int& count, float distance, bool self = false, bool fake_clients = true)
{
	count = 0;
	int clients[MAXPLAYERS + 1];

	float vecOrigin[3];
	GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vecOrigin);

	float vecOrigin2[3];
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || (!self && i == entity) || (!fake_clients && IsFakeClient(i)))
			continue;

		GetClientAbsOrigin(i, vecOrigin2);

		if (GetVectorDistance(vecOrigin, vecOrigin2) > distance)
			continue;

		clients[count++] = i;
	}

	return clients;
}

stock int GetNearestEntity(int entity, const char[] classname = "*")
{
	float vecStart[3];
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", vecStart);
	
	int nearest = -1;
	
	int buffer = -1; float vecEnd[3]; float cache; float distance;
	while ((buffer = FindEntityByClassname(buffer, classname)) != -1)
	{
		GetEntPropVector(buffer, Prop_Send, "m_vecOrigin", vecEnd);
		distance = GetVectorDistance(vecStart, vecEnd);
		
		if (cache == 0.0)
		{
			nearest = buffer;
			cache = distance;
			continue;
		}
		
		if (GetVectorDistance(vecStart, vecEnd) < cache)
		{
			nearest = buffer;
			cache = distance;
		}
	}
	
	return nearest;
}

stock float CalculateAccuracy(int hits, int shots)
{
	float rate = 0.0;
	
	if (shots > 0)
		rate = float(hits) / float(shots) * 100.0;
	
	return rate;
}

stock float CalculateKDR(int kills, int deaths)
{
	float rate = float(kills) / float(deaths);

	if (deaths == 0 && kills != 0)
		rate = float(kills);

	if (kills < 0)
		rate = float(0);

	return rate;
}

stock void CreatePlayerSpray(int client, float origin[3])
{
	TE_Start("Player Decal");
	TE_WriteVector("m_vecOrigin", origin);
	TE_WriteNum("m_nPlayer", client);
	TE_SendToAll();
	
	if (IsSoundPrecached("player/sprayer.wav"))
		EmitSoundToAll("player/sprayer.wav", client, SNDCHAN_AUTO, SNDLEVEL_NORMAL, SND_NOFLAGS, 0.6);
}

stock void RemovePlayerSpray(int client)
{
	TE_Start("Player Decal");
	TE_WriteVector("m_vecOrigin", view_as<float>({0.0, 0.0, 0.0}));
	TE_WriteNum("m_nEntity", 0);
	TE_WriteNum("m_nPlayer", client);
	TE_SendToAll();
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

    if (!half)
        maxs[2] += origin[2];
    else
        maxs[2] = mins[2];
}

stock void GetWorldMins(float[3] mins)
{
	GetEntPropVector(0, Prop_Data, "m_WorldMins", mins);
}

stock void GetWorldMaxs(float[3] maxs)
{
	GetEntPropVector(0, Prop_Data, "m_WorldMaxs", maxs);
}

stock void GetRandomPostion(float result[3], float min_height, float max_height, int max_ticks = 100)
{
	float vecWorldMins[3];
	GetWorldMins(vecWorldMins);
	vecWorldMins[2] = min_height;

	float vecWorldMaxs[3];
	GetWorldMaxs(vecWorldMaxs);
	vecWorldMaxs[2] = max_height;

	int ticks = 1;
	result[0] = GetRandomFloat(vecWorldMins[0], vecWorldMaxs[0]);
	result[1] = GetRandomFloat(vecWorldMins[1], vecWorldMaxs[1]);
	result[2] = GetRandomFloat(vecWorldMins[2], vecWorldMaxs[2]);

	while (TR_PointOutsideWorld(result) && max_ticks > ticks)
	{
		ticks++;
		result[0] = GetRandomFloat(vecWorldMins[0], vecWorldMaxs[0]);
		result[1] = GetRandomFloat(vecWorldMins[1], vecWorldMaxs[1]);
		result[2] = GetRandomFloat(vecWorldMins[2], vecWorldMaxs[2]);
	}
}

stock int GetNativeStringEx(int param, char[] buffer, int size, int& bytes)
{
	GetNativeStringLength(param, size); size++;
	return GetNativeString(param, buffer, size, bytes);
}

stock bool HasClassname(int entity, const char[] classname, bool caseSensitive = false)
{
	if (!IsValidEntity(entity))
		return false;
	
	char buffer[64];
	GetEntityClassname(entity, buffer, sizeof(buffer));
	
	return StrContains(buffer, classname, caseSensitive) != -1;
}

stock bool IsClassname(int entity, const char[] classname, bool caseSensitive = false)
{
	if (!IsValidEntity(entity))
		return false;
	
	char buffer[64];
	GetEntityClassname(entity, buffer, sizeof(buffer));
	
	return StrEqual(buffer, classname, caseSensitive);
}

stock bool HasName(int entity, const char[] name, bool caseSensitive = false)
{
	if (!IsValidEntity(entity))
		return false;
	
	char buffer[64];
	GetEntPropString(entity, Prop_Data, "m_iName", buffer, sizeof(buffer));
	
	return StrContains(buffer, name, caseSensitive) != -1;
}

stock bool IsName(int entity, const char[] name, bool caseSensitive = false)
{
	if (!IsValidEntity(entity))
		return false;
	
	char buffer[64];
	GetEntPropString(entity, Prop_Data, "m_iName", buffer, sizeof(buffer));
	
	return StrEqual(buffer, name, caseSensitive);
}

stock bool TriggerEntity(const char[] name, const char[] classname = "*")
{
	int entity = -1; char sName[256]; bool triggered;
	while ((entity = FindEntityByClassname(entity, classname)) != -1)
	{
		GetEntPropString(entity, Prop_Data, "m_iName", sName, sizeof(sName));
		
		if (StrEqual(sName, name, false))
		{
			AcceptEntityInput(entity, "Trigger");
			triggered = true;
		}
	}
	
	return triggered;
}

stock int GetEntityCountEx(const char[] classname)
{
	int count;
	int entity = -1;
	while ((entity = FindEntityByClassname(entity, classname)) != -1)
		count++;
	return count;
}

stock int GetEntityName(int entity, char[] buffer, int maxlen)
{
	return GetEntPropString(entity, Prop_Data, "m_iName", buffer, maxlen);
}

stock int SetEntityName(int entity, const char[] name)
{
	return SetEntPropString(entity, Prop_Data, "m_iName", name);
}

stock int FindEntityByName(const char[] name, const char[] classname = "*")
{
	int entity = -1; char temp[64];
	while ((entity = FindEntityByClassname(entity, classname)) != -1)
	{
		GetEntPropString(entity, Prop_Data, "m_iName", temp, sizeof(temp));
		
		if (StrEqual(temp, name, false))
			return entity;
	}
	
	return entity;
}

stock bool HasModel(int entity, const char[] model, bool caseSensitive = false)
{
	if (!IsValidEntity(entity))
		return false;
	
	char buffer[PLATFORM_MAX_PATH];
	GetEntPropString(entity, Prop_Data, "m_ModelName", buffer, sizeof(buffer));
	
	return StrContains(buffer, model, caseSensitive) != -1;
}

stock bool IsModel(int entity, const char[] model, bool caseSensitive = false)
{
	if (!IsValidEntity(entity))
		return false;
	
	char buffer[PLATFORM_MAX_PATH];
	GetEntPropString(entity, Prop_Data, "m_ModelName", buffer, sizeof(buffer));
	
	return StrEqual(buffer, model, caseSensitive);
}

stock void GetEntityModel(int entity, char[] buffer, int size)
{
	GetEntPropString(entity, Prop_Data, "m_ModelName", buffer, size);
}

stock int CreateProp(const char[] model, float origin[3], float angles[3] = {0.0, 0.0, 0.0}, int skin = 0, bool solid = true)
{
	if (strlen(model) == 0 || !IsModelPrecached(model))
		return -1;
	
	int entity = CreateEntityByName("prop_dynamic_override");
	
	if (IsValidEntity(entity))
	{
		DispatchKeyValue(entity, "model", model);
		DispatchKeyValue(entity, "solid", solid ? "6" : "0");
		DispatchKeyValueVector(entity, "origin", origin);
		DispatchKeyValueVector(entity, "angles", angles);
		
		char sSkin[16];
		IntToString(skin, sSkin, sizeof(sSkin));
		DispatchKeyValue(entity, "skin", sSkin);
		
		DispatchSpawn(entity);
	}
	
	return entity;
}

stock int AttachProp(int entity, const char[] model, const char[] attach = "", float angles[3] = {0.0, 0.0, 0.0}, int skin = 0, bool solid = true)
{
	float vecPosition[3];
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", vecPosition);

	int prop = CreateProp(model, vecPosition, angles, skin, solid);

	if (IsValidEntity(prop))
	{
		SetVariantString("!activator");
		AcceptEntityInput(prop, "SetParent", entity, prop, 0);

		if (strlen(attach) > 0)
		{
			SetVariantString(attach);
			AcceptEntityInput(prop, "SetParentAttachmentMaintainOffset", prop, prop, 0);
		}
	}

	return prop;
}

stock bool AnimateEntity(int entity, const char[] animation)
{
	if (entity == 0 || !IsValidEntity(entity) || strlen(animation) == 0)
		return false;
	
	SetVariantString(animation);
	return AcceptEntityInput(entity, "SetAnimation");
}

stock bool DeleteEntity(int entity)
{
	if (entity == 0 || !IsValidEntity(entity))
		return false;
	
	return AcceptEntityInput(entity, "Kill");
}

stock void DeleteAllEntities(const char[] classname)
{
	int entity = -1;
	while ((entity = FindEntityByClassname(entity, classname)) > MaxClients)
		AcceptEntityInput(entity, "Kill");
}

stock float GetEntitiesDistance(int entity1, int entity2)
{
	float fOrigin1[3];
	GetEntPropVector(entity1, Prop_Send, "m_vecOrigin", fOrigin1);

	float fOrigin2[3];
	GetEntPropVector(entity2, Prop_Send, "m_vecOrigin", fOrigin2);
	
	return GetVectorDistance(fOrigin1, fOrigin2);
}

stock int GetEntityParent(int entity)
{
	return GetEntPropEnt(entity, Prop_Data, "m_pParent");
}

stock int GetEntityOwner(int entity)
{
	return GetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity");
}

stock void SetEntityOwner(int entity, int value)
{
	SetEntPropEnt(entity, Prop_Data, "m_hOwnerEntity", value);
}

stock int GetEntityThrower(int entity)
{
	return GetEntPropEnt(entity, Prop_Data, "m_hThrower");
}

stock void SetEntityThrower(int entity, int value)
{
	SetEntPropEnt(entity, Prop_Data, "m_hThrower", value);
}

stock void ClearEntityParent(int entity)
{
	SetVariantString("");
	AcceptEntityInput(entity, "ClearParent");
}

stock void GetEntityOrigin(int entity, float[3] origin)
{
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", origin);
}

stock void GetEntityAbsOrigin(int entity, float[3] origin)
{
	GetEntPropVector(entity, Prop_Send, "m_vecAbsOrigin", origin);
}

stock void GetEntityAngles(int entity, float[3] angles)
{
	GetEntPropVector(entity, Prop_Send, "m_angRotation", angles);
}

stock void SetEntityAngle(int entity, float[3] angles)
{
	SetEntPropVector(entity, Prop_Send, "m_angRotation", angles);
}

stock void GetEntityAbsAngle(int entity, float[3] angles)
{
	GetEntPropVector(entity, Prop_Send, "m_angAbsRotation", angles);
}

stock void GetEntityVelocity(int entity, float[3] velocity)
{
	GetEntPropVector(entity, Prop_Data, "m_vecVelocity", velocity);
}

stock void SetEntityVelocity(int entity, float[3] velocity)
{
	SetEntPropVector(entity, Prop_Data, "m_vecVelocity", velocity);
}

stock void GetEntityAbsVelocity(int entity, float[3] velocity)
{
	GetEntPropVector(entity, Prop_Send, "m_vecAbsVelocity", velocity);
}

stock void SetEntityAbsVelocity(int entity, float[3] velocity)
{
	SetEntPropVector(entity, Prop_Send, "m_vecAbsVelocity", velocity);
}

stock void GetEntityMins(int entity, float[3] mins)
{
	GetEntPropVector(entity, Prop_Send, "m_vecMins", mins);
}

stock void GetEntityMaxs(int entity, float[3] maxs)
{
	GetEntPropVector(entity, Prop_Send, "m_vecMaxs", maxs);
}

stock bool EnableEntity(int entity)
{
	return AcceptEntityInput(entity, "Enable");
}

stock bool DisableEntity(int entity)
{
	return AcceptEntityInput(entity, "Disable");
}

stock bool IsEntityDisabled(int entity)
{
	return GetEntProp(entity, Prop_Data, "m_bDisabled", 1);
}

stock bool EnableEntityMotion(int entity)
{
	return AcceptEntityInput(entity, "EnableMotion");
}

stock bool DisableEntityMotion(int entity)
{
	return AcceptEntityInput(entity, "DisableMotion");
}

#define DAMAGE_NO 0
#define DAMAGE_EVENTS_ONLY 1 // Call damage functions, but don't modify health
#define DAMAGE_YES 2
#define DAMAGE_AIM 3

stock void SetEntityTakeDamage(int entity, int value = DAMAGE_YES)
{
	SetEntProp(entity, Prop_Data, "m_takedamage", value, 1);
}

stock int GetEntityHealth(int entity)
{
	return GetEntProp(entity, Prop_Data, "m_iHealth");
}

stock int GetEntityMaxHealth(int entity)
{
	return GetEntProp(entity, Prop_Data, "m_iMaxHealth");
}

stock float GetEntityMaxSpeed(int entity)
{
	return GetEntPropFloat(entity, Prop_Data, "m_flMaxspeed");
}

stock void SetEntityMaxSpeed(int entity, float value)
{
	SetEntPropFloat(entity, Prop_Data, "m_flMaxspeed", value);
}

stock bool IsEntityLocked(int entity)
{
	return GetEntProp(entity, Prop_Data, "m_bLocked", 1);
}

stock void SetEntityLocked(int entity, bool locked)
{
	SetEntProp(entity, Prop_Data, "m_bLocked", locked, 1);
}

stock int GetEntityModelIndex(int entity)
{
	return GetEntProp(entity, Prop_Data, "m_nModelIndex", 2);
}

stock void SetEntityModelIndex(int entity, int value)
{
	SetEntProp(entity, Prop_Data, "m_nModelIndex", value, 2);
}

stock int GetEntityWaterlevel(int entity)
{
	return GetEntProp(entity, Prop_Data, "m_nWaterLevel");
}

stock void SetEntityWaterlevel(int entity, int value)
{
	SetEntProp(entity, Prop_Data, "m_nWaterLevel", value);
}

stock bool DispatchKeyValueInt(int entity, const char[] keyName, const int value)
{
	char sValue[64];
	IntToString(value, sValue, sizeof(sValue));
	return DispatchKeyValue(entity, keyName, sValue);
}

stock bool GetEntPropBool(int entity, PropType type, const char[] prop, int size = 4, int element = 0)
{
	return view_as<bool>(GetEntProp(entity, type, prop, size, element));
}

stock void SetEntPropBool(int entity, PropType type, const char[] prop, any value, int size = 4, int element = 0)
{
	SetEntProp(entity, type, prop, value, size, element);
}

stock int GetWeaponState(int weapon)
{
	return GetEntProp(weapon, Prop_Send, "m_iWeaponState");
}

stock void SetWeaponState(int weapon, int state)
{
	SetEntProp(weapon, Prop_Send, "m_iWeaponState", state);
}

stock void ResetVector(float vec[3])
{
	vec[0] = vec[1] = vec[2] = 0.0;
}

stock bool IsVectorZero(float vec[3])
{
    return vec[0] == 0.0 && vec[1] == 0.0 && vec[2] == 0.0;
}

stock void SetEntityRenderColorEx(int entity, int color[4])
{
	SetEntityRenderColor(entity, color[0], color[1], color[2], color[3]);
}

stock RenderMode GetRenderModeByName(const char[] name)
{
	if (StrEqual(name, "normal", false) || StrEqual(name, "0"))
		return RENDER_NORMAL;
	else if (StrEqual(name, "transcolor", false) || StrEqual(name, "1"))
		return RENDER_TRANSCOLOR;
	else if (StrEqual(name, "transtexture", false) || StrEqual(name, "2"))
		return RENDER_TRANSTEXTURE;
	else if (StrEqual(name, "glow", false) || StrEqual(name, "3"))
		return RENDER_GLOW;
	else if (StrEqual(name, "transalpha", false) || StrEqual(name, "4"))
		return RENDER_TRANSALPHA;
	else if (StrEqual(name, "transadd", false) || StrEqual(name, "5"))
		return RENDER_TRANSADD;
	else if (StrEqual(name, "environmental", false) || StrEqual(name, "6"))
		return RENDER_ENVIRONMENTAL;
	else if (StrEqual(name, "transaddframeblend", false) || StrEqual(name, "7"))
		return RENDER_TRANSADDFRAMEBLEND;
	else if (StrEqual(name, "transalphaadd", false) || StrEqual(name, "8"))
		return RENDER_TRANSALPHAADD;
	else if (StrEqual(name, "worldglow", false) || StrEqual(name, "9"))
		return RENDER_WORLDGLOW;
	else if (StrEqual(name, "none", false) || StrEqual(name, "10"))
		return RENDER_NONE;
	
	return RENDER_NORMAL;
}

//List provided by: https://www.december.com/html/spec/colorrgbadec.html
//I just simply referenced it for this function.
stock int[] GetColorByName(const char[] name)
{
	int color[4]; color[3] = 255;
	
	if (StringToColor(name, color, view_as<int>({255, 255, 255, 255})))
		return color;
	
	if (StrEqual(name, "white", false))
		return color;
	
	if (StrEqual(name, "black", false))
	{
		color[0] = 0; color[1] = 0; color[2] = 0;
	}
	else if (StrEqual(name, "navy", false))
	{
		color[0] = 0; color[1] = 0; color[2] = 128;
	}
	else if (StrEqual(name, "blue", false))
	{
		color[0] = 0; color[1] = 0; color[2] = 255;
	}
	else if (StrEqual(name, "green", false))
	{
		color[0] = 0; color[1] = 128; color[2] = 0;
	}
	else if (StrEqual(name, "teal", false))
	{
		color[0] = 0; color[1] = 128; color[2] = 128;
	}
	else if (StrEqual(name, "lime", false))
	{
		color[0] = 0; color[1] = 255; color[2] = 0;
	}
	else if (StrEqual(name, "aqua", false))
	{
		color[0] = 0; color[1] = 255; color[2] = 255;
	}
	else if (StrEqual(name, "maroon", false))
	{
		color[0] = 128; color[1] = 0; color[2] = 0;
	}
	else if (StrEqual(name, "purple", false))
	{
		color[0] = 128; color[1] = 0; color[2] = 128;
	}
	else if (StrEqual(name, "olive", false))
	{
		color[0] = 128; color[1] = 128; color[2] = 0;
	}
	else if (StrEqual(name, "gray", false))
	{
		color[0] = 128; color[1] = 128; color[2] = 128;
	}
	else if (StrEqual(name, "silver", false))
	{
		color[0] = 192; color[1] = 192; color[2] = 192;
	}
	else if (StrEqual(name, "red", false))
	{
		color[0] = 255; color[1] = 0; color[2] = 0;
	}
	else if (StrEqual(name, "fuchsia", false))
	{
		color[0] = 255; color[1] = 0; color[2] = 255;
	}
	else if (StrEqual(name, "yellow", false))
	{
		color[0] = 255; color[1] = 255; color[2] = 0;
	}
	
	return color;
}

stock RenderFx GetRenderFxByName(const char[] name)
{
	if (StrEqual(name, "none", false) || StrEqual(name, "0"))
		return RENDERFX_NONE;
	else if (StrEqual(name, "puse_slow", false) || StrEqual(name, "1"))
		return RENDERFX_PULSE_SLOW;
	else if (StrEqual(name, "pulse_fast", false) || StrEqual(name, "2"))
		return RENDERFX_PULSE_FAST;
	else if (StrEqual(name, "pulse_slow_wide", false) || StrEqual(name, "3"))
		return RENDERFX_PULSE_SLOW_WIDE;
	else if (StrEqual(name, "pulse_fast_wide", false) || StrEqual(name, "4"))
		return RENDERFX_PULSE_FAST_WIDE;
	else if (StrEqual(name, "fade_slow", false) || StrEqual(name, "5"))
		return RENDERFX_FADE_SLOW;
	else if (StrEqual(name, "fade_fast", false) || StrEqual(name, "6"))
		return RENDERFX_FADE_FAST;
	else if (StrEqual(name, "solid_slow", false) || StrEqual(name, "7"))
		return RENDERFX_SOLID_SLOW;
	else if (StrEqual(name, "solid_fast", false) || StrEqual(name, "8"))
		return RENDERFX_SOLID_FAST;
	else if (StrEqual(name, "strobe_slow", false) || StrEqual(name, "9"))
		return RENDERFX_STROBE_SLOW;
	else if (StrEqual(name, "strobe_fast", false) || StrEqual(name, "10"))
		return RENDERFX_STROBE_FAST;
	else if (StrEqual(name, "strobe_faster", false) || StrEqual(name, "11"))
		return RENDERFX_STROBE_FASTER;
	else if (StrEqual(name, "flicker_slow", false) || StrEqual(name, "12"))
		return RENDERFX_FLICKER_SLOW;
	else if (StrEqual(name, "flicker_fast", false) || StrEqual(name, "13"))
		return RENDERFX_FLICKER_FAST;
	else if (StrEqual(name, "no_dissipation", false) || StrEqual(name, "14"))
		return RENDERFX_NO_DISSIPATION;
	else if (StrEqual(name, "distort", false) || StrEqual(name, "15"))
		return RENDERFX_DISTORT;
	else if (StrEqual(name, "hologram", false) || StrEqual(name, "16"))
		return RENDERFX_HOLOGRAM;
	else if (StrEqual(name, "explode", false) || StrEqual(name, "17"))
		return RENDERFX_EXPLODE;
	else if (StrEqual(name, "glowshell", false) || StrEqual(name, "18"))
		return RENDERFX_GLOWSHELL;
	else if (StrEqual(name, "clamp_min_scale", false) || StrEqual(name, "19"))
		return RENDERFX_CLAMP_MIN_SCALE;
	else if (StrEqual(name, "env_rain", false) || StrEqual(name, "20"))
		return RENDERFX_ENV_RAIN;
	else if (StrEqual(name, "env_snow", false) || StrEqual(name, "21"))
		return RENDERFX_ENV_SNOW;
	else if (StrEqual(name, "spotlight", false) || StrEqual(name, "22"))
		return RENDERFX_SPOTLIGHT;
	else if (StrEqual(name, "ragdoll", false) || StrEqual(name, "23"))
		return RENDERFX_RAGDOLL;
	else if (StrEqual(name, "pulse_fast_wider", false) || StrEqual(name, "24"))
		return RENDERFX_PULSE_FAST_WIDER;
	else if (StrEqual(name, "max", false) || StrEqual(name, "25"))
		return RENDERFX_MAX;
	
	return RENDERFX_NONE;
}

/**
*	Returns a damage bitflag based on name.
*
*	name		Name of the damagebit.
*
*	return	Damagebit.
**/
stock int GetDamageTypeByName(const char[] name)
{
	int flags = DMG_GENERIC;
	
	if (StrContains(name, "DMG_GENERIC", false) != -1)
		flags = DMG_GENERIC;
	else if (StrContains(name, "DMG_CRUSH", false) != -1)
		flags |= (flags | DMG_CRUSH);
	else if (StrContains(name, "DMG_BULLET", false) != -1)
		flags |= (flags | DMG_BULLET);
	else if (StrContains(name, "DMG_SLASH", false) != -1)
		flags |= (flags | DMG_SLASH);
	else if (StrContains(name, "DMG_BURN", false) != -1)
		flags |= (flags | DMG_BURN);
	else if (StrContains(name, "DMG_VEHICLE", false) != -1)
		flags |= (flags | DMG_VEHICLE);
	else if (StrContains(name, "DMG_FALL", false) != -1)
		flags |= (flags | DMG_FALL);
	else if (StrContains(name, "DMG_BLAST", false) != -1)
		flags |= (flags | DMG_BLAST);
	else if (StrContains(name, "DMG_CLUB", false) != -1)
		flags |= (flags | DMG_CLUB);
	else if (StrContains(name, "DMG_SHOCK", false) != -1)
		flags |= (flags | DMG_SHOCK);
	else if (StrContains(name, "DMG_SONIC", false) != -1)
		flags |= (flags | DMG_SONIC);
	else if (StrContains(name, "DMG_ENERGYBEAM", false) != -1)
		flags |= (flags | DMG_ENERGYBEAM);
	else if (StrContains(name, "DMG_PREVENT_PHYSICS_FORCE", false) != -1)
		flags |= (flags | DMG_PREVENT_PHYSICS_FORCE);
	else if (StrContains(name, "DMG_NEVERGIB", false) != -1)
		flags |= (flags | DMG_NEVERGIB);
	else if (StrContains(name, "DMG_ALWAYSGIB", false) != -1)
		flags |= (flags | DMG_ALWAYSGIB);
	else if (StrContains(name, "DMG_DROWN", false) != -1)
		flags |= (flags | DMG_DROWN);
	else if (StrContains(name, "DMG_PARALYZE", false) != -1)
		flags |= (flags | DMG_PARALYZE);
	else if (StrContains(name, "DMG_NERVEGAS", false) != -1)
		flags |= (flags | DMG_NERVEGAS);
	else if (StrContains(name, "DMG_POISON", false) != -1)
		flags |= (flags | DMG_POISON);
	else if (StrContains(name, "DMG_RADIATION", false) != -1)
		flags |= (flags | DMG_RADIATION);
	else if (StrContains(name, "DMG_DROWNRECOVER", false) != -1)
		flags |= (flags | DMG_DROWNRECOVER);
	else if (StrContains(name, "DMG_ACID", false) != -1)
		flags |= (flags | DMG_ACID);
	else if (StrContains(name, "DMG_SLOWBURN", false) != -1)
		flags |= (flags | DMG_SLOWBURN);
	else if (StrContains(name, "DMG_REMOVENORAGDOLL", false) != -1)
		flags |= (flags | DMG_REMOVENORAGDOLL);
	else if (StrContains(name, "DMG_PHYSGUN", false) != -1)
		flags |= (flags | DMG_PHYSGUN);
	else if (StrContains(name, "DMG_PLASMA", false) != -1)
		flags |= (flags | DMG_PLASMA);
	else if (StrContains(name, "DMG_AIRBOAT", false) != -1)
		flags |= (flags | DMG_AIRBOAT);
	else if (StrContains(name, "DMG_DISSOLVE", false) != -1)
		flags |= (flags | DMG_DISSOLVE);
	else if (StrContains(name, "DMG_BLAST_SURFACE", false) != -1)
		flags |= (flags | DMG_BLAST_SURFACE);
	else if (StrContains(name, "DMG_DIRECT", false) != -1)
		flags |= (flags | DMG_DIRECT);
	else if (StrContains(name, "DMG_BUCKSHOT", false) != -1)
		flags |= (flags | DMG_BUCKSHOT);
	else if (StrContains(name, "DMG_CRIT", false) != -1)
		flags |= (flags | DMG_CRIT);
	
	return flags;
}

stock void GetDamageNameByType(int damagetype, char[] buffer, int size)
{
	if ((damagetype & DMG_GENERIC) == DMG_GENERIC)
		Format(buffer, size, "%s| DMG_GENERIC", buffer);
	
	if ((damagetype & DMG_CRUSH) == DMG_CRUSH)
		Format(buffer, size, "%s| DMG_CRUSH", buffer);
	
	if ((damagetype & DMG_BULLET) == DMG_BULLET)
		Format(buffer, size, "%s| DMG_BULLET", buffer);
	
	if ((damagetype & DMG_SLASH) == DMG_SLASH)
		Format(buffer, size, "%s| DMG_SLASH", buffer);
	
	if ((damagetype & DMG_BURN) == DMG_BURN)
		Format(buffer, size, "%s| DMG_BURN", buffer);
	
	if ((damagetype & DMG_VEHICLE) == DMG_VEHICLE)
		Format(buffer, size, "%s| DMG_VEHICLE", buffer);
	
	if ((damagetype & DMG_FALL) == DMG_FALL)
		Format(buffer, size, "%s| DMG_FALL", buffer);
	
	if ((damagetype & DMG_BLAST) == DMG_BLAST)
		Format(buffer, size, "%s| DMG_BLAST", buffer);
	
	if ((damagetype & DMG_CLUB) == DMG_CLUB)
		Format(buffer, size, "%s| DMG_CLUB", buffer);
	
	if ((damagetype & DMG_SHOCK) == DMG_SHOCK)
		Format(buffer, size, "%s| DMG_SHOCK", buffer);
	
	if ((damagetype & DMG_SONIC) == DMG_SONIC)
		Format(buffer, size, "%s| DMG_SONIC", buffer);
	
	if ((damagetype & DMG_ENERGYBEAM) == DMG_ENERGYBEAM)
		Format(buffer, size, "%s| DMG_ENERGYBEAM", buffer);
	
	if ((damagetype & DMG_PREVENT_PHYSICS_FORCE) == DMG_PREVENT_PHYSICS_FORCE)
		Format(buffer, size, "%s| DMG_PREVENT_PHYSICS_FORCE", buffer);
	
	if ((damagetype & DMG_NEVERGIB) == DMG_NEVERGIB)
		Format(buffer, size, "%s| DMG_NEVERGIB", buffer);
	
	if ((damagetype & DMG_ALWAYSGIB) == DMG_ALWAYSGIB)
		Format(buffer, size, "%s| DMG_ALWAYSGIB", buffer);
	
	if ((damagetype & DMG_DROWN) == DMG_DROWN)
		Format(buffer, size, "%s| DMG_DROWN", buffer);
	
	if ((damagetype & DMG_PARALYZE) == DMG_PARALYZE)
		Format(buffer, size, "%s| DMG_PARALYZE", buffer);
	
	if ((damagetype & DMG_NERVEGAS) == DMG_NERVEGAS)
		Format(buffer, size, "%s| DMG_NERVEGAS", buffer);
	
	if ((damagetype & DMG_POISON) == DMG_POISON)
		Format(buffer, size, "%s| DMG_POISON", buffer);
	
	if ((damagetype & DMG_RADIATION) == DMG_RADIATION)
		Format(buffer, size, "%s| DMG_RADIATION", buffer);
	
	if ((damagetype & DMG_DROWNRECOVER) == DMG_DROWNRECOVER)
		Format(buffer, size, "%s| DMG_DROWNRECOVER", buffer);
	
	if ((damagetype & DMG_ACID) == DMG_ACID)
		Format(buffer, size, "%s| DMG_ACID", buffer);
	
	if ((damagetype & DMG_SLOWBURN) == DMG_SLOWBURN)
		Format(buffer, size, "%s| DMG_SLOWBURN", buffer);
	
	if ((damagetype & DMG_REMOVENORAGDOLL) == DMG_REMOVENORAGDOLL)
		Format(buffer, size, "%s| DMG_REMOVENORAGDOLL", buffer);
	
	if ((damagetype & DMG_PHYSGUN) == DMG_PHYSGUN)
		Format(buffer, size, "%s| DMG_PHYSGUN", buffer);
	
	if ((damagetype & DMG_PLASMA) == DMG_PLASMA)
		Format(buffer, size, "%s| DMG_PLASMA", buffer);
	
	if ((damagetype & DMG_AIRBOAT) == DMG_AIRBOAT)
		Format(buffer, size, "%s| DMG_AIRBOAT", buffer);
	
	if ((damagetype & DMG_DISSOLVE) == DMG_DISSOLVE)
		Format(buffer, size, "%s| DMG_DISSOLVE", buffer);
	
	if ((damagetype & DMG_BLAST_SURFACE) == DMG_BLAST_SURFACE)
		Format(buffer, size, "%s| DMG_BLAST_SURFACE", buffer);
	
	if ((damagetype & DMG_DIRECT) == DMG_DIRECT)
		Format(buffer, size, "%s| DMG_DIRECT", buffer);
	
	if ((damagetype & DMG_BUCKSHOT) == DMG_BUCKSHOT)
		Format(buffer, size, "%s| DMG_BUCKSHOT", buffer);
	
	if ((damagetype & DMG_CRIT) == DMG_CRIT)
		Format(buffer, size, "%s| DMG_CRIT", buffer);
}

/**
 * Wraps ProcessTargetString() and sends no error messages unlike FindTarget.
 *
 * @param client	Client who issued command
 * @param target	Client's target argument
 * @param nobots	Optional. Set to true if bots should NOT be targetted
 * @param immunity	Optional. Set to false to ignore target immunity.
 * @return			Index of target client, or -1 on error.
 */
stock int FindTargetEx(int client, const char[] target, bool nobots = false, bool immunity = true)
{
	int flags = COMMAND_FILTER_NO_MULTI;
	
	if (nobots)
		flags |= COMMAND_FILTER_NO_BOTS;
	
	if (!immunity)
		flags |= COMMAND_FILTER_NO_IMMUNITY;
	
	char target_name[MAX_TARGET_LENGTH];
	int target_list[1];
	bool tn_is_ml;
	
	if (ProcessTargetString(target, client, target_list, 1, flags, target_name, sizeof(target_name), tn_is_ml) > 0)
		return target_list[0];
	
	return -1;
}

/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
//SECTIONS
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
//COOKIES

stock void SetClientCookieInt(int client, Handle cookie, int value)
{
	char sValue[5192];
	IntToString(value, sValue, sizeof(sValue));
	SetClientCookie(client, cookie, sValue);
}

stock void SetClientCookieFloat(int client, Handle cookie, float value)
{
	char sValue[5192];
	FloatToString(value, sValue, sizeof(sValue));
	SetClientCookie(client, cookie, sValue);
}

stock void SetClientCookieBool(int client, Handle cookie, bool value)
{
	char sValue[5192];
	IntToString(value, sValue, sizeof(sValue));
	SetClientCookie(client, cookie, sValue);
}

/*---------------------------------------------------------*/
//ENTITY FLAGS

stock bool IsOnGround(int entity)
{
	int flags = GetEntityFlags(entity);
	return ((flags & FL_ONGROUND) == FL_ONGROUND && (flags & FL_INWATER) != FL_INWATER);
}

stock bool IsInAir(int entity)
{
	int flags = GetEntityFlags(entity);
	return ((flags & FL_ONGROUND) != FL_ONGROUND && (flags & FL_INWATER) != FL_INWATER);
}

stock bool IsInWater(int entity)
{
	return ((GetEntityFlags(entity) & FL_INWATER) != FL_INWATER);
}

/*---------------------------------------------------------*/
//COLLISIONS

//Solid Type
enum SolidTypes
{
    SOLID_TYPE_NONE,   	 	// no solid model
    SOLID_TYPE_BSP,    		// a BSP tree
    SOLID_TYPE_BBOX,    	// an AABB
    SOLID_TYPE_OBB,    		// an OBB (not implemented yet)
    SOLID_TYPE_OBB_YAW,    	// an OBB, constrained so that it can only yaw
    SOLID_TYPE_CUSTOM,    	// Always call into the entity for tests
    SOLID_TYPE_VPHYSICS,    // solid vphysics object, get vcollide from the model and collide with that
    SOLID_TYPE_LAST,
}

/**
 * Gets an entity's solid type.
 *
 * @param entity	Entity index.
 * @return			SolidTypes value.
 * @error			Invalid entity index, or lack of mod compliance.
 */
stock SolidTypes GetEntitySolidType(int entity)
{
	return view_as<SolidTypes>(GetEntProp(entity, Prop_Data, "m_nSolidType"));
}

/**
 * Sets an entity's solid type.
 *
 * @param entity	Entity index.
 * @param group		SolidTypes value.
 * @error			Invalid entity index, or lack of mod compliance.
 */
stock void SetEntitySolidType(int entity, SolidTypes type)
{
	SetEntProp(entity, Prop_Data, "m_nSolidType", type);
}

//Solid Flags
enum SolidFlags
{
    FSOLID_CUSTOMRAYTEST = 0x0001,    		// Ignore solid type + always call into the entity for ray tests
    FSOLID_CUSTOMBOXTEST = 0x0002,    		// Ignore solid type + always call into the entity for swept box tests
    FSOLID_NOT_SOLID = 0x0004,    			// Are we currently not solid?
    FSOLID_TRIGGER = 0x0008,    			// This is something may be collideable but fires touch functions
											// even when it's not collideable (when the FSOLID_NOT_SOLID flag is set)
    FSOLID_NOT_STANDABLE = 0x0010,    		// You can't stand on this
    FSOLID_VOLUME_CONTENTS = 0x0020,    	// Contains volumetric contents (like water)
    FSOLID_FORCE_WORLD_ALIGNED = 0x0040,	// Forces the collision rep to be world-aligned even if it's SOLID_BSP or SOLID_VPHYSICS
    FSOLID_USE_TRIGGER_BOUNDS = 0x0080,		// Uses a special trigger bounds separate from the normal OBB
    FSOLID_ROOT_PARENT_ALIGNED = 0x0100,	// Collisions are defined in root parent's local coordinate space
    FSOLID_MAX_BITS    = 9
}

/**
 * Gets an entity's collision group.
 *
 * @param entity	Entity index.
 * @return			SolidFlags value.
 * @error			Invalid entity index, or lack of mod compliance.
 */
stock SolidFlags GetEntitySolidFlags(int entity)
{
	return view_as<SolidFlags>(GetEntProp(entity, Prop_Data, "m_usSolidFlags"));
}

/**
 * Sets an entity's collision group.
 *
 * @param entity	Entity index.
 * @param group		SolidFlags value.
 * @error			Invalid entity index, or lack of mod compliance.
 */
stock void SetEntitySolidFlags(int entity, SolidFlags flags)
{
	SetEntProp(entity, Prop_Data, "m_usSolidFlags", flags);
}

//Collision Group
enum CollisionGroup
{
    COLLISION_GROUP_NONE,
    COLLISION_GROUP_DEBRIS,            	// Collides with nothing but world and static stuff
    COLLISION_GROUP_DEBRIS_TRIGGER, 	// Same as debris, but hits triggers
    COLLISION_GROUP_INTERACTIVE_DEBRIS,	// Collides with everything except other interactive debris or debris
    COLLISION_GROUP_INTERACTIVE,    	// Collides with everything except interactive debris or debris
    COLLISION_GROUP_PLAYER,
    COLLISION_GROUP_BREAKABLE_GLASS,
    COLLISION_GROUP_VEHICLE,
    COLLISION_GROUP_PLAYER_MOVEMENT,  	// For HL2, same as Collision_Group_Player
    COLLISION_GROUP_NPC,            	// Generic NPC group
    COLLISION_GROUP_IN_VEHICLE,        	// for any entity inside a vehicle
    COLLISION_GROUP_WEAPON,            	// for any weapons that need collision detection
    COLLISION_GROUP_VEHICLE_CLIP,    	// vehicle clip brush to restrict vehicle movement
    COLLISION_GROUP_PROJECTILE,        	// Projectiles!
    COLLISION_GROUP_DOOR_BLOCKER,    	// Blocks entities not permitted to get near moving doors
    COLLISION_GROUP_PASSABLE_DOOR,    	// Doors that the player shouldn't collide with
    COLLISION_GROUP_DISSOLVING,        	// Things that are dissolving are in this group
    COLLISION_GROUP_PUSHAWAY,        	// Nonsolid on client and server, pushaway in player code
    COLLISION_GROUP_NPC_ACTOR,        	// Used so NPCs in scripts ignore the player.
}

/**
 * Gets an entity's collision group.
 *
 * @param entity	Entity index.
 * @return			CollisionGroup value.
 * @error			Invalid entity index, or lack of mod compliance.
 */
stock CollisionGroup GetEntityCollisionGroup(int entity)
{
	return view_as<CollisionGroup>(GetEntProp(entity, Prop_Data, "m_CollisionGroup"));
}

/**
 * Sets an entity's collision group.
 *
 * @param entity	Entity index.
 * @param group		CollisionGroup value.
 * @error			Invalid entity index, or lack of mod compliance.
 */
stock void SetEntityCollisionGroup(int entity, CollisionGroup group)
{
	SetEntProp(entity, Prop_Data, "m_CollisionGroup", group);
}

/*---------------------------------------------------------*/
//COMMANDS

stock void GetCommandName(char[] buffer, int size)
{
	GetCmdArg(0, buffer, size);
}

stock int GetCmdArgInt(int argnum)
{
	char sBuffer[64];
	GetCmdArg(argnum, sBuffer, sizeof(sBuffer));
	return StringToInt(sBuffer);
}

stock float GetCmdArgFloat(int argnum)
{
	char sBuffer[64];
	GetCmdArg(argnum, sBuffer, sizeof(sBuffer));
	return StringToFloat(sBuffer);
}

stock bool GetCmdArgBool(int argnum)
{
	char sBuffer[64];
	GetCmdArg(argnum, sBuffer, sizeof(sBuffer));
	return view_as<bool>(StringToInt(sBuffer));
}

stock int GetCmdArgTarget(int client, int argnum, bool nobots = false, bool immunity = true)
{
	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(argnum, sTarget, sizeof(sTarget));
	return FindTarget(client, sTarget, nobots, immunity);
}

stock int GetCmdArgTargetEx(int client, int argnum, bool nobots = false, bool immunity = true)
{
	char sTarget[MAX_TARGET_LENGTH];
	GetCmdArg(argnum, sTarget, sizeof(sTarget));
	return FindTargetEx(client, sTarget, nobots, immunity);
}

/*---------------------------------------------------------*/
//DATAPACKS

stock void WritePackVector(DataPack pack, float[3] vector)
{
	pack.WriteFloat(vector[0]);
	pack.WriteFloat(vector[1]);
	pack.WriteFloat(vector[2]);
}

stock void ReadPackVector(DataPack pack, float vector[3])
{
	vector[0] = pack.ReadFloat();
	vector[1] = pack.ReadFloat();
	vector[2] = pack.ReadFloat();
}

/*--------------------------------------------------------->*/
//MODEL

stock bool SetModel(int entity, char model[PLATFORM_MAX_PATH], bool preload = false)
{
	if (entity <= 0)
		return false;
	
	switch (GetEngineVersion())
	{
		case Engine_TF2:
		{
			if (strlen(model) > 0 && StrContains(model, "models/") != 0)
				Format(model, sizeof(model), "models/%s", model);
			
			if (strlen(model) > 0 && !FileExists(model, true))
				return false;
			
			SetVariantString(model); //Empty string = disable custom model
			AcceptEntityInput(entity, "SetCustomModel");

			SetEntProp(entity, Prop_Send, "m_bCustomModelRotates", 1);
			SetEntProp(entity, Prop_Send, "m_bUseClassAnimations", 1);
			
			return true;
		}
		
		default:
		{
			if (strlen(model) == 0)
				return false;
			
			if (StrContains(model, "models/") != 0)
				Format(model, sizeof(model), "models/%s", model);
				
			if (!FileExists(model, true) || !IsModelPrecached(model))
				return false;
			
			SetEntityModel(entity, model);
			return true;
		}
	}

	//return false;
}

stock int PrepareModel(char model[PLATFORM_MAX_PATH], bool preload = false)
{
	if (strlen(model) == 0)
		return -1;

	if (StrContains(model, "models/") != 0)
		Format(model, sizeof(model), "models/%s", model);
	
	return PrecacheModel(model, preload);
}

/*--------------------------------------------------------->*/
//SOUNDS

stock bool EmitSoundToClientSafe(int client, char sample[PLATFORM_MAX_PATH], int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (client == 0 || !IsClientInGame(client) || IsFakeClient(client) || strlen(sample) == 0)
		return false;
	
	if (StrContains(sample, "sound/") == 0)
		strcopy(sample, sizeof(sample), sample[6]);
		
	if (IsSoundPrecached(sample))
		EmitSoundToClient(client, sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
	
	return false;
}

stock bool EmitSoundToClientSafeDelayed(int client, const char[] sample, float delayed = 0.0, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (delayed < 0.0)
		delayed = 0.0;
	
	DataPack hPack;
	CreateDataTimer(delayed, __Timer_PlayClientSound, hPack, TIMER_FLAG_NO_MAPCHANGE);
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

public Action __Timer_PlayClientSound(Handle timer, DataPack data)
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

stock bool EmitSoundToAllSafe(char sample[PLATFORM_MAX_PATH], int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (strlen(sample) == 0)
		return false;
	
	if (StrContains(sample, "sound/") == 0)
		strcopy(sample, sizeof(sample), sample[6]);
		
	if (IsSoundPrecached(sample))
		EmitSoundToAll(sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
	
	return false;
}

stock bool EmitSoundToAllSafeDelayed(const char[] sample, float delayed = 0.0, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (delayed < 0.0)
		delayed = 0.0;
	
	DataPack hPack;
	CreateDataTimer(delayed, __Timer_PlayAllSound, hPack, TIMER_FLAG_NO_MAPCHANGE);
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

public Action __Timer_PlayAllSound(Handle timer, DataPack data)
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
		return false;

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (GetEngineVersion() == Engine_CSGO)
		Format(sSound, sizeof(sSound), "*%s", sSound);

	if (IsSoundPrecached(sSound))
	{
		LogError("Error playing ambient sound, not precached: %s", sSound);
		return false;
	}
	
	EmitAmbientSound(sSound, origin, entity, level, flags, vol, pitch, delay);
	return true;
}

stock bool StopSoundSafe(int entity, int channel, const char[] sample)
{
	if (entity <= 0 || entity > 4096 || strlen(sample) == 0)
		return false;

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (GetEngineVersion() == Engine_CSGO)
		Format(sSound, sizeof(sSound), "*%s", sSound);

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

stock bool PrepareSound(const char[] sample, bool preload = false, bool download = true)
{
	if (strlen(sample) == 0)
		return false;

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);
	
	if (download)
	{
		char sDownload[PLATFORM_MAX_PATH];
		strcopy(sDownload, sizeof(sDownload), sample);
		
		if (StrContains(sDownload, "sound/") != 0)
			Format(sDownload, sizeof(sDownload), "sound/");
		
		AddFileToDownloadsTable(sDownload);
	}
	
	if (StrContains(sSound, "sound/") == 0)
		strcopy(sSound, sizeof(sSound), sample[6]);
		
	if (GetEngineVersion() == Engine_CSGO)
	{
		if (StrContains(sSound, "*/") != 0)
			Format(sSound, sizeof(sSound), "*/%s", sSound);
		
		AddToStringTable(FindStringTable("soundprecache"), sSound);
	}
	else
		PrecacheSound(sSound, preload);

	return true;
}

/*--------------------------------------------------------->*/
//DRAW BOXES (SMLIB)


stock void Effect_DrawBeamBoxToClient(int client, const float bottomCorner[3], const float upperCorner[3], int modelIndex, int haloIndex, int startFrame = 0, int frameRate = 30, float life = 5.0, float width = 5.0, float endWidth = 5.0, int fadeLength = 2, float amplitude = 1.0, const color[4] =  { 255, 0, 0, 255 }, int speed = 0)
{
	int clients[1]; clients[0] = client;
	Effect_DrawBeamBox(clients, 1, bottomCorner, upperCorner, modelIndex, haloIndex, startFrame, frameRate, life, width, endWidth, fadeLength, amplitude, color, speed);
}

stock void Effect_DrawBeamBoxToAll(const float bottomCorner[3], const float upperCorner[3], int modelIndex, int haloIndex, int startFrame = 0, int frameRate = 30, float life = 5.0, float width = 5.0, float endWidth = 5.0, int fadeLength = 2, float amplitude = 1.0, const int color[4] = { 255, 255, 255, 255 }, int speed = 0)
{
	int[] clients = new int[MaxClients];
	int numClients;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i) && !IsFakeClient(i))
			clients[numClients++] = i;
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

/*--------------------------------------------------------->*/
//Pelipoika Stocks (He sometimes randomly sends me these)


stock bool GetClientAbsPosition(int client, float origin[3])
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client))
		return false;

	GetClientAbsOrigin(client, origin);

	float target_velocity[3];
	GetEntPropVector(client, Prop_Data, "m_vecAbsVelocity", target_velocity);

	float correct = GetClientLatency(client, NetFlow_Outgoing);	// * 2

	int lerpTicks = RoundToFloor(0.5 + GetEntPropFloat(client, Prop_Send, "m_fLerpTime") / GetTickInterval());

	correct += (GetTickInterval() * lerpTicks);

	float sv_unlag = FindConVar("sv_maxunlag").FloatValue;
	correct = (correct > sv_unlag ? sv_unlag : (correct < 0.0 ? 0.0 : correct));

	int targettick = GetEntProp(client, Prop_Send, "m_nSimulationTick") - lerpTicks;	//m_nTickBase

	float deltaTime = correct - (GetTickInterval() * (GetGameTickCount() - targettick));

	if (FloatAbs(deltaTime) > 0.2)
		targettick = GetGameTickCount() - (RoundToFloor(0.5 + correct / GetTickInterval()));

	ScaleVector(target_velocity, correct);
	SubtractVectors(origin, target_velocity, origin);

	return true;
}

stock void LookAtPosition(int client, float flGoal[3], float flAimSpeed = 0.05)
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
	angle -= RoundToFloor(angle / 360.0) * 360.0;
	
	if (angle > 180)
		angle -= 360;
	
	if (angle < -180)
		angle += 360;
	
	return angle;
}

/* MAH BOI POIKA */
stock void EquipWeaponSlot(int client, int slot)
{
	int iWeapon = GetPlayerWeaponSlot(client, slot);
	
	if (IsValidEntity(iWeapon))
	{
		char class[64];
		GetEntityClassname(iWeapon, class, sizeof(class));
		FakeClientCommand(client, "use %s", class);
	}
}

stock void EquipWeapon(int client, int weapon)
{
	char class[64];
	GetEntityClassname(weapon, class, sizeof(class));
	FakeClientCommand(client, "use %s", class);
}
/* */

/*--------------------------------------------------------->*/
//CONVARS

stock bool SetConVarFlag(ConVar convar, bool add, int flag)
{
	int flags = convar.Flags;
	
	if (add)
		flags |= flag;
	else
		flags &= ~flag;
	
	convar.Flags = flags;
}

stock bool SetConVarFlagByName(const char[] name, bool add, int flag)
{
	ConVar convar = FindConVar(name);
	
	int flags = convar.Flags;
	
	if (add)
		flags |= flag;
	else
		flags &= ~flag;
	
	convar.Flags = flags;
}

stock int[] GetConVarColor(ConVar convar)
{
	int colors[4] = {255, 255, 255, 255};

	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
		return colors;

	char sPart[4][6];
	int iReturned = ExplodeString(sBuffer, StrContains(sBuffer, ", ") != -1 ? ", " : " ", sPart, 4, 6);

	for (int i = 0; i < iReturned; i++)
		colors[i] = StringToInt(sPart[i]);

	return colors;
}

stock float[] GetConVarVector(ConVar convar)
{
	float vectors[3] = {0.0, 0.0, 0.0};

	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
		return vectors;

	char sPart[3][12];
	int iReturned = ExplodeString(sBuffer, StrContains(sBuffer, ", ") != -1 ? ", " : " ", sPart, 3, 12);

	for (int i = 0; i < iReturned; i++)
		vectors[i] = StringToFloat(sPart[i]);

	return vectors;
}

stock float[] GetConVar2DVector(ConVar convar)
{
	float vectors[2] = {0.0, 0.0};

	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
		return vectors;

	char sPart[2][12];
	int iReturned = ExplodeString(sBuffer, StrContains(sBuffer, ", ") != -1 ? ", " : " ", sPart, 2, 12);

	for (int i = 0; i < iReturned; i++)
		vectors[i] = StringToFloat(sPart[i]);

	return vectors;
}

stock int GetConVarRandom(ConVar convar, const char[] splitter = "-")
{
	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
		return -1;

	char sPart[2][12];
	int iReturned = ExplodeString(sBuffer, splitter, sPart, 2, 12);
	
	int clamps[2];
	for (int i = 0; i < iReturned; i++)
		clamps[i] = StringToInt(sPart[i]);
		
	if (clamps[0] > clamps[1])
		clamps[0] = clamps[1];

	return GetRandomInt(clamps[0], clamps[1]);
}

stock float GetConVarRandomFloat(ConVar convar, const char[] splitter = "-")
{
	char sBuffer[128];
	convar.GetString(sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
		return -1.0;

	char sPart[2][12];
	int iReturned = ExplodeString(sBuffer, splitter, sPart, 2, 12);
	
	float clamps[2];
	for (int i = 0; i < iReturned; i++)
		clamps[i] = StringToFloat(sPart[i]);
		
	if (clamps[0] > clamps[1])
		clamps[0] = clamps[1];

	return GetRandomFloat(clamps[0], clamps[1]);
}

stock void CreateHudConVars(const char[] prefix, ConVar& position = null, ConVar& holdtime = null, ConVar& colors = null, ConVar& effect = null, ConVar& fxtime = null, ConVar& fades = null)
{
	char sName[512];

	FormatEx(sName, sizeof(sName), "%sposition", prefix);
	position = CreateConVar(sName, "-1.0, -1.0", "Position of this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%sholdtime", prefix);
	holdtime = CreateConVar(sName, "1.0", "Holdtime for this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%scolor", prefix);
	colors = CreateConVar(sName, "255, 255, 255, 255", "Color of this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%seffect", prefix);
	effect = CreateConVar(sName, "0", "Effect for this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%sfxtime", prefix);
	fxtime = CreateConVar(sName, "0.0", "Fxtime for this hud element.", FCVAR_NOTIFY);

	FormatEx(sName, sizeof(sName), "%sfades", prefix);
	fades = CreateConVar(sName, "-1.0, -1.0", "Fxtime for this hud element.", FCVAR_NOTIFY);
}

stock void SetHudTextParamsViaConVars(ConVar& position, ConVar& holdtime, ConVar& color, ConVar& effect, ConVar& fxtime, ConVar& fades)
{
	float vecPosition[2]; vecPosition = GetConVar2DVector(position);
	int iColor[4]; iColor = GetConVarColor(color);
	float fFades[2]; fFades = GetConVar2DVector(fades);

	SetHudTextParams(vecPosition[0], vecPosition[1], holdtime.FloatValue, iColor[0], iColor[1], iColor[2], iColor[3], effect.IntValue, fxtime.FloatValue, fFades[0], fFades[1]);
}

stock void AddConVarFlag(ConVar convar, int flag)
{
	int flags = convar.Flags;
	flags |= flag;
	convar.Flags = flags;
}

stock void StripConVarFlag(ConVar convar, int flag)
{
	int flags = convar.Flags;
	flags &= ~flag;
	convar.Flags = flags;
}

stock void CheatCommand(int client, char[] command, char[] arguments = "")
{
	int flags = GetCommandFlags(command);
	SetCommandFlags(command, flags & ~FCVAR_CHEAT);
	FakeClientCommand(client, "%s %s", command, arguments);
	SetCommandFlags(command, flags);
}

stock bool SetModelViaConVar(int entity, ConVar &convar, bool preload = false)
{
	if (convar == null)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return SetModel(entity, sBuffer, preload);
}

stock int PrepareModelConVar(ConVar &convar, bool preload = false)
{
	if (convar == null)
		return -1;

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return PrepareModel(sBuffer, preload);
}

stock bool EmitSoundToClientViaConVar(int client, ConVar convar, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (convar == null)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return EmitSoundToClientSafe(client, sBuffer, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}

stock bool EmitSoundToAllViaConVar(ConVar convar, int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (convar == null)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return EmitSoundToAllSafe(sBuffer, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}

stock bool EmitAmbientSoundViaConVar(ConVar convar, bool preload = false, const float origin[3], int entity = SOUND_FROM_WORLD, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float vol = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, float delay = 0.0)
{
	if (convar == null)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return EmitAmbientSoundSafe(sBuffer, origin, entity, level, flags, vol, pitch, delay);
}

stock bool PrepareSoundConVar(ConVar convar, bool preload = false, bool download = true)
{
	if (convar == null)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	convar.GetString(sBuffer, sizeof(sBuffer));

	return PrepareSound(sBuffer, preload, download);
}

/*--------------------------------------------------------->*/
//KEYVALUES

stock int KvGetInt(KeyValues kv, const char[] key, int defaultvalue = 0)
{
	return kv.GetNum(key, defaultvalue);
}

stock bool KvGetBool(KeyValues kv, const char[] key, bool defaultvalue = false)
{
	return view_as<bool>(kv.GetNum(key, view_as<int>(defaultvalue)));
}

stock bool KvGet2DVector(KeyValues kv, const char[] key, float buffer[2], const float defaultvector[2] = {0.0, 0.0})
{
	char sBuffer[512];
	kv.GetString(key, sBuffer, sizeof(sBuffer));

	if (strlen(sBuffer) == 0)
	{
		buffer[0] = defaultvector[0]; buffer[1] = defaultvector[1];
		return false;
	}

	char sPart[2][32];
	int iReturned = ExplodeString(sBuffer, StrContains(sBuffer, ",") != -1 ? ", " : " ", sPart, 2, 32);

	if (iReturned != 2)
	{
		buffer[0] = defaultvector[0]; buffer[1] = defaultvector[1];
		return false;
	}

	buffer[0] = StringToFloat(sPart[0]); buffer[1] = StringToFloat(sPart[1]);
	return true;
}

/*--------------------------------------------------------->*/
//MENUS

stock bool AddMenuItemInt(Menu menu, int info, const char[] name, int style = ITEMDRAW_DEFAULT)
{
	char sInfo[1024];
	IntToString(info, sInfo, sizeof(sInfo));
	return menu.AddItem(sInfo, name, style);
}

stock bool GetMenuItemInt(Menu menu, int position, int& info, int& style = 0, char[] dispBuf = "", int dispBufLen = 0)
{
	char sInfo[1024];
	bool found = menu.GetItem(position, sInfo, sizeof(sInfo), style, dispBuf, dispBufLen);
	info = StringToInt(sInfo);
	return found;
}

stock bool AddMenuItemFloat(Menu menu, float info, const char[] name, int style = ITEMDRAW_DEFAULT)
{
	char sInfo[1024];
	FloatToString(info, sInfo, sizeof(sInfo));
	return menu.AddItem(sInfo, name, style);
}

stock bool GetMenuItemFloat(Menu menu, int position, float& info, int& style = 0, char[] dispBuf = "", int dispBufLen = 0)
{
	char sInfo[1024];
	bool found = menu.GetItem(position, sInfo, sizeof(sInfo), style, dispBuf, dispBufLen);
	info = StringToFloat(sInfo);
	return found;
}

stock bool AddMenuItemColor(Menu menu, int color[4], const char[] name, int style = ITEMDRAW_DEFAULT)
{
	char sInfo[1024];
	FormatEx(sInfo, sizeof(sInfo), "%i %i %i %i", color[0], color[1], color[2], color[3]);
	return menu.AddItem(sInfo, name, style);
}

stock bool GetMenuItemColor(Menu menu, int position, int color[4], int& style = 0, char[] dispBuf = "", int dispBufLen = 0)
{
	char sInfo[1024];
	bool found = menu.GetItem(position, sInfo, sizeof(sInfo), style, dispBuf, dispBufLen);
	
	char sPart[4][64];
	ExplodeString(sInfo, " ", sPart, 4, 64);
	
	for (int i = 0; i < 4; i++)
		color[i] = StringToInt(sPart[i]);
	
	return found;
}

stock bool AddMenuItemVector(Menu menu, float vector[3], const char[] name, int style = ITEMDRAW_DEFAULT)
{
	char sInfo[1024];
	FormatEx(sInfo, sizeof(sInfo), "%f %f %f", vector[0], vector[1], vector[2]);
	return menu.AddItem(sInfo, name, style);
}

stock bool GetMenuItemVector(Menu menu, int position, float vector[3], int& style = 0, char[] dispBuf = "", int dispBufLen = 0)
{
	char sInfo[1024];
	bool found = menu.GetItem(position, sInfo, sizeof(sInfo), style, dispBuf, dispBufLen);
	
	char sPart[3][64];
	ExplodeString(sInfo, " ", sPart, 3, 64);
	
	for (int i = 0; i < 3; i++)
		vector[i] = StringToFloat(sPart[i]);
	
	return found;
}

stock bool AddMenuItem2DVector(Menu menu, float vector[2], const char[] name, int style = ITEMDRAW_DEFAULT)
{
	char sInfo[1024];
	FormatEx(sInfo, sizeof(sInfo), "%f %f", vector[0], vector[1]);
	return menu.AddItem(sInfo, name, style);
}

stock bool GetMenuItem2DVector(Menu menu, int position, float vector[2], int& style = 0, char[] dispBuf = "", int dispBufLen = 0)
{
	char sInfo[1024];
	bool found = menu.GetItem(position, sInfo, sizeof(sInfo), style, dispBuf, dispBufLen);
	
	char sPart[2][64];
	ExplodeString(sInfo, " ", sPart, 2, 64);
	
	for (int i = 0; i < 2; i++)
		vector[i] = StringToFloat(sPart[i]);
	
	return found;
}

/**
*	Saves an string value into a menu for lookup later.
*
*	menu	Menu handle.
*	id		Name of the menu item by info buffer to save under.
*	value	Value to store.
*
*	return	True if saved successfully, false otherwise.
**/
stock bool PushMenuString(Menu menu, const char[] id, const char[] value)
{
	if (menu == null || strlen(id) == 0)
		return false;
	
	return menu.AddItem(id, value, ITEMDRAW_IGNORE);
}

/**
*	Saves an integer value into a menu for lookup later.
*
*	menu	Menu handle.
*	id		Name of the menu item by info buffer to save under.
*	value	Value to store.
*
*	return	True if saved successfully, false otherwise.
**/
stock bool PushMenuInt(Menu menu, const char[] id, int value)
{
	if (menu == null || strlen(id) == 0)
		return false;
	
	char sBuffer[128];
	IntToString(value, sBuffer, sizeof(sBuffer));
	return menu.AddItem(id, sBuffer, ITEMDRAW_IGNORE);
}

/**
*	Saves an float value into a menu for lookup later.
*
*	menu	Menu handle.
*	id		Name of the menu item by info buffer to save under.
*	value	Value to store.
*
*	return	True if saved successfully, false otherwise.
**/
stock bool PushMenuFloat(Menu menu, const char[] id, float value)
{
	if (menu == null || strlen(id) == 0)
		return false;
	
	char sBuffer[128];
	FloatToString(value, sBuffer, sizeof(sBuffer));
	return menu.AddItem(id, sBuffer, ITEMDRAW_IGNORE);
}

/**
*	Saves an boolean value into a menu for lookup later.
*
*	menu	Menu handle.
*	id		Name of the menu item by info buffer to save under.
*	value	Value to store.
*
*	return	True if saved successfully, false otherwise.
**/
stock bool PushMenuBool(Menu menu, const char[] id, bool value)
{
	if (menu == null || strlen(id) == 0)
		return false;
	
	char sBuffer[128];
	IntToString(view_as<int>(value), sBuffer, sizeof(sBuffer));
	return menu.AddItem(id, sBuffer, ITEMDRAW_IGNORE);
}

/**
*	Gets a saved string value from a menu by name.
*
*	menu	Menu handle.
*	id		Name of the menu item by info buffer to search for.
*	buffer	Buffer to store the value in.
*	size	Size of the buffer.
*
*	return	True if found, false otherwise.
**/
stock bool GetMenuString(Menu menu, const char[] id, char[] buffer, int size)
{
	if (menu == null || strlen(id) == 0)
		return false;
	
	char info[128]; char data[8192];
	for (int i = 0; i < menu.ItemCount; i++)
	{
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(info, id))
		{
			strcopy(buffer, size, data);
			return true;
		}
	}
	
	return false;
}

/**
*	Gets a saved integer value from a menu by name.
*
*	menu			Menu handle.
*	id				Name of the menu item by info buffer to search for.
*	defaultvalue	Default value to use if not found.
*
*	return	Either the found value or the default value.
**/
stock int GetMenuInt(Menu menu, const char[] id, int defaultvalue = 0)
{
	if (menu == null || strlen(id) == 0)
		return defaultvalue;
	
	char info[128]; char data[128];
	for (int i = 0; i < menu.ItemCount; i++)
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(info, id))
			return StringToInt(data);
	
	return defaultvalue;
}

/**
*	Gets a saved float value from a menu by name.
*
*	menu			Menu handle.
*	id				Name of the menu item by info buffer to search for.
*	defaultvalue	Default value to use if not found.
*
*	return	Either the found value or the default value.
**/
stock float GetMenuFloat(Menu menu, const char[] id, float defaultvalue = 0.0)
{
	if (menu == null || strlen(id) == 0)
		return defaultvalue;
		
	char info[128]; char data[128];
	for (int i = 0; i < menu.ItemCount; i++)
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(info, id))
			return StringToFloat(data);
	
	return defaultvalue;
}

/**
*	Gets a saved boolean value from a menu by name.
*
*	menu			Menu handle.
*	id				Name of the menu item by info buffer to search for.
*	defaultvalue	Default value to use if not found.
*
*	return	Either the found value or the default value.
**/
stock bool GetMenuBool(Menu menu, const char[] id, bool defaultvalue = false)
{
	if (menu == null || strlen(id) == 0)
		return defaultvalue;
	
	char info[128]; char data[128];
	for (int i = 0; i < menu.ItemCount; i++)
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(info, id))
			return view_as<bool>(StringToInt(data));
	
	return defaultvalue;
}

/**
*	Copies all menu items of one menu handle into another menu handle.
*
*	menu	Menu handle.
*	destination	Destination menu handle.
*	id	Optional info buffer to search for.
*
*	return	True if menu has been copied successfully, false otherwise.
**/
stock bool CopyMenuAny(Menu source, Menu destination, const char[] id)
{
	if (source == null || destination == null)
		return false;
	
	char info[1024]; char data[1024];
	for (int i = 0; i < source.ItemCount; i++)
	{
		if (source.GetItem(i, info, sizeof(info), _, data, sizeof(data)))
		{
			if (strlen(id) > 0 && !StrEqual(info, id))
				continue;
			
			destination.AddItem(id, data, ITEMDRAW_IGNORE);
		}
	}
	
	return true;
}

/**
*	Adds a certain item to the menu with formatting parameters.
*
*	menu	Menu handle.
*	info	Info of the menu item.
*	style	Style of the item.
*	format	Format buffer.
*	any		Parameters for the format buffer.
*
*	return	True if menu item added successfully, false otherwise.
**/
stock bool AddMenuItemFormat(Menu menu, const char[] info, int style = ITEMDRAW_DEFAULT, const char[] format, any ...)
{
	if (menu == null)
		return false;
	
	char sBuffer[256];
	VFormat(sBuffer, sizeof(sBuffer), format, 5);

	return menu.AddItem(info, sBuffer, style);
}

/**
*	Removes a certain item from a menu by info buffer.
*
*	menu	Menu handle.
*	info		Info to search for.
*
*	return	True if found and removed, false otherwise.
**/
stock bool RemoveMenuItemByInfo(Menu menu, const char[] info)
{
	if (menu == null || strlen(info) == 0)
		return defaultvalue;
	
	char info[1024];
	for (int i = 0; i < menu.ItemCount; i++)
		if (menu.GetItem(i, info, sizeof(info)) && StrEqual(info, info, false))
			return menu.RemoveItem(i);
	
	return false;
}

/**
*	Removes a certain item from a menu by display name.
*
*	menu	Menu handle.
*	name		Name to search for.
*
*	return	True if found and removed, false otherwise.
**/
stock bool RemoveMenuItemByName(Menu menu, const char[] name)
{
	if (menu == null || strlen(name) == 0)
		return defaultvalue;
	
	char info[1024]; char data[1024];
	for (int i = 0; i < menu.ItemCount; i++)
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(data, name, false))
			return menu.RemoveItem(i);
	
	return false;
}

stock bool ChangeItemText(Menu menu, int position, const char[] display)
{
	if  (menu == null || strlen(display) == 0)
		return false;
	
	char info[1024]; int style;
	menu.GetItem(position, info, sizeof(info), style);
	
	if (!menu.RemoveItem(position) || !menu.InsertItem(position, info, display, style))
		return false;
	
	return true;
}

//This stocks broken, read below.
stock bool ChangeItemTextByName(Menu menu, const char[] name, const char[] display)
{
	if  (menu == null || strlen(name) == 0 || strlen(display) == 0)
		return false;
	
	int position; char info[1024]; int style; char data[1024];
	for (int i = 0; i < menu.ItemCount; i++)
	{
		if (menu.GetItem(i, info, sizeof(info), style, data, sizeof(data)) && StrEqual(data, name, false))
		{
			position = i;
			break;
		}
	}
	
	if (!menu.RemoveItem(position))
		return false;
	
	//Returns false, does not work.
	//if (!menu.InsertItem(position, info, display, style))
	//	return false;
	
	return true;
}

/*--------------------------------------------------------->*/
//Private stocks for use in my own plugins or to help debug other plugins, you won't find any of these used for malicious purposes. (good luck if you do look around)

stock void PrintToDrixevel(const char[] format, any ...)
{
	char sBuffer[255];
	VFormat(sBuffer, sizeof(sBuffer), format, 2);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || GetSteamAccountID(i) != 76528750)
			continue;

		PrintToChat(i, "[DRIXEVEL] %s", sBuffer);
		break;
	}
}

stock void DrixConsole(const char[] format, any ...)
{
	char sBuffer[255];
	VFormat(sBuffer, sizeof(sBuffer), format, 2);

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || GetSteamAccountID(i) != 76528750)
			continue;

		PrintToConsole(i, "[DRIXEVEL] %s", sBuffer);
		break;
	}
}

stock int GetDrixevel()
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || GetSteamAccountID(i) != 76528750)
			continue;

		return i;
	}

	return -1;
}

stock bool IsDrixevel(int client)
{
	if (client == 0 || client > MaxClients)
		return false;
	
	return GetSteamAccountID(client) == 76528750;
}

/*--------------------------------------------------------->*/
// Confirmation Menu
// Adds functionality to allow for confirmations to be made with callbacks easily.
// Loosely based on: https://forums.alliedmods.net/showthread.php?t=306954

enum ConfirmationResponses
{
	Confirm_Yes,			//Client said yes.
	Confirm_No,				//Client said no.
	Confirm_Disconnected,	//Client disconnected with the question active.
	Confirm_Interrupted,	//Client either couldn't receive the question was active or was interrupted with another menu.
	Confirm_Timeout,		//Client didn't answer the question in time.
}

typeset Callback_Confirmation
{
	function void (int client, ConfirmationResponses response, Handle data);
	function void (int client, ConfirmationResponses response, any data);
	function void (int client, ConfirmationResponses response);
}

static Callback_Confirmation g_ConfirmationCall[MAXPLAYERS + 1];
static ReplySource g_ConfirmReplySource[MAXPLAYERS + 1];

stock bool SendConfirmationMenu(int client, Callback_Confirmation callback, char[] title = "", int time = MENU_TIME_FOREVER, any data = 0)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || IsFakeClient(client))
		return false;
	
	g_ConfirmationCall[client] = callback;
	g_ConfirmReplySource[client] = GetCmdReplySource();
	
	Menu menu = new Menu(___MenuHandler_SendConfirmation, MenuAction_Select|MenuAction_Cancel|MenuAction_End);
	menu.SetTitle(strlen(title) > 0 ? title : "Are you sure you want to do this?");
	
	//menu.AddItem("", "---", ITEMDRAW_DISABLED);
	menu.AddItem("yes", "Yes");
	menu.AddItem("no", "No");
	
	char sBuffer[256];
	IntToString(data, sBuffer, sizeof(sBuffer));
	menu.AddItem("data", sBuffer, ITEMDRAW_IGNORE);
	
	menu.Display(client, time);
	return true;
}

public int ___MenuHandler_SendConfirmation(Menu menu, MenuAction action, int param1, int param2)
{
	any data; char info[128]; char datastring[128];
	for (int i = 0; i < menu.ItemCount; i++)
	{
		if (menu.GetItem(i, info, sizeof(info), _, datastring, sizeof(datastring)) && StrEqual(info, "data"))
		{
			data = StringToInt(datastring);
			break;
		}
	}
	
	switch (action)
	{
		case MenuAction_Select:
		{
			ReplySource reply = SetCmdReplySource(g_ConfirmReplySource[param1]);
			
			Call_StartFunction(null, g_ConfirmationCall[param1]);
			Call_PushCell(param1);
			
			char sInfo[12];
			menu.GetItem(param2, sInfo, sizeof(sInfo));
			Call_PushCell(StrEqual(sInfo, "yes") ? Confirm_Yes : Confirm_No);
			
			Call_PushCell(data);
			Call_Finish();
			
			SetCmdReplySource(reply);
		}
		case MenuAction_Cancel:
		{
			switch (param2)
			{
				case MenuCancel_Disconnected:
				{
					ReplySource reply = SetCmdReplySource(g_ConfirmReplySource[param1]);
					
					Call_StartFunction(null, g_ConfirmationCall[param1]);
					Call_PushCell(param1);
					Call_PushCell(Confirm_Disconnected);
					Call_PushCell(data);
					Call_Finish();
					
					SetCmdReplySource(reply);
				}
				case MenuCancel_Interrupted, MenuCancel_NoDisplay:
				{
					ReplySource reply = SetCmdReplySource(g_ConfirmReplySource[param1]);
					
					Call_StartFunction(null, g_ConfirmationCall[param1]);
					Call_PushCell(param1);
					Call_PushCell(Confirm_Interrupted);
					Call_PushCell(data);
					Call_Finish();
					
					SetCmdReplySource(reply);
				}
				case MenuCancel_Exit:
				{
					ReplySource reply = SetCmdReplySource(g_ConfirmReplySource[param1]);
					
					Call_StartFunction(null, g_ConfirmationCall[param1]);
					Call_PushCell(param1);
					Call_PushCell(Confirm_No);
					Call_PushCell(data);
					Call_Finish();
					
					SetCmdReplySource(reply);
				}
				case MenuCancel_Timeout:
				{
					ReplySource reply = SetCmdReplySource(g_ConfirmReplySource[param1]);
					
					Call_StartFunction(null, g_ConfirmationCall[param1]);
					Call_PushCell(param1);
					Call_PushCell(Confirm_Timeout);
					Call_PushCell(data);
					Call_Finish();
					
					SetCmdReplySource(reply);
				}
			}
		}
		case MenuAction_End:
			delete menu;
	}
}

/*--------------------------------------------------------->*/
//Easily pass strings through data parameters.

stock DataPack AnyString(const char[] format, any ...)
{
	if (strlen(format) < 1)
		return null;
	
	char buffer[5192];
	VFormat(buffer, sizeof(buffer), format, 2);
	
	DataPack pack = new DataPack();
	pack.WriteString(buffer);
	
	return pack;
}

stock bool ReadAnyString(DataPack pack, char[] buffer, int size)
{
	if (pack == null)
		return false;
	
	pack.Reset();
	pack.ReadString(buffer, size);
	delete pack;
	
	return true;
}

/*--------------------------------------------------------->*/
//Entity methodmaps.

methodmap Entity
{
	public Entity(const char[] classname)
	{
		return view_as<Entity>(CreateEntityByName(classname));
	}
	
	property int index 
	{ 
		public get()
		{
			return view_as<int>(this);
		} 
	}
	
	public bool Valid()
	{
		return IsValidEntity(this.index);
	}
	
	public bool SendInput(const char[] input, int activator = -1, int caller = -1, int outputid = 0)
	{
		return AcceptEntityInput(this.index, input, activator, caller, outputid);
	}
	
	public void Teleport(float origin[3], float angles[3], float velocity[3])
	{
		TeleportEntity(this.index, origin, angles, velocity);
	}
	
	//Dispatches
	public bool Dispatch(const char[] keyName, const char[] value)
	{
		return DispatchKeyValue(this.index, keyName, value);
	}
	
	public bool DispatchFloat(const char[] keyName, const float value)
	{
		return DispatchKeyValueFloat(this.index, keyName, value);
	}
	
	public bool DispatchVector(const char[] keyName, const float value[3])
	{
		return DispatchKeyValueVector(this.index, keyName, value);
	}
	
	public bool Spawn()
	{
		return DispatchSpawn(this.index);
	}
	
	//EntProp
	public bool SetProp(PropType type, const char[] prop, any value, int size = 4, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return false;
		
		SetEntProp(this.index, type, prop, value, size, element);
		return true;
	}
	
	public int GetProp(PropType type, const char[] prop, int size = 4, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return 0;
		
		return GetEntProp(this.index, type, prop, size, element);
	}
	
	//EntPropEnt
	public bool SetPropEnt(PropType type, const char[] prop, any value, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return false;
		
		SetEntPropEnt(this.index, type, prop, value, element);
		return true;
	}
	
	public int GetPropEnt(PropType type, const char[] prop, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return 0;
		
		return GetEntPropEnt(this.index, type, prop, element);
	}
	
	//EntPropFloat
	public bool SetPropFloat(PropType type, const char[] prop, float value, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return false;
		
		SetEntPropFloat(this.index, type, prop, value, element);
		return true;
	}
	
	public float GetPropFloat(PropType type, const char[] prop, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return 0.0;
		
		return GetEntPropFloat(this.index, type, prop, element);
	}
	
	//EntPropString
	public bool SetPropString(PropType type, const char[] prop, const char[] buffer, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return false;
		
		SetEntPropString(this.index, type, prop, buffer, element);
		return true;
	}
	
	public int GetPropString(PropType type, const char[] prop, char[] buffer, int maxlen, int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return 0;
		
		return GetEntPropString(this.index, type, prop, buffer, maxlen, element);
	}
	
	//EntPropVector
	public bool SetPropVector(PropType type, const char[] prop, const float vec[3], int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return false;
		
		SetEntPropVector(this.index, type, prop, vec, element);
		return true;
	}
	
	public bool GetPropVector(PropType type, const char[] prop, float vec[3], int element = 0)
	{
		if (!HasEntProp(this.index, type, prop))
			return false;
		
		GetEntPropVector(this.index, type, prop, vec, element);
		return true;
	}
	
	//Misc
	public bool HasProp(PropType type, const char[] prop)
	{
		return HasEntProp(this.index, type, prop);
	}
	
	public int GetSize(PropType type, const char[] prop)
	{
		return GetEntPropArraySize(this.index, type, prop);
	}
	
	//Variants
	//This section isn't as needed but it's still nice to have.
	public void VariantBool(bool val)
	{
		SetVariantBool(val);
	}
	
	public void VariantColor(const int color[4])
	{
		SetVariantColor(color);
	}
	
	public void VariantEntity(int entity)
	{
		SetVariantEntity(entity);
	}
	
	public void VariantFloat(float val)
	{
		SetVariantFloat(val);
	}
	
	public void VariantInt(int val)
	{
		SetVariantInt(val);
	}	
	
	public void VariantPosVector3D(const float vec[3])
	{
		SetVariantPosVector3D(vec);
	}	
	
	public void VariantString(const char[] str)
	{
		SetVariantString(str);
	}	
	
	public void VariantVector3D(const float vec[3])
	{
		SetVariantVector3D(vec);
	}
}

methodmap Hud < Handle
{
	public Hud()
	{
		return view_as<Hud>(CreateHudSynchronizer());
	}
	
	property Handle index 
	{ 
		public get()
		{
			return view_as<Handle>(this);
		} 
	}
	
	public void Clear(int client)
	{
		ClearSyncHud(client, this.index);
	}
	
	public void ClearAll()
	{
		for (int i = 1; i <= MaxClients; i++)
			if (IsClientInGame(i) && !IsFakeClient(i))
				ClearSyncHud(i, this.index);
	}
	
	public void SetParams(float x = -1.0, float y = -1.0, float holdTime = 2.0, int r = 255, int g = 255, int b = 255, int a = 255, int effect = 0, float fxTime = 6.0, float fadeIn = 0.1, float fadeOut = 0.2)
	{
		SetHudTextParams(x, y, holdTime, r, g, b, a, effect, fxTime, fadeIn, fadeOut);
	}
	
	public void SetParamsEx(float x = -1.0, float y = -1.0, float holdTime = 2.0, int color1[4] = {255, 255, 255, 255}, int color2[4] = {255, 255, 255, 255}, int effect = 0, float fxTime = 6.0, float fadeIn = 0.1, float fadeOut = 0.2)
	{
		SetHudTextParamsEx(x, y, holdTime, color1, color2, effect, fxTime, fadeIn, fadeOut);
	}
	
	public void Send(int client, const char[] format, any ...)
	{
		int size = strlen(format) + 255;
		char[] sBuffer = new char[size];
		VFormat(sBuffer, size, format, 4);
		ShowSyncHudText(client, this.index, sBuffer);
	}
	
	public void SendToAll(const char[] format, any ...)
	{
		int size = strlen(format) + 255;
		char[] sBuffer = new char[size];
		VFormat(sBuffer, size, format, 3);
		
		for (int i = 1; i <= MaxClients; i++)
			if (IsClientInGame(i) && !IsFakeClient(i))
				ShowSyncHudText(i, this.index, sBuffer);
	}
}

/*--------------------------------------------------------->*/
//This is the end of this THICCCCCC include file.
/*--------------------------------------------------------->*/