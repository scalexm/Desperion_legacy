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

#include "StdAfx.h"

namespace Desperion
{
	GameRolePlayActorInformations* ProtocolTypeManager::GetGameRolePlayActorInformations(uint16 protocol)
	{
		switch(protocol)
		{
		case GAME_ROLE_PLAY_NAMED_ACTOR_INFORMATIONS:
			return new GameRolePlayNamedActorInformations;
		case GAME_ROLE_PLAY_HUMANOID_INFORMATIONS:
			return new GameRolePlayHumanoidInformations;
		case GAME_ROLE_PLAY_CHARACTER_INFORMATIONS:
			return new GameRolePlayCharacterInformations;
		default:
		case GAME_ROLE_PLAY_ACTOR_INFORMATIONS:
			return new GameRolePlayActorInformations;
		}
	}

	EntityDispositionInformations* ProtocolTypeManager::GetEntityDispositionInformations(uint16 protocol)
	{
		switch(protocol)
		{
		default:
		case ENTITY_DISPOSITION_INFORMATIONS:
			return new EntityDispositionInformations;
		}
	}

	HumanInformations* ProtocolTypeManager::GetHumanInformations(uint16 protocol)
	{
		switch(protocol)
		{
		default:
		case HUMAN_INFORMATIONS:
			return new HumanInformations;
		}
	}

	ObjectEffect* ProtocolTypeManager::GetObjectEffect(uint16 protocol)
	{
		switch(protocol)
		{
		case OBJECT_EFFECT_INTEGER:
			return new ObjectEffectInteger;
		case OBJECT_EFFECT_DICE:
			return new ObjectEffectDice;
		case OBJECT_EFFECT_MIN_MAX:
			return new ObjectEffectMinMax;
		case OBJECT_EFFECT_MOUNT:
			return new ObjectEffectMount;
		case OBJECT_EFFECT_CREATURE:
			return new ObjectEffectCreature;
		case OBJECT_EFFECT_STRING:
			return new ObjectEffectString;
		case OBJECT_EFFECT_DATE:
			return new ObjectEffectDate;
		case OBJECT_EFFECT_DURATION:
			return new ObjectEffectDuration;
		case OBJECT_EFFECT_LADDER:
			return new ObjectEffectLadder;
		default:
		case OBJECT_EFFECT:
			return new ObjectEffect;
		}
	}
}