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

#ifndef __CONSOLE_MESSAGE__
#define __CONSOLE_MESSAGE__

enum ConsoleMessageType
{
	CONSOLE_TEXT_MESSAGE = 0,
	CONSOLE_INFO_MESSAGE = 1,
	CONSOLE_ERR_MESSAGE = 2,
};

class ConsoleMessage : public DofusMessage
{
public:
	virtual uint32 GetOpcode() const
	{ return SMSG_CONSOLE; }

	ConsoleMessage(int8 type, std::string content)
	{
		m_buffer<<type<<content;
	}
};

#endif