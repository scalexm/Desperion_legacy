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

void Session::HandleChatClientMultiMessage(ByteBuffer& packet)
{
	ChatClientMultiMessage data(packet);

	// TODO: gestion des differents timers, zones et ChatError en fonction du packet
	switch(data.channel)
	{
	case MULTI_CHANNEL_GLOBAL:
		m_char->GetMap()->Send(ChatServerMessage(data.channel, data.content, time(NULL), "", m_char->GetGuid(), m_char->GetName(),
			m_data[FLAG_GUID].intValue));
		break;
	default:
		return;
	}
}

void Session::HandleChatClientMultiWithObjectMessage(ByteBuffer& packet)
{
	ChatClientMultiWithObjectMessage data(packet);

	// idem
	switch(data.channel)
	{
	case MULTI_CHANNEL_GLOBAL:
		m_char->GetMap()->Send(ChatServerWithObjectMessage(data.channel, data.content, time(NULL), "", m_char->GetGuid(), m_char->GetName(),
			m_data[FLAG_GUID].intValue, data.objects));
		break;
	default:
		return;
	}
}

void Session::HandleChatClientPrivateMessage(ByteBuffer& packet)
{
	ChatClientPrivateMessage data(packet);
	
	CharacterMinimals* cm = World::Instance().GetCharacterMinimals(data.receiver);
	if(cm == NULL || cm->onlineCharacter == NULL)
	{
		Send(ChatErrorMessage(CHAT_ERROR_RECEIVER_NOT_FOUND));
		return;
	}
	else if(cm->id == m_char->GetGuid())
	{
		Send(ChatErrorMessage(CHAT_ERROR_INTERIOR_MONOLOGUE));
		return;
	}
	// TODO: ennemy/ignored, invisible/away

	time_t timestamp = time(NULL);
	Send(ChatServerCopyMessage(PSEUDO_CHANNEL_PRIVATE, data.content, timestamp, "", cm->id, cm->name));
	cm->onlineCharacter->GetSession()->Send(ChatServerMessage(PSEUDO_CHANNEL_PRIVATE, data.content, timestamp, "", m_char->GetGuid(), 
		m_char->GetName(), m_data[FLAG_GUID].intValue));
}

void Session::HandleChatClientPrivateWithObjectMessage(ByteBuffer& packet)
{
	ChatClientPrivateWithObjectMessage data(packet);

	CharacterMinimals* cm = World::Instance().GetCharacterMinimals(data.receiver);
	if(cm == NULL || cm->onlineCharacter == NULL)
	{
		Send(ChatErrorMessage(CHAT_ERROR_RECEIVER_NOT_FOUND));
		return;
	}
	else if(cm->id == m_char->GetGuid())
	{
		Send(ChatErrorMessage(CHAT_ERROR_INTERIOR_MONOLOGUE));
		return;
	}
	// idem

	time_t timestamp = time(NULL);
	Send(ChatServerCopyWithObjectMessage(PSEUDO_CHANNEL_PRIVATE, data.content, timestamp, "", cm->id, cm->name, data.objects));
	cm->onlineCharacter->GetSession()->Send(ChatServerWithObjectMessage(PSEUDO_CHANNEL_PRIVATE, data.content, timestamp, "", m_char->GetGuid(), 
		m_char->GetName(), m_data[FLAG_GUID].intValue, data.objects));
}