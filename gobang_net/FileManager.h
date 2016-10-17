#pragma once
#ifndef __FILEMANAGER__H__
#define __FILEMANAGER__H__


#include "Manager.h"

class FileManager : public Manager
{
	SingletonBuilder(FileManager)
public:
	virtual void startUp();
	virtual void shutDown();

private:


};








#endif // !__FILEMANAGER__H__
