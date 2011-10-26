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

#ifndef __DOFUS_MODEL__
#define __DOFUS_MODEL__

class DofusModel
{
protected:
	ByteBuffer m_buffer;
public:
	virtual uint16 GetProtocol() const = 0;

	operator ByteBuffer() const
	{ return m_buffer; }
	
	void Clear()
	{ m_buffer.Clear(); }

	DofusModel()
	{
	}
};

#endif