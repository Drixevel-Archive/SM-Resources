//Pragma
#pragma semicolon 1
#pragma newdecls required

//Includes
#include <sourcemod>

public Plugin myinfo = 
{
	name = "[TF2] No Waiting For Players",
	author = "Drixevel",
	description = "Disables No Waiting For Players in TF2 by just cancelling it on spawn.",
	version = "1.0.0",
	url = "https://drixevel.dev/"
};

public void TF2_OnWaitingForPlayersStart()
{
	ServerCommand("mp_waitingforplayers_cancel 1");
}