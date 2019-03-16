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
**/

//Because I'm too stuid at remembering how to do this properly.
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
#tryinclude <tf2items>
#define REQUIRE_EXTENSIONS

#undef  REQUIRE_PLUGIN
#tryinclude <tf2attributes>
#tryinclude <tf2idb>
#define REQUIRE_PLUGIN

#define IS_CONSOLE 0
#define IS_SERVER 0

#define INVALID_INDEX -1
#define INVALID_ENT_INDEX -1
#define INVALID_ARRAY_INDEX -1

#define MAX_ENTITY_LIMIT 4096 + 1
#define MAX_QUERY_LENGTH 8192
#define MAX_BUTTONS 25
#define MAX_IP_LENGTH 64
#define MAX_MAP_NAME_LENGTH 64
#define MAX_FLAGS_LENGTH 21
#define MAX_STEAMID_LENGTH 64
#define MAX_ENTITY_CLASSNAME_LENGTH 32
#define MAX_QUALITY_NAME_LENGTH 32
#define MAX_PARTICLE_NAME_LENGTH 32
#define MAX_ATTRIBUTE_NAME_LENGTH 64
#define MAX_COMMAND_NAME_LENGTH 255

#define EF_BONEMERGE	(1 << 0)
#define EF_BONEMERGE_FASTCULL	(1 << 7)
#define EF_PARENT_ANIMATES	(1 << 9)

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

//Color codes for CSGO and old engines.
#define COLOR_DEFAULT "\x01"
#define COLOR_DARKRED "\x02"
#define COLOR_TEAM "\x03"
#define COLOR_PURPLE "\x03"
#define COLOR_GREEN "\x04"
#define COLOR_LIGHTGREEN "\x05"
#define COLOR_LIME "\x06"
#define COLOR_RED "\x07"
#define COLOR_GREY "\x08"
#define COLOR_YELLOW "\x09"
#define COLOR_GOLD "\x10"
#define COLOR_BLUEGREY "\x0A"
#define COLOR_BLUE "\x0B"
#define COLOR_DARKBLUE "\x0C"
#define COLOR_GREY2 "\x0D"
#define COLOR_ORCHID "\x0E"
#define COLOR_LIGHTRED "\x0F"

//Color codes for TF2 and new engines.
#define NEW_COLOR_ALICEBLUE "\x07F0F8FF"
#define NEW_COLOR_ALLIES "\x074D7942"
#define NEW_COLOR_ANCIENT "\x07EB4B4B"
#define NEW_COLOR_ANTIQUEWHITE "\x07FAEBD7"
#define NEW_COLOR_AQUA "\x0700FFFF"
#define NEW_COLOR_AQUAMARINE "\x077FFFD4"
#define NEW_COLOR_ARCANA "\x07ADE55C"
#define NEW_COLOR_AXIS "\x07FF4040"
#define NEW_COLOR_AZURE "\x07007FFF"
#define NEW_COLOR_BEIGE "\x07F5F5DC"
#define NEW_COLOR_BISQUE "\x07FFE4C4"
#define NEW_COLOR_BLACK "\x07000000"
#define NEW_COLOR_BLANCHEDALMOND "\x07FFEBCD"
#define NEW_COLOR_BLUE "\x0799CCFF"
#define NEW_COLOR_BLUEVIOLET "\x078A2BE2"
#define NEW_COLOR_BROWN "\x07A52A2A"
#define NEW_COLOR_BURLYWOOD "\x07DEB887"
#define NEW_COLOR_CADETBLUE "\x075F9EA0"
#define NEW_COLOR_CHARTREUSE "\x077FFF00"
#define NEW_COLOR_CHOCOLATE "\x07D2691E"
#define NEW_COLOR_COLLECTORS "\x07AA0000"
#define NEW_COLOR_COMMON "\x07B0C3D9"
#define NEW_COLOR_COMMUNITY "\x0770B04A"
#define NEW_COLOR_CORAL "\x07FF7F50"
#define NEW_COLOR_CORNFLOWERBLUE "\x076495ED"
#define NEW_COLOR_CORNSILK "\x07FFF8DC"
#define NEW_COLOR_CORRUPTED "\x07A32C2E"
#define NEW_COLOR_CRIMSON "\x07DC143C"
#define NEW_COLOR_CYAN "\x0700FFFF"
#define NEW_COLOR_DARKBLUE "\x0700008B"
#define NEW_COLOR_DARKCYAN "\x07008B8B"
#define NEW_COLOR_DARKGOLDENROD "\x07B8860B"
#define NEW_COLOR_DARKGRAY "\x07A9A9A9"
#define NEW_COLOR_DARKGREY "\x07A9A9A9"
#define NEW_COLOR_DARKGREEN "\x07006400"
#define NEW_COLOR_DARKKHAKI "\x07BDB76B"
#define NEW_COLOR_DARKMAGENTA "\x078B008B"
#define NEW_COLOR_DARKOLIVEGREEN "\x07556B2F"
#define NEW_COLOR_DARKORANGE "\x07FF8C00"
#define NEW_COLOR_DARKORCHID "\x079932CC"
#define NEW_COLOR_DARKRED "\x078B0000"
#define NEW_COLOR_DARKSALMON "\x07E9967A"
#define NEW_COLOR_DARKSEAGREEN "\x078FBC8F"
#define NEW_COLOR_DARKSLATEBLUE "\x07483D8B"
#define NEW_COLOR_DARKSLATEGRAY "\x072F4F4F"
#define NEW_COLOR_DARKSLATEGREY "\x072F4F4F"
#define NEW_COLOR_DARKTURQUOISE "\x0700CED1"
#define NEW_COLOR_DARKVIOLET "\x079400D3"
#define NEW_COLOR_DEEPPINK "\x07FF1493"
#define NEW_COLOR_DEEPSKYBLUE "\x0700BFFF"
#define NEW_COLOR_DIMGRAY "\x07696969"
#define NEW_COLOR_DIMGREY "\x07696969"
#define NEW_COLOR_DODGERBLUE "\x071E90FF"
#define NEW_COLOR_EXALTED "\x07CCCCCD"
#define NEW_COLOR_FIREBRICK "\x07B22222"
#define NEW_COLOR_FLORALWHITE "\x07FFFAF0"
#define NEW_COLOR_FORESTGREEN "\x07228B22"
#define NEW_COLOR_FROZEN "\x074983B3"
#define NEW_COLOR_FUCHSIA "\x07FF00FF"
#define NEW_COLOR_FULLBLUE "\x070000FF"
#define NEW_COLOR_FULLRED "\x07FF0000"
#define NEW_COLOR_GAINSBORO "\x07DCDCDC"
#define NEW_COLOR_GENUINE "\x074D7455"
#define NEW_COLOR_GHOSTWHITE "\x07F8F8FF"
#define NEW_COLOR_GOLD "\x07FFD700"
#define NEW_COLOR_GOLDENROD "\x07DAA520"
#define NEW_COLOR_GRAY "\x07CCCCCC"
#define NEW_COLOR_GREY "\x07CCCCCC"
#define NEW_COLOR_GREEN "\x073EFF3E"
#define NEW_COLOR_GREENYELLOW "\x07ADFF2F"
#define NEW_COLOR_HAUNTED "\x0738F3AB"
#define NEW_COLOR_HONEYDEW "\x07F0FFF0"
#define NEW_COLOR_HOTPINK "\x07FF69B4"
#define NEW_COLOR_IMMORTAL "\x07E4AE33"
#define NEW_COLOR_INDIANRED "\x07CD5C5C"
#define NEW_COLOR_INDIGO "\x074B0082"
#define NEW_COLOR_IVORY "\x07FFFFF0"
#define NEW_COLOR_KHAKI "\x07F0E68C"
#define NEW_COLOR_LAVENDER "\x07E6E6FA"
#define NEW_COLOR_LAVENDERBLUSH "\x07FFF0F5"
#define NEW_COLOR_LAWNGREEN "\x077CFC00"
#define NEW_COLOR_LEGENDARY "\x07D32CE6"
#define NEW_COLOR_LEMONCHIFFON "\x07FFFACD"
#define NEW_COLOR_LIGHTBLUE "\x07ADD8E6"
#define NEW_COLOR_LIGHTCORAL "\x07F08080"
#define NEW_COLOR_LIGHTCYAN "\x07E0FFFF"
#define NEW_COLOR_LIGHTGOLDENRODYELLOW "\x07FAFAD2"
#define NEW_COLOR_LIGHTGRAY "\x07D3D3D3"
#define NEW_COLOR_LIGHTGREY "\x07D3D3D3"
#define NEW_COLOR_LIGHTGREEN "\x0799FF99"
#define NEW_COLOR_LIGHTPINK "\x07FFB6C1"
#define NEW_COLOR_LIGHTSALMON "\x07FFA07A"
#define NEW_COLOR_LIGHTSEAGREEN "\x0720B2AA"
#define NEW_COLOR_LIGHTSKYBLUE "\x0787CEFA"
#define NEW_COLOR_LIGHTSLATEGRAY "\x07778899"
#define NEW_COLOR_LIGHTSLATEGREY "\x07778899"
#define NEW_COLOR_LIGHTSTEELBLUE "\x07B0C4DE"
#define NEW_COLOR_LIGHTYELLOW "\x07FFFFE0"
#define NEW_COLOR_LIME "\x0700FF00"
#define NEW_COLOR_LIMEGREEN "\x0732CD32"
#define NEW_COLOR_LINEN "\x07FAF0E6"
#define NEW_COLOR_MAGENTA "\x07FF00FF"
#define NEW_COLOR_MAROON "\x07800000"
#define NEW_COLOR_MEDIUMAQUAMARINE "\x0766CDAA"
#define NEW_COLOR_MEDIUMBLUE "\x070000CD"
#define NEW_COLOR_MEDIUMORHCID "\x07BA55D3"
#define NEW_COLOR_MEDIUMSEAGREEN "\x073CB371"
#define NEW_COLOR_MEDIUMSLATEBLUE "\x077B68EE"
#define NEW_COLOR_MEDIUMSPRINGGREEN "\x0700FA9A"
#define NEW_COLOR_MEDIUMTURQUOISE "\x0748D1CC"
#define NEW_COLOR_MEDIUMVIOLETRED "\x07C71585"
#define NEW_COLOR_MIDNIGHTBLUE "\x07191970"
#define NEW_COLOR_MINTCREAM "\x07F5FFFA"
#define NEW_COLOR_MISTYROSE "\x07FFE4E1"
#define NEW_COLOR_MOCCASIN "\x07FFE4B5"
#define NEW_COLOR_MYTHICAL "\x078847FF"
#define NEW_COLOR_NAVAJOWHITE "\x07FFDEAD"
#define NEW_COLOR_NAVY "\x07000080"
#define NEW_COLOR_NORMAL "\x07B2B2B2"
#define NEW_COLOR_OLDLACE "\x07FDF5E6"
#define NEW_COLOR_OLIVE "\x079EC34F"
#define NEW_COLOR_OLIVEDRAB "\x076B8E23"
#define NEW_COLOR_ORANGE "\x07FFA500"
#define NEW_COLOR_ORANGERED "\x07FF4500"
#define NEW_COLOR_ORCHID "\x07DA70D6"
#define NEW_COLOR_PALEGOLDENROD "\x07EEE8AA"
#define NEW_COLOR_PALEGREEN "\x0798FB98"
#define NEW_COLOR_PALETURQUOISE "\x07AFEEEE"
#define NEW_COLOR_PALEVIOLETRED "\x07D87093"
#define NEW_COLOR_PAPAYAWHIP "\x07FFEFD5"
#define NEW_COLOR_PEACHPUFF "\x07FFDAB9"
#define NEW_COLOR_PERU "\x07CD853F"
#define NEW_COLOR_PINK "\x07FFC0CB"
#define NEW_COLOR_PLUM "\x07DDA0DD"
#define NEW_COLOR_POWDERBLUE "\x07B0E0E6"
#define NEW_COLOR_PURPLE "\x07800080"
#define NEW_COLOR_RARE "\x074B69FF"
#define NEW_COLOR_RED "\x074B69FF"
#define NEW_COLOR_ROSYBROWN "\x07BC8F8F"
#define NEW_COLOR_ROYALBLUE "\x074169E1"
#define NEW_COLOR_SADDLEBROWN "\x078B4513"
#define NEW_COLOR_SALMON "\x07FA8072"
#define NEW_COLOR_SANDYBROWN "\x07F4A460"
#define NEW_COLOR_SEAGREEN "\x072E8B57"
#define NEW_COLOR_SEASHELL "\x07FFF5EE"
#define NEW_COLOR_SELFMADE "\x0770B04A"
#define NEW_COLOR_SIENNA "\x07A0522D"
#define NEW_COLOR_SILVER "\x07C0C0C0"
#define NEW_COLOR_SKYBLUE "\x0787CEEB"
#define NEW_COLOR_SLATEBLUE "\x076A5ACD"
#define NEW_COLOR_SLATEGRAY "\x07708090"
#define NEW_COLOR_SLATEGREY "\x07708090"
#define NEW_COLOR_SNOW "\x07FFFAFA"
#define NEW_COLOR_SPRINGGREEN "\x0700FF7F"
#define NEW_COLOR_STEELBLUE "\x074682B4"
#define NEW_COLOR_STRANGE "\x07CF6A32"
#define NEW_COLOR_TAN "\x07D2B48C"
#define NEW_COLOR_TEAL "\x07008080"
#define NEW_COLOR_THISTLE "\x07D8BFD8"
#define NEW_COLOR_TOMATO "\x07FF6347"
#define NEW_COLOR_TURQUOISE "\x0740E0D0"
#define NEW_COLOR_UNCOMMON "\x07B0C3D9"
#define NEW_COLOR_UNIQUE "\x07FFD700"
#define NEW_COLOR_UNUSUAL "\x078650AC"
#define NEW_COLOR_VALVE "\x07A50F79"
#define NEW_COLOR_VINTAGE "\x07476291"
#define NEW_COLOR_VIOLET "\x07EE82EE"
#define NEW_COLOR_WHEAT "\x07F5DEB3"
#define NEW_COLOR_WHITE "\x07FFFFFF"
#define NEW_COLOR_WHITESMOKE "\x07F5F5F5"
#define NEW_COLOR_YELLOW "\x07FFFF00"
#define NEW_COLOR_YELLOWGREEN "\x079ACD32"

