# Windows-Keyboard-Mouse-Filter PowerShell SDK

`Install-Module WindowsKeyboardMouseFilter -Scope CurrentUser`

Requires PowerShell 7.4+ on Windows x64. Supported families: keyboard, mouse. The native product SDK and license/trial behavior are unchanged. No driver is installed on import or construction.

```powershell
Import-Module WindowsKeyboardMouseFilter
$client = Connect-WindowsKeyboardMouseFilterSDK
try { Get-WindowsKeyboardMouseFilterSDKInfo -Client $client }
finally { Disconnect-WindowsKeyboardMouseFilterSDK -Client $client }
```

See [API guide](docs/API.md) and `Get-Command -Module WindowsKeyboardMouseFilter`. The matching driver is installed separately.
