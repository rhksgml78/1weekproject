#pragma once
class SwimmingPool : public Actor
{
public:
	static SwimmingPool* Create(string name = "SwimmingPool");

private:
	SwimmingPool();
	~SwimmingPool();
public:
	void	Release() override;
};