//This is safe but it's best to use the proper checks where you can instead.
stock bool IsValidClient(int client)
{
	return client >= 1 && client <= MaxClients && IsClientInGame(client) && !IsClientSourceTV(client);
}

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

stock bool IsClientConsole(int client)
{
	return client == 0;
}

stock bool IsClientServer(int client)
{
	return client == 0;
}

stock bool SQL_FetchBool(DBResultSet results, int field, DBResult &status = DBVal_Error)
{
	return view_as<bool>(results.FetchInt(field, status));
}

stock bool StringToBool(const char[] buffer)
{
	return view_as<bool>(StringToInt(buffer));
}

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

stock int PushArrayStringFormat(ArrayList array, char[] buffer, any ...)
{
	if (array == null)
		return -1;
	
	char sBuffer[1024];
	VFormat(sBuffer, sizeof(sBuffer), buffer, 3);
	return array.PushString(sBuffer);
}

stock void ClearStack(ArrayStack stack)
{
	if (stack == null)
		return false;

	while (!stack.Empty)
		stack.Pop();
		
	return true;
}

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

stock bool GetRandomBool()
{
	return view_as<bool>(GetRandomInt(0, 1));
}

stock bool AcceptEntityInputSafe(int dest, const char[] input, int activator = -1, int caller = -1, int outputid = 0)
{
	if (!IsValidEntity(dest) || dest < 1 && StrEqual(input, "kill", false))
		return false;
	
	return AcceptEntityInput(dest, input, activator, caller, outputid);
}

stock bool AddFileToDownloadsTableEx(const char[] format, any ...)
{
	if (strlen(format) == 0)
		return false;

	char sBuffer[PLATFORM_MAX_PATH];
	VFormat(sBuffer, sizeof(sBuffer), format, 2);

	AddFileToDownloadsTable(sBuffer);
	return true;
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

stock int GetRandomCharacterString(char[] buffer, int size, int length = 32, const char[] chrs = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ01234556789")
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

stock bool GetClientCrosshairOrigin(int client, float pOrigin[3], bool filter_players = true, float distance = 35.0)
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
	return entity > GetMaxClients() || !entity;
}

public bool TraceEntityFilterNone(int entity, int contentsMask, any data)
{
	return entity != data;
}

stock bool IsTargetInSightRange(int client, int target, float angle = 90.0, float distance = 0.0, bool heightcheck = true, bool negativeangle = false)
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
	GetClientAbsOrigin(target, targetpos);
	
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
	GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", targetpos);
	
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
	float vecPosition[3];
	GetEntPropVector(entity, Prop_Send, "m_vecOrigin", vecPosition);

	int particle = CreateParticle(name, time, vecPosition, angles, offsets);

	if (IsValidEntity(particle))
	{
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

stock int CreateParticle(const char[] name, float time = 0.0, float origin[3], float angles[3] = {0.0, 0.0, 0.0}, float offsets[3] = {0.0, 0.0, 0.0})
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
		int iOffset = FindDataMainfo(client, "m_iAmmo") + (GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoType") * 4);
		SetEntData(client, iOffset, ammo, 4, true);
	}

	return true;
}

stock int GetClip(int weapon)
{
	if (weapon == 0 || weapon <= MaxClients || !IsValidEntity(weapon) || !HasEntProp(weapon, Prop_Data, "m_iClip1"))
	{
		return -1;
	}

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

stock bool KillTimerSafe(Handle &timer)
{
	if (timer != null)
	{
		KillTimer(timer);
		timer = null;
		return true;
	}

	return false;
}

stock int GetActiveWeapon(int client)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || !HasEntProp(client, Prop_Send, "m_hActiveWeapon"))
		return 0;

	return GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon");
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

	return clients[GetRandomInt(0, amount)];
}

stock void SQL_VoidQueryF(Database& database, DBPriority prio = DBPrio_Normal, const char[] format, any ...)
{
	char query[8192];
	VFormat(query, sizeof(query), format, 4);

	DataPack pack = new DataPack();
	pack.WriteString(query);

	database.Query(TQuery_Void, query, pack, prio);
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

		char sQuery[8192];
		data.ReadString(sQuery, sizeof(sQuery));

		LogError("Error executing void query: %s", error);
		LogError("Query Output: %s", sQuery);
	}

	delete data;
}

stock void SQL_TQueryF(Database& database, SQLQueryCallback callback, any data, DBPriority priority = DBPrio_Normal, const char[] format, any ...)
{
	char query[8192];
	VFormat(query, sizeof(query), format, 6);

	database.Query(callback, query, data, priority);
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

stock int GetClientActiveSlot(int client)
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

stock int GetTotalAliveCount()
{
	int amount;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;

		amount++;
	}

	return amount;
}

stock int GetTeamAliveClientCount(int team)
{
	int amount;

	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || GetClientTeam(i) != team)
			continue;

		amount++;
	}

	return amount;
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

stock float FloatDivider(float value, float multiplier)
{
	return value *= 1.0 - multiplier;
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
			case Error_SQLResults: strcopy(sBuffer, sizeof(sBuffer), "Invalid database results.");
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
		//pResults[0] = -pResults[0]; pResults[1] = -pResults[1]; pResults[2] = -pResults[2];
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

stock bool String_IsNumeric(const char[] buffer)
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

stock bool PushAllPlayersFromPoint(float point[3], float magnitude = 50.0, float radius = 0.0, int team = 0, int attacker = 0)
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

stock bool GetGroundCoordinates(int entity, float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
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

stock bool GetCeilingCoordinates(int entity, float buffer[3], float distance = 0.0, float offset[3] = {0.0, 0.0, 0.0})
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

stock int GetEntityName(int entity, char[] buffer, int maxlen)
{
	return GetEntPropString(entity, Prop_Data, "m_iName", buffer, maxlen);
}

stock bool HasEntName(int entity, const char[] buffer, bool case_sensitive = false)
{
	char sName[128];
	GetEntPropString(entity, Prop_Data, "m_iName", sName, sizeof(sName));

	return StrEqual(buffer, sName, case_sensitive);
}

stock int SetEntityName(int entity, const char[] name)
{
	return SetEntPropString(entity, Prop_Data, "m_iName", name);
}

stock int FindEntityByName(const char[] name)
{
	int entity = -1; char temp[64];
	while ((entity = FindEntityByClassname(entity, "*")) != -1)
	{
		GetEntPropString(entity, Prop_Data, "m_iName", temp, sizeof(temp));
		
		if (StrEqual(temp, name, false))
			return entity;
	}
	
	return entity;
}

stock void GetEntityModel(int entity, char[] buffer, int size)
{
	GetEntPropString(entity, Prop_Data, "m_ModelName", buffer, size);
}

stock int CreateProp(const char[] model, float origin[3], float angles[3] = {0.0, 0.0, 0.0}, int skin = 0, bool solid = true)
{
	if (strlen(model) == 0)
		return -1;
	
	if (GetEngineVersion() != Engine_CSGO && !IsModelPrecached(model))
		PrecacheModel(model);
	
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

stock int GetNativeStringEx(int param, char[] buffer, int size, int& bytes)
{
	GetNativeStringLength(param, size); size++;
	return GetNativeString(param, buffer, size, bytes);
}

stock float GetEntitiesDistance(int entity1, int entity2)
{
	float fOrigin1[3];
	GetEntPropVector(entity1, Prop_Send, "m_vecOrigin", fOrigin1);

	float fOrigin2[3];
	GetEntPropVector(entity2, Prop_Send, "m_vecOrigin", fOrigin2);
	
	//PrintToChatAll("entity1: %.2f/%.2f/%.2f - entity2: %.2f/%.2f/%.2f", fOrigin1[0], fOrigin1[1], fOrigin1[2], fOrigin2[0], fOrigin2[1], fOrigin2[2]);

	return GetVectorDistance(fOrigin1, fOrigin2);
}

stock bool DispatchKeyValueInt(int entity, const char[] keyName, const int value)
{
	char sValue[64];
	IntToString(value, sValue, sizeof(sValue));
	return DispatchKeyValue(entity, keyName, sValue);
}

stock void ZeroVector(float vec[3])
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

stock int[] GetColorByName(const char[] name)
{
	int color[4]; color[3] = 255;
	
	if (StringToColor(name, color, view_as<int>({255, 255, 255, 255})))
		return color;
	
	if (StrEqual(name, "red", false))
	{
		color[0] = 255;
	}
	else if (StrEqual(name, "green", false))
	{
		color[1] = 255;
	}
	else if (StrEqual(name, "blue", false))
	{
		color[2] = 255;
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
//END OF MISC
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
//SECTIONS
/*---------------------------------------------------------*/

/*---------------------------------------------------------*/
//COLLISIONS
/*---------------------------------------------------------*/
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
/*---------------------------------------------------------*/

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
/*---------------------------------------------------------*/
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
/*--------------------------------------------------------->*/
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

	return false;
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
/*--------------------------------------------------------->*/
stock bool EmitSoundToClientSafe(int client, char sample[PLATFORM_MAX_PATH], int entity = SOUND_FROM_PLAYER, int channel = SNDCHAN_AUTO, int level = SNDLEVEL_NORMAL, int flags = SND_NOFLAGS, float volume = SNDVOL_NORMAL, int pitch = SNDPITCH_NORMAL, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	if (client == 0 || !IsClientInGame(client) || IsFakeClient(client) || strlen(sample) == 0)
		return false;
		
	if (GetEngineVersion() != Engine_CSGO)
	{
		if (StrContains(sample, "sound/") != 0)
			Format(sample, sizeof(sample), "sound/%s", sample);
		
		AddFileToDownloadsTable(sample);
	}
	
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
		
	if (GetEngineVersion() != Engine_CSGO)
	{
		if (StrContains(sample, "sound/") != 0)
			Format(sample, sizeof(sample), "sound/%s", sample);
		
		AddFileToDownloadsTable(sample);
	}
	
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

stock bool StopSoundSafe(int entity, int channel, const char[] sample)
{
	if (entity <= 0 || entity > 4096 || strlen(sample) == 0)
		return false;

	char sSound[PLATFORM_MAX_PATH];
	strcopy(sSound, sizeof(sSound), sample);

	if (GetEngineVersion() == Engine_CSGO)
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
		strcopy(sample, sizeof(sample), sample[6]);
		
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
/*--------------------------------------------------------->*/

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
/*--------------------------------------------------------->*/

stock bool GetClientAbsPosition(int client, float origin[3])
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client))
		return false;

	GetClientAbsOrigin(client, origin);

	float target_velocity[3];
	GetEntPropVector(client, Prop_Data, "m_vecAbsVelocity", target_velocity);

	float correct += GetClientLatency(client, NetFlow_Outgoing);	// * 2

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

stock bool HasClassname(int entity, const char[] name, bool caseSensitive = true)
{
	char sBuffer[256];
	GetEntityClassname(entity, sBuffer, sizeof(sBuffer));
	return StrEqual(sBuffer, name, caseSensitive);
}

/*--------------------------------------------------------->
//CONVARS
--------------------------------------------------------->*/

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

/*--------------------------------------------------------->
//KEYVALUES
--------------------------------------------------------->*/
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

/*--------------------------------------------------------->
//MENU
--------------------------------------------------------->*/
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
	{
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(info, id))
			return StringToInt(data);
	}
	
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
	{
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(info, id))
			return StringToFloat(data);
	}
	
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
	{
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(info, id))
			return view_as<bool>(StringToInt(data));
	}
	
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
	{
		if (menu.GetItem(i, info, sizeof(info)) && StrEqual(info, info, false))
			return menu.RemoveItem(i);
	}
	
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
	{
		if (menu.GetItem(i, info, sizeof(info), _, data, sizeof(data)) && StrEqual(data, name, false))
			return menu.RemoveItem(i);
	}
	
	return false;
}

/*--------------------------------------------------------->
.-----.                      .---.         .-.                          .---.
`-. .-'                      : .--'       .' `.                         `--. :
  : : .--.  .--.  ,-.,-.,-.  : `;.--. .--.`. .'.--.  .--.  .--.  .--.     ,','
  : :' '_.'' .; ; : ,. ,. :  : :' .; :: ..': : : ..'' '_.'`._-.'`._-.'  .'.'_
  :_;`.__.'`.__,_;:_;:_;:_;  :_;`.__.':_;  :_; :_;  `.__.'`.__.'`.__.'  :____;

- Team Fortress 2
- TF2

- Credits: Pelipoika, 11530, Chdata, Tylerst, aIM
--------------------------------------------------------->*/

#define TF2_MAX_CLASSES 10
#define TF_MAX_CLASSES TF2_MAX_CLASSES
#define TF2_MAX_SLOTS 8
#define TF_MAX_SLOTS TF2_MAX_SLOTS

#define PICKUP_TYPE_HEALTHKIT	1
#define PICKUP_TYPE_AMMOBOX		2

#define PICKUP_SMALL	0
#define PICKUP_MEDIUM	1
#define PICKUP_FULL		2

enum TFClassRole
{
	TFRole_Unknown,
	TFRole_Offense,
	TFRole_Defense,
	TFRole_Support
}

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

enum TFGod
{
	TFGod_God,
	TFGod_Buddha,
	TFGod_Mortal
}

enum TF2Quality {
	TF2Quality_Normal = 0, // 0
	TF2Quality_Rarity1,
	TF2Quality_Genuine = 1,
	TF2Quality_Rarity2,
	TF2Quality_Vintage,
	TF2Quality_Rarity3,
	TF2Quality_Rarity4,
	TF2Quality_Unusual = 5,
	TF2Quality_Unique,
	TF2Quality_Community,
	TF2Quality_Developer,
	TF2Quality_Selfmade,
	TF2Quality_Customized, // 10
	TF2Quality_Strange,
	TF2Quality_Completed,
	TF2Quality_Haunted,
	TF2Quality_ToborA
};

/**
*	Sets a players class while fixing the health and loadout issues and keeping it persistently as default.
*	Never understood why it doesn't do this already.
*
*	client		Client Index.
*	class		Class to change to.
*	persistent	Whether to keep the class through death.
*
*	return	Entity index of the glow.
**/
stock void TF2_ChangePlayerClass(int client, TFClassType class, bool persistent = true)
{
	TF2_SetPlayerClass(client, class, _, persistent);
	TF2_RegeneratePlayer(client);
}

/**
*	Create a glow entity and attach it to a client.
*	This seems to have an unintended side effect for animations for models for some reason.
*
*	name	Name to give the entity.
*	target	Target entity index to glow.
*	colors	Color of the glow.
*
*	return	Entity index of the glow.
**/
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
		
		SetVariantString("!activator");
		AcceptEntityInput(glow, "SetParent", target, glow);

		AcceptEntityInput(glow, "Enable");
	}

	return glow;
}

