@{
RootModule = 'WindowsKeyboardMouseFilter.psm1'
ModuleVersion = '1.0.0'
GUID = 'f2ace8c6-0667-5afe-a316-6c5753a1d0ce'
Author = 'TitanCSA'
Description = 'Windows x64 Windows-Keyboard-Mouse-Filter input SDK for PowerShell 7.4+. Driver installed separately.'
PowerShellVersion = '7.4'
CompatiblePSEditions = @('Core')
FunctionsToExport = @('Connect-WindowsKeyboardMouseFilterSDK','Initialize-WindowsKeyboardMouseFilterSDK','Get-WindowsKeyboardMouseFilterSDKInfo','Get-WindowsKeyboardMouseFilterSDKDevice','Receive-WindowsKeyboardMouseFilterSDKInput','Send-WindowsKeyboardMouseFilterSDKBatch','Remove-WindowsKeyboardMouseFilterSDKBatch','Stop-WindowsKeyboardMouseFilterSDKWait','Get-WindowsKeyboardMouseFilterSDKDescriptor','Send-WindowsKeyboardMouseFilterSDKInput','Disconnect-WindowsKeyboardMouseFilterSDK')
CmdletsToExport = @()
VariablesToExport = @()
AliasesToExport = @()
PrivateData = @{ PSData = @{ Tags = @('Windows','SDK','Keyboard','Mouse','Gamepad'); LicenseUri = 'https://github.com/titanfyre/Windows-Keyboard-Mouse-Filter/blob/main/LICENSE'; ProjectUri = 'https://github.com/titanfyre/Windows-Keyboard-Mouse-Filter'; ReleaseNotes = 'First PowerShell SDK; docs and native bridge included.' } }
}
