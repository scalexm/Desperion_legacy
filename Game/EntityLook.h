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

#ifndef __ENTITY_LOOK__
#define __ENTITY_LOOK__

class EntityLook : public DofusModel
{
public:
	virtual uint16 GetProtocol() const
	{ return ENTITY_LOOK; }

	EntityLook(DEntityLook& look)
	{
		m_buffer<<look.Serialize(-1);
	}

	EntityLook(DEntityLook& look, int guid)
	{
		m_buffer<<look.Serialize(guid);
	}

	EntityLook(DEntityLook& look, Character* ch);
};

#endif