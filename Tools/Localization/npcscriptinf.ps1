# npcscriptinf.ps1 - read/write Data\Info\NPCScript.inf
#
# This is the file the CLIENT actually uses for NPC dialogue. GCNPCAsk carries
# only ObjectID + ScriptID + NPCID, so the server never sends the text; the
# client resolves the ScriptID against this table (MNPCScriptTable::LoadFromFile).
#
# Format:
#   int32 count
#   repeat count:
#     uint32  ScriptID
#     MString OwnerID          # int32 len + CP949 bytes
#     table   SubjectTable     # int32 n + n * MString
#     table   ContentTable     # int32 n + n * MString   (one entry per option)
#
# Note the options are separate array entries here, not "**"-joined the way the
# server's Script.Content column stores them.

$ErrorActionPreference='Stop'
$script:ENC949=[Text.Encoding]::GetEncoding(949)

function Read-NPCScriptInf([string]$Path){
    $b=[IO.File]::ReadAllBytes($Path)
    $off=0
    function RdInt{ $v=[BitConverter]::ToInt32($script:b,$script:off); $script:off+=4; return $v }
    $script:b=$b; $script:off=0
    $count=RdInt
    if($count -lt 0 -or $count -gt 100000){ throw "implausible script count $count" }
    $rdStr={
        $len=[BitConverter]::ToInt32($script:b,$script:off); $script:off+=4
        if($len -lt 0 -or $script:off+$len -gt $script:b.Length){ throw "bad string length $len at $($script:off)" }
        $s= if($len -gt 0){ $script:ENC949.GetString($script:b,$script:off,$len) } else { '' }
        $script:off+=$len
        return $s
    }
    $rdTab={
        $n=[BitConverter]::ToInt32($script:b,$script:off); $script:off+=4
        if($n -lt 0 -or $n -gt 10000){ throw "implausible table size $n" }
        $a=New-Object System.Collections.ArrayList
        for($j=0;$j -lt $n;$j++){ [void]$a.Add((& $rdStr)) }
        return ,$a
    }
    $rows=New-Object System.Collections.ArrayList
    for($i=0;$i -lt $count;$i++){
        $id=[BitConverter]::ToUInt32($script:b,$script:off); $script:off+=4
        $owner=& $rdStr
        $subj =& $rdTab
        $cont =& $rdTab
        [void]$rows.Add([pscustomobject]@{ ScriptID=$id; OwnerID=$owner; Subject=$subj; Content=$cont })
    }
    if($script:off -ne $b.Length){ throw "trailing data: consumed $($script:off) of $($b.Length)" }
    return ,$rows
}

function Write-NPCScriptInf([string]$Path,[object]$Rows){
    $ms=New-Object IO.MemoryStream
    $bw=New-Object IO.BinaryWriter($ms)
    $wrStr={ param($s)
        [byte[]]$by = if([string]::IsNullOrEmpty($s)){ New-Object byte[] 0 } else { $script:ENC949.GetBytes($s) }
        $bw.Write([int]$by.Length)
        if($by.Length -gt 0){ $bw.Write($by,0,$by.Length) }
    }
    $bw.Write([int]$Rows.Count)
    foreach($r in $Rows){
        $bw.Write([uint32]$r.ScriptID)
        & $wrStr $r.OwnerID
        $bw.Write([int]$r.Subject.Count); foreach($s in $r.Subject){ & $wrStr $s }
        $bw.Write([int]$r.Content.Count); foreach($s in $r.Content){ & $wrStr $s }
    }
    $bw.Flush()
    [IO.File]::WriteAllBytes($Path,$ms.ToArray())
    $bw.Dispose(); $ms.Dispose()
}
