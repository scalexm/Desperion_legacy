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

#ifndef __UPDATE_MOUNT_BOOST_MESSAGE__
#define __UPDATE_MOUNT_BOOST_MESSAGE__

class UpdateMountBoostMessage : public DofusMessage
{
public:
	int64 rideId;
	std::vector<UpdateMountBoostPtr> boostToUpdateList;

	uint16 GetOpcode() const
	{ return SMSG_UPDATE_MOUNT_BOOST; }

	UpdateMountBoostMessage()
	{
	}

	UpdateMountBoostMessage(int64 rideId, std::vector<UpdateMountBoostPtr>& boostToUpdateList) : rideId(rideId), boostToUpdateList(boostToUpdateList)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<rideId;
		uint16 size = boostToUpdateList.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<boostToUpdateList[a]->GetProtocol();
			boostToUpdateList[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>rideId;
		boostToUpdateList.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			UpdateMountBoostPtr model(Desperion::ProtocolTypeManager::GetUpdateMountBoost(protocol));
			model->Deserialize(data);
			boostToUpdateList.push_back(model);
		}
	}
};

#endif