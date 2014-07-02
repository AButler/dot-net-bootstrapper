#include <stdio.h>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <stdexcept>

// Constants that represent registry key names and value names
// to use for detection
const TCHAR *g_szNetfx10RegKeyName = _T("Software\\Microsoft\\.NETFramework\\Policy\\v1.0");
const TCHAR *g_szNetfx10RegKeyValue = _T("3705");
const TCHAR *g_szNetfx10SPxMSIRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}");
const TCHAR *g_szNetfx10SPxOCMRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}");
const TCHAR *g_szNetfx11RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
const TCHAR *g_szNetfx20RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727");
const TCHAR *g_szNetfx30RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0\\Setup");
const TCHAR *g_szNetfx30SpRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0");
const TCHAR *g_szNetfx30RegValueName = _T("InstallSuccess");
const TCHAR *g_szNetfx35RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.5");
const TCHAR *g_szNetfx40ClientRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client");
const TCHAR *g_szNetfx40FullRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
const TCHAR *g_szNetfx40SPxRegValueName = _T("Servicing");
const TCHAR *g_szNetfx45RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
const TCHAR *g_szNetfx45RegValueName = _T("Release");
const TCHAR *g_szNetfxStandardRegValueName = _T("Install");
const TCHAR *g_szNetfxStandardSPxRegValueName = _T("SP");
const TCHAR *g_szNetfxStandardVersionRegValueName = _T("Version");

// Version information for final release of .NET Framework 3.0
const int g_iNetfx30VersionMajor = 3;
const int g_iNetfx30VersionMinor = 0;
const int g_iNetfx30VersionBuild = 4506;
const int g_iNetfx30VersionRevision = 26;

// Version information for final release of .NET Framework 3.5
const int g_iNetfx35VersionMajor = 3;
const int g_iNetfx35VersionMinor = 5;
const int g_iNetfx35VersionBuild = 21022;
const int g_iNetfx35VersionRevision = 8;

// Version information for final release of .NET Framework 4
const int g_iNetfx40VersionMajor = 4;
const int g_iNetfx40VersionMinor = 0;
const int g_iNetfx40VersionBuild = 30319;
const int g_iNetfx40VersionRevision = 0;

// Version information for final release of .NET Framework 4.5
const int g_dwNetfx45ReleaseVersion = 378389;

// Version information for final release of .NET Framework 4.5.1
// The deployment guide says to use value 378758, but the version of the 
// .NET Framework 4.5.1 in Windows 8.1 has value 378675, so we have to use that instead
const int g_dwNetfx451ReleaseVersion = 378675;

// Version information for final release of .NET Framework 4.5.2
const int g_dwNetfx452ReleaseVersion = 379893;

// Function prototypes
bool CheckNetfxBuildNumber( const TCHAR*, const TCHAR*, const int, const int, const int, const int );
bool IsNetfx10Installed();
bool IsNetfx11Installed();
bool IsNetfx20Installed();
bool IsNetfx30Installed();
bool IsNetfx35Installed();
bool IsNetfx40ClientInstalled();
bool IsNetfx40FullInstalled();
bool IsNetfx45Installed();
bool IsNetfx451Installed();
bool IsNetfx452Installed();
bool RegistryGetValue( HKEY, const TCHAR*, const TCHAR*, DWORD, LPBYTE, DWORD );

bool IsDotNetFxInstalled( const TCHAR* version );

