# stringtable.ps1 - read/write DarkEden String.inf tables
#
# Format (verified byte-exact against String.inf 61789 bytes / 1969 records
# and SHelpString.inf 2795 bytes / 96 records):
#
#   int32 count
#   repeat count:
#       int32 length
#       byte[length] text        # CP949, no NUL terminator
#
# Records are length-prefixed, so translated text may be any length.
#
# The data contains real TAB (23 records) and real LF (16 records), AND nine
# records holding a literal two-character "\n" that the game uses as its own
# line-break marker. The TSV escaping therefore escapes the backslash first so
# the two remain distinguishable on the way back.

$ErrorActionPreference='Stop'
$script:ENC949=[Text.Encoding]::GetEncoding(949)

function Read-DEStringTable([string]$Path){
    $b=[IO.File]::ReadAllBytes($Path)
    $off=0
    $count=[BitConverter]::ToInt32($b,$off); $off+=4
    if($count -lt 0 -or $count -gt 200000){ throw "implausible record count $count" }
    $rows=New-Object System.Collections.ArrayList
    for($i=0;$i -lt $count;$i++){
        if($off+4 -gt $b.Length){ throw "ran off end at record $i" }
        $len=[BitConverter]::ToInt32($b,$off); $off+=4
        if($len -lt 0 -or $off+$len -gt $b.Length){ throw "bad length $len at record $i" }
        $s= if($len -gt 0){ $script:ENC949.GetString($b,$off,$len) } else { '' }
        $off+=$len
        [void]$rows.Add($s)
    }
    if($off -ne $b.Length){ throw "trailing data: consumed $off of $($b.Length)" }
    return ,$rows
}

function Write-DEStringTable([string]$Path,[object]$Rows){
    $ms=New-Object IO.MemoryStream
    $bw=New-Object IO.BinaryWriter($ms)
    $bw.Write([int]$Rows.Count)
    foreach($s in $Rows){
        # Use the explicit (byte[],int,int) overload: $bw.Write($bytes) lets
        # PowerShell resolve to Write(byte) and emit one byte per record,
        # silently truncating the whole table.
        [byte[]]$bytes = if([string]::IsNullOrEmpty($s)){ New-Object byte[] 0 } else { $script:ENC949.GetBytes($s) }
        $bw.Write([int]$bytes.Length)
        if($bytes.Length -gt 0){ $bw.Write($bytes,0,$bytes.Length) }
    }
    $bw.Flush()
    [IO.File]::WriteAllBytes($Path,$ms.ToArray())
    $bw.Dispose(); $ms.Dispose()
}

function Compress-DEEscapes([string]$s){
    # backslash first, then the control characters
    return ($s -replace '\\','\\' -replace "`t",'\t' -replace "`r",'\r' -replace "`n",'\n')
}

function Expand-DEEscapes([string]$s){
    if($s.IndexOf('\') -lt 0){ return $s }
    $sb=New-Object Text.StringBuilder
    $i=0
    while($i -lt $s.Length){
        $done=$false
        if($s[$i] -eq '\' -and $i+1 -lt $s.Length){
            # NOTE: 'continue' inside a switch continues the SWITCH, not the
            # enclosing loop - hence the explicit flag and the advance outside.
            $handled=$true
            switch($s[$i+1]){
                '\'     { [void]$sb.Append('\') }
                't'     { [void]$sb.Append([char]9) }
                'r'     { [void]$sb.Append([char]13) }
                'n'     { [void]$sb.Append([char]10) }
                default { $handled=$false }
            }
            if($handled){ $i+=2; $done=$true }
        }
        if(-not $done){ [void]$sb.Append($s[$i]); $i++ }
    }
    return $sb.ToString()
}

function Export-DEStringTsv([string]$Src,[string]$Tsv){
    $rows=Read-DEStringTable $Src
    $sb=New-Object Text.StringBuilder
    [void]$sb.AppendLine("Index`tKorean`tEnglish")
    for($i=0;$i -lt $rows.Count;$i++){
        [void]$sb.AppendLine("$i`t$(Compress-DEEscapes $rows[$i])`t")
    }
    [IO.File]::WriteAllText($Tsv,$sb.ToString(),(New-Object Text.UTF8Encoding($true)))
    return $rows.Count
}

# Build a table from a TSV, using the English column where filled and falling
# back to the original Korean where blank. Partial translations are fine.
function Import-DEStringTsv([string]$Tsv,[string]$Dest){
    $lines=[IO.File]::ReadAllLines($Tsv,[Text.Encoding]::UTF8)
    if($lines[0] -notmatch 'Index'){ throw 'missing header row' }
    $rows=New-Object System.Collections.ArrayList
    $translated=0
    for($i=1;$i -lt $lines.Count;$i++){
        if($lines[$i] -eq ''){ continue }
        $c=$lines[$i] -split "`t",3
        if($c.Count -lt 2){ throw "malformed row $i" }
        $kr=$c[1]; $en= if($c.Count -ge 3){ $c[2] } else { '' }
        $pick= if([string]::IsNullOrWhiteSpace($en)){ $kr } else { $translated++; $en }
        [void]$rows.Add((Expand-DEEscapes $pick))
    }
    Write-DEStringTable $Dest $rows
    return [pscustomobject]@{ Records=$rows.Count; Translated=$translated }
}
