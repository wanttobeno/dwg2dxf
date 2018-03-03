//#include "StdAfx.h"
#include "transcode.h"
#include <shlobj.h>
#include <AccCtrl.h>
#include <AclAPI.h>
#include <TCHAR.h>
#include <shlwapi.h>

void Transcode::Unicode_to_UTF8( const wchar_t* in, size_t len, std::string& out )
{
	size_t nUtf8Len = WideCharToMultiByte(CP_UTF8,0,in,len,NULL,0,NULL,NULL);

	char* lpUTF8 = new char[nUtf8Len + 1];
	memset(lpUTF8, 0, nUtf8Len);

	WideCharToMultiByte(CP_UTF8,0,in,len,lpUTF8,nUtf8Len,NULL,NULL);
	out.assign(lpUTF8, nUtf8Len);

	delete[] lpUTF8;
}

void Transcode::UTF8_to_Unicode( const char* in, size_t len, std::wstring& out )
{
	wchar_t* lpBuf = new wchar_t[len + 1];
	size_t out_len = (len + 1) * sizeof(wchar_t);

	memset(lpBuf, 0, (len + 1) * sizeof(wchar_t));

	out_len = ::MultiByteToWideChar(CP_UTF8, 0, in, len, lpBuf, len * sizeof(wchar_t));
	out.assign(lpBuf, out_len);

	delete [] lpBuf;
}

void Transcode::ANSI_to_Unicode( const char* in, size_t len, std::wstring& out )
{
	int wbufferlen = (int)::MultiByteToWideChar(CP_ACP,0, in, (int)len, NULL, 0);
	wchar_t* lpwbuffer = new wchar_t[wbufferlen+1];

	wbufferlen = (int)::MultiByteToWideChar(CP_ACP,0, in, (int)len, lpwbuffer, wbufferlen);
	lpwbuffer[wbufferlen] = '\0';
	out.assign( lpwbuffer, wbufferlen );
	delete[] lpwbuffer;
}

void Transcode::ANSI_to_UTF8(const char* in, size_t len, std::string& out)
{
	std::wstring tempstr;
	ANSI_to_Unicode(in,len,tempstr);
	Unicode_to_UTF8(tempstr.c_str(),tempstr.length(),out);
}

void Transcode::Unicode_to_ANSI(const wchar_t* wstr,string& str)
{
	//string str="";
#ifdef UNICODE
	int nLen = lstrlen(wstr)*2+100;
#else
	int nLen = wcslen(wstr)*2+100;
#endif // UNICODE
	

	char* pChar = new char[nLen];
	if (pChar)
	{
		memset(pChar,0,nLen);
#ifdef UNICODE
		::WideCharToMultiByte(CP_ACP,0,wstr,lstrlen(wstr),pChar,nLen,0,NULL);
#else
		::WideCharToMultiByte(CP_ACP,0,wstr,wcslen(wstr),pChar,nLen,0,NULL);
#endif // UNICODE
		
		str = pChar;
		delete[] pChar;
	}
	//return str;
} 

//---------------------------------------------

