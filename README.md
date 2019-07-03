.NET Bootstrapper
====================

Application to check whether the specified .NET Framework is installed. If so, the specified application is launched otherwise an error message is displayed.

### Usage

```Batchfile
DotNetBootstrapper.exe <Version> <Application> [<Arguments>]
```

### Parameters

| Parameter       | Description                                                           |
| --------------- | --------------------------------------------------------------------- |
| `<Version>`     | Version of the .NET Framework to check is installed (see table below) |
| `<Application>` | Path to application to launch if check passes                         |
| `<Arguments>`   | Arguments to pass to application                                      |

### Supported Versions

| `<Version>`     | .NET Framework Version                  |
| --------------- | --------------------------------------- |
| `v4.7.2`        | .NET Framework v4.7.2                   |
| `v4.7.1`        | .NET Framework v4.7.1                   |
| `v4.7`          | .NET Framework v4.7                     |
| `v4.6.2`        | .NET Framework v4.6.2                   |
| `v4.6.1`        | .NET Framework v4.6.1                   |
| `v4.6`          | .NET Framework v4.6                     |
| `v4.5.2`        | .NET Framework v4.5.2                   |
| `v4.5.1`        | .NET Framework v4.5.1                   |
| `v4.5`          | .NET Framework v4.5                     |
| `v4.0-Full`     | .NET Framework v4.0 (Full)              |
| `v4.0-Client`   | .NET Framework v4.0 (Client Profile)    |
| `v3.5`          | .NET Framework v3.5                     |
| `v3.0`          | .NET Framework v3.0                     |
| `v2.0`          | .NET Framework v2.0                     |
| `v1.1`          | .NET Framework v1.1                     |
| `v1.0`          | .NET Framework v1.0                     |


### Example

```Batchfile
DotNetBootstrapper.exe v4.5 C:\Folder\Program.exe -Foo -Bar
```

### Credits

Based on the sample code from https://docs.microsoft.com/en-us/office365/troubleshoot/administration/switch-channel-for-office-365
