//
// Created by Daggersoath on 18/05/2023.
//

#pragma once

#include "Game.h"

class Pong : Game {
public:
	Pong() = default;
	~Pong() = default;

	void Start() override;

private:

	int scores[2]{0,0};
	float position[2]{0,0};
	float ballPosition[2]{0,0};
	float ballDirection[2]{1,1};
	float ballspeed = 30.f;
	float paddleSpeed = 30.f;

};
