#include "conf.h"
#include "socket.h"

#include <stdio.h>


CMySocket::CMySocket(CMapPlugin *parent)
{
	Parent = parent;
}

CMySocket::~CMySocket()
{

}

void CMySocket::OnLine(unsigned char *buffer)
{
	//Parent->OnLine(buffer);
}

void CMySocket::OnAfterMainLoop()
{
			
}

void CMySocket::OnBeforeMainLoop()
{

}