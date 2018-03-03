#pragma once
#include <string>
using namespace std;

class Transcode
{
public:
	static void Unicode_to_UTF8(const wchar_t* in, size_t len, std::string& out);
	static void UTF8_to_Unicode(const char* in, size_t len, std::wstring& out);

	static void ANSI_to_Unicode(const char* in, size_t len, std::wstring& out);
	static void ANSI_to_UTF8(const char* in, size_t len, std::string& out);

	static void Unicode_to_ANSI(const wchar_t* wstr,string& str);
};

//
//class CommonUse
//{
//public:
//	static bool			CreateDirectory_EveryOneUser( const void* pDirName, bool bAnsi );
//	static wstring		MakePathFromAllUser( const wchar_t* szSub );
//	static bool			CheckOrCreateConfigFile(const wchar_t* szFile);
//	static void			SetConfiginiString( const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,const wchar_t* szValue=L"" );
//	static wstring		GetConfiginiString(const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,const wchar_t* szDefualt=L"" );
//	static void			SetConfiginiInt(const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,int nValue=0 );
//	static int			GetConfiginiInt(const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,int nDefualt=0 );
//
//	static wstring		GetAppVersion(const wchar_t* szAppPath );
//	static wstring		GetLocalTimeToString();
//};