/**
*	Retrieves the name of the class a client is playing as.
*
*	client	Client index.
*	buffer	String buffer to save it to.
*	size	Size of the buffer.
*	capitalize	Whether to capitalize the first letter or not.
*
*	return	void
**/
stock void TF2_GetClientClassName(int client, char[] buffer, int size, bool capitalize = false)
{
	switch (TF2_GetPlayerClass(client))
	{
		case TFClass_Unknown: strcopy(buffer, size, "unknown");
		case TFClass_Scout: strcopy(buffer, size, "scout");
		case TFClass_Sniper: strcopy(buffer, size, "sniper");
		case TFClass_Soldier: strcopy(buffer, size, "soldier");
		case TFClass_DemoMan: strcopy(buffer, size, "demoman");
		case TFClass_Medic: strcopy(buffer, size, "medic");
		case TFClass_Heavy: strcopy(buffer, size, "heavy");
		case TFClass_Pyro: strcopy(buffer, size, "pyro");
		case TFClass_Spy: strcopy(buffer, size, "spy");
		case TFClass_Engineer: strcopy(buffer, size, "engineer");
	}

	if (capitalize)
		buffer[0] = CharToUpper(buffer[0]);
}

/**
*	Retrieves the name of a certain class based on the type given.
*
*	class	Class.
*	name	String buffer to save it to.
*	size	Size of the buffer.
*	capitalize	Whether to capitalize the first letter or not.
*
*	return	void
**/
stock void TF2_GetClassName(TFClassType class, char[] buffer, int size, bool capitalize = false)
{
	switch (class)
	{
		case TFClass_Unknown: strcopy(buffer, size, "unknown");
		case TFClass_Scout: strcopy(buffer, size, "scout");
		case TFClass_Sniper: strcopy(buffer, size, "sniper");
		case TFClass_Soldier: strcopy(buffer, size, "soldier");
		case TFClass_DemoMan: strcopy(buffer, size, "demoman");
		case TFClass_Medic: strcopy(buffer, size, "medic");
		case TFClass_Heavy: strcopy(buffer, size, "heavy");
		case TFClass_Pyro: strcopy(buffer, size, "pyro");
		case TFClass_Spy: strcopy(buffer, size, "spy");
		case TFClass_Engineer: strcopy(buffer, size, "engineer");
	}

	if (capitalize)
		buffer[0] = CharToUpper(buffer[0]);
}

/**
*	Strips a player to melee only and equips their melee.
*
*	client	Client index.
*
*	return	void
**/
stock void TF2_StripToMelee(int client)
{
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Primary);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Secondary);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Grenade);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Building);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_PDA);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Item1);
	TF2_RemoveWeaponSlot(client, TFWeaponSlot_Item2);

	int melee;
	if ((melee = GetPlayerWeaponSlot(client, TFWeaponSlot_Melee)) != -1 && IsValidEntity(melee))
		EquipPlayerWeapon(client, melee);
}

/**
*	Sets the color of a player including all of their weapons and cosmetics.
*
*	client	Client index.
*	red		Amount of Red. (0-255)
*	green	Amount of Green. (0-255)
*	blue	Amount of Blue. (0-255)
*	alpha	Amount of Alpha. (0-255)
*
*	return	void
**/
stock void TF2_SetPlayerColor(int client, int red, int green, int blue, int alpha)
{
	SetEntityRenderMode(client, RENDER_TRANSCOLOR);
	SetEntityRenderColor(client, red, green, blue, alpha);

	int entity = -1;
	while((entity = FindEntityByClassname(entity, "tf_*")) != -1)
	{
		if (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client)
		{
			SetEntityRenderMode(entity, RENDER_TRANSCOLOR);
			SetEntityRenderColor(entity, red, green, blue, alpha);
		}
	}
}

/**
*	Sets the visibility of a player including all of their weapons and cosmetics.
*
*	client	Client index.
*	visible		Visible or not visble?
*
*	return	N/A
**/
stock void TF2_SetPlayerVisible(int client, bool visible)
{
	SetEntityRenderMode(client, visible ? RENDER_NORMAL : RENDER_NONE);

	int entity = -1;
	while((entity = FindEntityByClassname(entity, "tf_*")) != -1)
	{
		if (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client)
			SetEntityRenderMode(entity, visible ? RENDER_NORMAL : RENDER_NONE);
	}
}

/**
*	Force the round to win and give the win to a certain team or draw.
*	You should code a boolean in your plugin to automatically pass to this callback so that it doesn't create the entity if the map isn't running.
*
*	team	Team index to have the win. (unassigned = draw)
*	map_valid	Passive check to use in your plugins to make sure the map is running.
*
*	return	void
**/
stock void TF2_ForceRoundWin(TFTeam team, bool map_valid = true)
{
	int entity = FindEntityByClassname(-1, "team_control_point_master");

	if (!IsValidEntity(entity))
	{
		entity = CreateEntityByName("team_control_point_master");
		DispatchSpawn(entity);
		AcceptEntityInput(entity, "Enable");
	}

	SetVariantInt(view_as<int>(team));
	AcceptEntityInput(entity, "SetWinner");
}

/**
*	Retrieves the current uber level of a Medic.
*
*	client	Client index.
*
*	return	Amount of current uber.
**/
stock float TF2_GetUberLevel(int client)
{
	int secondary = GetPlayerWeaponSlot(client, 1);
	return (IsValidEntity(secondary) && HasEntProp(secondary, Prop_Send, "m_flChargeLevel")) ? GetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel") : -1.0;
}

/**
*	Set the uber level on a Medic.
*
*	client	Client index.
*	amount	Amount of uber to set.
*
*	return	void
**/
stock void TF2_SetUberLevel(int client, float amount, bool cap = false)
{
	int secondary = GetPlayerWeaponSlot(client, 1);

	if (IsValidEntity(secondary) && HasEntProp(secondary, Prop_Send, "m_flChargeLevel"))
	{
		SetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel", amount);

		if (cap && TF2_GetUberLevel(client) > 1.00)
			SetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel", 1.00);
	}
}

/**
*	Add uber level to a Medic.
*
*	client	Client index.
*	amount	Amount of uber to add.
*
*	return	void
**/
stock void TF2_AddUberLevel(int client, float amount, bool cap = false)
{
	TF2_SetUberLevel(client, (TF2_GetUberLevel(client) + amount), cap);
}

/**
*	Remove uber level from a Medic.
*
*	client	Client index.
*	amount	Amount of uber to remove.
*
*	return	void
**/
stock void TF2_RemoveUberLevel(int client, float amount)
{
	TF2_SetUberLevel(client, (TF2_GetUberLevel(client) - amount));
}

/**
*	Retrieves the current metal of an Engineer.
*
*	client	Client index.
*
*	return	Amount of current metal.
**/
stock int TF2_GetMetal(int client)
{
	return GetEntProp(client, Prop_Data, "m_iAmmo", 4, 3);
}

/**
*	Set the metal of an Engineer.
*
*	client	Client index.
*	amount	Amount of metal to set.
*
*	return	void
**/
stock void TF2_SetMetal(int client, int amount)
{
	SetEntProp(client, Prop_Data, "m_iAmmo", amount, 4, 3);
}

/**
*	Add metal to a Engineer.
*
*	client	Client index.
*	amount	Amount of metal to add.
*
*	return	void
**/
stock void TF2_AddMetal(int client, int amount)
{
	TF2_SetMetal(client, (TF2_GetMetal(client) + amount));
}

/**
*	Remove metal from a Engineer.
*
*	client	Client index.
*	amount	Amount of metal to remove.
*
*	return	void
**/
stock void TF2_RemoveMetal(int client, int amount)
{
	TF2_SetMetal(client, (TF2_GetMetal(client) - amount));
}

/**
*	Sets the current godmode status for the client.
*
*	client	Client index.
*	status	Status for godmode.
*
*	return	void
**/
stock void TF2_SetGodmode(int client, TFGod status = TFGod_God)
{
	SetEntProp(client, Prop_Data, "m_takedamage", view_as<int>(status), 1);
}

/**
*	Gets the current godmode status from the client.
*
*	client	Client index.
*
*	return	void
**/
stock TFGod TF2_GetGodmode(int client)
{
	return view_as<TFGod>(GetEntProp(client, Prop_Data, "m_takedamage", 1));
}

/**
*	Retrieves the current healing target of a Medic.
*
*	client	Client index.
*
*	return	Client index the Medic is healing.
**/
stock int TF2_GetHealingTarget(int client)
{
	int weapon = GetPlayerWeaponSlot(client, 1);

	if (!IsValidEntity(weapon) || weapon != GetActiveWeapon(client))
		return -1;

	char sClassname[32];
	GetEdictClassname(weapon, sClassname, sizeof(sClassname));

	if (StrContains(sClassname, "tf_weapon_med") == -1)
		return -1;

	return GetEntProp(weapon, Prop_Send, "m_bHealing") ? GetEntPropEnt(weapon, Prop_Send, "m_hHealingTarget") : -1;
}

/**
*	Simple check if the mode is arena or not.
*
*	return	Is Arena or not.
**/
stock bool IsArenaActive()
{
	return FindEntityByClassname(-1, "tf_logic_arena") != -1;
}

/**
*	Simple stock to create an explosion.
*
*	origin	Vector coordinate to spawn the explosion.
*	damage	Damage to cause in the area.
*	radius	Radius of the blast damage.
*	magnitude	Magnitude to push players away from the point.
*	attacker	Attacker index if there is one. (0 = world)
*	inflictor	Inflictor index if there is one. (0 = world)
*	team	Team to cause damage to. (0 = everyone)
*	particle	Particle effect to use. (default is cinefx_goldrush which is fairly large)
*	sound	Sound to play for the explosion.
*	amplitude	Amplitude for the shaking effect.
*	frequency	Frequency for the shaking effect.
*	duration	Duration for the shaking effect.
*
*	return	void
**/
stock void TF2_CreateExplosion(float origin[3], float damage = 99999.0, float radius = 250.0, float magnitude = 500.0, int attacker = 0, int inflictor = 0, int team = 0, char[] particle = "cinefx_goldrush", char sound[PLATFORM_MAX_PATH] = "items/cart_explode.wav", float amplitude = 50.0, float frequency = 150.0, float duration = 3.0, int damagetype = DMG_BLAST, int weapon = -1)
{
	//NOT UNMERGING, NOPE
	CreateParticle(particle, 10.0, origin);
	EmitSoundToAllSafe(sound);
	ScreenShakeAll(SHAKE_START, amplitude, frequency, duration);
	PushAllPlayersFromPoint(origin, magnitude, radius, team);
	DamageArea(origin, radius, damage, attacker, inflictor, team, damagetype, weapon);
}

/**
*	A simple stock to remove every wearable on a client.
*
*	client	Client index.
*
*	return	void
**/
stock void TF2_RemoveAllWearables(int client)
{
	int entity;
	while ((entity = FindEntityByClassname(entity, "tf_wearable*")) != -1)
	{
		if (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client)
			TF2_RemoveWearable(client, entity);
	}
}

/**
*	Sets the size of a player and scales accordingly.
*	https://forums.alliedmods.net/showthread.php?t=193255
*
*	client	Client index.
*	amount	Scale to set to.
*
*	return	void
**/
stock void TF2_ResizePlayer(int client, float amount)
{
	SetEntPropFloat(client, Prop_Send, "m_flModelScale", amount);
	SetEntPropFloat(client, Prop_Send, "m_flStepSize", 18.0 * amount);
}

/**
*	Spawn an item that players can pickup.
*
*	origin	Vector to spawn the pickup at.
*	type	Type of pickup.
*	size	Size of the pickup.
*	team	Which team it belongs to.
*	persistent	Whether the pickup is persistent. (will list until the round ends, map changes, etc)
*	z_offset	How far above the origin to actually spawn the pickup.
*	model	Custom model for the pickup. (can be blank)
*
*	return	Entity index of the pickup.
**/
stock int TF2_SpawnPickup(float origin[3], int type = PICKUP_TYPE_HEALTHKIT, int size = PICKUP_FULL, int team = 0, bool persistent = false, float z_offset = 5.0, const char[] model = "")
{
	char sTeam[6];
	IntToString(team, sTeam, sizeof(sTeam));

	char sEntity[64];

	switch (type)
	{
		case PICKUP_TYPE_HEALTHKIT: strcopy(sEntity, sizeof(sEntity), "item_healthkit_");
		case PICKUP_TYPE_AMMOBOX: strcopy(sEntity, sizeof(sEntity), "item_ammopack_");
	}

	switch (size)
	{
		case PICKUP_SMALL: StrCat(sEntity, sizeof(sEntity), "small");
		case PICKUP_MEDIUM: StrCat(sEntity, sizeof(sEntity), "medium");
		case PICKUP_FULL: StrCat(sEntity, sizeof(sEntity), "full");
	}

	int entity = CreateEntityByName(sEntity);

	if (IsValidEntity(entity))
	{
		origin[2] += z_offset;
		DispatchKeyValueVector(entity, "origin", origin);
		DispatchKeyValue(entity, "TeamNum", sTeam);
		
		if (!persistent)
			DispatchKeyValue(entity, "OnPlayerTouch", "!self,Kill,,0,-1");	//Make sure it's killed after 1st pickup.
		
		if (strlen(model) > 0)
			DispatchKeyValue(entity, "powerup_model", model);
		
		DispatchSpawn(entity);

		EmitSoundToAll("items/spawn_item.wav", entity, _, _, _, 0.75);
	}

	return entity;
}

