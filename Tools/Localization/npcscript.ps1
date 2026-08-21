# npcscript.ps1 - read/write NPC dialogue in the server's Script table
#
# Content holds the player's menu options separated by "**", but the exact
# whitespace before each "**" varies per NPC:
#   Tanya  (4301,4306) : CR LF **
#   Zach   (4101...)   : LF **
#   Kaiser (4000...)   : TAB TAB **
# Guessing one convention would break the others, so Set-DEScript rebuilds
# Content using the ORIGINAL separator bytes captured from the source row and
# only substitutes the option text.
#
# All writes go through UNHEX() so nothing depends on the client charset.

$ErrorActionPreference='Stop'
$script:ENC949=[Text.Encoding]::GetEncoding(949)
$script:MYSQL='C:\Program Files\MySQL\MySQL Workbench 8.0 CE\mysql.exe'

function Invoke-DE([string]$sql){
    $conf=Get-Content 'D:\GitHub\DEServer_v664\conf\gameserver.local.conf' -Encoding UTF8
    $pw=(($conf | Where-Object { $_ -match '^\s*DB_PASSWORD\s*[:=]\s*(.+)$' } | Select-Object -First 1) -replace '^\s*DB_PASSWORD\s*[:=]\s*','').Trim()
    $psi=New-Object System.Diagnostics.ProcessStartInfo
    $psi.FileName=$script:MYSQL
    $psi.Arguments='-h 127.0.0.1 -u elcastle -D DARKEDEN -N -B --default-character-set=latin1'
    $psi.RedirectStandardInput=$true; $psi.RedirectStandardOutput=$true; $psi.RedirectStandardError=$true
    $psi.UseShellExecute=$false
    $psi.StandardOutputEncoding=[Text.Encoding]::GetEncoding(28591)
    $psi.EnvironmentVariables['MYSQL_PWD']=$pw
    $p=[System.Diagnostics.Process]::Start($psi)
    $p.StandardInput.Write($sql); $p.StandardInput.Close()
    $out=$p.StandardOutput.ReadToEnd(); $err=$p.StandardError.ReadToEnd(); $p.WaitForExit()
    if($p.ExitCode -ne 0){ throw "mysql failed: $err" }
    return $out
}

function Get-DEScript([int]$id){
    $raw=(Invoke-DE "SELECT HEX(IFNULL(Subject,'')), HEX(IFNULL(Content,'')) FROM Script WHERE ScriptID=$id;").Trim()
    if(-not $raw){ throw "script $id not found" }
    $p=$raw -split "`t"
    $dec={ param($h) if(-not $h){ return '' }
           $b=[byte[]]::new($h.Length/2)
           for($i=0;$i -lt $b.Length;$i++){ $b[$i]=[Convert]::ToByte($h.Substring($i*2,2),16) }
           $script:ENC949.GetString($b) }
    return [pscustomobject]@{ ScriptID=$id; Subject=(& $dec $p[0]); Content=(& $dec $p[1]) }
}

# Returns the separator strings that sit immediately before each "**".
function Get-DESeparators([string]$content){
    $seps=@()
    foreach($m in [regex]::Matches($content,'([\r\n\t ]*)\*\*')){ $seps += $m.Groups[1].Value }
    return ,$seps
}

function Set-DEScript([int]$id,[string]$subject,[string[]]$options){
    $cur=Get-DEScript $id
    $newContent=''
    if($options -and $options.Count -gt 0){
        $seps=Get-DESeparators $cur.Content
        if($seps.Count -ne $options.Count-1){
            throw ("script {0}: source has {1} separators (={2} options) but {3} options supplied" -f $id,$seps.Count,($seps.Count+1),$options.Count)
        }
        $sb=New-Object Text.StringBuilder
        for($i=0;$i -lt $options.Count;$i++){
            [void]$sb.Append($options[$i])
            if($i -lt $seps.Count){ [void]$sb.Append($seps[$i]); [void]$sb.Append('**') }
        }
        # keep any trailing whitespace the source had after the last option
        $tail=[regex]::Match($cur.Content,'([\r\n\t ]*)$').Groups[1].Value
        [void]$sb.Append($tail)
        $newContent=$sb.ToString()
    } else {
        $newContent=$cur.Content   # untouched when no options are supplied
    }
    $hex={ param($s) if($s -eq ''){ return '' } ; (($script:ENC949.GetBytes($s) | ForEach-Object { '{0:X2}' -f $_ }) -join '') }
    $sHex=& $hex $subject
    $cHex=& $hex $newContent
    $sExpr = if($sHex){ "UNHEX('$sHex')" } else { "''" }
    $cExpr = if($cHex){ "UNHEX('$cHex')" } else { "''" }
    Invoke-DE "UPDATE Script SET Subject=$sExpr, Content=$cExpr WHERE ScriptID=$id;" | Out-Null
}
