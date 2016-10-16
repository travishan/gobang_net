#pragma once
#ifndef __MANAGER__H__
#define __MANAGER__H__


class Manager
{
public:
	virtual ~Manager() {} 
	virtual void startUp() = 0;
	virtual void shutDown() = 0;
};



#endif // !__MANAGER__H__