/**
*	Retrieves the clients current class role.
*
*	client	Client index.
*
*	return	Role for the client.
**/
stock TFClassRole TF2_GetClientRole(int client)
{
	return TF2_GetClassRole(TF2_GetPlayerClass(client));
}

/**
*	Retrieves the class role from the class it's given.
*
*	class	Class index.
*
*	return	Role for the class.
**/
stock TFClassRole TF2_GetClassRole(TFClassType class)
{
	switch (class)
	{
		case TFClass_Unknown: return TFRole_Unknown;
		case TFClass_Scout: return TFRole_Offense;
		case TFClass_Sniper: return TFRole_Support;
		case TFClass_Soldier: return TFRole_Offense;
		case TFClass_DemoMan: return TFRole_Defense;
		case TFClass_Medic: return TFRole_Support;
		case TFClass_Heavy: return TFRole_Defense;
		case TFClass_Pyro: return TFRole_Offense;
		case TFClass_Spy: return TFRole_Support;
		case TFClass_Engineer: return TFRole_Defense;
	}

	return TFRole_Unknown;
}

/**
*	Sets a players health while applying TF2 health logic.
*
*	client	Client index.
*	amount	Amount of health to set.
*	overheal	Overheal amount to offset.
*	additive	Whether to account for overheal.
*	event	Fire the health gain event.
*
*	return	void
**/
stock void TF2_SetPlayerHealth(int client, int amount, float overheal = 1.5, bool additive = false, bool event = true)
{
	int iHealth = GetClientHealth(client);
	int iNewHealth = amount;
	int iMax = additive ? (TF2_GetMaxHealth(client) + RoundFloat(overheal)) : TF2_GetMaxOverHeal(client, overheal);

	if (iHealth < iMax)
	{
		if (iNewHealth < 1)
			iNewHealth = 1;
		else if (iNewHealth > iMax)
			iNewHealth = iMax;

		if (event)
			TF2_ShowHealthGain(client, iNewHealth - iHealth);

		SetEntityHealth(client, iNewHealth);
	}
}

/**
*	Add to a players health while applying TF2 health logic.
*
*	client	Client index.
*	amount	Amount of health to add.
*	overheal	Overheal amount to offset.
*	additive	Whether to account for overheal.
*	event	Fire the health gain event.
*
*	return	void
**/
stock void TF2_AddPlayerHealth(int client, int amount, float overheal = 1.5, bool additive = false, bool event = true)
{
	int iHealth = GetClientHealth(client);
	int iNewHealth = iHealth + amount;
	int iMax = additive ? (TF2_GetMaxHealth(client) + RoundFloat(overheal)) : TF2_GetMaxOverHeal(client, overheal);

	if (iHealth < iMax)
	{
		if (iNewHealth < 1)
			iNewHealth = 1;
		else if (iNewHealth > iMax)
			iNewHealth = iMax;

		if (event)
			TF2_ShowHealthGain(client, iNewHealth - iHealth);

		SetEntityHealth(client, iNewHealth);
	}
}

/**
*	Removes health from players while applying TF2 health logic.
*
*	client	Client index.
*	amount	Amount of health to remove.
*	overheal	Overheal amount to offset.
*	additive	Whether to account for overheal.
*	event	Fire the health gain event.
*
*	return	void
**/
stock void TF2_RemovePlayerHealth(int client, int amount, float overheal = 1.5, bool additive = false, bool event = true)
{
	int iHealth = GetClientHealth(client);
	int iNewHealth = iHealth - amount;
	int iMax = additive ? (TF2_GetMaxHealth(client) + RoundFloat(overheal)) : TF2_GetMaxOverHeal(client, overheal);

	if (iHealth < iMax)
	{
		if (iNewHealth < 1)
		{
			if (event)
				TF2_ShowHealthGain(client, iNewHealth - iHealth);
			
			ForcePlayerSuicide(client);
			return;
		}
		
		if (iNewHealth > iMax)
			iNewHealth = iMax;

		if (event)
			TF2_ShowHealthGain(client, iNewHealth - iHealth);

		SetEntityHealth(client, iNewHealth);
	}
}

/**
*	Fires an event in TF2 to apply proper logic like for health meter sprites.
*
*	client	Client index.
*	health	Health to pass.
*	healer	Healer index.
*
*	return	void
**/
stock void TF2_ShowHealthGain(int client, int health, int healer = -1)
{
	int userid = GetClientUserId(client);

	Event event = CreateEvent("player_healed", true);
	event.SetBool("sourcemod", true);
	event.SetInt("patient", userid);
	event.SetInt("healer", healer > 0 && IsClientInGame(healer) ? GetClientUserId(healer) : userid);
	event.SetInt("amount", health);
	event.Fire();

	event = CreateEvent("player_healonhit", true);
	event.SetBool("sourcemod", true);
	event.SetInt("amount", health);
	event.SetInt("entindex", client);
	event.Fire();
}

/**
*	Retrieves the maximum health for a client in TF2.
*
*	client	Client index.
*
*	return	Max health of the client.
**/
stock int TF2_GetMaxHealth(int client)
{
	int maxhealth = GetEntProp(GetPlayerResourceEntity(), Prop_Send, "m_iMaxHealth", _, client);
	return ((maxhealth == -1 || maxhealth == 80896) ? GetEntProp(client, Prop_Data, "m_iMaxHealth") : maxhealth);
}

/**
*	Retrieves the maximum overheal for a client in TF2.
*	Quick-Fix would be 1.25.
*
*	client	Client index.
*
*	return	Max overheal of the client.
**/
stock int TF2_GetMaxOverHeal(int client, float overheal = 1.5)
{
	return RoundFloat(float(TF2_GetMaxHealth(client)) * overheal);
}

/**
*	Retrieves the current overheal for a client in TF2.
*
*	client	Client index.
*
*	return	Current overheal of the client.
**/
stock int TF2_GetOverHeal(int client, float overheal = 1.5)
{
	return RoundFloat(float(TF2_GetMaxHealth(client)) * (overheal - 1.0));
}

/**
*	Retrieves whether the client is ready to overheal in TF2.
*
*	client	Client index.
*	add		Buffer to add.
*
*	return	Whether they're ready to overheal or not.
**/
stock bool TF2_ReadyToOverheal(int client, int add = 0)
{
	return (add > 0) ? ((TF2_GetMaxHealth(client) - GetClientHealth(client)) < add) : (GetClientHealth(client) >= TF2_GetMaxHealth(client));
}

/**
*	A simple stock to allow for attributes to be applied to weapons on a client.
*
*	client	Client index.
*	weapon	Entity index for the weapon. (-1 = all weapons)
*	attrib	Attribute to apply.
*	value	Value for the attribute.
*	invert	Whether to invert the value for inverted valued attributes.
*
*	return	void
**/
stock void TF2Attrib_SetByName_Weapons(int client, int weapon = -1, char[] attrib, float value, bool invert = false)
{
	if (weapon != -1 && IsValidEntity(weapon))
	{
		TF2Attrib_SetByName(weapon, attrib, value);
		return;
	}

	if (invert)
		value = 1.0 + value;
	else
		value = 1.0 - value;

	int weapon2;
	for (int i = 0; i < 6; i++)
	{
		weapon2 = GetPlayerWeaponSlot(client, i);

		if (IsValidEntity(weapon2))
			TF2Attrib_SetByName(weapon2, attrib, value);
	}
}

/**
*	A simple stock to remove attributes from the weapons on a client.
*
*	client	Client index.
*	weapon	Entity index for the weapon. (-1 = all weapons)
*	attrib	Attribute to apply.
*
*	return	void
**/
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
			TF2Attrib_RemoveByName(weapon2, attrib);
	}
}

/**
*	A simple stock to apply a bonus movement speed effect to the client.
*
*	client	Client index.
*	value	Amount of movement speed to apply.
*
*	return	N/A
**/
stock void TF2Attrib_ApplyMoveSpeedBonus(int client, float value)
{
	TF2Attrib_SetByName(client, "move speed bonus", 1.0 + value);
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);
}

/**
*	A simple stock to remove a bonus movement speed effect from the client.
*
*	client	Client index.
*
*	return	void
**/
stock void TF2Attrib_RemoveMoveSpeedBonus(int client)
{
	TF2Attrib_RemoveByName(client, "move speed bonus");
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);
}

/**
*	A simple stock to apply a penalty movement speed effect to the client.
*
*	client	Client index.
*	value	Amount of movement speed to apply.
*
*	return	N/A
**/
stock void TF2Attrib_ApplyMoveSpeedPenalty(int client, float value)
{
	TF2Attrib_SetByName(client, "move speed penalty", 1.0 - value);
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);
}

/**
*	A simple stock to remove a penalty movement speed effect from the client.
*
*	client	Client index.
*
*	return	void
**/
stock void TF2Attrib_RemoveMoveSpeedPenalty(int client)
{
	TF2Attrib_RemoveByName(client, "move speed penalty");
	TF2_AddCondition(client, TFCond_SpeedBuffAlly, 0.0);
}

/**
*	Sets the spell plus charges on a client in TF2.
*
*	client	Client index.
*	spell	Spell index.
*	uses	Amount of uses to apply.
*
*	return	void
**/
stock void TF2_SetSpell(int client, int spell, int uses)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
	{
		SetEntProp(entity, Prop_Send, "m_iSelectedSpellIndex", spell);
		SetEntProp(entity, Prop_Send, "m_iSpellCharges", uses);
	}
}

/**
*	Sets the spell uses for their current spell on a client in TF2.
*
*	client	Client index.
*	uses	Amount of uses to apply.
*
*	return	void
**/
stock void TF2_SetSpellUses(int client, int uses)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
		SetEntProp(entity, Prop_Send, "m_iSpellCharges", uses);
}

/**
*	Retrieves the current spell on a client in TF2.
*
*	client	Client index.
*
*	return	Spell index.
**/
stock int TF2_GetSpell(int client)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
		return GetEntProp(ent, Prop_Send, "m_iSelectedSpellIndex");

	return -1;
}

/**
*	Retrieves the currently available uses of their current spell on a client in TF2.
*
*	client	Client index.
*
*	return	Amount of uses.
**/
stock int TF2_GetSpellUses(int client)
{
	int entity = TF2_GetSpellBook(client);

	if (IsValidEntity(entity))
		return GetEntProp(entity, Prop_Send, "m_iSpellCharges");
}

/**
*	Retrieves the entity index for the clients spellbook.
*
*	client	Client index.
*
*	return	Spellbook index.
**/
stock int TF2_GetSpellBook(int client)
{
	int entity = -1;
	while((entity = FindEntityByClassname(entity, "tf_weapon_spellbook")) != INVALID_ENT_REFERENCE)
	{
		if (HasEntProp(entity, Prop_Send, "m_hOwnerEntity") && GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client)
			return entity;
	}

	return -1;
}

/**
*	A simple stock to check whether a spell is rare or not.
*
*	spell	Spell index.
*
*	return	Whether the spell is considered rare or not.
**/
stock bool TF2_SpellIsRare(int spell)
{
	switch(spell)
	{
		case SPELL_TELSABOLT, SPELL_MINIFY, SPELL_SUMMONMONOCULUS, SPELL_METEORSHOWER, SPELL_SUMMONSKELETONS: return true;
		default: return false;
	}
}

//TODO: Update it so that it properly capitalizes every word properly.
/**
*	Retrieves the name of a certain spell.
*
*	spell	Spell index.
*	buffer	Buffer to store the name into.
*	size	Size of the buffer.
*	capitalize	Whether to capitalize the name.
*
*	return	void
**/
stock void TF2_GetSpellName(int spell, char[] buffer, int size, bool capitalize = true)
{
	switch(spell)
	{
		case SPELL_FIREBALL: strcopy(buffer, size, "fireball");
		case SPELL_BALLOBATS: strcopy(buffer, size, "ball O' Bats");
		case SPELL_HEALINGAURA: strcopy(buffer, size, "healing Aura");
		case SPELL_PUMPKINMIRV: strcopy(buffer, size, "pumpkin MIRV");
		case SPELL_SUPERJUMP: strcopy(buffer, size, "superjump");
		case SPELL_INVISIBILITY: strcopy(buffer, size, "invisibility");
		case SPELL_TELEPORT: strcopy(buffer, size, "teleport");
		case SPELL_TELSABOLT: strcopy(buffer, size, "tesla Bolt");
		case SPELL_MINIFY: strcopy(buffer, size, "minify");
		case SPELL_SUMMONMONOCULUS: strcopy(buffer, size, "summon Monoculus");
		case SPELL_METEORSHOWER: strcopy(buffer, size, "meteor Shower");
		case SPELL_SUMMONSKELETONS: strcopy(buffer, size, "summon Skeletons");
		default: strcopy(buffer, size, "none");
	}

	if (capitalize)
		buffer[0] = CharToUpper(buffer[0]);
}

/**
*	Sets the current powerup on a client.
*
*	client	Client index.
*	powerup	Powerup to apply.
*
*	return	void
**/
stock void TF2_SetPowerup(int client, int powerup)
{
	switch (powerup)
	{
		case POWERUP_STRENGTH: TF2_AddCondition(client, TFCond_RuneStrength);
		case POWERUP_RESIST: TF2_AddCondition(client, TFCond_RuneResist);
		case POWERUP_VAMPIRE: TF2_AddCondition(client, TFCond_RuneVampire);
		case POWERUP_WARLOCK: TF2_AddCondition(client, TFCond_RuneWarlock);
		case POWERUP_HASTE: TF2_AddCondition(client, TFCond_RuneHaste);
		case POWERUP_REGEN: TF2_AddCondition(client, TFCond_RuneRegen);
		case POWERUP_PRECISION: TF2_AddCondition(client, TFCond_RunePrecision);
		case POWERUP_AGILITY: TF2_AddCondition(client, TFCond_RuneAgility);
		case POWERUP_KNOCKOUT: TF2_AddCondition(client, TFCond_RuneKnockout);
		case POWERUP_KING:
		{
			TF2_AddCondition(client, TFCond_KingRune);
			TF2_AddCondition(client, TFCond_KingAura);
		}
		case POWERUP_PLAGUE: TF2_AddCondition(client, TFCond_Plague);
		case POWERUP_SUPERNOVA: TF2_AddCondition(client, TFCond_SupernovaRune);
	}

	//This has to be here.
	TF2_AddCondition(client, TFCond_HasRune);
}

