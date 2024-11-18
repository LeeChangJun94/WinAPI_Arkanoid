#pragma once


enum class ERenderOrder
{
	DETHLINE = -1500,
	BACKGROUND = -1000,
	COLMAP = -999,
	BALL = -2,
	PLAYER = 0,
	UI = 10000,
	FADE = 20000,
};

enum class ECollisionGroup
{
	Brick,
	Ball,
	Bullet,
	Item,
	Vaus,
	DethLine,
	MousePoint,
};
