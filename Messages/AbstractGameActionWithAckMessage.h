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

#ifndef __ABSTRACT_GAME_ACTION_WITH_ACK_MESSAGE__
#define __ABSTRACT_GAME_ACTION_WITH_ACK_MESSAGE__

class AbstractGameActionWithAckMessage : public AbstractGameActionMessage
{
public:
	int16 waitAckId;

	uint16 GetOpcode() const
	{ return SMSG_ABSTRACT_GAME_ACTION_WITH_ACK; }

	AbstractGameActionWithAckMessage()
	{
	}

	AbstractGameActionWithAckMessage(int16 actionId, int sourceId, int16 waitAckId) : AbstractGameActionMessage(actionId, sourceId), waitAckId(waitAckId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		AbstractGameActionMessage::Serialize(data);
		data<<waitAckId;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractGameActionMessage::Deserialize(data);
		data>>waitAckId;
	}
};

#endif