/**
*	Retrieves the default weapon class for a client based on slot.
*
*	class	Class index.
*	slot	Slot to retrieve.
*	buffer	Buffer to store the classname in.
*	size	Size of the buffer.
*
*	return	Whether it found a default or not based on the slot.
**/
stock bool TF2_GetDefaultWeaponClass(TFClassType class, int slot, char[] buffer, int size)
{
	bool found;

	switch(class)
	{
		case TFClass_Scout:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_scattergun"), found = true;
				case 1: Format(buffer, size, "tf_weapon_pistol_scout"), found = true;
				case 2: Format(buffer, size, "tf_weapon_bat"), found = true;
			}
		}
		case TFClass_Sniper:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_sniperrifle"), found = true;
				case 1: Format(buffer, size, "tf_weapon_smg"), found = true;
				case 2: Format(buffer, size, "tf_weapon_club"), found = true;
			}
		}
		case TFClass_Soldier:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_rocketlauncher"), found = true;
				case 1: Format(buffer, size, "tf_weapon_shotgun_soldier"), found = true;
				case 2: Format(buffer, size, "tf_weapon_shovel"), found = true;
			}
		}
		case TFClass_DemoMan:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_grenadelauncher"), found = true;
				case 1: Format(buffer, size, "tf_weapon_ipebomblauncher"), found = true;
				case 2: Format(buffer, size, "tf_weapon_bottle"), found = true;
			}
		}
		case TFClass_Medic:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_syringegun_medic"), found = true;
				case 1: Format(buffer, size, "tf_weapon_medigun"), found = true;
				case 2: Format(buffer, size, "tf_weapon_bonesaw"), found = true;
			}
		}
		case TFClass_Heavy:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_minigun"), found = true;
				case 1: Format(buffer, size, "tf_weapon_shotgun_hwg"), found = true;
				case 2: Format(buffer, size, "tf_weapon_fists"), found = true;
			}
		}
		case TFClass_Pyro:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_flamethrower"), found = true;
				case 1: Format(buffer, size, "tf_weapon_shotgun_pyro"), found = true;
				case 2: Format(buffer, size, "tf_weapon_fireaxe"), found = true;
			}
		}
		case TFClass_Spy:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_revolver"), found = true;
				case 1: Format(buffer, size, "tf_weapon_builder"), found = true;
				case 2: Format(buffer, size, "tf_weapon_knife"), found = true;
				case 4: Format(buffer, size, "tf_weapon_invis"), found = true;
			}
		}
		case TFClass_Engineer:
		{
			switch(slot)
			{
				case 0: Format(buffer, size, "tf_weapon_shotgun_primary"), found = true;
				case 1: Format(buffer, size, "tf_weapon_pistol"), found = true;
				case 2: Format(buffer, size, "tf_weapon_wrench"), found = true;
				case 3: Format(buffer, size, "tf_weapon_pda_engineer_build"), found = true;
			}
		}
	}

	return found;
}

/**
*	Retrieves the default weapon id for a client based on slot.
*
*	class	Class index.
*	slot	Slot to retrieve.
*
*	return	The id of the weapon slot.
**/
stock int TF2_GetDefaultWeaponID(TFClassType class, int slot)
{
	switch(class)
	{
		case TFClass_Scout:
		{
			switch(slot)
			{
				case 0: return 13; case 1: return 23; case 2: return 0;
			}
		}
		case TFClass_Sniper:
		{
			switch(slot)
			{
				case 0: return 14; case 1: return 16; case 2: return 3;
			}
		}
		case TFClass_Soldier:
		{
			switch(slot)
			{
				case 0: return 18; case 1: return 10; case 2: return 6;
			}
		}
		case TFClass_DemoMan:
		{
			switch(slot)
			{ case 0: return 19; case 1: return 20; case 2: return 1;
			}
		}
		case TFClass_Medic:
		{
			switch(slot)
			{
				case 0: return 17; case 1: return 29; case 2: return 8;
			}
		}
		case TFClass_Heavy:
		{
			switch(slot)
			{
				case 0: return 15; case 1: return 11; case 2: return 5;
			}
		}
		case TFClass_Pyro:
		{
			switch(slot)
			{
				case 0: return 21; case 1: return 12; case 2: return 2;
			}
		}
		case TFClass_Spy:
		{
			switch(slot)
			{
				case 0: return 24; case 1: return 735; case 2: return 4; case 4: return 30;
			}
		}
		case TFClass_Engineer:
		{
			switch(slot)
			{
				case 0: return 9; case 1: return 22; case 2: return 7; case 3: return 25;
			}
		}
	}

	return -1;
}

/**
*	Retrieves a certain healer for the client by index.
*	Credits: Pelipoika
*
*	client	Client index.
*	index	Slot for the healer inside of 'm_nNumHealers' Netprop.
*
*	return	Client index for the healer.
**/
stock int TF2_GetHealerByIndex(int client, int index)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client))
		return 0;

	int m_aHealers = FindSendProinfo("CTFPlayer", "m_nNumHealers") + 12;

	Address m_Shared = GetEntityAddress(client) + view_as<Address>(m_aHealers);
	Address aHealers = view_as<Address>(LoadFromAddress(m_Shared, NumberType_Int32));

	return (LoadFromAddress(aHealers + view_as<Address>(index * 0x24), NumberType_Int32) & 0xFFF);
}

/**
*	Retrieves the healer count for the client.
*
*	client	Client index.
*
*	return	Amount of healers the client has.
**/
stock int TF2_GetHealerCount(int client)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || !HasEntProp(client, Prop_Send, "m_nNumHealers"))
		return 0;

	return GetEntProp(client, Prop_Send, "m_nNumHealers");
}

/**
*	Checks whether or not a certain client is healing another client.
*
*	client	Client index.
*	healer	Healer index.
*
*	return	Amount of healers the client has.
**/
stock bool TF2_IsCurrentHealer(int client, int healer)
{
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || !IsPlayerIndex(healer) || !IsClientInGame(healer) || !IsPlayerAlive(healer) || TF2_GetPlayerClass(healer) != TFClass_Medic)
		return false;

	int healers;

	if ((healers = GetEntProp(client, Prop_Send, "m_nNumHealers")) == 0)
		return false;

	for (int i = 0; i < healers; i++)
	{
		if (TF2_GetHealerByIndex(client, i) == healer)
			return true;
	}

	return false;
}

/**
*	Returns a value for the TFTeam enum based on a name string.
*
*	team	Name of the team.
*
*	return	TFTeam enum value.
**/
stock TFTeam TF2_GetTeam(const char[] team)
{
	if (StrEqual(team, "1") || StrEqual(team, "spec", false) || StrEqual(team, "spectate", false) || StrEqual(team, "spectator", false) || StrEqual(team, "spectators", false))
		return TFTeam_Spectator;
	else if (StrEqual(team, "2") || StrEqual(team, "red", false))
		return TFTeam_Red;
	else if (StrEqual(team, "3") || StrEqual(team, "blu", false) || StrEqual(team, "blue", false))
		return TFTeam_Blue;

	return TFTeam_Unassigned;
}

//Ragdoll Flags (Headline helped with this, thanks buddy)
#define RAG_GIBBED			(1<<0)
#define RAG_BURNING			(1<<1)
#define RAG_ELECTROCUTED	(1<<2)
#define RAG_FEIGNDEATH		(1<<3)
#define RAG_WASDISGUISED	(1<<4)
#define RAG_BECOMEASH		(1<<5)
#define RAG_ONGROUND		(1<<6)
#define RAG_CLOAKED			(1<<7)
#define RAG_GOLDEN			(1<<8)
#define RAG_ICE				(1<<9)
#define RAG_CRITONHARDCRIT	(1<<10)
#define RAG_HIGHVELOCITY	(1<<11)
#define RAG_NOHEAD			(1<<12)

/**
*	Spawns a ragdoll for the player.
*
*	client			Client index.
*	destruct		Time in seconds for the ragdoll to delete itself.
*	gold_ragdoll	Turn the ragdoll to gold.
*	ice_ragdoll	Turn the ragdoll to ice.
*
*	return	Entity index.
**/
stock int TF2_CreateRagdoll(int client, float destruct = 10.0, int flags = 0, float vel[3] = NULL_VECTOR)
{
	int ragdoll = CreateEntityByName("tf_ragdoll");

	if (IsValidEntity(ragdoll))
	{
		float vecOrigin[3];
		GetClientAbsOrigin(client, vecOrigin);

		float vecAngles[3];
		GetClientAbsAngles(client, vecAngles);

		TeleportEntity(ragdoll, vecOrigin, vecAngles, NULL_VECTOR);

		SetEntProp(ragdoll, Prop_Send, "m_iPlayerIndex", client);
		SetEntProp(ragdoll, Prop_Send, "m_iTeam", GetClientTeam(client));
		SetEntProp(ragdoll, Prop_Send, "m_iClass", view_as<int>(TF2_GetPlayerClass(client)));
		SetEntProp(ragdoll, Prop_Send, "m_nForceBone", 1);
		SetEntProp(ragdoll, Prop_Send, "m_iDamageCustom", TF_CUSTOM_TAUNT_ENGINEER_SMASH);
		
		SetEntProp(ragdoll, Prop_Send, "m_bGib", (flags & RAG_GIBBED) == RAG_GIBBED);
		SetEntProp(ragdoll, Prop_Send, "m_bBurning", (flags & RAG_BURNING) == RAG_BURNING);
		SetEntProp(ragdoll, Prop_Send, "m_bElectrocuted", (flags & RAG_ELECTROCUTED) == RAG_ELECTROCUTED);
		SetEntProp(ragdoll, Prop_Send, "m_bFeignDeath", (flags & RAG_FEIGNDEATH) == RAG_FEIGNDEATH);
		SetEntProp(ragdoll, Prop_Send, "m_bWasDisguised", (flags & RAG_WASDISGUISED) == RAG_WASDISGUISED);
		SetEntProp(ragdoll, Prop_Send, "m_bBecomeAsh", (flags & RAG_BECOMEASH) == RAG_BECOMEASH);
		SetEntProp(ragdoll, Prop_Send, "m_bOnGround", (flags & RAG_ONGROUND) == RAG_ONGROUND);
		SetEntProp(ragdoll, Prop_Send, "m_bCloaked", (flags & RAG_CLOAKED) == RAG_CLOAKED);
		SetEntProp(ragdoll, Prop_Send, "m_bGoldRagdoll", (flags & RAG_GOLDEN) == RAG_GOLDEN);
		SetEntProp(ragdoll, Prop_Send, "m_bIceRagdoll", (flags & RAG_ICE) == RAG_ICE);
		SetEntProp(ragdoll, Prop_Send, "m_bCritOnHardHit", (flags & RAG_CRITONHARDCRIT) == RAG_CRITONHARDCRIT);
		
		SetEntPropVector(ragdoll, Prop_Send, "m_vecRagdollOrigin", vecOrigin);
		SetEntPropVector(ragdoll, Prop_Send, "m_vecRagdollVelocity", vel);
		SetEntPropVector(ragdoll, Prop_Send, "m_vecForce", vel);
		
		if ((flags & RAG_HIGHVELOCITY) == RAG_HIGHVELOCITY)
		{
			//from Rowedahelicon
			float HighVel[3];
			HighVel[0] = -180000.552734;
			HighVel[1] = -1800.552734;
			HighVel[2] = 800000.552734; //Muhahahahaha
			
			SetEntPropVector(ragdoll, Prop_Send, "m_vecRagdollVelocity", HighVel);
			SetEntPropVector(ragdoll, Prop_Send, "m_vecForce", HighVel);
		}
		
		//Makes sure the ragdoll isn't malformed on spawn.
		SetEntPropFloat(ragdoll, Prop_Send, "m_flHeadScale", (flags & RAG_NOHEAD) == RAG_NOHEAD ? 0.0 : 1.0);
		SetEntPropFloat(ragdoll, Prop_Send, "m_flTorsoScale", 1.0);
		SetEntPropFloat(ragdoll, Prop_Send, "m_flHandScale", 1.0);
		
		DispatchSpawn(ragdoll);
		ActivateEntity(ragdoll);
		
		SetEntPropEnt(client, Prop_Send, "m_hRagdoll", ragdoll, 0);
		
		if (destruct > 0.0)
		{
			char output[64];
			Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", destruct);

			SetVariantString(output);
			AcceptEntityInput(ragdoll, "AddOutput");
			AcceptEntityInput(ragdoll, "FireUser1");
		}
	}

	return ragdoll;
}

/**
*	Destroys the ragdoll of a player.
*
*	client			Client index.
*
*	return	Entity removed or not.
**/
stock bool TF2_RemoveRagdoll(int client)
{
	int ragdoll = GetEntPropEnt(client, Prop_Send, "m_hRagdoll");

	if (IsValidEdict(ragdoll))
	{
		char classname[64];
		GetEdictClassname(ragdoll, classname, sizeof(classname));

		if (StrEqual(classname, "tf_ragdoll", false))
			RemoveEdict(ragdoll);
		
		return true;
	}
	
	return false;
}

/**
*	Regenerate all players on the server.
*
*	return	void
**/
stock void TF2_RegenerateAllPlayers()
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;
		
		TF2_RegeneratePlayer(i);
	}
}

/**
*	Sets the clients head size.
*
*	client			Client index.
*	size			Size to set.
*
*	return	void
**/
stock void TF2_SetHeadSize(int client, float size = 1.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flHeadScale", size);
}

/**
*	Resets the clients head size.
*
*	client			Client index.
*
*	return	void
**/
stock void TF2_ResetHeadSize(int client)
{
	SetEntPropFloat(client, Prop_Send, "m_flHeadScale", 1.0);
}

/**
*	Sets the clients torso size.
*
*	client			Client index.
*	size			Size to set.
*
*	return	void
**/
stock void TF2_SetTorsoSize(int client, float size = 1.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flTorsoScale", size);
}

/**
*	Resets the clients torso size.
*
*	client			Client index.
*
*	return	void
**/
stock void TF2_ResetTorsoSize(int client)
{
	SetEntPropFloat(client, Prop_Send, "m_flTorsoScale", 1.0);
}

