#pragma once


enum class ERenderOrder
{
	BACKGROUND = -1000,
	COLMAP = -999,
	BALL = -1,
	PLAYER = 0,
	UI = 10000,
};

enum class ECollisionGroup
{
	PlayerBody,
	MonsterBody,
};
