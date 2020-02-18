/**
*	.--.                    .-.                  .--.  .-.       _ .-.
*	: .--'                  .' `.                : .--'.' `.     :_;: :.-.       _
*	: :    .--. .-..-.,-.,-.`. .'.--. .--.  _____`. `. `. .'.--. .-.: `'.' .--. :_:
*	: :__ ' .; :: :; :: ,. : : :' '_.': ..':_____:_`, : : : : ..': :: . `.' '_.' _
*	`.__.'`.__.'`.__.':_;:_; :_;`.__.':_;        `.__.' :_; :_;  :_;:_;:_;`.__.':_;
*	.--. .-.        .-.          .-.     .--.  .--. .--.                 _
*	: .--': :        : :          : :    : ,. :: .-': .-'                :_;
*	: : _ : :   .--. : `-.  .--.  : :    : :: :: `; : `;.--. ,-.,-. .--. .-..-..-. .--.
*	: :; :: :_ ' .; :' .; :' .; ; : :_   : :; :: :  : :' '_.': ,. :`._-.': :: `; :' '_.'
*	`.__.'`.__;`.__.'`.__.'`.__,_;`.__;  `.__.':_;  :_;`.__.':_;:_;`.__.':_;`.__.'`.__.'
*	
*	This include contains a ton of useful stocks and functions you can use for Counter-Strike: Global Offensive.
*	Author: Keith Warren (Drixevel)
*	https://github.com/Drixevel
*
*	NOTE: The best way to use this include is to copy and paste into your projects manually.
*	Credits: SM9();
**/


#if defined _misc_csgo_included
#endinput
#endif
#define _misc_csgo_included

#undef REQUIRE_EXTENSIONS
#tryinclude <cstrike>
#define REQUIRE_EXTENSIONS

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
	SetEntProp(client, Prop_Send, "m_ArmorValue", amount);
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
	int current = GetEntProp(client, Prop_Send, "m_ArmorValue");
	SetEntProp(client, Prop_Send, "m_ArmorValue", current + amount);
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
	int current = GetEntProp(client, Prop_Send, "m_ArmorValue") - amount;
	
	if (current < 1)
		current = 1;
	
	SetEntProp(client, Prop_Send, "m_ArmorValue", current);
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

stock int CSGO_GetWeaponSlot(const char[] weapon)
{
	if (StrContains(weapon, "AK-47", false) != -1 || StrContains(weapon, "ak47", false) != -1)
		return 0;
	else if (StrContains(weapon, "AUG", false) != -1)
		return 0;
	else if (StrContains(weapon, "AWP", false) != -1)
		return 0;
	else if (StrContains(weapon, "CZ75-Auto", false) != -1 || StrContains(weapon, "cz75a", false) != -1)
		return 1;
	else if (StrContains(weapon, "Desert Eagle", false) != -1 || StrContains(weapon, "deagle", false) != -1)
		return 1;
	else if (StrContains(weapon, "Dual Beretta", false) != -1 || StrContains(weapon, "elite", false) != -1)
		return 1;
	else if (StrContains(weapon, "FAMAS", false) != -1)
		return 0;
	else if (StrContains(weapon, "Five-SeveN", false) != -1 || StrContains(weapon, "fiveseven", false) != -1)
		return 1;
	else if (StrContains(weapon, "G3SG1", false) != -1)
		return 0;
	else if (StrContains(weapon, "Galil AR", false) != -1 || StrContains(weapon, "galilar", false) != -1)
		return 0;
	else if (StrContains(weapon, "Glock", false) != -1)
		return 1;
	else if (StrContains(weapon, "Knife", false) != -1)
		return 2;
	else if (StrContains(weapon, "M249", false) != -1)
		return 0;
	else if (StrContains(weapon, "M4A1-S", false) != -1 || StrContains(weapon, "m4a1_silencer", false) != -1)
		return 0;
	else if (StrContains(weapon, "M4A4", false) != -1)
		return 0;
	else if (StrContains(weapon, "MAC-10", false) != -1)
		return 0;
	else if (StrContains(weapon, "MAG-7", false) != -1 || StrContains(weapon, "mac10", false) != -1)
		return 0;
	else if (StrContains(weapon, "MP5-SD", false) != -1 || StrContains(weapon, "mp5sd", false) != -1)
		return 0;
	else if (StrContains(weapon, "MP7", false) != -1)
		return 0;
	else if (StrContains(weapon, "MP9", false) != -1)
		return 0;
	else if (StrContains(weapon, "Negev", false) != -1)
		return 0;
	else if (StrContains(weapon, "Nova", false) != -1)
		return 0;
	else if (StrContains(weapon, "P2000", false) != -1)
		return 1;
	else if (StrContains(weapon, "P250", false) != -1)
		return 1;
	else if (StrContains(weapon, "P90", false) != -1)
		return 0;
	else if (StrContains(weapon, "Bizon", false) != -1)
		return 0;
	else if (StrContains(weapon, "R8", false) != -1 || StrContains(weapon, "Revolver", false) != -1)
		return 1;
	else if (StrContains(weapon, "SCAR-20", false) != -1 || StrContains(weapon, "scar20", false) != -1)
		return 0;
	else if (StrContains(weapon, "SG 553", false) != -1 || StrContains(weapon, "SG 556", false) != -1 || StrContains(weapon, "sg556", false) != -1)
		return 0;
	else if (StrContains(weapon, "SSG 08", false) != -1 || StrContains(weapon, "ssg08", false) != -1)
		return 0;
	else if (StrContains(weapon, "Sawed-Off", false) != -1 || StrContains(weapon, "sawedoff", false) != -1)
		return 0;
	else if (StrContains(weapon, "Tec-9", false) != -1 || StrContains(weapon, "tec9", false) != -1)
		return 1;
	else if (StrContains(weapon, "UMP-45", false) != -1 || StrContains(weapon, "ump45", false) != -1)
		return 0;
	else if (StrContains(weapon, "USP-S", false) != -1 || StrContains(weapon, "usp_silencer", false) != -1)
		return 1;
	else if (StrContains(weapon, "XM1014", false) != -1)
		return 0;
	
	return -1;
}