/* 
  Usage:
  
    DotNetBootstrapper.exe <Version> <Application> [<Arguments>]

  Description:

    Launches the application supplied if the the version of .NET 
    that is supplied is installed

  Parameters:

    Version:        .NET version to check is installed
    Application:    Path to application to launch if check passes
    Arguments:      Arguments to pass to application

  Supported Versions:

    * v4.5.2      = .NET Framework v4.5.2
    * v4.5.1      = .NET Framework v4.5.1
    * v4.5        = .NET Framework v4.5
    * v4.0-Full   = .NET Framework v4.0 (Full)
    * v4.0-Client = .NET Framework v4.0 (Client Profile)
    * v3.5        = .NET Framework v3.5
    * v3.0        = .NET Framework v3.0
    * v2.0        = .NET Framework v2.0
    * v1.1        = .NET Framework v1.1
    * v1.0        = .NET Framework v1.0

  Example:

      DotNetBootstrapper.exe v4.5 C:\Folder\Program.exe -Foo -Bar
*/
int APIENTRY _tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow ) {

  int argCount;
  LPTSTR *szArgList;

  // Parse command line
  szArgList = CommandLineToArgvW( lpCmdLine, &argCount );
  
  if( argCount < 2 ) {
    // Minimum required arguments is .NET version and application
    return 1;
  }

  try {
    // Check .NET is installed
    bool isDotNetFxInstalled = IsDotNetFxInstalled( szArgList[0] );

    if( isDotNetFxInstalled ) {
      // Create info objects
      STARTUPINFO si;
      PROCESS_INFORMATION pi;

      ZeroMemory( &si, sizeof( si ) );
      si.cb = sizeof( si );
      ZeroMemory( &pi, sizeof( pi ) );

      // Create command line
      WCHAR commandLine[MAX_PATH];
      _tcscpy_s( commandLine, _countof( commandLine ), _tcsninc( lpCmdLine, _tcslen( szArgList[0] ) + 1 ) );
      
      if( !CreateProcess( NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) ) {
        MessageBox( NULL, _T( "Could not launch application" ), _T( ".NET Framework" ), MB_OK | MB_ICONERROR);
        return 2;
      }

      WaitForSingleObject( pi.hProcess, INFINITE );

      CloseHandle( pi.hProcess );
      CloseHandle( pi.hThread );
    } else {
      MessageBox( NULL, _T( ".NET Framework is NOT installed" ), _T( ".NET Framework" ), MB_OK | MB_ICONERROR);
    }

  } catch ( const std::invalid_argument ) {
    MessageBox( NULL, _T( ".NET Framework is unknown" ), _T( ".NET Framework" ), MB_OK | MB_ICONERROR);
  }

  return 0;
}

bool IsDotNetFxInstalled( const TCHAR* version ) {
  if( _tcscmp( version, _T( "v4.5.2" ) ) == 0 ) {
    // .NET 4.5.2
    return IsNetfx452Installed();
  } else if( _tcscmp( version, _T( "v4.5.1" ) ) == 0 ) {
    // .NET 4.5.1
    return IsNetfx451Installed();
  } else if( _tcscmp( version, _T( "v4.5" ) ) == 0 ) {
    // .NET 4.5
    return IsNetfx45Installed();
  } else if( _tcscmp( version, _T( "v4.0-Full" ) ) == 0 ) {
    // .NET 4.0 Full
    return IsNetfx40FullInstalled();
  } else if( _tcscmp( version, _T( "v4.0-Client" ) ) == 0 ) {
    // .NET 4.0 Client
    return IsNetfx40ClientInstalled();
  } else if( _tcscmp( version, _T( "v3.5" ) ) == 0 ) {
    // .NET 3.5
    return IsNetfx35Installed();
  } else if( _tcscmp( version, _T( "v3.0" ) ) == 0 ) {
    // .NET 3.0
    return IsNetfx30Installed();
  } else if( _tcscmp( version, _T( "v2.0" ) ) == 0 ) {
    // .NET 2.0
    return IsNetfx20Installed();
  } else if( _tcscmp( version, _T( "v1.1" ) ) == 0 ) {
    // .NET 1.1
    return IsNetfx11Installed();
  } else if( _tcscmp( version, _T( "v1.0" ) ) == 0 ) {
    // .NET 1.0
    return IsNetfx10Installed();
  }

  throw std::invalid_argument( "Unknown version" );
}

/******************************************************************
Function Name:	IsNetfx10Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/library/ms994349.aspx
to determine whether the .NET Framework 1.0 is
installed on the machine
Inputs:	        NONE
Results:        true if the .NET Framework 1.0 is installed
false otherwise
******************************************************************/
bool IsNetfx10Installed()
{
  TCHAR szRegValue[MAX_PATH];
  return (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx10RegKeyName, g_szNetfx10RegKeyValue, NULL, (LPBYTE)szRegValue, MAX_PATH));
}

