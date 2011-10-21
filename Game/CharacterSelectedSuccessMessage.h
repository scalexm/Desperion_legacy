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

#ifndef __CHARACTER_SELECTED_SUCCESS_MESSAGE__
#define __CHARACTER_SELECTED_SUCCESS_MESSAGE__

class CharacterSelectedSuccessMessage : public DofusMessage
{
public:
	uint32 GetOpcode() const
	{ return SMSG_CHARACTER_SELECTED_SUCCESS; }

	CharacterSelectedSuccessMessage(CharacterMinimals* ch)
	{
		m_buffer<<CharacterBaseInformations(ch->id, ch->level, ch->name, ch->look, ch->onlineCharacter, ch->breed, ch->sex);
	}
};

#endif