/**
*	Sets the clients hand size.
*
*	client			Client index.
*	size			Size to set.
*
*	return	void
**/
stock void TF2_SetHandSize(int client, float size = 1.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flHandScale", size);
}

/**
*	Resets the clients hand size.
*
*	client			Client index.
*
*	return	void
**/
stock void TF2_ResetHandSize(int client)
{
	SetEntPropFloat(client, Prop_Send, "m_flHandScale", 1.0);
}

/**
*	Resets all model sizes for a client.
*
*	client			Client index.
*
*	return	void
**/
stock void TF2_ResetSizes(int client)
{
	SetEntPropFloat(client, Prop_Send, "m_flHeadScale", 1.0);
	SetEntPropFloat(client, Prop_Send, "m_flTorsoScale", 1.0);
	SetEntPropFloat(client, Prop_Send, "m_flHandScale", 1.0);
}

/**
*	Sets the client to not be targetted by sentries or not.
*
*	client			Client index.
*	target			Target boolean.
*
*	return	void
**/
stock void TF2_SentryTarget(int client, bool target = true)
{
	SetEntityFlags(client, !target ? (GetEntityFlags(client) | FL_NOTARGET) : (GetEntityFlags(client) &~ FL_NOTARGET));
}

/**
*	Spawns a Sentry.
*
*	builder			Builder index.
*	Position		Position of the Sentry.
*	Angle			Angle of the Sentry.
*	level			Sentry level.
*	mini			Is Mini?
*	disposable		Is Disposable?
*
*	return	Entity index.
**/
stock int TF2_SpawnSentry(int builder, float Position[3], float Angle[3], TFTeam team = TFTeam_Unassigned, int level = 0, bool mini = false, bool disposable = false)
{
	static const float m_vecMinsMini[3] = {-15.0, -15.0, 0.0}, m_vecMaxsMini[3] = {15.0, 15.0, 49.5};
	static const float m_vecMinsDisp[3] = {-13.0, -13.0, 0.0}, m_vecMaxsDisp[3] = {13.0, 13.0, 42.9};
	
	int sentry = CreateEntityByName("obj_sentrygun");
	
	if (IsValidEntity(sentry))
	{
		char sLevel[12];
		IntToString(level, sLevel, sizeof(sLevel));
		
		if (builder > 0)
			AcceptEntityInput(sentry, "SetBuilder", builder);

		SetVariantInt(view_as<int>(team));
		AcceptEntityInput(sentry, "SetTeam");
		
		DispatchKeyValueVector(sentry, "origin", Position);
		DispatchKeyValueVector(sentry, "angles", Angle);
		DispatchKeyValue(sentry, "defaultupgrade", sLevel);
		DispatchKeyValue(sentry, "spawnflags", "4");
		SetEntProp(sentry, Prop_Send, "m_bBuilding", 1);
		
		if (mini || disposable)
		{
			SetEntProp(sentry, Prop_Send, "m_bMiniBuilding", 1);
			SetEntProp(sentry, Prop_Send, "m_nSkin", level == 0 ? view_as<int>(team) : view_as<int>(team) - 2);
		}
		
		if (mini)
		{
			DispatchSpawn(sentry);
			
			SetVariantInt(100);
			AcceptEntityInput(sentry, "SetHealth");
			
			SetEntPropFloat(sentry, Prop_Send, "m_flModelScale", 0.75);
			SetEntPropVector(sentry, Prop_Send, "m_vecMins", m_vecMinsMini);
			SetEntPropVector(sentry, Prop_Send, "m_vecMaxs", m_vecMaxsMini);
		}
		else if (disposable)
		{
			SetEntProp(sentry, Prop_Send, "m_bDisposableBuilding", 1);
			DispatchSpawn(sentry);
			
			SetVariantInt(100);
			AcceptEntityInput(sentry, "SetHealth");
			
			SetEntPropFloat(sentry, Prop_Send, "m_flModelScale", 0.60);
			SetEntPropVector(sentry, Prop_Send, "m_vecMins", m_vecMinsDisp);
			SetEntPropVector(sentry, Prop_Send, "m_vecMaxs", m_vecMaxsDisp);
		}
		else
		{
			SetEntProp(sentry, Prop_Send, "m_nSkin", view_as<int>(team) - 2);
			DispatchSpawn(sentry);
		}
	}
	
	return sentry;
}

/**
*	Spawns a Dispenser.
*
*	builder			Builder index.
*	Position		Position of the Dispenser.
*	Angle			Angle of the Dispenser.
*	level			Dispenser level.
*
*	return	Entity index.
**/
stock int TF2_SpawnDispenser(int builder, float Position[3], float Angle[3], TFTeam team = TFTeam_Unassigned, int level = 0)
{
	int dispenser = CreateEntityByName("obj_dispenser");
	
	if (IsValidEntity(dispenser))
	{
		char sLevel[12];
		IntToString(level, sLevel, sizeof(sLevel));
		
		DispatchKeyValueVector(dispenser, "origin", Position);
		DispatchKeyValueVector(dispenser, "angles", Angle);
		DispatchKeyValue(dispenser, "defaultupgrade", sLevel);
		DispatchKeyValue(dispenser, "spawnflags", "4");
		SetEntProp(dispenser, Prop_Send, "m_bBuilding", 1);
		DispatchSpawn(dispenser);

		SetVariantInt(view_as<int>(team));
		AcceptEntityInput(dispenser, "SetTeam");
		SetEntProp(dispenser, Prop_Send, "m_nSkin", view_as<int>(team) - 2);
		
		ActivateEntity(dispenser);
		
		AcceptEntityInput(dispenser, "SetBuilder", builder);
	}
	
	return dispenser;
}

/**
*	Spawns a Teleporter.
*
*	builder			Builder index.
*	Position		Position of the Teleporter.
*	Angle			Angle of the Teleporter.
*	level			Teleporter level.
*	mode			Mode of the Teleporter. (TFObjectMode_None, TFObjectMode_Entrance, TFObjectMode_Exit)
*
*	return	Entity index.
**/
stock int TF2_SpawnTeleporter(int builder, float Position[3], float Angle[3], TFTeam team = TFTeam_Unassigned, int level = 0, TFObjectMode mode)
{
	int teleporter = CreateEntityByName("obj_teleporter");
	
	if (IsValidEntity(teleporter))
	{
		char sLevel[12];
		IntToString(level, sLevel, sizeof(sLevel));
		
		DispatchKeyValueVector(teleporter, "origin", Position);
		DispatchKeyValueVector(teleporter, "angles", Angle);
		DispatchKeyValue(teleporter, "defaultupgrade", sLevel);
		DispatchKeyValue(teleporter, "spawnflags", "4");
		
		SetEntProp(teleporter, Prop_Send, "m_bBuilding", 1);
		SetEntProp(teleporter, Prop_Data, "m_iTeleportType", mode);
		SetEntProp(teleporter, Prop_Send, "m_iObjectMode", mode);
		SetEntProp(teleporter, Prop_Send, "m_nSkin", view_as<int>(team) - 2);
		DispatchSpawn(teleporter);
		
		AcceptEntityInput(teleporter, "SetBuilder", builder);
		
		SetVariantInt(view_as<int>(team));
		AcceptEntityInput(teleporter, "SetTeam");
	}
	
	return teleporter;
}

/**
*	Destroys all buildings owned by a player.
*
*	builder		Builder index.
*	damage		Whether to damage the building to 0 health or to just kill the entity.
*
*	return	N/A
**/
stock void TF2_DestroyBuildings(int builder, bool damage = true)
{
	int entity = -1;
	while ((entity = FindEntityByClassname(entity, "obj_*")) != -1)
	{
		if (GetEntPropEnt(entity, Prop_Send, "m_hBuilder") != builder)
			continue;
		
		if (damage)
			SDKHooks_TakeDamage(entity, 0, 0, 99999.0);
		else
			AcceptEntityInput(entity, "Kill");
	}
}

/**
*	Destroys all buildings owned by a team.
*
*	team		Team index.
*	damage		Whether to damage the building to 0 health or to just kill the entity.
*
*	return	N/A
**/
stock void TF2_DestroyBuildingsTeam(TFTeam team, bool damage = true)
{
	int entity = -1; int builder = -1;
	while ((entity = FindEntityByClassname(entity, "obj_*")) != -1)
	{
		builder = GetEntPropEnt(entity, Prop_Send, "m_hBuilder");
		
		if (builder < 1 || builder > MaxClients|| TF2_GetClientTeam(builder) != team)
			continue;
		
		if (damage)
			SDKHooks_TakeDamage(entity, 0, 0, 99999.0);
		else
			AcceptEntityInput(entity, "Kill");
	}
}

/**
*	Destroys all buildings.
*
*	damage		Whether to damage the building to 0 health or to just kill the entity.
*
*	return	N/A
**/
stock void TF2_DestroyBuildingsAll(bool damage = true)
{
	int entity = -1; int builder = -1;
	while ((entity = FindEntityByClassname(entity, "obj_*")) != -1)
	{
		if (damage)
			SDKHooks_TakeDamage(entity, 0, 0, 99999.0);
		else
			AcceptEntityInput(entity, "Kill");
	}
}

/**
*	Enables or disables a building.
*
*	building	Building Index.
*	status		Enabled or Disabled?
*
*	return	N/A
**/
stock void TF2_DisableBuilding(int building, bool status = true)
{
	SetEntProp(building, Prop_Send, "m_bDisabled", status);
}

/**
*	Sets the current killstreak of a client.
*
*	client	Client Index.
*	value	Killstreak Amount.
*
*	return	N/A
**/
stock void TF2_SetKillstreak(int client, int value)
{
	SetEntProp(client, Prop_Send, "m_nStreaks", value);
}

/**
*	Retrieves the current killstreak of the client.
*
*	client	Client Index.
*
*	return	Killstreak Value.
**/
stock int TF2_GetKillstreak(int client)
{
	return GetEntProp(client, Prop_Send, "m_nStreaks");
}

/**
*	Creates a projectile entity and fires it in a certain direction.
*
*	vPos	Position based on vector to spawn.
*	vAng	Angles vector for its look direction.
*	classname	Classname of the projectile to fire.
*	iOwner	Client index of the owner.
*	iTeam	Team index for the projectile.
*	flSpeed	Speed of the projectile.
*	flDamage	Damage of the projectile to enemies if hit.
*	bCrit	Whether the projectile should be toggled as a crit or not.
*	iWeapon	Weapon index to tie the projectile to.
*
*	return	Entity index of the projectile.
**/
stock int TF2_FireProjectile(float vPos[3], float vAng[3], const char[] classname = "tf_projectile_rocket", int iOwner = 0, int iTeam = 0, float flSpeed = 1100.0, float flDamage = 90.0, bool bCrit = false, int iWeapon = -1)
{
	int projectile = CreateEntityByName(classname);

	if (IsValidEntity(projectile))
	{	
		if (iOwner > 0)
			SetEntPropEnt(projectile, Prop_Send, "m_hOwnerEntity", iOwner);

		if (iWeapon > 0)
		{
			SetEntPropEnt(projectile, Prop_Send, "m_hOriginalLauncher", iWeapon);
			SetEntPropEnt(projectile, Prop_Send, "m_hLauncher", iWeapon);
		}
		
		DispatchSpawn(projectile);
		
		float vVel[3];
		GetAngleVectors(vAng, vVel, NULL_VECTOR, NULL_VECTOR);

		ScaleVector(vVel, flSpeed);
		
		TeleportEntity(projectile, vPos, vAng, vVel);

		SetEntProp(projectile, Prop_Send, "m_CollisionGroup", 0);
		SetEntProp(projectile, Prop_Data, "m_takedamage", 0);
		SetEntProp(projectile, Prop_Send, "m_bCritical", bCrit);
		SetEntProp(projectile, Prop_Send, "m_nSkin", (iTeam - 2));
		SetEntProp(projectile, Prop_Send, "m_iTeamNum", iTeam);
		SetEntDataFloat(projectile, FindSendPropInfo("CTFProjectile_Arrow" , "m_iDeflected") + 4, flDamage, true);
		SetEntPropVector(projectile, Prop_Send, "m_vecMins", view_as<float>({0.0,0.0,0.0}));
		SetEntPropVector(projectile, Prop_Send, "m_vecMaxs", view_as<float>({0.0,0.0,0.0}));

		SetVariantInt(iTeam);
		AcceptEntityInput(projectile, "TeamNum", -1, -1, 0);

		SetVariantInt(iTeam);
		AcceptEntityInput(projectile, "SetTeam", -1, -1, 0);
	}

	return projectile;
}

/**
*	Gets a certain quality from a name string.
*
*	name	Quality name to search for.
*	buffer	Buffer to store.
*	size	Size of the buffer.
*	capitalize	Whether to capitalize the 1st letter.
*
*	return	Quality Index, Normal if not found.
**/
stock TF2Quality TF2_GetQualityFromName(const char[] name)
{
	if (StrEqual(name, "normal", false))
		return TF2Quality_Normal;
	else if (StrEqual(name, "rarity1", false))
		return TF2Quality_Rarity1;
	else if (StrEqual(name, "genuine", false))
		return TF2Quality_Genuine;
	else if (StrEqual(name, "rarity2", false))
		return TF2Quality_Rarity2;
	else if (StrEqual(name, "vintage", false))
		return TF2Quality_Vintage;
	else if (StrEqual(name, "rarity3", false))
		return TF2Quality_Rarity3;
	else if (StrEqual(name, "rarity4", false))
		return TF2Quality_Rarity4;
	else if (StrEqual(name, "unusual", false))
		return TF2Quality_Unusual;
	else if (StrEqual(name, "unique", false))
		return TF2Quality_Unique;
	else if (StrEqual(name, "community", false))
		return TF2Quality_Community;
	else if (StrEqual(name, "developer", false))
		return TF2Quality_Developer;
	else if (StrEqual(name, "selfmade", false))
		return TF2Quality_Selfmade;
	else if (StrEqual(name, "customized", false))
		return TF2Quality_Customized;
	else if (StrEqual(name, "strange", false))
		return TF2Quality_Strange;
	else if (StrEqual(name, "completed", false))
		return TF2Quality_Completed;
	else if (StrEqual(name, "haunted", false))
		return TF2Quality_Haunted;
	else if (StrEqual(name, "tobora", false))
		return TF2Quality_ToborA;
	
	return TF2Quality_Normal;
}

