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

#ifndef __EXCHANGE_MOUNT_STERILIZE_FROM_PADDOCK_MESSAGE__
#define __EXCHANGE_MOUNT_STERILIZE_FROM_PADDOCK_MESSAGE__

class ExchangeMountSterilizeFromPaddockMessage : public DofusMessage
{
public:
	std::string name;
	int16 worldX;
	int16 worldY;
	std::string sterilizator;

	uint16 GetOpcode() const
	{ return SMSG_EXCHANGE_MOUNT_STERILIZE_FROM_PADDOCK; }

	ExchangeMountSterilizeFromPaddockMessage()
	{
	}

	ExchangeMountSterilizeFromPaddockMessage(std::string name, int16 worldX, int16 worldY, std::string sterilizator) : name(name), worldX(worldX), worldY(worldY), sterilizator(sterilizator)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		data<<name<<worldX<<worldY<<sterilizator;
	}

	void Deserialize(ByteBuffer& data)
	{
		data>>name>>worldX>>worldY>>sterilizator;
	}
};

#endif