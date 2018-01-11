#include <windows.h>
#include <tchar.h>

  // Constants that represent registry key names and value names
// to use for detection
static const TCHAR *g_szNetfx10RegKeyName = _T("Software\\Microsoft\\.NETFramework\\Policy\\v1.0");
static const TCHAR *g_szNetfx10RegKeyValue = _T("3705");
static const TCHAR *g_szNetfx10SPxMSIRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{78705f0d-e8db-4b2d-8193-982bdda15ecd}");
static const TCHAR *g_szNetfx10SPxOCMRegKeyName = _T("Software\\Microsoft\\Active Setup\\Installed Components\\{FDC11A6F-17D1-48f9-9EA3-9051954BAA24}");
static const TCHAR *g_szNetfx11RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v1.1.4322");
static const TCHAR *g_szNetfx20RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v2.0.50727");
static const TCHAR *g_szNetfx30RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0\\Setup");
static const TCHAR *g_szNetfx30SpRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.0");
static const TCHAR *g_szNetfx30RegValueName = _T("InstallSuccess");
static const TCHAR *g_szNetfx35RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v3.5");
static const TCHAR *g_szNetfx40ClientRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Client");
static const TCHAR *g_szNetfx40FullRegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
static const TCHAR *g_szNetfx40SPxRegValueName = _T("Servicing");
static const TCHAR *g_szNetfx45RegKeyName = _T("Software\\Microsoft\\NET Framework Setup\\NDP\\v4\\Full");
static const TCHAR *g_szNetfx45RegValueName = _T("Release");
static const TCHAR *g_szNetfxStandardRegValueName = _T("Install");
static const TCHAR *g_szNetfxStandardSPxRegValueName = _T("SP");
static const TCHAR *g_szNetfxStandardVersionRegValueName = _T("Version");

// Version information for final release of .NET Framework 3.0
static const int g_iNetfx30VersionMajor = 3;
static const int g_iNetfx30VersionMinor = 0;
static const int g_iNetfx30VersionBuild = 4506;
static const int g_iNetfx30VersionRevision = 26;

// Version information for final release of .NET Framework 3.5
static const int g_iNetfx35VersionMajor = 3;
static const int g_iNetfx35VersionMinor = 5;
static const int g_iNetfx35VersionBuild = 21022;
static const int g_iNetfx35VersionRevision = 8;

// Version information for final release of .NET Framework 4
static const int g_iNetfx40VersionMajor = 4;
static const int g_iNetfx40VersionMinor = 0;
static const int g_iNetfx40VersionBuild = 30319;
static const int g_iNetfx40VersionRevision = 0;

// Version information for final release of .NET Framework 4.5
static const int g_dwNetfx45ReleaseVersion = 378389;

// Version information for final release of .NET Framework 4.5.1
// The deployment guide says to use value 378758, but the version of the 
// .NET Framework 4.5.1 in Windows 8.1 has value 378675, so we have to use that instead
static const int g_dwNetfx451ReleaseVersion = 378675;

// Version information for final release of .NET Framework 4.5.2
static const int g_dwNetfx452ReleaseVersion = 379893;

// Version information for final release of .NET Framework 4.6
const int g_dwNetfx46ReleaseVersion = 393295;

// Version information for final release of .NET Framework 4.6.1
const int g_dwNetfx461ReleaseVersion = 394254;

// Version information for final release of .NET Framework 4.6.2
const int g_dwNetfx462ReleaseVersion = 394802;

// Version information for final release of .NET Framework 4.7
const int g_dwNetfx47ReleaseVersion = 460798;

// Version information for final release of .NET Framework 4.7.1
const int g_dwNetfx471ReleaseVersion = 461308;

class DotNetVersion {
private:
  bool CheckNetfxBuildNumber(const TCHAR *pszNetfxRegKeyName, const TCHAR *pszNetfxRegKeyValue, const int iRequestedVersionMajor, const int iRequestedVersionMinor, const int iRequestedVersionBuild, const int iRequestedVersionRevision);
  bool RegistryGetValue(HKEY hk, const TCHAR * pszKey, const TCHAR * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize);

public:
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
  bool IsNetfx46Installed();
  bool IsNetfx461Installed();
  bool IsNetfx462Installed();
  bool IsNetfx47Installed();
  bool IsNetfx471Installed();
};