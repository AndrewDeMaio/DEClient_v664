$ErrorActionPreference='Stop'
$scratch=$PSScriptRoot
. (Join-Path $scratch 'npcscriptinf.ps1')
. (Join-Path $scratch 'npcscript.ps1')      # Get-DEScript, for reading the DB

$repo=(Resolve-Path (Join-Path $scratch '..\..')).Path
$inf=Join-Path $repo 'Release\Data\Info\NPCScript.inf'
$bak="$inf.orig"
if(-not (Test-Path $bak)){ Copy-Item $inf $bak; "backed up -> NPCScript.inf.orig" } else { "backup already exists" }

$rows=Read-NPCScriptInf $bak
$byId=@{}; foreach($r in $rows){ $byId[[int]$r.ScriptID]=$r }
"client scripts: $($rows.Count)"

# every ScriptID translated in the server DB so far
$ids = @(8000..8008) + @(8010) + @(8020..8023) +      # Carmen
       @(4000) + @(4002..4021) +                       # Kaiser core
       @(4101..4124) +                                 # Zach
       @(4301..4317)                                   # Tanya

$done=0; $skipped=@(); $mismatch=@()
foreach($id in $ids){
    if(-not $byId.ContainsKey($id)){ $skipped += "$id not in client file"; continue }
    try { $db=Get-DEScript $id } catch { $skipped += "$id not in DB"; continue }

    $target=$byId[$id]

    # subject: the client stores it as a table; these all have exactly one entry
    if($target.Subject.Count -ne 1){ $mismatch += "$id has $($target.Subject.Count) subject rows"; continue }

    # options: server joins them with **, client stores one per array entry
    $opts=@()
    if($db.Content.Trim()){
        $opts = @($db.Content -split '\*\*' | ForEach-Object { $_.Trim() } | Where-Object { $_ -ne '' })
    }
    if($opts.Count -ne $target.Content.Count){
        $mismatch += ("{0}: DB has {1} options, client expects {2}" -f $id,$opts.Count,$target.Content.Count)
        continue
    }

    $target.Subject[0]=$db.Subject
    for($i=0;$i -lt $opts.Count;$i++){ $target.Content[$i]=$opts[$i] }
    $done++
}

"transferred    : $done scripts"
if($skipped.Count){ "skipped:"; $skipped | ForEach-Object { "   $_" } }
if($mismatch.Count){ "`nOPTION COUNT MISMATCH - nothing written:"; $mismatch | ForEach-Object { "   $_" }; throw "$($mismatch.Count) mismatch(es)" }

Write-NPCScriptInf $inf $rows
"installed      : $inf ($((Get-Item $inf).Length) bytes, was $((Get-Item $bak).Length))"

# verify by re-reading the installed file
$check=Read-NPCScriptInf $inf
if($check.Count -ne $rows.Count){ throw "script count changed" }
$stillKo=0
foreach($id in $ids){
    $r=$check | Where-Object { $_.ScriptID -eq $id }
    if(-not $r){ continue }
    $all=($r.Subject -join '') + ($r.Content -join '')
    if(@($all.ToCharArray()|Where-Object{[int]$_ -ge 0x80}).Count -gt 0){ $stillKo++ }
}
"scripts still containing Korean, of the $($ids.Count) targeted: $stillKo"
