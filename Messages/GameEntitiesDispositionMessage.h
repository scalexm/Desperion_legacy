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

#ifndef __GAME_ENTITIES_DISPOSITION_MESSAGE__
#define __GAME_ENTITIES_DISPOSITION_MESSAGE__

class GameEntitiesDispositionMessage : public DofusMessage
{
public:
	std::vector<IdentifiedEntityDispositionInformationsPtr> dispositions;

	uint16 GetOpcode() const
	{ return SMSG_GAME_ENTITIES_DISPOSITION; }

	GameEntitiesDispositionMessage()
	{
	}

	GameEntitiesDispositionMessage(std::vector<IdentifiedEntityDispositionInformationsPtr>& dispositions) : dispositions(dispositions)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = dispositions.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
		{
			data<<dispositions[a]->GetProtocol();
			dispositions[a]->Serialize(data);
		}
	}

	void Deserialize(ByteBuffer& data)
	{
		dispositions.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			uint16 protocol;
			data>>protocol;
			IdentifiedEntityDispositionInformationsPtr model(Desperion::ProtocolTypeManager::GetIdentifiedEntityDispositionInformations(protocol));
			model->Deserialize(data);
			dispositions.push_back(model);
		}
	}
};

#endif