#include "DotNetVersion.h"
/*
  Based on https://blogs.msdn.microsoft.com/astebner/2009/06/16/sample-code-to-detect-net-framework-install-state-and-service-pack-level/
*/

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
bool DotNetVersion::IsNetfx10Installed()
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
bool DotNetVersion::IsNetfx11Installed()
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
bool DotNetVersion::IsNetfx20Installed()
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
bool DotNetVersion::IsNetfx30Installed()
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
bool DotNetVersion::IsNetfx35Installed()
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
bool DotNetVersion::IsNetfx40ClientInstalled()
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
bool DotNetVersion::IsNetfx40FullInstalled()
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
bool DotNetVersion::IsNetfx45Installed()
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
bool DotNetVersion::IsNetfx451Installed()
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
bool DotNetVersion::IsNetfx452Installed()
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
Function Name:	IsNetfx46Installed
Description:	Uses the detection method recommended at
                http://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
                to determine whether the .NET Framework 4.6 is
                installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.6 is installed
                false otherwise
******************************************************************/
bool DotNetVersion::IsNetfx46Installed()
{
	bool bRetValue = false;
	DWORD dwRegValue=0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (g_dwNetfx46ReleaseVersion <= dwRegValue)
			bRetValue = true;
	}

	return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx461Installed
Description:	Uses the detection method recommended at
                http://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
                to determine whether the .NET Framework 4.6.1 is
                installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.6.1 is installed
                false otherwise
******************************************************************/
bool DotNetVersion::IsNetfx461Installed()
{
	bool bRetValue = false;
	DWORD dwRegValue=0;

	if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
	{
		if (g_dwNetfx461ReleaseVersion <= dwRegValue)
			bRetValue = true;
	}

	return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx462Installed
Description:	Uses the detection method recommended at
                http://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
                to determine whether the .NET Framework 4.6.1 is
                installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.6.2 is installed
                false otherwise
******************************************************************/
bool DotNetVersion::IsNetfx462Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue = 0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (g_dwNetfx462ReleaseVersion <= dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx47Installed
Description:	Uses the detection method recommended at
https://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
to determine whether the .NET Framework 4.7 is
installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.7 is installed
false otherwise
******************************************************************/
bool DotNetVersion::IsNetfx47Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue = 0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (g_dwNetfx47ReleaseVersion <= dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:	IsNetfx471Installed
Description:	Uses the detection method recommended at
https://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
to determine whether the .NET Framework 4.7.1 is
installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.7.1 is installed
false otherwise
******************************************************************/
bool DotNetVersion::IsNetfx471Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue = 0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (g_dwNetfx471ReleaseVersion <= dwRegValue)
      bRetValue = true;
  }

  return bRetValue;
}

/******************************************************************
Function Name:  IsNetfx472Installed
Description:    Uses the detection method recommended at
                https://msdn.microsoft.com/en-us/library/ee942965(v=vs.110).aspx
                to determine whether the .NET Framework 4.7.2 is
                installed on the machine
Inputs:         NONE
Results:        true if the .NET Framework 4.7.2 is installed
                false otherwise
******************************************************************/
bool DotNetVersion::IsNetfx472Installed()
{
  bool bRetValue = false;
  DWORD dwRegValue=0;

  if (RegistryGetValue(HKEY_LOCAL_MACHINE, g_szNetfx45RegKeyName, g_szNetfx45RegValueName, NULL, (LPBYTE)&dwRegValue, sizeof(DWORD)))
  {
    if (g_dwNetfx472ReleaseVersion <= dwRegValue)
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
bool DotNetVersion::CheckNetfxBuildNumber(const TCHAR *pszNetfxRegKeyName, const TCHAR *pszNetfxRegKeyValue, const int iRequestedVersionMajor, const int iRequestedVersionMinor, const int iRequestedVersionBuild, const int iRequestedVersionRevision)
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
bool DotNetVersion::RegistryGetValue(HKEY hk, const TCHAR * pszKey, const TCHAR * pszValue, DWORD dwType, LPBYTE data, DWORD dwSize)
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
