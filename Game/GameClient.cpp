/*
	This file is part of Desperion.
	Copyright 2010, 2011 LittleScaraby, Nekkro

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

template<> GameClient * Singleton<GameClient>::m_singleton = NULL;
template<> GameClient::HandlerStorageMap BaseSession<ComPacketHandler>::m_handlers;

GameClient::~GameClient()
{
}

void GameClient::Connect()
{
	boost::asio::ip::tcp::endpoint host(boost::asio::ip::address::from_string("127.0.0.1"),
		Desperion::Config::Instance().GetUInt(DISTANT_SERVER_PORT_STRING, DISTANT_SERVER_PORT_DEFAULT));
	m_socket->async_connect(host, boost::bind(&GameClient::Start, this));
}

void GameClient::Start()
{
	try
	{
		int8 test[2] = {0, 0};
		boost::asio::write(*m_socket, boost::asio::buffer(test, 2));
	}catch(const std::exception& e)
	{
		CloseConnection();
		return;
	}

	Packet data(CMSG_CONNECT);
	data<<uint16(Desperion::Config::Instance().GetUInt(LOCAL_SERVER_ID_STRING, LOCAL_SERVER_ID_DEFAULT));
	data<<Desperion::Config::Instance().GetString(LOCAL_SERVER_AUTH_KEY_STRING, LOCAL_SERVER_AUTH_KEY_DEFAULT);
	Send(data);

	Packet state(CMSG_STATE);
	state<<m_state;
	Send(state);

	Run();
}