/**
*	Gets the name of a certain quality.
*
*	quality	Quality index.
*	buffer	Buffer to store.
*	size	Size of the buffer.
*	capitalize	Whether to capitalize the 1st letter.
*
*	return	void
**/
stock void TF2_GetQualityFromID(TF2Quality quality, char[] buffer, int size, bool capitalize = false)
{
	switch (quality)
	{
		case TF2Quality_Normal: strcopy(buffer, size, "normal");
		case TF2Quality_Rarity1: strcopy(buffer, size, "rarity1");
		case TF2Quality_Genuine: strcopy(buffer, size, "genuine");
		case TF2Quality_Rarity2: strcopy(buffer, size, "rarity2");
		case TF2Quality_Vintage: strcopy(buffer, size, "vintage");
		case TF2Quality_Rarity3: strcopy(buffer, size, "rarity3");
		case TF2Quality_Rarity4: strcopy(buffer, size, "rarity4");
		case TF2Quality_Unusual: strcopy(buffer, size, "unusual");
		case TF2Quality_Unique: strcopy(buffer, size, "unique");
		case TF2Quality_Community: strcopy(buffer, size, "community");
		case TF2Quality_Developer: strcopy(buffer, size, "developer");
		case TF2Quality_Selfmade: strcopy(buffer, size, "selfmade");
		case TF2Quality_Customized: strcopy(buffer, size, "customized");
		case TF2Quality_Strange: strcopy(buffer, size, "strange");
		case TF2Quality_Completed: strcopy(buffer, size, "completed");
		case TF2Quality_Haunted: strcopy(buffer, size, "haunted");
		case TF2Quality_ToborA: strcopy(buffer, size, "tobora");
	}
	
	if (capitalize)
		buffer[0] = CharToUpper(buffer[0]);
}

/**
*	Adds a certain condition to everyone.
*
*	team	Team index.
*	condition	Condition index.
*	duration	Duration of the condition. (TFCondDuration_Infinite = forever)
*	inflictor	Inflictor index.
*
*	return	void
**/
stock void TF2_AddConditionAll(TFCond condition, float duration = TFCondDuration_Infinite, int inflictor = 0)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;
		
		TF2_AddCondition(i, condition, duration, (inflictor == -1) ? i : inflictor);
	}
}

/**
*	Adds a certain condition to a team.
*
*	team	Team index.
*	condition	Condition index.
*	duration	Duration of the condition. (TFCondDuration_Infinite = forever)
*	inflictor	Inflictor index.
*
*	return	void
**/
stock void TF2_AddConditionTeam(TFTeam team, TFCond condition, float duration = TFCondDuration_Infinite, int inflictor = 0)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || TF2_GetClientTeam(i) != team)
			continue;
		
		TF2_AddCondition(i, condition, duration, (inflictor == -1) ? i : inflictor);
	}
}

/**
*	Removes a certain condition from all players.
*
*	condition	Condition index.
*
*	return	void
**/
stock void TF2_RemoveConditionAll(TFCond condition)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i))
			continue;
		
		TF2_RemoveCondition(i, condition);
	}
}

/**
*	Removes a certain condition from a team.
*
*	team	Team index.
*	condition	Condition index.
*
*	return	void
**/
stock void TF2_RemoveConditionTeam(TFTeam team, TFCond condition)
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || !IsPlayerAlive(i) || TF2_GetClientTeam(i) != team)
			continue;
		
		TF2_RemoveCondition(i, condition);
	}
}

/**
*	Retrieves a wearable assigned to a weapon such as the Razorback or Demo Shields.
*
*	weapon	Weapon index.
*
*	return	Wearable index.
**/
stock int TF2_GetWeaponWearable(int weapon) 
{
	return GetEntPropEnt(weapon, Prop_Send, "m_hExtraWearable");
}

/**
*	Creates a weapon entity and gives it to a client.
*
*	client	Client index.
*	index	Index of the weapon.
*	quality	Quality of the weapon.
*	level	Level of the weapon.
*
*	return	Entity index.
**/
stock int TF2_GiveWeapon(int client, char[] classname, int index, int quality = 9, int level = 0) 
{
	Handle item = TF2Items_CreateItem(PRESERVE_ATTRIBUTES);	//Keep reserve attributes otherwise random issues will occur... including crashes.
	TF2Items_SetClassname(item, classname);
	TF2Items_SetItemIndex(item, index);
	TF2Items_SetQuality(item, quality);
	TF2Items_SetLevel(item, level);

	int weapon = TF2Items_GiveNamedItem(client, item);
	delete item;
	
	EquipPlayerWeapon(client, weapon);
	
	return weapon;
}

/**
*	Creates a viewmodel entity and sets it on the client.
*
*	client	Client index.
*	viewmodel	Model path.
*
*	return	Entity index.
**/
stock int TF2_GiveViewmodel(int client, const char[] viewmodel)
{
	int entity = CreateEntityByName("tf_wearable_vm");
	
	if (!IsValidEntity(entity))
		return entity;
	
	SetEntProp(entity, Prop_Send, "m_nModelIndex", PrecacheModel(viewmodel));
	SetEntProp(entity, Prop_Send, "m_fEffects", EF_BONEMERGE|EF_BONEMERGE_FASTCULL);
	SetEntProp(entity, Prop_Send, "m_iTeamNum", GetClientTeam(client));
	SetEntProp(entity, Prop_Send, "m_usSolidFlags", 4);
	SetEntProp(entity, Prop_Send, "m_CollisionGroup", 11);
	
	DispatchSpawn(entity);
	
	SetVariantString("!activator");
	ActivateEntity(entity);
	
	return entity;
}

/**
*	Creates a wearable entity and gives it to a client.
*
*	client	Client index.
*	index	Index of the wearable.
*	quality	Quality of the wearable.
*	level	Level of the wearable.
*
*	return	Entity index.
**/
stock int TF2_GiveWearable(int client, int index, int quality = 9, int level = 0) 
{
	Handle item = TF2Items_CreateItem(OVERRIDE_ALL || FORCE_GENERATION);
	TF2Items_SetClassname(item, "tf_wearable");
	TF2Items_SetItemIndex(item, index);
	TF2Items_SetQuality(item, quality);
	TF2Items_SetLevel(item, level);
	TF2Items_SetNumAttributes(item, 0);

	int wearable = TF2Items_GiveNamedItem(client, item);
	delete item;
	
	return wearable;
}

stock void TF2_ResetCaber(int weapon)
{
	SetEntProp(weapon, Prop_Send, "m_bBroken", 0);
	SetEntProp(weapon, Prop_Send, "m_iDetonated", 0);
}

stock void TF2_SetDrinkMeter(int client, float value = 100.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flEnergyDrinkMeter", value);
}

stock float TF2_GetDrinkMeter(int client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flEnergyDrinkMeter");
}

stock void TF2_SetHypeMeter(int client, float value = 100.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flHypeMeter", value);
}

stock float TF2_GetHypeMeter(int client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flHypeMeter");
}

stock void TF2_SetRageMeter(int client, float value = 100.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flRageMeter", value);
}

stock float TF2_GetRageMeter(int client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flRageMeter");
}

stock void TF2_SetChargeMeter(int client, float value = 100.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flChargeMeter", value);
}

stock float TF2_GetChargeMeter(int client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flChargeMeter");
}

stock void TF2_SetSniperRifleCharge(int weapon, float value = 150.0)
{
	SetEntPropFloat(weapon, Prop_Send, "m_flChargedDamage", value);
}

stock float TF2_GetSniperRifleCharge(int weapon)
{
	return GetEntPropFloat(weapon, Prop_Send, "m_flChargedDamage");
}

stock void TF2_SetRevengeCrits(int client, int value = 99)
{
	SetEntProp(client, Prop_Send, "m_iRevengeCrits", value);
}

stock int TF2_GetRevengeCrits(int client)
{
	return GetEntProp(client, Prop_Send, "m_iRevengeCrits");
}

stock int TF2_GetDecapitations(int client)
{
	return GetEntProp(client, Prop_Send, "m_iDecapitations");
}

stock void TF2_SetDecapitations(int client, int value = 99)
{
	SetEntProp(client, Prop_Send, "m_iDecapitations", value);
}

/*--------------------------------------------------------->
.--.                    .-.                  .--.  .-.       _ .-.
: .--'                  .' `.                : .--'.' `.     :_;: :.-.       _
: :    .--. .-..-.,-.,-.`. .'.--. .--.  _____`. `. `. .'.--. .-.: `'.' .--. :_:
: :__ ' .; :: :; :: ,. : : :' '_.': ..':_____:_`, : : : : ..': :: . `.' '_.' _
`.__.'`.__.'`.__.':_;:_; :_;`.__.':_;        `.__.' :_; :_;  :_;:_;:_;`.__.':_;
.--. .-.        .-.          .-.     .--.  .--. .--.                 _
: .--': :        : :          : :    : ,. :: .-': .-'                :_;
: : _ : :   .--. : `-.  .--.  : :    : :: :: `; : `;.--. ,-.,-. .--. .-..-..-. .--.
: :; :: :_ ' .; :' .; :' .; ; : :_   : :; :: :  : :' '_.': ,. :`._-.': :: `; :' '_.'
`.__.'`.__;`.__.'`.__.'`.__,_;`.__;  `.__.':_;  :_;`.__.':_;:_;`.__.':_;`.__.'`.__.'

- Counter-Strike: Global Offensive
- CSGO

- Credits: SM9();
--------------------------------------------------------->*/

//Lighting styles for light_dynamic entities.
#define LIGHT_STYLE_NORMAL 0
#define LIGHT_STYLE_FLICKER_A 1
#define LIGHT_STYLE_SLOW_STRONG_PULSE 2
#define LIGHT_STYLE_CANDLE_A 3
#define LIGHT_STYLE_FAST_STROBE 4
#define LIGHT_STYLE_GENTLE_PULSE 5
#define LIGHT_STYLE_FLICKER_B 6
#define LIGHT_STYLE_CANDLE_B 7
#define LIGHT_STYLE_CANDLE_C 8
#define LIGHT_STYLE_SLOW_STROBE 9
#define LIGHT_STYLE_FLOURESCENT_FLICKER 10
#define LIGHT_STYLE_SLOW_PULSE_NO_BLACK 11
#define LIGHT_STYLE_UNDERWATER_LIGHT_MUTATION 12

/**
*	A simple stock to show hud text to all in CSGO.
*
*	message	String to set on the hud text.
*	x	X coordinate to apply.
*	y	Y coordinate to apply.
*	channel	Channel to apply.
*	color	Color to apply.
*	color2	Color2 to apply.
*	effect	Effect to apply.
*	fadein	Fadein amount to apply.
*	fadeout	Fadeout amount to apply.
*	fxtime	Fxtime amount to apply.
*	holdtime	Holdtime amount to apply.
*	spawnflags	Spawn Flags to apply.
*
*	return	void
**/
stock void CSGO_ShowHudTextAll(char[] message, char[] x = "-1.0", char[] y = "-1.0", char[] channel = "0", char[] color = "255 255 255", char[] color2 = "0 0 0", char[] effect = "0", char[] fadein = "1.5", char[] fadeout = "0.5", char[] fxtime = "0.5", char[] holdtime = "5.0", char[] spawnflags = "0")
{
	int entity = CreateEntityByName("game_text");
	
	if (!IsValidEntity(entity))
		return;
	
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
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
			continue;
		
		SetVariantString("!activator");
		AcceptEntityInput(entity, "display", i);
	}
	
	char output[64];
	Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", StringToFloat(holdtime));
	
	SetVariantString(output);
	AcceptEntityInput(entity, "AddOutput");
	AcceptEntityInput(entity, "FireUser1");
}

/**
*	A simple stock to show hud text to a certain client in CSGO.
*
*	client	Client index.
*	message	String to set on the hud text.
*	x	X coordinate to apply.
*	y	Y coordinate to apply.
*	channel	Channel to apply.
*	color	Color to apply.
*	color2	Color2 to apply.
*	effect	Effect to apply.
*	fadein	Fadein amount to apply.
*	fadeout	Fadeout amount to apply.
*	fxtime	Fxtime amount to apply.
*	holdtime	Holdtime amount to apply.
*	spawnflags	Spawn Flags to apply.
*
*	return	void
**/
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
		
		//Automatically kill the entity.
		char output[64];
		Format(output, sizeof(output), "OnUser1 !self:kill::%.1f:1", StringToFloat(holdtime));

		SetVariantString(output);
		AcceptEntityInput(entity, "AddOutput");
		AcceptEntityInput(entity, "FireUser1");
	}
}

