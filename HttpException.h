#pragma once

#include<exception>    
using namespace std;

class HttpException :public exception
{
public:
	HttpException(CString m);
	~HttpException();
	CString msg;
	CString what();
};

