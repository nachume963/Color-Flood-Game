#pragma once
#include "Button.h"

class Exit : public Button
{
public:
	Exit();
	~Exit();

	virtual void click(Controller & controller) override;
};

