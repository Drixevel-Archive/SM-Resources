/**
* .-----.                      .---.         .-.                          .---.
* `-. .-'                      : .--'       .' `.                         `--. :
*   : : .--.  .--.  ,-.,-.,-.  : `;.--. .--.`. .'.--.  .--.  .--.  .--.     ,','
*   : :' '_.'' .; ; : ,. ,. :  : :' .; :: ..': : : ..'' '_.'`._-.'`._-.'  .'.'_
*   :_;`.__.'`.__,_;:_;:_;:_;  :_;`.__.':_;  :_; :_;  `.__.'`.__.'`.__.'  :____;
*                                                                                
*	This include contains a ton of useful stocks and functions you can use for Team Fortress 2.
*	Author: Keith Warren (Drixevel)
*	https://github.com/Drixevel
*
*	NOTE: The best way to use this include is to copy and paste into your projects manually.
*	Credits: Pelipoika, 11530, Chdata, Tylerst, aIM
**/

#if defined _misc_tf_included
#endinput
#endif
#define _misc_tf_included

#undef REQUIRE_EXTENSIONS
#tryinclude <tf2_stocks>
#tryinclude <tf2items>
#define REQUIRE_EXTENSIONS

#undef REQUIRE_PLUGIN
#tryinclude <tf2attributes>
#define REQUIRE_PLUGINS

