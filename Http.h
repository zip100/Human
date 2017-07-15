#pragma once
#include <curl/curl.h>  

class Http
{
public:
	CURL *curl;
	CString response;

	Http();
	~Http();
	CURLcode Http::Get(CString url);
	size_t static Reply(void * ptr, size_t size, size_t nmemb, void * stream);
	CString GetResponse();
};