/******************************************************************
Function Name:	IsNetfx11Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/library/ms994339.aspx
to determine whether the .NET Framework 1.1 is
installed on the machine
Inputs:	        NONE
Results:        true if the .NET Framework 1.1 is installed
false otherwise
******************************************************************/
bool IsNetfx11Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx11RegKeyName, g_szNetfxStandardRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (1 == dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx20Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/library/aa480243.aspx
to determine whether the .NET Framework 2.0 is
installed on the machine
Inputs:	        NONE
Results:        true if the .NET Framework 2.0 is installed
false otherwise
******************************************************************/
bool IsNetfx20Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx20RegKeyName, g_szNetfxStandardRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (1 == dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx30Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/library/aa964979.aspx
to determine whether the .NET Framework 3.0 is
installed on the machine
Inputs:	        NONE
Results:        true if the .NET Framework 3.0 is installed
false otherwise
******************************************************************/
bool IsNetfx30Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  // Check that the InstallSuccess registry value exists and equals 1
  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx30RegKeyName, g_szNetfx30RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (1 == dwRegValue)
      bRetValue = true;
  }

  // A system with a pre-release version of the .NET Framework 3.0 can
  // have the InstallSuccess value.  As an added verification, check the
  // version number listed in the registry
  return (bRetValue && CheckNetfxBuildNumber(g_szNetfx30RegKeyName, g_szNetfxStandardVersionRegValueName, g_iNetfx30VersionMajor, g_iNetfx30VersionMinor, g_iNetfx30VersionBuild, g_iNetfx30VersionRevision));
}

/******************************************************************
Function Name:	IsNetfx35Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/library/cc160716.aspx
to determine whether the .NET Framework 3.5 is
installed on the machine
Inputs:	        NONE
Results:        true if the .NET Framework 3.5 is installed
false otherwise
******************************************************************/
bool IsNetfx35Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  // Check that the Install registry value exists and equals 1
  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx35RegKeyName, g_szNetfxStandardRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (1 == dwRegValue)
      bRetValue = true;
  }

  // A system with a pre-release version of the .NET Framework 3.5 can
  // have the Install value.  As an added verification, check the
  // version number listed in the registry
  return (bRetValue && CheckNetfxBuildNumber(g_szNetfx35RegKeyName, g_szNetfxStandardVersionRegValueName, g_iNetfx35VersionMajor, g_iNetfx35VersionMinor, g_iNetfx35VersionBuild, g_iNetfx35VersionRevision));
}

/******************************************************************
Function Name:	IsNetfx40ClientInstalled
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/library/ee942965(v=VS.100).aspx
to determine whether the .NET Framework 4 Client is
installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4 Client is installed
false otherwise
******************************************************************/
bool IsNetfx40ClientInstalled()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40ClientRegKeyName, g_szNetfxStandardRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (1 == dwRegValue)
      bRetValue = true;
  }

  // A system with a pre-release version of the .NET Framework 4 can
  // have the Install value.  As an added verification, check the
  // version number listed in the registry
  return (bRetValue && CheckNetfxBuildNumber(g_szNetfx40ClientRegKeyName, g_szNetfxStandardVersionRegValueName, g_iNetfx40VersionMajor, g_iNetfx40VersionMinor, g_iNetfx40VersionBuild, g_iNetfx40VersionRevision));
}

/******************************************************************
Function Name:	IsNetfx40FullInstalled
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/library/ee942965(v=VS.100).aspx
to determine whether the .NET Framework 4 Full is
installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4 Full is installed
false otherwise
******************************************************************/
bool IsNetfx40FullInstalled()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx40FullRegKeyName, g_szNetfxStandardRegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (1 == dwRegValue)
      bRetValue = true;
  }

  // A system with a pre-release version of the .NET Framework 4 can
  // have the Install value.  As an added verification, check the
  // version number listed in the registry
  return (bRetValue && CheckNetfxBuildNumber(g_szNetfx40FullRegKeyName, g_szNetfxStandardVersionRegValueName, g_iNetfx40VersionMajor, g_iNetfx40VersionMinor, g_iNetfx40VersionBuild, g_iNetfx40VersionRevision));
}

