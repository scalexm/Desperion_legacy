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

#ifndef __GAME_ROLE_PLAY_FIGHT_REQUEST_CANCELED_MESSAGE__
#define __GAME_ROLE_PLAY_FIGHT_REQUEST_CANCELED_MESSAGE__

class GameRolePlayFightRequestCanceledMessage : public DofusMessage
{
public:
	int fightId;
	int sourceId;
	int targetId;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ROLE_PLAY_FIGHT_REQUEST_CANCELED; }

	GameRolePlayFightRequestCanceledMessage()
	{
	}

	GameRolePlayFightRequestCanceledMessage(int fightId, int sourceId, int targetId) : fightId(fightId), sourceId(sourceId), targetId(targetId)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		data<<fightId<<sourceId<<targetId;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>fightId>>sourceId>>targetId;
	}
};

#endif