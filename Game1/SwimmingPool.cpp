#include "stdafx.h"

SwimmingPool* SwimmingPool::Create(string name)
{
	SwimmingPool* temp = new SwimmingPool();
	temp->LoadFile("swimmingpool2.xml");

	return temp;
}

void SwimmingPool::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}

SwimmingPool::SwimmingPool()
{
}

SwimmingPool::~SwimmingPool()
{
}


