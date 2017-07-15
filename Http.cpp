#include "stdafx.h"
#include "Http.h"
#include <curl/curl.h>  
#include <string>
#include "HttpException.h"


using namespace std;

Http::Http()
{
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
}

Http::~Http()
{
	curl_easy_cleanup(curl);
}

CURLcode Http::Get(CString url)
{
	CURLcode res;

	char* u = (LPSTR)(LPCTSTR)url;

	string data;
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL,u);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
		res = curl_easy_perform(curl);
		if (res != CURLE_OK)
			throw HttpException(CString(curl_easy_strerror(res)));
		curl_easy_cleanup(curl);
	}
	else {
		OutputDebugString(_T("Curl Init Failed"));
	}
	OutputDebugString(CString(data.c_str()));

	response = CString(data.c_str());

	return res;
}

size_t Http::Reply(void * ptr, size_t size, size_t nmemb, void * stream)
{
	string* str = (string*)stream;
	(*str).append((char*)ptr, size*nmemb);
	return size*nmemb;
}

CString Http::GetResponse()
{
	return response;
}
