#include "stdafx.h"
#include "HttpException.h"


HttpException::HttpException(CString m)
{
	msg = m;
}


HttpException::~HttpException()
{
}


CString HttpException::what()
{
	return msg;
}
