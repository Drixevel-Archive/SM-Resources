//Pragma
#pragma semicolon 1
#pragma newdecls required

//Sourcemod Includes
#include <sourcemod>

//ConVars

//Globals
Database g_Database;

public Plugin myinfo = 
{
	name = "", 
	author = "", 
	description = "", 
	version = "1.0.0", 
	url = ""
};

public void OnPluginStart()
{
	RegAdminCmd("sm_testquery", Command_TestQuery, ADMFLAG_ROOT, "Tests a database query.");	//Admin flag so the public doesn't have access to tons of queries on command except for admins.
}

public void OnConfigsExecuted()
{
	//Check if our connection is invalid.
	//If invalid, create a new connection.
	//'default' is the configuration to use.
	if (g_Database == null)
		Database.Connect(OnSQLConnect, "default");	//https://sm.alliedmods.net/new-api/dbi/Database/Connect
}

public void OnSQLConnect(Database db, const char[] error, any data)
{
	//Check if we have a valid database connect.
	//If not, give an error and don't store it globally.
	if (db == null)
	{
		LogError("Error while connecting to database: %s", error);
		return;
	}
	
	//This might be unnecessary but it's always best to be safe.
	//Checks if we have a valid connection and deletes the connection we just made if so.
	if (g_Database != null)
	{
		delete db;
		return;
	}
	
	//Save our connection for use later and give a handy console message.
	//https://sm.alliedmods.net/new-api/dbi/Database
	g_Database = db;
	LogMessage("Connected to database successfully.");
}

public Action Command_TestQuery(int client, int args)
{
	//Can't create a query if we don't have a valid database connection.
	if (g_Database == null)
	{
		ReplyToCommand(client, "Database isn't connected for use.");
		return Plugin_Handled;
	}
	
	//Always pass the userid of a client through the data parameter and turn it into an index on the other end for queries.
	//https://sm.alliedmods.net/new-api/dbi/Database/Query
	g_Database.Query(OnQueryFinished, "SELECT * FROM `table_name`;", GetClientUserId(client), DBPrio_Low);
	
	return Plugin_Handled;
}

public void OnQueryFinished(Database db, DBResultSet results, const char[] error, any data)
{
	//No valid results for this query.
	if (results == null)
	{
		LogError("Error while fetching results: %s", error);
		return;
	}
	
	//Create an integer to store the client index then turn the userid we passed into an index and see if it's still valid.
	int client;
	if ((client = GetClientOfUserId(data)) == 0)
		return;
	
	//Use a while statement if we know there will be more than 1 row available, otherwise use an if statement.
	//We have to fetch the available rows in order to save the data and use it.
	int value; float value_float; char value_string[32];
	while (results.FetchRow())
	{
		//Values fetched always start from 1 for the 1st column and onwards.
		//https://sm.alliedmods.net/new-api/dbi/DBResultSet
		value = results.FetchInt(1);									//Save the 1st columns value if it exists as an integer.
		value_float = results.FetchFloat(2);							//Save the 2nd columns value if it exists as a float.
		results.FetchString(3, value_string, sizeof(value_string));		//Save the 3rd columns value if it exists as a string.
		
		ReplyToCommand(client, "value = %i, value_float = %f, value_string = %s", value, value_float, value_string);
	}
}