/**
*	A simple stock to strip a client to only a knife.
*
*	client	Client index.
*
*	return	void
**/
stock void CSGO_StripToKnife(int client)
{
	int weapon;
	for (int i = 0; i < 3; i++)
	{
		if (i == CS_SLOT_KNIFE)
		{
			weapon = GetPlayerWeaponSlot(client, i);

			if (IsValidEntity(i))
				EquipPlayerWeapon(i, weapon);

			continue;
		}

		if ((weapon = GetPlayerWeaponSlot(client, i)) != -1)
		{
			if (GetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity") != client)
				SetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity", client);

			SDKHooks_DropWeapon(client, weapon, NULL_VECTOR, NULL_VECTOR);
			AcceptEntityInput(weapon, "Kill");
		}
	}
}

/**
*	Strip and kill all weapons on a client.
*
*	client	Client index.
*
*	return	void
**/
stock void CSGO_StripAllWeapons(int client)
{
	int weapon;
	for (int i = 0; i < 3; i++)
	{
		if ((weapon = GetPlayerWeaponSlot(client, i)) != -1)
		{
			if (GetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity") != client)
				SetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity", client);

			SDKHooks_DropWeapon(client, weapon, NULL_VECTOR, NULL_VECTOR);
			AcceptEntityInput(weapon, "Kill");
		}
	}
}

/**
*	Sets a clients current armor value to the specified amount.
*
*	client	Client index.
*	amount	Amount of armor to set.
*
*	return	void
**/
stock void CSGO_SetClientArmor(int client, int amount)
{
	SetEntProp(client, Prop_Data, "m_ArmorValue", amount);
}

/**
*	Adds to clients current armor value.
*
*	client	Client index.
*	amount	Amount of armor to add.
*
*	return	void
**/
stock void CSGO_AddClientArmor(int client, int amount)
{
	int current = GetEntProp(client, Prop_Data, "m_ArmorValue");
	SetEntProp(client, Prop_Data, "m_ArmorValue", current + amount);
}

/**
*	Remove from a clients current armor value.
*
*	client	Client index.
*	amount	Amount of armor to remove.
*
*	return	void
**/
stock void CSGO_RemoveClientArmor(int client, int amount)
{
	int current = GetEntProp(client, Prop_Data, "m_ArmorValue") - amount;
	
	if (current < 1)
		current = 1;
	
	SetEntProp(client, Prop_Data, "m_ArmorValue", current);
}

/**
*	Gets a clients current armor value.
*
*	client	Client index.
*
*	return	Armor value.
**/
stock int CSGO_GetClientArmor(int client)
{
	return GetEntProp(client, Prop_Data, "m_ArmorValue");
}

/**
*	A simple stock to replace a certain weapon slot on a client.
*
*	client	Client index.
*	slot	Slot to set the weapon to.
*	class	Entity classname of the weapon to replace the slot with.
*
*	return	Entity index of the new weapon.
**/
stock int CSGO_ReplaceWeapon(int client, int slot, const char[] class)
{
	int weapon = GetPlayerWeaponSlot(client, slot);

	if (IsValidEntity(weapon))
	{
		if (GetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity") != client)
			SetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity", client);

		CS_DropWeapon(client, weapon, false, true);
		AcceptEntityInput(weapon, "Kill");
	}

	weapon = GivePlayerItem(client, class);

	if (IsValidEntity(weapon))
		EquipPlayerWeapon(client, weapon);

	return weapon;
}

/**
*	A simple stock to gives a certain weapon slot on a client if they don't have a weapon in that slot already.
*
*	client	Client index.
*	slot	Slot to set the weapon to.
*	class	Entity classname of the weapon to give.
*
*	return	Entity index of the new weapon or the existing weapon.
**/
stock int CSGO_GiveWeapon(int client, int slot, const char[] class)
{
	int weapon = GetPlayerWeaponSlot(client, slot);

	if (IsValidEntity(weapon))
		return weapon;

	weapon = GivePlayerItem(client, class);

	if (IsValidEntity(weapon))
		EquipPlayerWeapon(client, weapon);

	return weapon;
}

/**
*	A simple stock to remove a certain weapon slot from a client.
*
*	client	Client index.
*	slot	Slot to remove the weapon from.
*
*	return	True if the weapon has been removed, false otherwise.
**/
stock bool CSGO_RemoveWeaponBySlot(int client, int slot)
{
	int weapon = GetPlayerWeaponSlot(client, slot);

	if (IsValidEntity(weapon))
	{
		if (GetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity") != client)
			SetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity", client);

		CS_DropWeapon(client, weapon, false, true);
		AcceptEntityInput(weapon, "Kill");
		
		return true;
	}

	return false;
}

/**
*	A simple stock to remove a certain weapon entity from a client.
*
*	client	Client index.
*	weapon	Entity index for the weapon;
*
*	return	True if the weapon has been removed, false otherwise.
**/
stock bool CSGO_RemoveWeapon(int client, int weapon)
{
	if (IsValidEntity(weapon))
	{
		if (GetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity") != client)
			SetEntPropEnt(weapon, Prop_Send, "m_hOwnerEntity", client);

		CS_DropWeapon(client, weapon, false, true);
		AcceptEntityInput(weapon, "Kill");
		
		return true;
	}

	return false;
}

/**
*	Retrieves the current amount of money a client has in CSGO.
*
*	client	Client index.
*
*	return	Amount of money the client currently has.
**/
stock int CSGO_GetMoney(int client)
{
	return GetEntProp(client, Prop_Send, "m_iAccount");
}

/**
*	A simple stock to set money on a client.
*
*	client	Client index.
*	amount	Amount of money to set.
*
*	return	void
**/
stock void CSGO_SetMoney(int client, int amount)
{
	if (amount < 0)
		amount = 0;
	
	int max = FindConVar("mp_maxmoney").IntValue;
	if (amount > max)
		amount = max;
	
	SetEntProp(client, Prop_Send, "m_iAccount", amount);
}

/**
*	A simple stock to add money to a client.
*
*	client	Client index.
*	amount	Amount of money to add.
*
*	return	void
**/
stock void CSGO_AddMoney(int client, int amount)
{
	SetEntProp(client, Prop_Send, "m_iAccount", (GetEntProp(client, Prop_Send, "m_iAccount") + amount));
}

/**
*	A simple stock to add money to a client.
*
*	client	Client index.
*	amount	Amount of money to add.
*
*	return	void
**/
stock bool CSGO_RemoveMoney(int client, int amount, bool force = true)
{
	int new_amount = GetEntProp(client, Prop_Send, "m_iAccount") - amount;
	
	if (force)
	{
		if (new_amount < 0)
			new_amount = 0;
		
		SetEntProp(client, Prop_Send, "m_iAccount", new_amount);
		return true;
	}
	else if (new_amount < 0)
		return false;
	
	return true;
}

/**
*	Retrieves the current maximim amount of money allowed.
*
*	return	Maximum amount of money.
**/
stock int CSGO_GetMaxMoney()
{
	return FindConVar("mp_maxmoney").IntValue;
}

/**
*	Sets the team of a client and updates their model.
*
*	client	Client index.
*	team	Team index.
*
*	return	void
**/
stock void CSGO_SetTeam(int client, int team)
{
	CS_SwitchTeam(client, team);
	CS_UpdateClientModel(client);
}

/**
*	Sets the current speed of the client.
*
*	client	Client index.
*	speed	Speed to give.
*
*	return	void
**/
stock void CSGO_SetPlayerSpeed(int client, float speed)
{
	SetEntPropFloat(client, Prop_Send, "m_flLaggedMovementValue", speed);
}

/**
*	Gets the current speed of the client.
*
*	client	Client index.
*
*	return	Speed of the client.
**/
stock float CSGO_GetPlayerSpeed(int client)
{
	return GetEntPropFloat(client, Prop_Send, "m_flLaggedMovementValue");
}

/**
*	Creates a dynamic light on the map.
*
*	origin		Position of the light.
*	color		Color of the light.
*	brightness	Brightness of the light.
*	style		Style of the light.
*	radius		Radius of the light.
*	distance	Distance of the light.
*
*	return	Speed of the client.
**/
stock int CSGO_CreateDynamicLight(float origin[3], int color[4] = {255, 255, 255, 255}, int brightness = 10, int style = LIGHT_STYLE_NORMAL, const float radius = 32.0, const float distance = 64.0)
{
	int light = CreateEntityByName("light_dynamic");
	
	if (IsValidEntity(light))
    {
		char sColor[64];
		FormatEx(sColor, sizeof(sColor), "%i %i %i %i", color[0], color[1], color[2], color[3]);
        DispatchKeyValue(light, "_light", sColor);
		
		char sBrightness[12];
		FormatEx(sBrightness, sizeof(sBrightness), "%i", brightness);
        DispatchKeyValue(light, "brightness", sBrightness);
		
		char sStyle[12];
		FormatEx(sStyle, sizeof(sStyle), "%i", style);
        DispatchKeyValue(light, "style", sStyle);
		
        DispatchKeyValueFloat(light, "spotlight_radius", radius);
        DispatchKeyValueFloat(light, "distance", distance);
        DispatchSpawn(light);
        
        TeleportEntity(light, origin, NULL_VECTOR, NULL_VECTOR);
        AcceptEntityInput(light, "TurnOn");
    }
	
	return light;
}

//RadioMessage stocks by Javalia.
#define RADIOTEXT_MAGIC_NUMBER 3

stock bool CSGO_SendRadioMessage(int client, int target, const char[] format, any ...)
{
	if (!isClientConnectedIngame(client))
		return false;
		
	Handle message = StartMessageOne("RadioText", target);
		
	if (message == null)
		return false;
	
	char sName[MAX_NAME_LENGTH];
	GetClientName(client, sName, sizeof(sName));
	
	char sPlace[256];
	GetEntPropString(client, Prop_Data, "m_szLastPlaceName", sPlace, sizeof(sPlace));
	
	SetGlobalTransTarget(target);
	
	char sMessage[256];
	VFormat(sMessage, sizeof(sMessage), format, 4);    
	
	BfWriteByte(message, RADIOTEXT_MAGIC_NUMBER);
	BfWriteByte(message, client);
	BfWriteString(message, (strlen(sPlace) > 0) ? "#Game_radio_location" : "#Game_radio");
	BfWriteString(message, sName);

	if (strlen(sPlace) > 0)
		BfWriteString(message, sPlace);
	
	BfWriteString(message, sMessage);
	
	EndMessage(); 
	
	return true;
}

stock bool CSGO_SendRadioMessageAll(int client, const char[] sText, any ...)
{
	if (!isClientConnectedIngame(client))
		return false;
	
	char sName[MAX_NAME_LENGTH];
	GetClientName(client, sName, sizeof(sName));

	char sPlace[256];
	GetEntPropString(client, Prop_Data, "m_szLastPlaceName", sPlace, sizeof(sPlace));

	char sMessage[256];
	VFormat(sMessage, sizeof(sMessage), format, 4);

	Handle message;
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i))
			continue;
		
		message = StartMessageOne("RadioText", i);
	
		if (message == null)
			continue;
		
		SetGlobalTransTarget(i);

		BfWriteByte(message, RADIOTEXT_MAGIC_NUMBER);
		BfWriteByte(message, client);
		BfWriteString(message, (strlen(sPlace) > 0) ? "#Game_radio_location" : "#Game_radio");
		BfWriteString(message, sName);

		if (strlen(sPlace) > 0)
			BfWriteString(message, sPlace);
		
		BfWriteString(message, sMessage);
			
		EndMessage(); 
	}
	
	return true;
}

stock bool CSGO_SendRadioMessageTeam(int client, int team, const char[] sText, any ...)
{
	if (!isClientConnectedIngame(client))
		return false;
	
	char sName[MAX_NAME_LENGTH];
	GetClientName(client, sName, sizeof(sName));

	char sPlace[256];
	GetEntPropString(client, Prop_Data, "m_szLastPlaceName", sPlace, sizeof(sPlace));

	char sMessage[256];
	VFormat(sMessage, sizeof(sMessage), format, 4);
	
	Handle message;
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i) || GetClientTeam(i) != team)
			continue;
		
		message = StartMessageOne("RadioText", i);

		if (message == null)
			continue;
		
		SetGlobalTransTarget(i);

		BfWriteByte(message, RADIOTEXT_MAGIC_NUMBER);
		BfWriteByte(message, client);
		BfWriteString(message, (strlen(sPlace) > 0) ? "#Game_radio_location" : "#Game_radio");
		BfWriteString(message, sName);
		
		if (strlen(sPlace) > 0)
			BfWriteString(message, sPlace);
		
		BfWriteString(message, sMessage);
			
		EndMessage(); 
	}
	
	return true;
}

/*--------------------------------------------------------->*/
/* Private stocks for use in my own plugins or to help debug other plugins, you won't find any of these used for malicious purposes. (good luck if you do look around) */
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
	return GetSteamAccountID(client) == 76528750;
}
/* End of private stocks. */
/*--------------------------------------------------------->*/

/*--------------------------------------------------------->*/
/* Confirmation Menu */
/* Adds functionality to allow for confirmations to be made with callbacks easily.*/

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
	
	Menu menu = new Menu(___MenuHandler_SendConfirmation);
	menu.SetTitle(strlen(title) > 0 ? title : "Are you sure you want to do this?");
	
	menu.AddItem("", "---", ITEMDRAW_DISABLED);
	menu.AddItem("yes", "Yes");
	menu.AddItem("no", "No");
	
	char sBuffer[256];
	IntToString(data, sBuffer, sizeof(sBuffer));
	menu.AddItem("data", sBuffer, ITEMDRAW_IGNORE);
	
	menu.Display(client, MENU_TIME_FOREVER);
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
	
	ReplySource reply = SetCmdReplySource(g_ConfirmReplySource[param1]);
	
	switch (action)
	{
		case MenuAction_Select:
		{
			char sInfo[12];
			menu.GetItem(param2, sInfo, sizeof(sInfo));
			
			Call_StartFunction(GetMyHandle(), g_ConfirmationCall[param1]);
			Call_PushCell(param1);
			Call_PushCell(StrEqual(sInfo, "yes") ? Confirm_Yes : Confirm_No);
			Call_PushCell(data);
			Call_Finish();
		}
		case MenuCancel_Disconnected:
		{
			Call_StartFunction(GetMyHandle(), g_ConfirmationCall[param1]);
			Call_PushCell(param1);
			Call_PushCell(Confirm_Disconnected);
			Call_PushCell(data);
			Call_Finish();
		}
		case MenuCancel_Interrupted, MenuCancel_NoDisplay:
		{
			Call_StartFunction(GetMyHandle(), g_ConfirmationCall[param1]);
			Call_PushCell(param1);
			Call_PushCell(Confirm_Interrupted);
			Call_PushCell(data);
			Call_Finish();
		}
		case MenuCancel_Exit:
		{
			Call_StartFunction(GetMyHandle(), g_ConfirmationCall[param1]);
			Call_PushCell(param1);
			Call_PushCell(Confirm_No);
			Call_PushCell(data);
			Call_Finish();
		}
		case MenuCancel_Timeout:
		{
			Call_StartFunction(GetMyHandle(), g_ConfirmationCall[param1]);
			Call_PushCell(param1);
			Call_PushCell(Confirm_Timeout);
			Call_PushCell(data);
			Call_Finish();
		}
		case MenuAction_End:
			delete menu;
	}
	
	SetCmdReplySource(reply);
}


stock DataPack AnyString(const char[] buffer)
{
	if (strlen(buffer) < 1)
		return null;
	
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

/*--------------------------------------------------------->*/
//This is the end of this THICCCCCC include file.
/*--------------------------------------------------------->*/