$ErrorActionPreference='Stop'
$scratch=$PSScriptRoot
. (Join-Path $scratch 'stringtable.ps1')

# Paths are derived from this script's location, so the repo can live anywhere.
$repo  = (Resolve-Path (Join-Path $scratch '..\..')).Path
$info  = Join-Path $repo 'Release\Data\info'
$src   = Join-Path $info 'String.inf.kr'
$dest  = Join-Path $info 'String.inf'
$rows  = Read-DEStringTable $src
$trans = & (Join-Path $scratch 'translations.ps1')

"source records : $($rows.Count)"
"translations   : $($trans.Count)"

# --- validate BEFORE writing anything ---------------------------------------
# The client passes printf arguments positionally, so the specifier sequence in
# the English text must match the Korean exactly - same specifiers, same order.
function Get-Specs([string]$s){
    return (([regex]::Matches($s,'%[-+ #0]*[0-9]*(?:\.[0-9]+)?[a-zA-Z]') | ForEach-Object { $_.Value }) -join ',')
}

$problems=@()
foreach($k in $trans.Keys){
    $i=[int]$k
    if($i -lt 0 -or $i -ge $rows.Count){ $problems += ("index {0} out of range" -f $i); continue }
    $ko=Get-Specs $rows[$i]
    $en=Get-Specs $trans[$k]
    if($ko -ne $en){ $problems += ("index {0}: specifiers differ  KR[{1}]  EN[{2}]" -f $i,$ko,$en) }
    if($trans[$k] -match '[\uAC00-\uD7A3]'){ $problems += ("index {0}: translation still contains Korean" -f $i) }
}

if($problems.Count){
    "`nVALIDATION FAILED - nothing written:"
    $problems | ForEach-Object { "  $_" }
    throw "$($problems.Count) problem(s)"
}
"specifier check: OK ($($trans.Count) entries)"

# --- apply -------------------------------------------------------------------
$out=New-Object System.Collections.ArrayList
for($i=0;$i -lt $rows.Count;$i++){
    if($trans.ContainsKey($i)){ [void]$out.Add([string]$trans[$i]) } else { [void]$out.Add($rows[$i]) }
}
Write-DEStringTable $dest $out

# --- verify what landed ------------------------------------------------------
$check=Read-DEStringTable $dest
if($check.Count -ne $rows.Count){ throw "record count changed: $($check.Count) vs $($rows.Count)" }
$stillKo=@($check | Where-Object { $_ -match '[\uAC00-\uD7A3\u3131-\u318E]' }).Count
$origKo =@($rows  | Where-Object { $_ -match '[\uAC00-\uD7A3\u3131-\u318E]' }).Count

""
"installed      : $dest ($((Get-Item $dest).Length) bytes)"
"records        : $($check.Count)"
"Korean before  : $origKo"
"Korean after   : $stillKo   (translated $($origKo - $stillKo) this pass)"
"remaining      : $stillKo of $origKo  ($([math]::Round(100*$stillKo/$origKo,1))%)"
""
"--- spot check ---"
foreach($i in 0,19,31,49,81){ "  [{0,4}] {1}" -f $i,$check[$i] }

