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

#ifndef __PARTY_CANCEL_INVITATION_MESSAGE__
#define __PARTY_CANCEL_INVITATION_MESSAGE__

class PartyCancelInvitationMessage : public AbstractPartyMessage
{
public:
	int guestId;

	uint16 GetOpcode() const
	{ return CMSG_PARTY_CANCEL_INVITATION; }

	PartyCancelInvitationMessage()
	{
	}

	PartyCancelInvitationMessage(int partyId, int guestId) : AbstractPartyMessage(partyId), guestId(guestId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Serialize(data);
		data<<guestId;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractPartyMessage::Deserialize(data);
		data>>guestId;
	}
};

#endif