//bool CommonUse::CreateDirectory_EveryOneUser( const void* pDirName, bool bAnsi )
//{
//	bool bRes = false;
//	SECURITY_ATTRIBUTES sa;
//	EXPLICIT_ACCESS ea[2];
//	PSID pEveryoneSID			= NULL;
//	PSID pAdminSID				= NULL;
//	PACL pACL					= NULL;
//	PSECURITY_DESCRIPTOR pSD	= NULL;
//	SID_IDENTIFIER_AUTHORITY SIDAuthWorld	= SECURITY_WORLD_SID_AUTHORITY;
//	SID_IDENTIFIER_AUTHORITY SIDAuthNT		= SECURITY_NT_AUTHORITY;
//
//	sa.nLength = sizeof (SECURITY_ATTRIBUTES);
//	sa.lpSecurityDescriptor = NULL;
//	sa.bInheritHandle = FALSE;
//
//	if( NULL == pDirName )
//		return bRes;
//
//	do{
//		pSD = (PSECURITY_DESCRIPTOR) LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
//		if( NULL == pSD )
//			break;
//
//		if( !InitializeSecurityDescriptor(pSD, SECURITY_DESCRIPTOR_REVISION) )
//			break;
//
//		if( !AllocateAndInitializeSid(&SIDAuthWorld, 1, SECURITY_WORLD_RID, 0, 0, 0, 0, 0, 0, 0, &pEveryoneSID) )
//			break;
//
//		if( !AllocateAndInitializeSid(&SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdminSID)) 
//			break;
//
//		memset( &ea, 0x00, 2*sizeof(EXPLICIT_ACCESS));
//		ea[0].grfAccessPermissions = FILE_ALL_ACCESS;
//		ea[0].grfAccessMode = GRANT_ACCESS;//GRANT_ACCESS
//		ea[0].grfInheritance= OBJECT_INHERIT_ACE|CONTAINER_INHERIT_ACE;
//		ea[0].Trustee.TrusteeForm = TRUSTEE_IS_SID;
//		ea[0].Trustee.TrusteeType = TRUSTEE_IS_WELL_KNOWN_GROUP;
//		ea[0].Trustee.ptstrName  = (LPTSTR) pEveryoneSID;
//
//		ea[1].grfAccessPermissions = FILE_ALL_ACCESS;
//		ea[1].grfAccessMode = GRANT_ACCESS;
//		ea[1].grfInheritance= OBJECT_INHERIT_ACE|CONTAINER_INHERIT_ACE;
//		ea[1].Trustee.TrusteeForm = TRUSTEE_IS_SID;
//		ea[1].Trustee.TrusteeType = TRUSTEE_IS_GROUP;
//		ea[1].Trustee.ptstrName  = (LPTSTR) pAdminSID;
//
//		if( SetEntriesInAcl(2, ea, NULL, &pACL) != ERROR_SUCCESS )
//			break;
//
//		if( !SetSecurityDescriptorDacl(pSD, TRUE, pACL, FALSE) )
//			break;
//
//		sa.lpSecurityDescriptor = pSD;
//		bRes = true;
//
//	}while(false);
//
//	if( bAnsi )
//	{
//		::CreateDirectoryA( (const char*)pDirName, &sa );
//	}
//	else
//	{
//		::CreateDirectoryW( (const wchar_t*)pDirName, &sa );
//	}
//
//	if (pEveryoneSID) 
//		FreeSid(pEveryoneSID);
//	if (pAdminSID) 
//		FreeSid(pAdminSID);
//	if (pACL) 
//		LocalFree(pACL);
//	if (pSD) 
//		LocalFree(pSD);
//
//	return bRes;
//}
//
//wstring CommonUse::MakePathFromAllUser( const wchar_t* szSub )
//{
//	wstring str;
//	static wchar_t szAppDataDir[260];
//	if (szAppDataDir[0] == 0)
//	{
//		SHGetSpecialFolderPath(NULL, szAppDataDir, CSIDL_COMMON_APPDATA, 0);
//		str = szAppDataDir;
//		str += L"\\DtlCalendar";
//		CreateDirectory_EveryOneUser( str.c_str(), false );
//	}
//	else
//	{
//		str = szAppDataDir;
//		str += L"\\DtlCalendar";
//	}
//	if (szSub[0] != L'\\')
//	{
//		str += L"\\";
//	}
//	str += szSub;
//	return str;
//
//}
//
//bool CommonUse::CheckOrCreateConfigFile(const wchar_t* szFile)
//{
//	// always return true;
//	if (!::PathFileExists(szFile))
//	{
//		HANDLE hFile = ::CreateFile(szFile,0,0,NULL,CREATE_NEW,NULL,NULL);
//		if (hFile)
//		{
//			::CloseHandle(hFile);
//			return true;
//		}
//	}
//	return true;
//}
//
//void CommonUse::SetConfiginiString( const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,const wchar_t* szValue )
//{
//	if (CheckOrCreateConfigFile(szFileName))
//	{
//		WritePrivateProfileString(szAppName,szKeyName,szValue,szFileName);
//	}	
//}
//wstring CommonUse::GetConfiginiString(const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,const wchar_t* szDefualt )
//{
//	wchar_t buf[MAX_PATH]={0};
//	wstring str;
//	GetPrivateProfileString(szAppName,szKeyName,szDefualt,buf,MAX_PATH,szFileName);
//	str = buf;
//	return str;
//}
//void CommonUse::SetConfiginiInt(const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,int nValue )
//{
//	wchar_t szValue[MAX_PATH]={0};
//	wsprintf(szValue,L"%d",nValue);
//
//	SetConfiginiString(szFileName, szAppName, szKeyName, szValue);
//
//}
//int CommonUse::GetConfiginiInt(const wchar_t* szFileName, const wchar_t* szAppName, const wchar_t* szKeyName,int nDefualt )
//{
//	return GetPrivateProfileInt(szAppName,szKeyName,nDefualt,szFileName);
//}
//
//struct VS_VERSIONINFO
//{
//	WORD                wLength;
//	WORD                wValueLength;
//	WORD                wType;
//	WCHAR               szKey[1];
//	WORD                wPadding1[1];
//	VS_FIXEDFILEINFO    Value;
//	WORD                wPadding2[1];
//	WORD                wChildren[1];
//};
//
//wstring CommonUse::GetAppVersion(const wchar_t* szAppPath)
//{
//	VS_VERSIONINFO      *pVerInfo;
//	LPBYTE              pOffsetBytes;
//	VS_FIXEDFILEINFO    *pFixedInfo;
//	DWORD               dwHandle=0,dwSize=0,dwResult = 0;
//	wstring             strFile = szAppPath;
//	wstring str=L"";
//
//	dwSize = GetFileVersionInfoSize(strFile.c_str(), &dwHandle);
//	if (0 < dwSize)
//	{
//		LPBYTE lpBuffer = new BYTE[dwSize];
//
//		if (GetFileVersionInfo(strFile.c_str(), 0, dwSize, lpBuffer) != FALSE)
//		{
//			// these macros help to align on r-byte boundaries (thanks Ted Peck)
//			#define roundoffs(a,b,r) (((BYTE *) (b) - (BYTE *) (a) + ((r) - 1)) & ~((r) - 1))
//			#define roundpos(a,b,r) (((BYTE *) (a)) + roundoffs(a,b,r))
//
//			// 'point to' the start of the version information block
//			pVerInfo = (VS_VERSIONINFO *) lpBuffer;
//
//			// the fixed section starts right after the 'VS_VERSION_INFO' string
//			pOffsetBytes = (BYTE *) &pVerInfo->szKey[_tcslen(pVerInfo->szKey) + 1];
//
//			pFixedInfo = (VS_FIXEDFILEINFO *) roundpos(pVerInfo, pOffsetBytes, 4);
//
//			// increment the numbers!
//			unsigned short ver1,ver2,ver3,ver4;
//			ver1 = (pFixedInfo->dwFileVersionLS);
//			ver2 = (pFixedInfo->dwFileVersionLS>>16);
//			ver3 = pFixedInfo->dwFileVersionMS;
//			ver4 = (pFixedInfo->dwFileVersionMS>>16);
//			wchar_t buf[MAX_PATH];
//			wsprintf(buf,L"%u.%u.%u.%u",ver4,ver3,ver2,ver1);
//			str = buf;
//		}
//		delete[] lpBuffer;
//	}
//	return str;
//}
//
//wstring CommonUse::GetLocalTimeToString()
//{
//	SYSTEMTIME st;
//	::GetLocalTime(&st);
//	wstring str;
//	wchar_t buf[MAX_PATH]={0};
//	wsprintf(buf,L"%d%02d%02d%02d%02d%02d",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond);
//	str = buf;
//	return str;
//}