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

#ifndef __JOB_EXPERIENCE_MULTI_UPDATE_MESSAGE__
#define __JOB_EXPERIENCE_MULTI_UPDATE_MESSAGE__

class JobExperienceMultiUpdateMessage : public DofusMessage
{
public:
	std::vector<JobExperiencePtr> experiencesUpdate;

	uint16 GetOpcode() const
	{ return SMSG_JOB_EXPERIENCE_MULTI_UPDATE; }

	JobExperienceMultiUpdateMessage()
	{
	}

	JobExperienceMultiUpdateMessage(std::vector<JobExperiencePtr>& experiencesUpdate) : experiencesUpdate(experiencesUpdate)
	{
	}

	void Serialize(ByteBuffer& data) const
	{
		uint16 size = experiencesUpdate.size();
		data<<size;
		for(uint16 a = 0; a < size; ++a)
			experiencesUpdate[a]->Serialize(data);
	}

	void Deserialize(ByteBuffer& data)
	{
		experiencesUpdate.clear();
		uint16 size;
		data>>size;
		for(uint16 a = 0; a < size; ++a)
		{
			JobExperiencePtr model(new JobExperience);
			model->Deserialize(data);
			experiencesUpdate.push_back(model);
		}
	}
};

#endif