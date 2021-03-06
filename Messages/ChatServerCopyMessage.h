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

#ifndef __CHAT_SERVER_COPY_MESSAGE__
#define __CHAT_SERVER_COPY_MESSAGE__

class ChatServerCopyMessage : public ChatAbstractServerMessage
{
public:
	int receiverId;
	std::string receiverName;

	uint16 GetOpcode() const
	{ return SMSG_CHAT_SERVER_COPY; }

	ChatServerCopyMessage()
	{
	}

	ChatServerCopyMessage(int8 channel, std::string content, int timestamp, std::string fingerprint, int receiverId, std::string receiverName) : ChatAbstractServerMessage(channel, content, timestamp, fingerprint), receiverId(receiverId), receiverName(receiverName)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		ChatAbstractServerMessage::Serialize(data);
		data<<receiverId<<receiverName;
	}

	void Deserialize(ByteBuffer& data)
	{
		ChatAbstractServerMessage::Deserialize(data);
		data>>receiverId>>receiverName;
	}
};

#endif