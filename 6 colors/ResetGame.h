#pragma once
#include "Button.h"

class ResetGame : public Button
{
public:
	ResetGame();
	~ResetGame();

	virtual void click(Controller & controller) override;
};