#define QUALITY_NAME_LENGTH 32
#define ATTRIBUTE_NAME_LENGTH 64

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
*	return	N/A
**/
stock void TF2_SetClass(int client, TFClassType class, bool persistent = true)
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
		DispatchKeyValue(glow, "Mode", "1"); //Mode is currently broken.
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
*	This version is cleaner and doesn't use an entity.
*
*	team	Team index to have the win. (unassigned = draw)
*	map_valid	Passive check to use in your plugins to make sure the map is running.
*
*	return	void
**/
stock void TF2_ForceWin(TFTeam team = TFTeam_Unassigned)
{
	int iFlags = GetCommandFlags("mp_forcewin");
	SetCommandFlags("mp_forcewin", iFlags &= ~FCVAR_CHEAT);
	ServerCommand("mp_forcewin %i", view_as<int>(team));
	SetCommandFlags("mp_forcewin", iFlags);
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
stock void TF2_ForceRoundWin(TFTeam team = TFTeam_Unassigned)
{
	//Need to make sure the world exists in order for entities to be created.
	if (!IsValidEntity(0))
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
stock bool TF2_IsArena()
{
	return FindEntityByClassname(-1, "tf_logic_arena") != -1;
}

/**
*	Simple check if the mode is mvm or not.
*
*	return	Is MvM or not.
**/
stock bool TF2_IsMvM()
{
	return FindEntityByClassname(-1, "tf_logic_mann_vs_machine") != -1;
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
		if (GetEntPropEnt(entity, Prop_Send, "m_hOwnerEntity") == client)
			TF2_RemoveWearable(client, entity);
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
stock int TF2_SpawnRagdoll(int client, float destruct = 10.0, int flags = 0, float vel[3] = NULL_VECTOR)
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

stock int TF2_CreateRagdoll(float origin[3], float angles[3], int class, int team, int skin, float destruct = 10.0, int flags = 0, float vel[3] = NULL_VECTOR)
{
	int ragdoll = CreateEntityByName("tf_ragdoll");

	if (IsValidEntity(ragdoll))
	{
		TeleportEntity(ragdoll, origin, angles, NULL_VECTOR);

		SetEntProp(ragdoll, Prop_Send, "m_iPlayerIndex", -1);
		SetEntProp(ragdoll, Prop_Send, "m_iTeam", team);
		SetEntProp(ragdoll, Prop_Send, "m_iClass", class);
		SetEntProp(ragdoll, Prop_Data, "m_nSkin", skin);
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
		
		SetEntPropVector(ragdoll, Prop_Send, "m_vecRagdollOrigin", origin);
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
*	Creates an item entity and gives it to a client.
*
*	client	Client index.
*	index	Index of the weapon.
*	quality	Quality of the weapon.
*	level	Level of the weapon.
*
*	return	Entity index.
**/
stock int TF2_GiveItem(int client, char[] classname, int index, TF2Quality quality = TF2Quality_Normal, int level = 0, const char[] attributes = "")
{
	char sClass[64];
	strcopy(sClass, sizeof(sClass), classname);
	
	if (StrContains(sClass, "saxxy", false) != -1)
	{
		switch (TF2_GetPlayerClass(client))
		{
			case TFClass_Scout: strcopy(sClass, sizeof(sClass), "tf_weapon_bat");
			case TFClass_Sniper: strcopy(sClass, sizeof(sClass), "tf_weapon_club");
			case TFClass_Soldier: strcopy(sClass, sizeof(sClass), "tf_weapon_shovel");
			case TFClass_DemoMan: strcopy(sClass, sizeof(sClass), "tf_weapon_bottle");
			case TFClass_Engineer: strcopy(sClass, sizeof(sClass), "tf_weapon_wrench");
			case TFClass_Pyro: strcopy(sClass, sizeof(sClass), "tf_weapon_fireaxe");
			case TFClass_Heavy: strcopy(sClass, sizeof(sClass), "tf_weapon_fists");
			case TFClass_Spy: strcopy(sClass, sizeof(sClass), "tf_weapon_knife");
			case TFClass_Medic: strcopy(sClass, sizeof(sClass), "tf_weapon_bonesaw");
		}
	}
	else if (StrContains(sClass, "shotgun", false) != -1)
	{
		switch (TF2_GetPlayerClass(client))
		{
			case TFClass_Soldier: strcopy(sClass, sizeof(sClass), "tf_weapon_shotgun_soldier");
			case TFClass_Pyro: strcopy(sClass, sizeof(sClass), "tf_weapon_shotgun_pyro");
			case TFClass_Heavy: strcopy(sClass, sizeof(sClass), "tf_weapon_shotgun_hwg");
			case TFClass_Engineer: strcopy(sClass, sizeof(sClass), "tf_weapon_shotgun_primary");
		}
	}
	
	Handle item = TF2Items_CreateItem(PRESERVE_ATTRIBUTES | FORCE_GENERATION);	//Keep reserve attributes otherwise random issues will occur... including crashes.
	TF2Items_SetClassname(item, sClass);
	TF2Items_SetItemIndex(item, index);
	TF2Items_SetQuality(item, view_as<int>(quality));
	TF2Items_SetLevel(item, level);
	
	char sAttrs[32][32];
	int count = ExplodeString(attributes, " ; ", sAttrs, 32, 32);
	
	if (count > 1)
	{
		TF2Items_SetNumAttributes(item, count / 2);
		
		int i2;
		for (int i = 0; i < count; i += 2)
		{
			TF2Items_SetAttribute(item, i2, StringToInt(sAttrs[i]), StringToFloat(sAttrs[i + 1]));
			i2++;
		}
	}
	else
		TF2Items_SetNumAttributes(item, 0);

	int weapon = TF2Items_GiveNamedItem(client, item);
	delete item;
	
	if (StrEqual(sClass, "tf_weapon_builder", false) || StrEqual(sClass, "tf_weapon_sapper", false))
	{
		SetEntProp(weapon, Prop_Send, "m_iObjectType", 3);
		SetEntProp(weapon, Prop_Data, "m_iSubType", 3);
		SetEntProp(weapon, Prop_Send, "m_aBuildableObjectTypes", 0, _, 0);
		SetEntProp(weapon, Prop_Send, "m_aBuildableObjectTypes", 0, _, 1);
		SetEntProp(weapon, Prop_Send, "m_aBuildableObjectTypes", 0, _, 2);
		SetEntProp(weapon, Prop_Send, "m_aBuildableObjectTypes", 1, _, 3);
	}
	
	if (StrContains(sClass, "tf_weapon_", false) == 0)
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
		
	int ef_bonemerge = (1 << 0);
	int ef_fastcull = (1 << 7);
	
	SetEntProp(entity, Prop_Send, "m_nModelIndex", viewmodel);
	SetEntProp(entity, Prop_Send, "m_fEffects", ef_bonemerge | ef_fastcull);
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

stock int TF2_GetCash(int client)
{
	return GetEntProp(client, Prop_Send, "m_nCurrency");
}

stock bool TF2_SetCash(int client, int value)
{
	if (value < 0)
		return false;
	
	SetEntProp(client, Prop_Send, "m_nCurrency", value);
	return true;
}

stock bool TF2_AddCash(int client, int value)
{
	int total = GetEntProp(client, Prop_Send, "m_nCurrency") + value;
	SetEntProp(client, Prop_Send, "m_nCurrency", total);
	return true;
}

stock bool TF2_RemoveCash(int client, int value)
{
	int total = GetEntProp(client, Prop_Send, "m_nCurrency") - value;
	
	if (total < 0)
	{
		SetEntProp(client, Prop_Send, "m_nCurrency", 0);
		return false;
	}
	
	SetEntProp(client, Prop_Send, "m_nCurrency", total);
	return true;
}