#include <stdio.h>
#include <stdexcept>
#include "DotNetVersion.h"

bool IsDotNetFxInstalled( const TCHAR* version );
const TCHAR* GetFriendlyVersion( const TCHAR* version );

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

    * v4.6.2      = .NET Framework v4.6.2
    * v4.6.1      = .NET Framework v4.6.1
    * v4.6        = .NET Framework v4.6
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

  TCHAR message[MAX_PATH];
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

    if( !isDotNetFxInstalled ) { 
      // .NET isn't installed
      _stprintf_s( message, _countof( message ), _T( ".NET Framework %s is required before you can run this application." ), GetFriendlyVersion( szArgList[0] ) );
     
      MessageBox( NULL, message, _T( ".NET Framework" ), MB_OK | MB_ICONERROR );
      return 1;
    }

    // Create info objects
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;

    ZeroMemory( &si, sizeof( si ) );
    si.cb = sizeof( si );
    ZeroMemory( &pi, sizeof( pi ) );

    // Create command line
    WCHAR commandLine[32768];
    _tcscpy_s( commandLine, _countof( commandLine ), _tcsninc( lpCmdLine, _tcslen( szArgList[0] ) + 1 ) );
      
    if( !CreateProcess( NULL, commandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi ) ) {
      MessageBox( NULL, _T( "Could not launch application" ), _T( ".NET Framework" ), MB_OK | MB_ICONERROR);
      return 2;
    }

    WaitForSingleObject( pi.hProcess, INFINITE );

    if( !GetExitCodeProcess( pi.hProcess, &exitCode ) ) {
      // If we couldn't get the exit code then assume all went OK
      exitCode = 0;
    }

    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );

    return exitCode;
   
  } catch ( const std::invalid_argument ) {
    _stprintf_s( message, _countof( message ), _T( ".NET Framework %s is not supported by DotNetBootstrapper." ), szArgList[0] );
    
    MessageBox( NULL, message, _T( ".NET Framework" ), MB_OK | MB_ICONERROR);
  }

  return 0;
}

bool IsDotNetFxInstalled( const TCHAR* version ) {
  DotNetVersion dotNetVersion;

  if( _tcscmp( version, _T( "v4.6.2" ) ) == 0 ) {
    // .NET 4.6.2
    return dotNetVersion.IsNetfx462Installed();
  } else if( _tcscmp( version, _T( "v4.6.1" ) ) == 0 ) {
    // .NET 4.6.1
    return dotNetVersion.IsNetfx461Installed();
  } else if( _tcscmp( version, _T( "v4.6" ) ) == 0 ) {
    // .NET 4.6
    return dotNetVersion.IsNetfx46Installed();
  } else if( _tcscmp( version, _T( "v4.5.2" ) ) == 0 ) {
    // .NET 4.5.2
    return dotNetVersion.IsNetfx452Installed();
  } else if( _tcscmp( version, _T( "v4.5.1" ) ) == 0 ) {
    // .NET 4.5.1
    return dotNetVersion.IsNetfx451Installed();
  } else if( _tcscmp( version, _T( "v4.5" ) ) == 0 ) {
    // .NET 4.5
    return dotNetVersion.IsNetfx45Installed();
  } else if( _tcscmp( version, _T( "v4.0-Full" ) ) == 0 ) {
    // .NET 4.0 Full
    return dotNetVersion.IsNetfx40FullInstalled();
  } else if( _tcscmp( version, _T( "v4.0-Client" ) ) == 0 ) {
    // .NET 4.0 Client
    return dotNetVersion.IsNetfx40ClientInstalled();
  } else if( _tcscmp( version, _T( "v3.5" ) ) == 0 ) {
    // .NET 3.5
    return dotNetVersion.IsNetfx35Installed();
  } else if( _tcscmp( version, _T( "v3.0" ) ) == 0 ) {
    // .NET 3.0
    return dotNetVersion.IsNetfx30Installed();
  } else if( _tcscmp( version, _T( "v2.0" ) ) == 0 ) {
    // .NET 2.0
    return dotNetVersion.IsNetfx20Installed();
  } else if( _tcscmp( version, _T( "v1.1" ) ) == 0 ) {
    // .NET 1.1
    return dotNetVersion.IsNetfx11Installed();
  } else if( _tcscmp( version, _T( "v1.0" ) ) == 0 ) {
    // .NET 1.0
    return dotNetVersion.IsNetfx10Installed();
  }

  throw std::invalid_argument( "Unknown version" );
}

const TCHAR* GetFriendlyVersion( const TCHAR* version ) {
  if( _tcscmp( version, _T( "v4.0-Full" ) ) == 0 ) {
    // .NET 4.0 Full
    return _T( "v4.0 (Full)" );
  } else if( _tcscmp( version, _T( "v4.0-Client" ) ) == 0 ) {
    // .NET 4.0 Client
    return _T( "v4.0 (Client Profile)" );
  }

  return version;
}