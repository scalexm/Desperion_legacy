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

#ifndef __PROTECTED_ENTITY_WAITING_FOR_HELP_INFO__
#define __PROTECTED_ENTITY_WAITING_FOR_HELP_INFO__

class ProtectedEntityWaitingForHelpInfo : public DofusModel
{
public:
	int timeLeftBeforeFight;
	int waitTimeForPlacement;
	int8 nbPositionForDefensors;

	uint16 GetProtocol() const
	{ return PROTECTED_ENTITY_WAITING_FOR_HELP_INFO; }

	ProtectedEntityWaitingForHelpInfo()
	{
	}

	ProtectedEntityWaitingForHelpInfo(int timeLeftBeforeFight, int waitTimeForPlacement, int8 nbPositionForDefensors) : timeLeftBeforeFight(timeLeftBeforeFight), waitTimeForPlacement(waitTimeForPlacement), nbPositionForDefensors(nbPositionForDefensors)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<timeLeftBeforeFight<<waitTimeForPlacement<<nbPositionForDefensors;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>timeLeftBeforeFight>>waitTimeForPlacement>>nbPositionForDefensors;
	}
};

typedef boost::shared_ptr<ProtectedEntityWaitingForHelpInfo> ProtectedEntityWaitingForHelpInfoPtr;

#endif