/******************************************************************
Function Name:	IsNetfx45Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
to determine whether the .NET Framework 4.5 is
installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.5 is installed
false otherwise
******************************************************************/
bool IsNetfx45Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (g_dwNetfx45ReleaseVersion <= dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx451Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
to determine whether the .NET Framework 4.5.1 is
installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.5.1 is installed
false otherwise
******************************************************************/
bool IsNetfx451Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (g_dwNetfx451ReleaseVersion <= dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx452Installed
Description:	Uses the detection method recommended at
http://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
to determine whether the .NET Framework 4.5.2 is
installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.5.2 is installed
false otherwise
******************************************************************/
bool IsNetfx452Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (g_dwNetfx452ReleaseVersion <= dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:	CheckNetfxBuildNumber
Description:	Retrieves the .NET Framework build number from
the registry and validates that it is not a pre-release
version number
Inputs:         NONE
Results:        true if the build number in the registry is greater
than or equal to the passed in version; false otherwise
******************************************************************/
bool CheckNetfxBuildNumber(const TCHAR *pszNetfxRegKeyName, const TCHAR *pszNetfxRegKeyValue, const int iRequestedVersionMajor, const int iRequestedVersionMinor, const int iRequestedVersionBuild, const int iRequestedVersionRevision)
{
  TCHAR szRegValue[MAX_PATH];
  TCHAR *pszToken = NULL;
  TCHAR *pszNextToken = NULL;
  int iVersionPartCounter = 0;
  int iRegistryVersionMajor = 0;
  int iRegistryVersionMinor = 0;
  int iRegistryVersionBuild = 0;
  int iRegistryVersionRevision = 0;
  bool bRegistryRetVal = false;

  // Attempt to retrieve the build number registry value
  bRegistryRetVal = RegistryGetValue(HKEY_LOCAL_MACHINE, pszNetfxRegKeyName, pszNetfxRegKeyValue, NULL, (LPBYTE)szRegValue, MAX_PATH);

  if (bRegistryRetVal)
  {
    // This registry value should be of the format
    // #.#.#####.##.  Try to parse the 4 parts of
    // the version here
    pszToken = _tcstok_s(szRegValue, _T("."), &pszNextToken);
    while (NULL != pszToken)
    {
      iVersionPartCounter++;

      switch (iVersionPartCounter)
      {
      case 1:
        // Convert the major version value to an integer
        iRegistryVersionMajor = _tstoi(pszToken);
        break;
      case 2:
        // Convert the minor version value to an integer
        iRegistryVersionMinor = _tstoi(pszToken);
        break;
      case 3:
        // Convert the build number value to an integer
        iRegistryVersionBuild = _tstoi(pszToken);
        break;
      case 4:
        // Convert the revision number value to an integer
        iRegistryVersionRevision = _tstoi(pszToken);
        break;
      default:
        break;

      }

      // Get the next part of the version number
      pszToken = _tcstok_s(NULL, _T("."), &pszNextToken);
    }
  }

  // Compare the version number retrieved from the registry with
  // the version number of the final release of the .NET Framework
  // that we are checking
  if (iRegistryVersionMajor > iRequestedVersionMajor)
  {
    return true;
  }
  else if (iRegistryVersionMajor == iRequestedVersionMajor)
  {
    if (iRegistryVersionMinor > iRequestedVersionMinor)
    {
      return true;
    }
    else if (iRegistryVersionMinor == iRequestedVersionMinor)
    {
      if (iRegistryVersionBuild > iRequestedVersionBuild)
      {
        return true;
      }
      else if (iRegistryVersionBuild == iRequestedVersionBuild)
      {
        if (iRegistryVersionRevision >= iRequestedVersionRevision)
        {
          return true;
        }
      }
    }
  }

  // If we get here, the version in the registry must be less than the
  // version of the final release of the .NET Framework we are checking,
  // so return false
  return false;
}


/******************************************************************
Function Name:	RegistryGetValue
Description:	Get the value of a reg key
Inputs:			HKEY hk - The hk of the key to retrieve
TCHAR *pszKey - Name of the key to retrieve
TCHAR *pszValue - The value that will be retrieved
DWORD dwType - The type of the value that will be retrieved
LPBYTE data - A buffer to save the retrieved data
DWORD dwSize - The size of the data retrieved
Results:		true if successful, false otherwise
******************************************************************/
bool RegistryGetValue(HKEY hk, const TCHAR * pszKey, const TCHAR * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize)
{
  HKEY hkOpened;

  // Try to open the key
  if (RegOpenKeyEx(hk, pszKey, 0, KEY_READ, &hkOpened) != ERROR_SUCCESS)
  {
    return false;
  }

  // If the key was opened, try to retrieve the value
  if (RegQueryValueEx(hkOpened, pszValue, 0, &dwType, (LPBYTE)data, &dwSize) != ERROR_SUCCESS)
  {
    RegCloseKey(hkOpened);
    return false;
  }

  // Clean up
  RegCloseKey(hkOpened);

  return true;
}