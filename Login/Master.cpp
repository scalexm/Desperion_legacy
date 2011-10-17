/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby

    Desperion is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Desperion is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Desperion.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "StdAfx.h"

template<> Desperion::Master* Singleton<Desperion::Master>::m_singleton = NULL;

namespace Desperion
{
	Database* sDatabase = NULL;

	void OnSignal(int s)
	{
		switch (s)
		{
		case SIGINT:
		case SIGTERM:
		case SIGABRT:
#ifdef _WIN32
		case SIGBREAK:
#endif
			Master::Instance().Stop();
			break;
		}
		signal(s, OnSignal);
	}

	void HookSignals()
	{
		signal( SIGINT, OnSignal );
		signal( SIGTERM, OnSignal );
		signal( SIGABRT, OnSignal );
	#ifdef _WIN32
		signal( SIGBREAK, OnSignal );
	#endif
	}

	void UnHookSignals()
	{
		signal( SIGINT, 0 );
		signal( SIGTERM, 0 );
		signal( SIGABRT, 0 );
	#ifdef _WIN32
		signal( SIGBREAK, 0 );
	#endif
	}

	Master::~Master()
	{
		CleanupRandomNumberGenerators();
		delete sListener;
		delete eListener;
	}

	bool Master::StartUpDatabase()
	{
		Log::Instance().outNotice("Database", "Connecting to the local database...");
		{
			barGoLink bar(1);
			sDatabase = new Database(3);
			if(!sDatabase->Init(Config::Instance().GetString(LOCAL_DATABASE_HOST_STRING, LOCAL_DATABASE_HOST_DEFAULT), 
				Config::Instance().GetUInt(LOCAL_DATABASE_PORT_STRING, LOCAL_DATABASE_PORT_DEFAULT), 
				Config::Instance().GetString(LOCAL_DATABASE_USER_STRING, LOCAL_DATABASE_USER_DEFAULT), 
				Config::Instance().GetString(LOCAL_DATABASE_PASSWORD_STRING, LOCAL_DATABASE_PASSWORD_DEFAULT), 
				Config::Instance().GetString(LOCAL_DATABASE_NAME_STRING, LOCAL_DATABASE_NAME_DEFAULT)))
				return false;
			bar.step();
		}
		Log::Instance().outNotice("Database", "Connection successful!\n\n");

		return true;
	}

	bool Master::Run(int argc, char **argv)
	{
		std::string logPath = "logs";
		std::string configPath = "config";
		std::string logFlags = "0";

		m_startTime = getMSTime();

		new Log;
		Log::Instance().Init(logPath, OUTLOG_ALL);

		InitRandomNumberGenerators();

		SetApplicationTitle("Desperion2 LoginServer v" + m_version);
		Log::Instance().outColor(TBLUE, 	",------,  ,-----. ,-----, ,------. ,-----. ,------.  ,------. ,------, ,,    ,,");
		Log::Instance().outColor(TBLUE, 	"| ,--,  ` | .---' |  ,--` | ,--, | | .---' | ,--, |  `--||--' | ,--, | ||\\   ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--.  |  `--, | |  | | | |--.  | |  | |     ||    | |  | | || \\  ||");
		Log::Instance().outColor(TBLUE, 	"| |  |  | | |--'  `---, | | `--` | | |--'  | `--` ,     ||    | |  | | ||  \\ ||");
		Log::Instance().outColor(TBLUE, 	"| '--'  , | '---, ,---| | | ,----` | '---, | ,-\\  \\  .--||--, | '--' | ||   \\||");
		Log::Instance().outColor(TBLUE, 	"`------`  `-----' `-----` `-`      `-----' `-`  '--' `------` `------` ``    `'");
		Log::Instance().outColor(TBLUE, "By Little-scaraby for Dofus 2.0\n\n");
		Log::Instance().outColor(TBLUE, "LoginServer v%s\n\n\n", m_version.c_str());
	
		new Config;
		Config::Instance().Init(configPath, TARGET_REALM);

		if(!StartUpDatabase())
			return false;

		new World;
		World::Instance().Init();

		sListener = new SocketListener<Session>(m_service);
		sListener->Init(Config::Instance().GetUInt(LOCAL_SERVER_PORT_STRING, LOCAL_SERVER_PORT_DEFAULT));
		if(sListener->IsOpen())
			Log::Instance().outNotice("Network", "Local socket running!");
		else
		{
			Log::Instance().outError("Error: Local socket");
			return false;
		}

		eListener = new SocketListener<GameSession>(m_service);
		eListener->Init(Config::Instance().GetUInt(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));
		if(eListener->IsOpen())
			Log::Instance().outNotice("Network", "Distant socket running!\n");
		else
		{
			Log::Instance().outError("Error: Distant socket");
			return false;
		}
	
		Log::Instance().outColor(TBLUE, "Uptime: %ums", getMSTime() - m_startTime);
		Log::Instance().outColor(TBLUE, "Type Ctrl+C to safely shutdown the server.\n");

		sListener->Run();
		eListener->Run();

		HookSignals();
		try
		{
			m_service.run();
		}catch(const std::exception& err)
		{
			Log::Instance().outError("Unhandled exception: %s", err.what());
		}
		UnHookSignals();
		return true;
	}

}