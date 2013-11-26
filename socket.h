#ifndef __MYSOCKET
#define __MYSOCKET
#include "dll.h"
#include "sclient.h"

class CMapPlugin;
class CMySocket : public CClient
{
	CMapPlugin *Parent;

	virtual void OnLine(unsigned char *buffer);
	virtual void OnAfterMainLoop();
	virtual void OnBeforeMainLoop();

public:
	CMySocket(CMapPlugin *parent);
	~CMySocket();

	
};

#endif