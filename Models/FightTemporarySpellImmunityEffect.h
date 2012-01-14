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

#ifndef __FIGHT_TEMPORARY_SPELL_IMMUNITY_EFFECT__
#define __FIGHT_TEMPORARY_SPELL_IMMUNITY_EFFECT__

class FightTemporarySpellImmunityEffect : public AbstractFightDispellableEffect
{
public:
	int immuneSpellId;

	uint16 GetProtocol() const
	{ return FIGHT_TEMPORARY_SPELL_IMMUNITY_EFFECT; }

	FightTemporarySpellImmunityEffect()
	{
	}

	FightTemporarySpellImmunityEffect(int uid, int targetId, int16 turnDuration, int8 dispelable, int16 spellId, int parentBoostUid, int immuneSpellId) : AbstractFightDispellableEffect(uid, targetId, turnDuration, dispelable, spellId, parentBoostUid), immuneSpellId(immuneSpellId)
	{
	}

	void Serialize(ByteBuffer& data)
	{
		AbstractFightDispellableEffect::Serialize(data);
		data<<immuneSpellId;
	}

	void Deserialize(ByteBuffer& data)
	{
		AbstractFightDispellableEffect::Deserialize(data);
		data>>immuneSpellId;
	}
};

typedef boost::shared_ptr<FightTemporarySpellImmunityEffect> FightTemporarySpellImmunityEffectPtr;

#endif