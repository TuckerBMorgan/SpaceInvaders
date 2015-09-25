#pragma once


struct TGUID
{
	int number;
	
	bool operator==(TGUID other);

	static TGUID* CreateGUID();


	static int GUIDCount;

};

