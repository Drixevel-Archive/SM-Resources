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
**/

//Because I'm too stupid at remembering how to do this properly.
//Apply Bit: bitbuffer |= BIT_1;
//Apply Multi Bit: bitbuffer |= (BIT_1 | BIT_2);
//Remove Bit: bitbuffer &= ~BIT_2;
//Remove Multi Bit: bitbuffer &= ~(BIT_1 | BIT_2);
//
//Damage = MaxDmg - (Range - StartFalloff) / (EndFalloff - StartFalloff) * (MaxDmg - MinDmg)

#if defined _sourcemod_misc_included
#endinput
#endif
#define _sourcemod_misc_included

#undef REQUIRE_EXTENSIONS
#tryinclude <sdktools>
#tryinclude <sdkhooks>
#tryinclude <tf2_stocks>
#tryinclude <cstrike>
#tryinclude <regex>
#tryinclude <clientprefs>
#tryinclude <tf2items>
#tryinclude <steamworks>
#define REQUIRE_EXTENSIONS

#undef REQUIRE_PLUGIN
#tryinclude <tf2attributes>
#define REQUIRE_PLUGIN

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

/*
* Checks whether a client is valid or not.
* This is safe but it's best to use the proper checks where you can instead.
*
* client	Client index.
*
* return	True if valid, false otherwise.
*/
stock bool IsValidClient(int client)
{
	return client >= 1 && client <= MaxClients && IsClientInGame(client) && !IsClientSourceTV(client);
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
* Kicks a client based on the specified SteamID if it exists on the server.
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
* Retrieves a client with a specific steamid found if the server if they exist.
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
* Retrieves a client with a specific accountid found if the server if they exist.
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
		int iOffset = FindDataMainfo(client, "m_iAmmo") + (GetEntProp(weapon, Prop_Data, "m_iPrimaryAmmoType") * 4);
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

	return clients[GetRandomInt(0, amount)];
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

stock void GetEntityAngle(int entity, float[3] angles)
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

stock bool GetEntityHealth(int entity)
{
	return GetEntProp(entity, Prop_Data, "m_iHealth");
}

stock bool GetEntityMaxHealth(int entity)
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
//MYSQL / SQLITE

stock bool SQL_FetchBool(DBResultSet results, int field, DBResult &status = DBVal_Error)
{
	return view_as<bool>(results.FetchInt(field, status));
}

stock void SQL_SendQuery(Database& database, const char[] query, DBPriority prio = DBPrio_Normal)
{
	DataPack pack = new DataPack();
	pack.WriteString(query);

	database.Query(TQuery_Void, query, pack, prio);
}

stock void SQL_SendQuery2(Database& database, DBPriority prio = DBPrio_Normal, const char[] format, any ...)
{
	char query[8192];
	VFormat(query, sizeof(query), format, 4);

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

//TF2 Damage Types (Found in some CW3 Plugins)
#define TF_DMG_BULLET (1 << 1) // 2
#define TF_DMG_BLEED (1 << 2) // 4
#define TF_DMG_BLAST (1 << 6) // 64
#define TF_DMG_CRIT (1 << 20) // 1048576
#define TF_DMG_UNKNOWN_1 (1 << 11) // 2048
#define TF_DMG_FIRE (1 << 24) // 16777216
#define TF_DMG_AFTERBURN TF_DMG_UNKNOWN_1 | (1 << 3) // 2048 + 8 = 2056

#define TF_DMG_FLAMETHROWER TF_DMG_UNKNOWN_1 | TF_DMG_FIRE // 2048 + 16777216 = 16779264

#define TF_DMG_MELEE (1 << 27) | (1 << 12) | (1 << 7)    // 134217728 + 4096 + 128 = 134221952
#define TF_DMG_MELEE_CRIT TF_DMG_MELEE | TF_DMG_CRIT // 134221952 + 1048576 = 135270528

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
	else
		buffer[0] = CharToLower(buffer[0]);
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
	else
		buffer[0] = CharToLower(buffer[0]);
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
stock void TF2_ForceRoundWin(TFTeam team = TFTeam_Unassigned, bool map_valid = true)
{
	if (map_valid && !IsValidEntity(0))
		return;
	
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

stock void TF2_ForceWin(TFTeam team = TFTeam_Unassigned)
{
	int iFlags = GetCommandFlags("mp_forcewin");
	SetCommandFlags("mp_forcewin", iFlags &= ~FCVAR_CHEAT);
	ServerCommand("mp_forcewin %i", view_as<int>(team));
	SetCommandFlags("mp_forcewin", iFlags);
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
	
	if (!IsValidEntity(secondary) || !HasEntProp(secondary, Prop_Send, "m_flChargeLevel"))
		return;
	
	float set = amount;
	
	if (cap && set > 1.00)
		set = 1.00;
	else if (set < 0.0)
		set = 0.0;
	
	SetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel", set);
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
	int secondary = GetPlayerWeaponSlot(client, 1);
	
	if (!IsValidEntity(secondary) || !HasEntProp(secondary, Prop_Send, "m_flChargeLevel"))
		return;
	
	float set = GetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel") + amount;
	
	if (cap && set > 1.00)
		set = 1.00;
	
	SetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel", set);
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
	int secondary = GetPlayerWeaponSlot(client, 1);
	
	if (!IsValidEntity(secondary) || !HasEntProp(secondary, Prop_Send, "m_flChargeLevel"))
		return;
	
	float set = GetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel") - amount;
	
	if (set < 0.0)
		set = 0.0;
	
	SetEntPropFloat(secondary, Prop_Send, "m_flChargeLevel", set);
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

	if (!IsValidEntity(weapon) || weapon != GetEntPropEnt(client, Prop_Send, "m_hActiveWeapon"))
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
	DamageRadius(origin, radius, damage, attacker, inflictor, damagetype, weapon);
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
stock void TF2_SetPlayerHealth(int client, int amount, float overheal = 1.5, bool additive = false, bool fireevent = true, int healer = -1)
{
	int maxhealth = GetEntProp(GetPlayerResourceEntity(), Prop_Send, "m_iMaxHealth", _, client);
	int actualmax = ((maxhealth == -1 || maxhealth == 80896) ? GetEntProp(client, Prop_Data, "m_iMaxHealth") : maxhealth);
	
	int iHealth = GetClientHealth(client);
	int iNewHealth = amount;
	int iMax = additive ? (actualmax + RoundFloat(overheal)) : RoundFloat(float(actualmax) * overheal);

	if (iHealth < iMax)
	{
		if (iNewHealth < 1)
			iNewHealth = 1;
		else if (iNewHealth > iMax)
			iNewHealth = iMax;

		if (fireevent)
		{
			int value = iNewHealth - iHealth;
			int userid = GetClientUserId(client);

			Event event = CreateEvent("player_healed", true);
			event.SetBool("sourcemod", true);
			event.SetInt("patient", userid);
			event.SetInt("healer", healer > 0 && IsClientInGame(healer) ? GetClientUserId(healer) : userid);
			event.SetInt("amount", value);
			event.Fire();

			event = CreateEvent("player_healonhit", true);
			event.SetBool("sourcemod", true);
			event.SetInt("amount", value);
			event.SetInt("entindex", client);
			event.Fire();
		}

		SetEntityHealth(client, iNewHealth);
	}
}

/**
*	Add to a players health while applying TF2 health logic.
*
*	client	Client index.
*	amount	Amount of health to add.
*	overheal	Overheal amount to offset.
*	additive	Whether to add overheal or multiply it.
*	event	Fire the health gain event.
*
*	return	void
**/
stock void TF2_AddPlayerHealth(int client, int amount, float overheal = 1.5, bool additive = false, bool fireevent = true, int healer = -1)
{
	int maxhealth = GetEntProp(GetPlayerResourceEntity(), Prop_Send, "m_iMaxHealth", _, client);
	int actualmax = ((maxhealth == -1 || maxhealth == 80896) ? GetEntProp(client, Prop_Data, "m_iMaxHealth") : maxhealth);
	
	int iHealth = GetClientHealth(client);
	int iNewHealth = iHealth + amount;
	int iMax = additive ? (actualmax + RoundFloat(overheal)) : RoundFloat(float(actualmax) * overheal);

	if (iHealth < iMax)
	{
		if (iNewHealth < 1)
			iNewHealth = 1;
		else if (iNewHealth > iMax)
			iNewHealth = iMax;

		if (fireevent)
		{
			int value = iNewHealth - iHealth;
			int userid = GetClientUserId(client);

			Event event = CreateEvent("player_healed", true);
			event.SetBool("sourcemod", true);
			event.SetInt("patient", userid);
			event.SetInt("healer", healer > 0 && IsClientInGame(healer) ? GetClientUserId(healer) : userid);
			event.SetInt("amount", value);
			event.Fire();

			event = CreateEvent("player_healonhit", true);
			event.SetBool("sourcemod", true);
			event.SetInt("amount", value);
			event.SetInt("entindex", client);
			event.Fire();
		}

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
stock void TF2_RemovePlayerHealth(int client, int amount, float overheal = 1.5, bool additive = false, bool fireevent = true, int healer = -1)
{
	int maxhealth = GetEntProp(GetPlayerResourceEntity(), Prop_Send, "m_iMaxHealth", _, client);
	int actualmax = ((maxhealth == -1 || maxhealth == 80896) ? GetEntProp(client, Prop_Data, "m_iMaxHealth") : maxhealth);
	
	int iHealth = GetClientHealth(client);
	int iNewHealth = iHealth - amount;
	int iMax = additive ? (actualmax + RoundFloat(overheal)) : RoundFloat(float(actualmax) * overheal);

	if (iHealth < iMax)
	{
		if (iNewHealth < 1)
		{
			if (fireevent)
			{
				int value = iNewHealth - iHealth;
				int userid = GetClientUserId(client);

				Event event = CreateEvent("player_healed", true);
				event.SetBool("sourcemod", true);
				event.SetInt("patient", userid);
				event.SetInt("healer", healer > 0 && IsClientInGame(healer) ? GetClientUserId(healer) : userid);
				event.SetInt("amount", value);
				event.Fire();

				event = CreateEvent("player_healonhit", true);
				event.SetBool("sourcemod", true);
				event.SetInt("amount", value);
				event.SetInt("entindex", client);
				event.Fire();
			}
			
			ForcePlayerSuicide(client);
			return;
		}
		
		if (iNewHealth > iMax)
			iNewHealth = iMax;

		if (fireevent)
		{
			int value = iNewHealth - iHealth;
			int userid = GetClientUserId(client);

			Event event = CreateEvent("player_healed", true);
			event.SetBool("sourcemod", true);
			event.SetInt("patient", userid);
			event.SetInt("healer", healer > 0 && IsClientInGame(healer) ? GetClientUserId(healer) : userid);
			event.SetInt("amount", value);
			event.Fire();

			event = CreateEvent("player_healonhit", true);
			event.SetBool("sourcemod", true);
			event.SetInt("amount", value);
			event.SetInt("entindex", client);
			event.Fire();
		}

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

stock void TF2Attrib_SetByDefIndex_Weapons(int client, int weapon = -1, int index, float value, bool invert = false)
{
	if (weapon != -1 && IsValidEntity(weapon))
	{
		TF2Attrib_SetByDefIndex(weapon, index, value);
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
			TF2Attrib_SetByDefIndex(weapon2, index, value);
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

stock void TF2Attrib_RemoveByDefIndex_Weapons(int client, int weapon = -1, int index)
{
	if (weapon != -1 && IsValidEntity(weapon))
	{
		TF2Attrib_RemoveByDefIndex(weapon, index);
		return;
	}

	int weapon2;
	for (int i = 0; i < 6; i++)
	{
		weapon2 = GetPlayerWeaponSlot(client, i);

		if (IsValidEntity(weapon2))
			TF2Attrib_RemoveByDefIndex(weapon2, index);
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
	else
		buffer[0] = CharToLower(buffer[0]);
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

	int m_aHealers = FindSendPropInfo("CTFPlayer", "m_nNumHealers") + 12;
	Address m_Shared = GetEntityAddress(client) + view_as<Address>(m_aHealers);
	Address aHealers = view_as<Address>(LoadFromAddress(m_Shared, NumberType_Int32));

	return LoadFromAddress(aHealers + view_as<Address>(index * 0x24), NumberType_Int32) & 0xFFF;
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
	if (client == 0 || client > MaxClients || !IsClientInGame(client) || !IsPlayerAlive(client) || healer == 0 || healer > MaxClients || !IsClientInGame(healer) || !IsPlayerAlive(healer) || TF2_GetPlayerClass(healer) != TFClass_Medic)
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
*	destroy		Whether to destroy the building or to just kill the entity.
*
*	return	N/A
**/
stock void TF2_DestroyBuildings(int builder, bool destroy = true)
{
	int entity = -1;
	while ((entity = FindEntityByClassname(entity, "obj_*")) != -1)
	{
		if (GetEntPropEnt(entity, Prop_Send, "m_hBuilder") != builder)
			continue;
		
		if (destroy)
			SDKHooks_TakeDamage(entity, 0, 0, 99999.0);
		else
			AcceptEntityInput(entity, "Kill");
	}
}

/**
*	Destroys all buildings owned by a team.
*
*	team		Team index.
*	destroy		Whether to destroy the building or to just kill the entity.
*
*	return	N/A
**/
stock void TF2_DestroyBuildingsTeam(TFTeam team, bool destroy = true)
{
	int entity = -1; int builder = -1;
	while ((entity = FindEntityByClassname(entity, "obj_*")) != -1)
	{
		builder = GetEntPropEnt(entity, Prop_Send, "m_hBuilder");
		
		if (builder < 1 || builder > MaxClients|| TF2_GetClientTeam(builder) != team)
			continue;
		
		if (destroy)
			SDKHooks_TakeDamage(entity, 0, 0, 99999.0);
		else
			AcceptEntityInput(entity, "Kill");
	}
}

/**
*	Destroys all buildings.
*
*	destroy		Whether to destroy the building or to just kill the entity.
*
*	return	N/A
**/
stock void TF2_DestroyBuildingsAll(bool destroy = true)
{
	int entity = -1; int builder = -1;
	while ((entity = FindEntityByClassname(entity, "obj_*")) != -1)
	{
		if (destroy)
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
		
		if (HasEntProp(projectile, Prop_Send, "m_bCritical"))
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
	else
		buffer[0] = CharToLower(buffer[0]);
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

stock void TF2_GetConditionName(TFCond condition, char[] buffer, int size, bool capitalize = false)
{
	switch (condition)
	{
		case TFCond_Slowed: strcopy(buffer, size, "Slowed");
		case TFCond_Zoomed: strcopy(buffer, size, "Zoomed");
		case TFCond_Disguising: strcopy(buffer, size, "Disguising");
		case TFCond_Disguised: strcopy(buffer, size, "Disguised");
		case TFCond_Cloaked: strcopy(buffer, size, "Cloaked");
		case TFCond_Ubercharged: strcopy(buffer, size, "Ubercharged");
		case TFCond_TeleportedGlow: strcopy(buffer, size, "TeleportedGlow");
		case TFCond_Taunting: strcopy(buffer, size, "Taunting");
		case TFCond_UberchargeFading: strcopy(buffer, size, "UberchargeFading");
		//case TFCond_Unknown1: strcopy(buffer, size, "Unknown1");
		case TFCond_CloakFlicker: strcopy(buffer, size, "CloakFlicker");
		case TFCond_Teleporting: strcopy(buffer, size, "Teleporting");
		case TFCond_Kritzkrieged: strcopy(buffer, size, "Kritzkrieged");
		//case TFCond_Unknown2: strcopy(buffer, size, "Unknown2");
		case TFCond_TmpDamageBonus: strcopy(buffer, size, "TmpDamageBonus");
		case TFCond_DeadRingered: strcopy(buffer, size, "DeadRingered");
		case TFCond_Bonked: strcopy(buffer, size, "Bonked");
		case TFCond_Dazed: strcopy(buffer, size, "Dazed");
		case TFCond_Buffed: strcopy(buffer, size, "Buffed");
		case TFCond_Charging: strcopy(buffer, size, "Charging");
		case TFCond_DemoBuff: strcopy(buffer, size, "DemoBuff");
		case TFCond_CritCola: strcopy(buffer, size, "CritCola");
		case TFCond_InHealRadius: strcopy(buffer, size, "InHealRadius");
		case TFCond_Healing: strcopy(buffer, size, "Healing");
		case TFCond_OnFire: strcopy(buffer, size, "OnFire");
		case TFCond_Overhealed: strcopy(buffer, size, "Overhealed");
		case TFCond_Jarated: strcopy(buffer, size, "Jarated");
		case TFCond_Bleeding: strcopy(buffer, size, "Bleeding");
		case TFCond_DefenseBuffed: strcopy(buffer, size, "DefenseBuffed");
		case TFCond_Milked: strcopy(buffer, size, "Milked");
		case TFCond_MegaHeal: strcopy(buffer, size, "MegaHeal");
		case TFCond_RegenBuffed: strcopy(buffer, size, "RegenBuffed");
		case TFCond_MarkedForDeath: strcopy(buffer, size, "MarkedForDeath");
		case TFCond_NoHealingDamageBuff: strcopy(buffer, size, "NoHealingDamageBuff");
		case TFCond_SpeedBuffAlly: strcopy(buffer, size, "SpeedBuffAlly");
		case TFCond_HalloweenCritCandy: strcopy(buffer, size, "HalloweenCritCandy");
		case TFCond_CritCanteen: strcopy(buffer, size, "CritCanteen");
		case TFCond_CritDemoCharge: strcopy(buffer, size, "CritDemoCharge");
		case TFCond_CritHype: strcopy(buffer, size, "CritHype");
		case TFCond_CritOnFirstBlood: strcopy(buffer, size, "CritOnFirstBlood");
		case TFCond_CritOnWin: strcopy(buffer, size, "CritOnWin");
		case TFCond_CritOnFlagCapture: strcopy(buffer, size, "CritOnFlagCapture");
		case TFCond_CritOnKill: strcopy(buffer, size, "CritOnKill");
		case TFCond_RestrictToMelee: strcopy(buffer, size, "RestrictToMelee");
		case TFCond_DefenseBuffNoCritBlock: strcopy(buffer, size, "DefenseBuffNoCritBlock");
		case TFCond_Reprogrammed: strcopy(buffer, size, "Reprogrammed");
		case TFCond_CritMmmph: strcopy(buffer, size, "CritMmmph");
		case TFCond_DefenseBuffMmmph: strcopy(buffer, size, "DefenseBuffMmmph");
		case TFCond_FocusBuff: strcopy(buffer, size, "FocusBuff");
		case TFCond_DisguiseRemoved: strcopy(buffer, size, "DisguiseRemoved");
		case TFCond_MarkedForDeathSilent: strcopy(buffer, size, "MarkedForDeathSilent");
		case TFCond_DisguisedAsDispenser: strcopy(buffer, size, "DisguisedAsDispenser");
		case TFCond_Sapped: strcopy(buffer, size, "Sapped");
		case TFCond_UberchargedHidden: strcopy(buffer, size, "UberchargedHidden");
		case TFCond_UberchargedCanteen: strcopy(buffer, size, "UberchargedCanteen");
		case TFCond_HalloweenBombHead: strcopy(buffer, size, "HalloweenBombHead");
		case TFCond_HalloweenThriller: strcopy(buffer, size, "HalloweenThriller");
		case TFCond_RadiusHealOnDamage: strcopy(buffer, size, "RadiusHealOnDamage");
		case TFCond_CritOnDamage: strcopy(buffer, size, "CritOnDamage");
		case TFCond_UberchargedOnTakeDamage: strcopy(buffer, size, "UberchargedOnTakeDamage");
		case TFCond_UberBulletResist: strcopy(buffer, size, "UberBulletResist");
		case TFCond_UberBlastResist: strcopy(buffer, size, "UberBlastResist");
		case TFCond_UberFireResist: strcopy(buffer, size, "UberFireResist");
		case TFCond_SmallBulletResist: strcopy(buffer, size, "SmallBulletResist");
		case TFCond_SmallBlastResist: strcopy(buffer, size, "SmallBlastResist");
		case TFCond_SmallFireResist: strcopy(buffer, size, "SmallFireResist");
		case TFCond_Stealthed: strcopy(buffer, size, "Stealthed");
		case TFCond_MedigunDebuff: strcopy(buffer, size, "MedigunDebuff");
		case TFCond_StealthedUserBuffFade: strcopy(buffer, size, "StealthedUserBuffFade");
		case TFCond_BulletImmune: strcopy(buffer, size, "BulletImmune");
		case TFCond_BlastImmune: strcopy(buffer, size, "BlastImmune");
		case TFCond_FireImmune: strcopy(buffer, size, "FireImmune");
		case TFCond_PreventDeath: strcopy(buffer, size, "PreventDeath");
		case TFCond_MVMBotRadiowave: strcopy(buffer, size, "MVMBotRadiowave");
		case TFCond_HalloweenSpeedBoost: strcopy(buffer, size, "HalloweenSpeedBoost");
		case TFCond_HalloweenQuickHeal: strcopy(buffer, size, "HalloweenQuickHeal");
		case TFCond_HalloweenGiant: strcopy(buffer, size, "HalloweenGiant");
		case TFCond_HalloweenTiny: strcopy(buffer, size, "HalloweenTiny");
		case TFCond_HalloweenInHell: strcopy(buffer, size, "HalloweenInHell");
		case TFCond_HalloweenGhostMode: strcopy(buffer, size, "HalloweenGhostMode");
		case TFCond_MiniCritOnKill: strcopy(buffer, size, "MiniCritOnKill");
		//case TFCond_DodgeChance: strcopy(buffer, size, "DodgeChance");
		case TFCond_ObscuredSmoke: strcopy(buffer, size, "ObscuredSmoke");
		case TFCond_Parachute: strcopy(buffer, size, "Parachute");
		case TFCond_BlastJumping: strcopy(buffer, size, "BlastJumping");
		case TFCond_HalloweenKart: strcopy(buffer, size, "HalloweenKart");
		case TFCond_HalloweenKartDash: strcopy(buffer, size, "HalloweenKartDash");
		case TFCond_BalloonHead: strcopy(buffer, size, "BalloonHead");
		case TFCond_MeleeOnly: strcopy(buffer, size, "MeleeOnly");
		case TFCond_SwimmingCurse: strcopy(buffer, size, "SwimmingCurse");
		//case TFCond_HalloweenKartNoTurn: strcopy(buffer, size, "HalloweenKartNoTurn");
		case TFCond_FreezeInput: strcopy(buffer, size, "FreezeInput");
		case TFCond_HalloweenKartCage: strcopy(buffer, size, "HalloweenKartCage");
		case TFCond_HasRune: strcopy(buffer, size, "HasRune");
		case TFCond_RuneStrength: strcopy(buffer, size, "RuneStrength");
		case TFCond_RuneHaste: strcopy(buffer, size, "RuneHaste");
		case TFCond_RuneRegen: strcopy(buffer, size, "RuneRegen");
		case TFCond_RuneResist: strcopy(buffer, size, "RuneResist");
		case TFCond_RuneVampire: strcopy(buffer, size, "RuneVampire");
		case TFCond_RuneWarlock: strcopy(buffer, size, "RuneWarlock");
		case TFCond_RunePrecision: strcopy(buffer, size, "RunePrecision");
		case TFCond_RuneAgility: strcopy(buffer, size, "RuneAgility");
		case TFCond_GrapplingHook: strcopy(buffer, size, "GrapplingHook");
		case TFCond_GrapplingHookSafeFall: strcopy(buffer, size, "GrapplingHookSafeFall");
		case TFCond_GrapplingHookLatched: strcopy(buffer, size, "GrapplingHookLatched");
		case TFCond_GrapplingHookBleeding: strcopy(buffer, size, "GrapplingHookBleeding");
		case TFCond_AfterburnImmune: strcopy(buffer, size, "AfterburnImmune");
		case TFCond_RuneKnockout: strcopy(buffer, size, "RuneKnockout");
		case TFCond_RuneImbalance: strcopy(buffer, size, "RuneImbalance");
		case TFCond_CritRuneTemp: strcopy(buffer, size, "CritRuneTemp");
		case TFCond_PasstimeInterception: strcopy(buffer, size, "PasstimeInterception");
		case TFCond_SwimmingNoEffects: strcopy(buffer, size, "SwimmingNoEffects");
		case TFCond_EyeaductUnderworld: strcopy(buffer, size, "EyeaductUnderworld");
		case TFCond_KingRune: strcopy(buffer, size, "KingRune");
		case TFCond_PlagueRune: strcopy(buffer, size, "PlagueRune");
		case TFCond_SupernovaRune: strcopy(buffer, size, "SupernovaRune");
		case TFCond_Plague: strcopy(buffer, size, "Plague");
		case TFCond_KingAura: strcopy(buffer, size, "KingAura");
		case TFCond_SpawnOutline: strcopy(buffer, size, "SpawnOutline");
		case TFCond_KnockedIntoAir: strcopy(buffer, size, "KnockedIntoAir");
		case TFCond_CompetitiveWinner: strcopy(buffer, size, "CompetitiveWinner");
		case TFCond_CompetitiveLoser: strcopy(buffer, size, "CompetitiveLoser");
		//case TFCond_NoTaunting_DEPRECATED: strcopy(buffer, size, "NoTaunting_DEPRECATED");
		case TFCond_HealingDebuff: strcopy(buffer, size, "HealingDebuff");
		case TFCond_PasstimePenaltyDebuff: strcopy(buffer, size, "PasstimePenaltyDebuff");
		case TFCond_GrappledToPlayer: strcopy(buffer, size, "GrappledToPlayer");
		case TFCond_GrappledByPlayer: strcopy(buffer, size, "GrappledByPlayer");
		case TFCond_ParachuteDeployed: strcopy(buffer, size, "ParachuteDeployed");
		case TFCond_Gas: strcopy(buffer, size, "Gas");
		case TFCond_BurningPyro: strcopy(buffer, size, "BurningPyro");
		case TFCond_RocketPack: strcopy(buffer, size, "RocketPack");
		case TFCond_LostFooting: strcopy(buffer, size, "LostFooting");
		case TFCond_AirCurrent: strcopy(buffer, size, "AirCurrent");
	}
	
	if (capitalize)
		buffer[0] = CharToUpper(buffer[0]);
	else
		buffer[0] = CharToLower(buffer[0]);
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
stock int TF2_GiveWeapon(int client, char[] classname, int index, TF2Quality quality = TF2Quality_Normal, int level = 0) 
{
	Handle item = TF2Items_CreateItem(PRESERVE_ATTRIBUTES|FORCE_GENERATION);	//Keep reserve attributes otherwise random issues will occur... including crashes.
	TF2Items_SetClassname(item, classname);
	TF2Items_SetItemIndex(item, index);
	TF2Items_SetQuality(item, view_as<int>(quality));
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
*	viewmodel	Model index. (Returned from PrecacheModel)
*
*	return	Entity index.
**/
stock int TF2_GiveViewmodel(int client, int viewmodel)
{
	int entity = CreateEntityByName("tf_wearable_vm");
	
	if (!IsValidEntity(entity))
		return entity;
	
	SetEntProp(entity, Prop_Send, "m_nModelIndex", viewmodel);
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
stock int TF2_GiveWearable(int client, int index, char[] classname = "tf_wearable", int quality = 9, int level = 0) 
{
	Handle item = TF2Items_CreateItem(OVERRIDE_ALL || FORCE_GENERATION);
	TF2Items_SetClassname(item, classname);
	TF2Items_SetItemIndex(item, index);
	TF2Items_SetQuality(item, quality);
	TF2Items_SetLevel(item, level);
	TF2Items_SetNumAttributes(item, 0);

	int wearable = TF2Items_GiveNamedItem(client, item);
	delete item;
	
	return wearable;
}

stock int TF2_CreateDroppedWeapon(int index, float origin[3], float angle[3] = NULL_VECTOR, float velocity[3] = NULL_VECTOR, const char[] model = "")
{
	int entity = CreateEntityByName("tf_dropped_weapon");
	
	if (!IsValidEntity(entity))
		return entity;
	
	SetEntProp(entity, Prop_Send, "m_iItemDefinitionIndex", index);
	SetEntProp(entity, Prop_Send, "m_bInitialized", 1);
	SetEntProp(entity, Prop_Send, "m_iItemIDLow", -1);
	SetEntProp(entity, Prop_Send, "m_iItemIDHigh", -1);
	
	if (strlen(model) > 0)
		SetEntityModel(entity, model);
	
	DispatchSpawn(entity);
	TeleportEntity(entity, origin, angle, velocity);
	
	return entity;
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

stock void TF2_SetItemChargeMeter(int client, int slot, float value = 100.0)
{
	SetEntPropFloat(client, Prop_Send, "m_flItemChargeMeter", value, slot);
}

stock float TF2_GetItemChargeMeter(int client, int slot)
{
	return GetEntPropFloat(client, Prop_Send, "m_flItemChargeMeter", slot);
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

stock int TF2_GetTauntIndex(int client)
{
	return GetEntProp(client, Prop_Send, "m_iTauntIndex");
}

stock int TF2_GetTauntDefIndex(int client)
{
	return GetEntProp(client, Prop_Send, "m_iTauntItemDefIndex");
}

enum MinigunState
{
	Minigun_Idle,
	Minigun_Windup,
	Minigun_Firing,
	Minigun_Spinning
}

stock MinigunState TF2_GetMinigunState(int client)
{
	int weapon = GetPlayerWeaponSlot(client, 0);
	
	if (!IsValidEntity(weapon))
		return Minigun_Idle;
	
	char classname[64];
	GetEntityClassname(weapon, classname, sizeof(classname));
	
	if (!StrEqual(classname, "tf_weapon_minigun", false))
		return Minigun_Idle;
	
	return view_as<MinigunState>(GetEntProp(weapon, Prop_Send, "m_iWeaponState"));
}

stock void TF2_RespawnAll()
{
	for (int i = 1; i <= MaxClients; i++)
	{
		if (!IsClientInGame(i))
			continue;
		
		TF2_RespawnPlayer(i);
	}
}

stock bool TF2_IsWeaponByName(int entity, const char[] name)
{
	if (!IsValidEntity(entity) || strlen(name) == 0)
		return false;
	
	int index = GetEntProp(entity, Prop_Send, "m_iItemDefinitionIndex");
	
	char buffer[64];
	TF2_GetWeaponNameFromIndex(index, buffer, sizeof(buffer));
	
	return StrEqual(buffer, name, false);
}

//This is the dumbest shit ever.
stock int TF2_GetIndexFromWeaponName(const char[] name)
{
	char buffer[32];
	for (int i = 0; i < 30673; i++)
	{
		TF2_GetWeaponNameFromIndex(i, buffer, sizeof(buffer));
		
		if (StrEqual(buffer, name, false))
			return i;
	}
	
	return -1;
}

stock void TF2_GetWeaponNameFromIndex(int index, char[] buffer, int size)
{
	switch (index)
	{
		//Misc
		case 154: strcopy(buffer, size, "The Pain Train");
		case 160: strcopy(buffer, size, "Vintage Lugermorph");
		case 199: strcopy(buffer, size, "Shotgun (Renamed/Strange)");
		case 209: strcopy(buffer, size, "Pistol (Renamed/Strange)");
		case 264: strcopy(buffer, size, "Frying Pan");
		case 294: strcopy(buffer, size, "Lugermorph");
		case 357: strcopy(buffer, size, "The Half-Zatoichi");
		case 415: strcopy(buffer, size, "The Reserve Shooter");
		case 423: strcopy(buffer, size, "Saxxy");
		case 474: strcopy(buffer, size, "The Conscientious Objector");
		case 880: strcopy(buffer, size, "The Freedom Staff");
		case 939: strcopy(buffer, size, "The Bat Outta Hell");
		case 954: strcopy(buffer, size, "The Memory Maker");
		case 1013: strcopy(buffer, size, "The Ham Shank");
		case 1071: strcopy(buffer, size, "Gold Frying Pan");
		case 1101: strcopy(buffer, size, "The B.A.S.E. Jumper");
		case 1123: strcopy(buffer, size, "The Necro Smasher");
		case 1127: strcopy(buffer, size, "The Crossing Guard");
		case 1141: strcopy(buffer, size, "Festive Shotgun");
		case 1153: strcopy(buffer, size, "Panic Attack");
		case 15003: strcopy(buffer, size, "Backwoods Boomstick");
		case 15013: strcopy(buffer, size, "Red Rock Roscoe");
		case 15016: strcopy(buffer, size, "Rustic Ruiner");
		case 15018: strcopy(buffer, size, "Homemade Heater");
		case 15035: strcopy(buffer, size, "Hickory Holepuncher");
		case 15041: strcopy(buffer, size, "Local Hero");
		case 15044: strcopy(buffer, size, "Civic Duty");
		case 15046: strcopy(buffer, size, "Black Dahlia");
		case 15047: strcopy(buffer, size, "Lightning Rod");
		case 15056: strcopy(buffer, size, "Sandstone Special");
		case 15060: strcopy(buffer, size, "Macabre Web");
		case 15061: strcopy(buffer, size, "Nutcracker");
		case 15085: strcopy(buffer, size, "Autumn");
		case 15100: strcopy(buffer, size, "Blue Mew");
		case 15101: strcopy(buffer, size, "Brain Candy");
		case 15102: strcopy(buffer, size, "Shot to Hell");
		case 15109: strcopy(buffer, size, "Flower Power");
		case 15123: strcopy(buffer, size, "Coffin Nail");
		case 15126: strcopy(buffer, size, "Dressed To Kill");
		case 15132: strcopy(buffer, size, "Coffin Nail");
		case 15133: strcopy(buffer, size, "Dressed to Kill");
		case 15148: strcopy(buffer, size, "Blitzkrieg");
		case 15152: strcopy(buffer, size, "Red Bear");
		case 30666: strcopy(buffer, size, "The C.A.P.P.E.R.");
		case 30758: strcopy(buffer, size, "Prinny Machete");
		
		//Scout Primary
		case 13: strcopy(buffer, size, "Scattergun");
		case 200: strcopy(buffer, size, "Scattergun (Renamed/Strange)");
		case 45: strcopy(buffer, size, "Force-A-Nature");
		case 220: strcopy(buffer, size, "The Shortstop");
		case 448: strcopy(buffer, size, "The Soda Popper");
		case 669: strcopy(buffer, size, "Festive Scattergun");
		case 772: strcopy(buffer, size, "Baby Face's Blaster");
		case 799: strcopy(buffer, size, "Silver Botkiller Scattergun Mk.I");
		case 808: strcopy(buffer, size, "Gold Botkiller Scattergun Mk.I");
		case 888: strcopy(buffer, size, "Rust Botkiller Scattergun Mk.I");
		case 897: strcopy(buffer, size, "Blood Botkiller Scattergun Mk.I");
		case 906: strcopy(buffer, size, "Carbonado Botkiller Scattergun Mk.I");
		case 915: strcopy(buffer, size, "Diamond Botkiller Scattergun Mk.I");
		case 964: strcopy(buffer, size, "Silver Botkiller Scattergun Mk.II");
		case 973: strcopy(buffer, size, "Gold Botkiller Scattergun Mk.II");
		case 1078: strcopy(buffer, size, "Festive Force-A-Nature");
		case 1103: strcopy(buffer, size, "The Back Scatter");
		case 15002: strcopy(buffer, size, "Night Terror");
		case 15015: strcopy(buffer, size, "Tartan Torpedo");
		case 15021: strcopy(buffer, size, "Country Crusher");
		case 15029: strcopy(buffer, size, "Backcountry Blaster");
		case 15036: strcopy(buffer, size, "Spruce Deuce");
		case 15053: strcopy(buffer, size, "Current Event");
		case 15065: strcopy(buffer, size, "Macabre Web");
		case 15069: strcopy(buffer, size, "Nutcracker");
		case 15106: strcopy(buffer, size, "Blue Mew");
		case 15107: strcopy(buffer, size, "Flower Power");
		case 15108: strcopy(buffer, size, "Shot to Hell");
		case 15131: strcopy(buffer, size, "Coffin Nail");
		case 15151: strcopy(buffer, size, "Killer Bee");
		case 15157: strcopy(buffer, size, "Corsair");
		
		//Scout Secondary
		case 23: strcopy(buffer, size, "Scout's Pistol");
		case 46: strcopy(buffer, size, "Bonk! Atomic Punch");
		case 163: strcopy(buffer, size, "Crit-a-Cola");
		case 222: strcopy(buffer, size, "Mad Milk");
		case 449: strcopy(buffer, size, "The Winger");
		case 773: strcopy(buffer, size, "Pretty Boy's Pocket Pistol");
		case 812: strcopy(buffer, size, "The Flying Guillotine");
		case 833: strcopy(buffer, size, "The Flying Guillotine (Genuine)");
		case 1121: strcopy(buffer, size, "Mutated Milk");
		case 1145: strcopy(buffer, size, "Festive Bonk!");
		
		//Scout Melee
		case 0: strcopy(buffer, size, "Bat");
		case 190: strcopy(buffer, size, "Bat (Renamed/Strange)");
		case 44: strcopy(buffer, size, "The Sandman");
		case 221: strcopy(buffer, size, "The Holy Mackerel");
		case 317: strcopy(buffer, size, "The Candy Cane");
		case 325: strcopy(buffer, size, "The Boston Basher");
		case 349: strcopy(buffer, size, "Sun-on-a-Stick");
		case 355: strcopy(buffer, size, "The Fan O'War");
		case 450: strcopy(buffer, size, "The Atomizer");
		case 452: strcopy(buffer, size, "Three-Rune Blade");
		case 572: strcopy(buffer, size, "Unarmed Combat");
		case 648: strcopy(buffer, size, "The Wrap Assassin");
		case 660: strcopy(buffer, size, "Festive Bat");
		case 999: strcopy(buffer, size, "Festive Holy Mackerel");
		case 30667: strcopy(buffer, size, "Batsaber");
		
		//Soldier Primary
		case 18: strcopy(buffer, size, "Rocket Launcher");
		case 205: strcopy(buffer, size, "Rocket Launcher (Renamed/Strange)");
		case 127: strcopy(buffer, size, "The Direct Hit");
		case 228: strcopy(buffer, size, "The Black Box");
		case 237: strcopy(buffer, size, "Rocket Jumper");
		case 414: strcopy(buffer, size, "The Liberty Launcher");
		case 441: strcopy(buffer, size, "The Cow Mangler 5000");
		case 513: strcopy(buffer, size, "The Original");
		case 658: strcopy(buffer, size, "Festive Rocket Launcher");
		case 730: strcopy(buffer, size, "The Beggar's Bazooka");
		case 800: strcopy(buffer, size, "Silver Botkiller Rocket Launcher Mk.I");
		case 809: strcopy(buffer, size, "Gold Botkiller Rocket Launcher Mk.I");
		case 889: strcopy(buffer, size, "Rust Botkiller Rocket Launcher Mk.I");
		case 898: strcopy(buffer, size, "Blood Botkiller Rocket Launcher Mk.I");
		case 907: strcopy(buffer, size, "Carbonado Botkiller Rocket Launcher Mk.I");
		case 916: strcopy(buffer, size, "Diamond Botkiller Rocket Launcher Mk.I");
		case 965: strcopy(buffer, size, "Silver Botkiller Rocket Launcher Mk.II");
		case 974: strcopy(buffer, size, "Gold Botkiller Rocket Launcher Mk.II");
		case 1085: strcopy(buffer, size, "Festive Black Box");
		case 1104: strcopy(buffer, size, "The Air Strike");
		case 15006: strcopy(buffer, size, "Woodland Warrior");
		case 15014: strcopy(buffer, size, "Sand Cannon");
		case 15028: strcopy(buffer, size, "American Pastoral");
		case 15043: strcopy(buffer, size, "Smalltown Bringdown");
		case 15052: strcopy(buffer, size, "Shell Shocker");
		case 15057: strcopy(buffer, size, "Aqua Marine");
		case 15081: strcopy(buffer, size, "Autumn");
		case 15104: strcopy(buffer, size, "Blue Mew");
		case 15105: strcopy(buffer, size, "Brain Candy");
		case 15129: strcopy(buffer, size, "Coffin Nail");
		case 15130: strcopy(buffer, size, "High Roller's");
		case 15150: strcopy(buffer, size, "Warhawk");
		
		//Soldier Secondary
		case 10: strcopy(buffer, size, "Soldier's Shotgun");
		case 129: strcopy(buffer, size, "The Buff Banner");
		case 133: strcopy(buffer, size, "Gunboats");
		case 226: strcopy(buffer, size, "The Battalion's Backup");
		case 354: strcopy(buffer, size, "The Concheror");
		case 442: strcopy(buffer, size, "The Righteous Bison");
		case 444: strcopy(buffer, size, "The Mantreads");
		case 1001: strcopy(buffer, size, "Festive Buff Banner");
		
		//Soldier Melee
		case 6: strcopy(buffer, size, "Shovel");
		case 196: strcopy(buffer, size, "Shovel (Renamed/Strange)");
		case 128: strcopy(buffer, size, "The Equalizer");
		case 416: strcopy(buffer, size, "The Market Gardener");
		case 447: strcopy(buffer, size, "The Disciplinary Action");
		case 775: strcopy(buffer, size, "The Escape Plan");

		//Pyro Primary
		case 21: strcopy(buffer, size, "Flame Thrower");
		case 208: strcopy(buffer, size, "Flame Thrower (Renamed/Strange)");
		case 40: strcopy(buffer, size, "The Backburner");
		case 215: strcopy(buffer, size, "The Degreaser");
		case 594: strcopy(buffer, size, "The Phlogistinator");
		case 659: strcopy(buffer, size, "Festive Flame Thrower");
		case 741: strcopy(buffer, size, "The Rainblower");
		case 798: strcopy(buffer, size, "Silver Botkiller Flame Thrower Mk.I");
		case 807: strcopy(buffer, size, "Gold Botkiller Flame Thrower Mk.I");
		case 887: strcopy(buffer, size, "Rust Botkiller Flame Thrower Mk.I");
		case 896: strcopy(buffer, size, "Blood Botkiller Flame Thrower Mk.I");
		case 905: strcopy(buffer, size, "Carbonado Botkiller Flame Thrower Mk.I");
		case 914: strcopy(buffer, size, "Diamond Botkiller Flame Thrower Mk.I");
		case 963: strcopy(buffer, size, "Silver Botkiller Flame Thrower Mk.II");
		case 972: strcopy(buffer, size, "Gold Botkiller Flame Thrower Mk.II");
		case 1146: strcopy(buffer, size, "Festive Backburner");
		case 1178: strcopy(buffer, size, "Dragon's Fury");
		case 15005: strcopy(buffer, size, "Forest Fire");
		case 15017: strcopy(buffer, size, "Barn Burner");
		case 15030: strcopy(buffer, size, "Bovine Blazemaker");
		case 15034: strcopy(buffer, size, "Earth, Sky and Fire");
		case 15049: strcopy(buffer, size, "Flash Fryer");
		case 15054: strcopy(buffer, size, "Turbine Torcher");
		case 15066: strcopy(buffer, size, "Autumn");
		case 15067: strcopy(buffer, size, "Pumpkin Patch");
		case 15068: strcopy(buffer, size, "Nutcracker");
		case 15089: strcopy(buffer, size, "Balloonicorn");
		case 15090: strcopy(buffer, size, "Rainbow");
		case 15115: strcopy(buffer, size, "Coffin Nail");
		case 15141: strcopy(buffer, size, "Warhawk");
		case 30474: strcopy(buffer, size, "Nostromo Napalmer");
		
		//Pyro Secondary
		case 12: strcopy(buffer, size, "Pyro's Shotgun");
		case 39: strcopy(buffer, size, "The Flare Gun");
		case 351: strcopy(buffer, size, "The Detonator");
		case 595: strcopy(buffer, size, "The Manmelter");
		case 740: strcopy(buffer, size, "The Scorch Shot");
		case 1081: strcopy(buffer, size, "Festive Flare Gun");
		case 1179: strcopy(buffer, size, "Thermal Thruster");
		case 1180: strcopy(buffer, size, "Gas Passer");
		
		//Pyro Melee
		case 2: strcopy(buffer, size, "Fire Axe");
		case 192: strcopy(buffer, size, "Fire Axe (Renamed/Strange)");
		case 38: strcopy(buffer, size, "The Axtinguisher");
		case 153: strcopy(buffer, size, "Homewrecker");
		case 214: strcopy(buffer, size, "The Powerjack");
		case 326: strcopy(buffer, size, "The Back Scratcher");
		case 348: strcopy(buffer, size, "Sharpened Volcano Fragment");
		case 457: strcopy(buffer, size, "The Postal Pummeler");
		case 466: strcopy(buffer, size, "The Maul");
		case 593: strcopy(buffer, size, "The Third Degree");
		case 739: strcopy(buffer, size, "The Lollichop");
		case 813: strcopy(buffer, size, "Neon Annihilator");
		case 834: strcopy(buffer, size, "Neon Annihilator (Genuine)");
		case 1000: strcopy(buffer, size, "The Festive Axtinguisher");
		case 1181: strcopy(buffer, size, "Hot Hand");
		
		//Demoman Primary
		case 19: strcopy(buffer, size, "Grenade Launcher");
		case 206: strcopy(buffer, size, "Grenade Launcher (Renamed/Strange)");
		case 308: strcopy(buffer, size, "The Loch-n-Load");
		case 405: strcopy(buffer, size, "Ali Baba's Wee Booties");
		case 608: strcopy(buffer, size, "The Bootlegger");
		case 996: strcopy(buffer, size, "The Loose Cannon");
		case 1007: strcopy(buffer, size, "Festive Grenade Launcher");
		case 1151: strcopy(buffer, size, "The Iron Bomber");
		case 15077: strcopy(buffer, size, "Autumn");
		case 15079: strcopy(buffer, size, "Macabre Web");
		case 15091: strcopy(buffer, size, "Rainbow");
		case 15092: strcopy(buffer, size, "Sweet Dreams");
		case 15116: strcopy(buffer, size, "Coffin Nail");
		case 15117: strcopy(buffer, size, "Top Shelf");
		case 15142: strcopy(buffer, size, "Warhawk");
		case 15158: strcopy(buffer, size, "Butcher Bird");
		
		//Demoman Secondary
		case 20: strcopy(buffer, size, "Stickybomb Launcher");
		case 207: strcopy(buffer, size, "Stickybomb Launcher (Renamed/Strange)");
		case 130: strcopy(buffer, size, "The Scottish Resistance");
		case 131: strcopy(buffer, size, "The Chargin' Targe");
		case 265: strcopy(buffer, size, "Sticky Jumper");
		case 406: strcopy(buffer, size, "The Splendid Screen");
		case 661: strcopy(buffer, size, "Festive Stickybomb Launcher");
		case 797: strcopy(buffer, size, "Silver Botkiller Stickybomb Launcher Mk.I");
		case 806: strcopy(buffer, size, "Gold Botkiller Stickybomb Launcher Mk.I");
		case 886: strcopy(buffer, size, "Rust Botkiller Stickybomb Launcher Mk.I");
		case 895: strcopy(buffer, size, "Blood Botkiller Stickybomb Launcher Mk.I");
		case 904: strcopy(buffer, size, "Carbonado Botkiller Stickybomb Launcher Mk.I");
		case 913: strcopy(buffer, size, "Diamond Botkiller Stickybomb Launcher Mk.I");
		case 962: strcopy(buffer, size, "Silver Botkiller Stickybomb Launcher Mk.II");
		case 971: strcopy(buffer, size, "Gold Botkiller Stickybomb Launcher Mk.II");
		case 1099: strcopy(buffer, size, "The Tide Turner");
		case 1144: strcopy(buffer, size, "Festive Targe");
		case 1150: strcopy(buffer, size, "The Quickiebomb Launcher");
		case 15009: strcopy(buffer, size, "Sudden Flurry");
		case 15012: strcopy(buffer, size, "Carpet Bomber");
		case 15024: strcopy(buffer, size, "Blasted Bombardier");
		case 15038: strcopy(buffer, size, "Rooftop Wrangler");
		case 15045: strcopy(buffer, size, "Liquid Asset");
		case 15048: strcopy(buffer, size, "Pink Elephant");
		case 15082: strcopy(buffer, size, "Autumn");
		case 15083: strcopy(buffer, size, "Pumpkin Patch");
		case 15084: strcopy(buffer, size, "Macabre Web");
		case 15113: strcopy(buffer, size, "Sweet Dreams");
		case 15137: strcopy(buffer, size, "Coffin Nail");
		case 15138: strcopy(buffer, size, "Dressed to Kill");
		case 15155: strcopy(buffer, size, "Blitzkrieg");
		
		//Demoman Melee
		case 1: strcopy(buffer, size, "Bottle");
		case 191: strcopy(buffer, size, "Bottle (Renamed/Strange)");
		case 132: strcopy(buffer, size, "The Eyelander");
		case 172: strcopy(buffer, size, "The Scotsman's Skullcutter");
		case 266: strcopy(buffer, size, "Horseless Headless Horsemann's Headtaker");
		case 307: strcopy(buffer, size, "Ullapool Caber");
		case 327: strcopy(buffer, size, "The Claidheamh Mòr");
		case 404: strcopy(buffer, size, "The Persian Persuader");
		case 482: strcopy(buffer, size, "Nessie's Nine Iron");
		case 609: strcopy(buffer, size, "The Scottish Handshake");
		case 1082: strcopy(buffer, size, "Festive Eyelander");
		
		//Heavy Primary
		case 15: strcopy(buffer, size, "Minigun");
		case 202: strcopy(buffer, size, "Minigun (Renamed/Strange)");
		case 41: strcopy(buffer, size, "Natascha");
		case 298: strcopy(buffer, size, "Iron Curtain");
		case 312: strcopy(buffer, size, "The Brass Beast");
		case 424: strcopy(buffer, size, "Tomislav");
		case 654: strcopy(buffer, size, "Festive Minigun");
		case 793: strcopy(buffer, size, "Silver Botkiller Minigun Mk.I");
		case 802: strcopy(buffer, size, "Gold Botkiller Minigun Mk.I");
		case 811: strcopy(buffer, size, "The Huo-Long Heater");
		case 832: strcopy(buffer, size, "The Huo-Long Heater (Genuine)");
		case 850: strcopy(buffer, size, "Deflector (MvM only?)");
		case 882: strcopy(buffer, size, "Rust Botkiller Minigun Mk.I");
		case 891: strcopy(buffer, size, "Blood Botkiller Minigun Mk.I");
		case 900: strcopy(buffer, size, "Carbonado Botkiller Minigun Mk.I");
		case 909: strcopy(buffer, size, "Diamond Botkiller Minigun Mk.I");
		case 958: strcopy(buffer, size, "Silver Botkiller Minigun Mk.II");
		case 967: strcopy(buffer, size, "Gold Botkiller Minigun Mk.II");
		case 15004: strcopy(buffer, size, "King of the Jungle");
		case 15020: strcopy(buffer, size, "Iron Wood");
		case 15026: strcopy(buffer, size, "Antique Annihilator");
		case 15031: strcopy(buffer, size, "War Room");
		case 15040: strcopy(buffer, size, "Citizen Pain");
		case 15055: strcopy(buffer, size, "Brick House");
		case 15086: strcopy(buffer, size, "Macabre Web");
		case 15087: strcopy(buffer, size, "Pumpkin Patch");
		case 15088: strcopy(buffer, size, "Nutcracker");
		case 15098: strcopy(buffer, size, "Brain Candy");
		case 15099: strcopy(buffer, size, "Mister Cuddles");
		case 15124: strcopy(buffer, size, "Dressed to Kill");
		case 15125: strcopy(buffer, size, "Top Shelf");
		case 15147: strcopy(buffer, size, "Butcher Bird");

		//Heavy Secondary
		case 11: strcopy(buffer, size, "Heavy's Shotgun");
		case 42: strcopy(buffer, size, "Sandvich");
		case 159: strcopy(buffer, size, "The Dalokohs Bar");
		case 311: strcopy(buffer, size, "The Buffalo Steak Sandvich");
		case 425: strcopy(buffer, size, "The Family Business");
		case 433: strcopy(buffer, size, "Fishcake");
		case 863: strcopy(buffer, size, "Robo-Sandvich");
		case 1002: strcopy(buffer, size, "Festive Sandvich");
		
		//Heavy Melee
		case 5: strcopy(buffer, size, "Fists");
		case 195: strcopy(buffer, size, "Fists (Renamed/Strange)");
		case 43: strcopy(buffer, size, "The Killing Gloves of Boxing");
		case 239: strcopy(buffer, size, "Gloves of Running Urgently");
		case 310: strcopy(buffer, size, "Warrior's Spirit");
		case 331: strcopy(buffer, size, "Fists of Steel");
		case 426: strcopy(buffer, size, "The Eviction Notice");
		case 587: strcopy(buffer, size, "Apoco-Fists");
		case 656: strcopy(buffer, size, "The Holiday Punch");
		case 1084: strcopy(buffer, size, "Festive Gloves of Running Urgently (G.R.U.)");
		case 1100: strcopy(buffer, size, "The Bread Bite");
		case 1184: strcopy(buffer, size, "Gloves of Running Urgently MvM");
		
		//Engineer Primary
		case 9: strcopy(buffer, size, "Engineer's Shotgun");
		case 141: strcopy(buffer, size, "The Frontier Justice");
		case 527: strcopy(buffer, size, "The Widowmaker");
		case 588: strcopy(buffer, size, "The Pomson 6000");
		case 997: strcopy(buffer, size, "The Rescue Ranger");
		case 1004: strcopy(buffer, size, "Festive Frontier Justice");
		
		//Engineer Secondary
		case 22: strcopy(buffer, size, "Engineer's Pistol");
		case 140: strcopy(buffer, size, "The Wrangler");
		case 528: strcopy(buffer, size, "The Short Circuit");
		case 1086: strcopy(buffer, size, "Festive Wrangler");
		case 30668: strcopy(buffer, size, "The Gigar Counter");
		
		//Engineer Melee
		case 7: strcopy(buffer, size, "Wrench");
		case 197: strcopy(buffer, size, "Wrench (Renamed/Strange)");
		case 142: strcopy(buffer, size, "The Gunslinger");
		case 155: strcopy(buffer, size, "The Southern Hospitality");
		case 169: strcopy(buffer, size, "Golden Wrench");
		case 329: strcopy(buffer, size, "The Jag");
		case 589: strcopy(buffer, size, "The Eureka Effect");
		case 662: strcopy(buffer, size, "Festive Wrench");
		case 795: strcopy(buffer, size, "Silver Botkiller Wrench Mk.I");
		case 804: strcopy(buffer, size, "Gold Botkiller Wrench Mk.I");
		case 884: strcopy(buffer, size, "Rust Botkiller Wrench Mk.I");
		case 893: strcopy(buffer, size, "Blood Botkiller Wrench Mk.I");
		case 902: strcopy(buffer, size, "Carbonado Botkiller Wrench Mk.I");
		case 911: strcopy(buffer, size, "Diamond Botkiller Wrench Mk.I");
		case 960: strcopy(buffer, size, "Silver Botkiller Wrench Mk.II");
		case 969: strcopy(buffer, size, "Gold Botkiller Wrench Mk.II");
		case 15073: strcopy(buffer, size, "Nutcracker");
		case 15074: strcopy(buffer, size, "Autumn");
		case 15075: strcopy(buffer, size, "Boneyard");
		case 15139: strcopy(buffer, size, "Dressed to Kill");
		case 15140: strcopy(buffer, size, "Top Shelf");
		case 15114: strcopy(buffer, size, "Torqued to Hell");
		case 15156: strcopy(buffer, size, "Airwolf");
		
		//Medic Primary
		case 17: strcopy(buffer, size, "Syringe Gun");
		case 204: strcopy(buffer, size, "Syringe Gun (Renamed/Strange)");
		case 36: strcopy(buffer, size, "The Blutsauger");
		case 305: strcopy(buffer, size, "Crusader's Crossbow");
		case 412: strcopy(buffer, size, "The Overdose");
		case 1079: strcopy(buffer, size, "Festive Crusader's Crossbow");
		
		//Medic Secondary
		case 29: strcopy(buffer, size, "Medi Gun");
		case 211: strcopy(buffer, size, "Medi Gun(Renamed/Strange)");
		case 35: strcopy(buffer, size, "The Kritzkrieg");
		case 411: strcopy(buffer, size, "The Quick-Fix");
		case 663: strcopy(buffer, size, "Festive Medi Gun");
		case 796: strcopy(buffer, size, "Silver Botkiller Medi Gun Mk.I");
		case 805: strcopy(buffer, size, "Gold Botkiller Medi Gun Mk.I");
		case 885: strcopy(buffer, size, "Rust Botkiller Medi Gun Mk.I");
		case 894: strcopy(buffer, size, "Blood Botkiller Medi Gun Mk.I");
		case 903: strcopy(buffer, size, "Carbonado Botkiller Medi Gun Mk.I");
		case 912: strcopy(buffer, size, "Diamond Botkiller Medi Gun Mk.I");
		case 961: strcopy(buffer, size, "Silver Botkiller Medi Gun Mk.II");
		case 970: strcopy(buffer, size, "Gold Botkiller Medi Gun Mk.II");
		case 998: strcopy(buffer, size, "The Vaccinator");
		case 15008: strcopy(buffer, size, "Masked Mender");
		case 15010: strcopy(buffer, size, "Wrapped Reviver");
		case 15025: strcopy(buffer, size, "Reclaimed Reanimator");
		case 15039: strcopy(buffer, size, "Civil Servant");
		case 15050: strcopy(buffer, size, "Spark of Life");
		case 15078: strcopy(buffer, size, "Wildwood");
		case 15097: strcopy(buffer, size, "Flower Power");
		case 15121: strcopy(buffer, size, "Dressed To Kill");
		case 15122: strcopy(buffer, size, "High Roller's");
		case 15145: strcopy(buffer, size, "Blitzkrieg");
		case 15146: strcopy(buffer, size, "Corsair");
		
		//Medic Melee
		case 8: strcopy(buffer, size, "Bonesaw");
		case 198: strcopy(buffer, size, "Bonesaw (Renamed/Strange)");
		case 37: strcopy(buffer, size, "The Ubersaw");
		case 173: strcopy(buffer, size, "The Vita-Saw");
		case 304: strcopy(buffer, size, "Amputator");
		case 413: strcopy(buffer, size, "The Solemn Vow");
		case 1003: strcopy(buffer, size, "Festive Ubersaw");
		case 1143: strcopy(buffer, size, "Festive Bonesaw");
		
		//Sniper Primary
		case 14: strcopy(buffer, size, "Sniper Rifle");
		case 201: strcopy(buffer, size, "Sniper Rifle (Renamed/Strange)");
		case 56: strcopy(buffer, size, "The Huntsman");
		case 230: strcopy(buffer, size, "The Sydney Sleeper");
		case 402: strcopy(buffer, size, "The Bazaar Bargain");
		case 526: strcopy(buffer, size, "The Machina");
		case 664: strcopy(buffer, size, "Festive Sniper Rifle");
		case 752: strcopy(buffer, size, "The Hitman's Heatmaker");
		case 792: strcopy(buffer, size, "Silver Botkiller Sniper Rifle Mk.I");
		case 801: strcopy(buffer, size, "Gold Botkiller Sniper Rifle Mk.I");
		case 851: strcopy(buffer, size, "The AWPer Hand");
		case 881: strcopy(buffer, size, "Rust Botkiller Sniper Rifle Mk.I");
		case 890: strcopy(buffer, size, "Blood Botkiller Sniper Rifle Mk.I");
		case 899: strcopy(buffer, size, "Carbonado Botkiller Sniper Rifle Mk.I");
		case 908: strcopy(buffer, size, "Diamond Botkiller Sniper Rifle Mk.I");
		case 957: strcopy(buffer, size, "Silver Botkiller Sniper Rifle Mk.II");
		case 966: strcopy(buffer, size, "Gold Botkiller Sniper Rifle Mk.II");
		case 1005: strcopy(buffer, size, "Festive Huntsman");
		case 1092: strcopy(buffer, size, "The Fortified Compound");
		case 1098: strcopy(buffer, size, "The Classic");
		case 15000: strcopy(buffer, size, "Night Owl");
		case 15007: strcopy(buffer, size, "Purple Range");
		case 15019: strcopy(buffer, size, "Lumber From Down Under");
		case 15023: strcopy(buffer, size, "Shot in the Dark");
		case 15033: strcopy(buffer, size, "Bogtrotter");
		case 15059: strcopy(buffer, size, "Thunderbolt");
		case 15070: strcopy(buffer, size, "Pumpkin Patch");
		case 15071: strcopy(buffer, size, "Boneyard");
		case 15072: strcopy(buffer, size, "Wildwood");
		case 15111: strcopy(buffer, size, "Balloonicorn");
		case 15112: strcopy(buffer, size, "Rainbow");
		case 15135: strcopy(buffer, size, "Coffin Nail");
		case 15136: strcopy(buffer, size, "Dressed to Kill");
		case 15154: strcopy(buffer, size, "Airwolf");
		case 30665: strcopy(buffer, size, "Shooting Star");
		
		//Sniper Secondary
		case 16: strcopy(buffer, size, "SMG");
		case 203: strcopy(buffer, size, "SMG (Renamed/Strange)");
		case 57: strcopy(buffer, size, "The Razorback");
		case 58: strcopy(buffer, size, "Jarate");
		case 231: strcopy(buffer, size, "Darwin's Danger Shield");
		case 642: strcopy(buffer, size, "Cozy Camper");
		case 751: strcopy(buffer, size, "The Cleaner's Carbine");
		case 1083: strcopy(buffer, size, "Festive Jarate");
		case 1105: strcopy(buffer, size, "The Self-Aware Beauty Mark");
		case 1149: strcopy(buffer, size, "Festive SMG");
		case 15001: strcopy(buffer, size, "Woodsy Widowmaker");
		case 15022: strcopy(buffer, size, "Plaid Potshotter");
		case 15032: strcopy(buffer, size, "Treadplate Tormenter");
		case 15037: strcopy(buffer, size, "Team Sprayer");
		case 15058: strcopy(buffer, size, "Low Profile");
		case 15076: strcopy(buffer, size, "Wildwood");
		case 15110: strcopy(buffer, size, "Blue Mew");
		case 15134: strcopy(buffer, size, "High Roller's");
		case 15153: strcopy(buffer, size, "Blitzkrieg");
		
		//Sniper Melee
		case 3: strcopy(buffer, size, "Kukri");
		case 193: strcopy(buffer, size, "Kukri (Renamed/Strange)");
		case 171: strcopy(buffer, size, "The Tribalman's Shiv");
		case 232: strcopy(buffer, size, "The Bushwacka");
		case 401: strcopy(buffer, size, "The Shahanshah");
		
		//Spy Primary
		case 24: strcopy(buffer, size, "Revolver");
		case 210: strcopy(buffer, size, "Revolver (Renamed/Strange)");
		case 61: strcopy(buffer, size, "The Ambassador");
		case 161: strcopy(buffer, size, "Big Kill");
		case 224: strcopy(buffer, size, "L'Etranger");
		case 460: strcopy(buffer, size, "The Enforcer");
		case 525: strcopy(buffer, size, "The Diamondback");
		case 1006: strcopy(buffer, size, "Festive Ambassador");
		case 1142: strcopy(buffer, size, "Festive Revolver");
		case 15011: strcopy(buffer, size, "Psychedelic Slugger");
		case 15027: strcopy(buffer, size, "Old Country");
		case 15042: strcopy(buffer, size, "Mayor");
		case 15051: strcopy(buffer, size, "Dead Reckoner");
		case 15063: strcopy(buffer, size, "Wildwood");
		case 15064: strcopy(buffer, size, "Macabre Web");
		case 15103: strcopy(buffer, size, "Flower Power");
		case 15128: strcopy(buffer, size, "Top Shelf");
		case 15149: strcopy(buffer, size, "Blitzkrieg");
		
		//Spy Secondary
		case 735: strcopy(buffer, size, "Sapper");
		case 736: strcopy(buffer, size, "Sapper (Renamed/Strange)");
		case 810: strcopy(buffer, size, "The Red-Tape Recorder");
		case 831: strcopy(buffer, size, "The Red-Tape Recorder (Genuine)");
		case 933: strcopy(buffer, size, "The Ap-Sap (Genuine)");
		case 1080: strcopy(buffer, size, "Festive Sapper");
		case 1102: strcopy(buffer, size, "The Snack Attack");
		
		//Spy Melee
		case 4: strcopy(buffer, size, "Knife");
		case 194: strcopy(buffer, size, "Knife (Renamed/Strange)");
		case 225: strcopy(buffer, size, "Your Eternal Reward");
		case 356: strcopy(buffer, size, "Conniver's Kunai");
		case 461: strcopy(buffer, size, "The Big Earner");
		case 574: strcopy(buffer, size, "The Wanga Prick");
		case 638: strcopy(buffer, size, "The Sharp Dresser");
		case 649: strcopy(buffer, size, "The Spy-cicle");
		case 665: strcopy(buffer, size, "Festive Knife");
		case 727: strcopy(buffer, size, "The Black Rose");
		case 794: strcopy(buffer, size, "Silver Botkiller Knife Mk.I");
		case 803: strcopy(buffer, size, "Gold Botkiller Knife Mk.I");
		case 883: strcopy(buffer, size, "Rust Botkiller Knife Mk.I");
		case 892: strcopy(buffer, size, "Blood Botkiller Knife Mk.I");
		case 901: strcopy(buffer, size, "Carbonado Botkiller Knife Mk.I");
		case 910: strcopy(buffer, size, "Diamond Botkiller Knife Mk.I");
		case 959: strcopy(buffer, size, "Silver Botkiller Knife Mk.II");
		case 968: strcopy(buffer, size, "Gold Botkiller Knife Mk.II");
		case 15062: strcopy(buffer, size, "Boneyard");
		case 15094: strcopy(buffer, size, "Blue Mew");
		case 15095: strcopy(buffer, size, "Brain Candy");
		case 15096: strcopy(buffer, size, "Stabbed to Hell");
		case 15118: strcopy(buffer, size, "Dressed to Kill");
		case 15119: strcopy(buffer, size, "Top Shelf");
		case 15143: strcopy(buffer, size, "Blitzkrieg");
		case 15144: strcopy(buffer, size, "Airwolf");
	}
}

stock int TF2_GetFestiveEquivalent(int index)
{
	switch (index)
	{
		case 13:	return 669;		//scattergun
		case 45:	return 1078;	//force-a-nature
		case 46:	return 1145;	//bonk!
		case 0:		return 660;		//bat
		case 221:	return 999;		//holy mackerel
		case 18:	return 658;		//rocket launcher
		case 228:	return 1085;	//black box
		case 128:	return 1001;	//buff banner
		case 21:	return 659;		//flamethrower
		case 40:	return 1146;	//backburner
		case 39:	return 1081;	//flare gun
		case 12:	return 1141;	//pyro shotgun
		case 38:	return 1000;	//axtinguisher
		case 19:	return 1007;	//grenade launcher
		case 20:	return 661;		//stickybomb launcher
		case 131:	return 1144;	//targe
		case 132:	return 1082;	//eyelander
		case 15:	return 654;		//minigun
		case 42:	return 1002;	//sandvich
		case 11:	return 1141;	//heavy shotgun
		case 239:	return 1084;	//gloves of running urgently
		case 141:	return 1004;	//frontier justice
		case 9:		return 1141;	//engineer shotgun
		case 140:	return 1086;	//wrangler
		case 7:		return 662;		//wrench
		case 305:	return 1079;	//crossbow
		case 29:	return 663;		//medi gun
		case 37:	return 1003;	//ubersaw
		case 8:		return 1143;	//bonesaw
		case 14:	return 664;		//sniper rifle
		case 56:	return 1005;	//huntsman
		case 58:	return 1083;	//Jarate
		case 16:	return 1149;	//SMG
		case 64:	return 1006;	//Ambassador
		case 24:	return 1142;	//Revolver
		case 735:	return 1080;	//Sapper
		case 4:		return 665;		//Knife
	}

	return -1;
}

stock bool TF2_IsWaitingForPlayers()
{
	return view_as<bool>(GameRules_GetProp("m_bInWaitingForPlayers"));
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
*	WARNING: This has the unattended side effect of also updating velocity values, might not be what you want.
*	It's better to just use the 'GetPlayerMaxSpeed' offsets for CSGO with DHooks.
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
	if (!IsClientInGame(client))
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
	if (!IsClientInGame(client))
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
	if (!IsClientInGame(client))
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

stock bool CSGO_IsWarmup()
{
	return GameRules_GetProp("m_bWarmupPeriod");
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
	
	menu.AddItem("", "---", ITEMDRAW_DISABLED);
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

/*--------------------------------------------------------->*/
//This is the end of this THICCCCCC include file.
/*--------------------------------------------------------->*/