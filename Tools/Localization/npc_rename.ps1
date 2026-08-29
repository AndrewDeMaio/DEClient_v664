$ErrorActionPreference='Stop'
$scratch=$PSScriptRoot
. (Join-Path $scratch 'npcscriptinf.ps1')
$e=[Text.Encoding]::GetEncoding(949)

# ---------------------------------------------------------------------------
# 1. creature.inf - the floating world label.
#
# GCAddNPCHandler uses the packet name only for zones 1500-1506; everywhere
# else it uses g_pCreatureTable[creatureType].Name, which comes from this file.
# Name is the first field of CREATURETABLE_INFO and is a length-prefixed
# string, and the container is a sequential CTypeTable with no offset table,
# so substituting a different-length name is safe.
# ---------------------------------------------------------------------------
$repo=(Resolve-Path (Join-Path $scratch '..\..')).Path
$info=Join-Path $repo 'Release\Data\Info'
$cf=Join-Path $info 'creature.inf'
$cbak="$cf.orig"
if(-not (Test-Path $cbak)){ Copy-Item $cf $cbak; "backed up creature.inf -> .orig" } else { "creature.inf backup exists" }

$b=[IO.File]::ReadAllBytes($cbak)

# prefixOffset, oldByteLen, english   (verified against the source bytes)
$renames=@(
  @{ off=3094;  len=4;  en='Zach'          }   # Zach   (sprite 15, NPC 16)
  @{ off=3267;  len=6;  en='Kaiser'        }   # Kaiser (sprite 16, NPC 17)
  @{ off=4834;  len=4;  en='Tanya'         }   # Tanya  (sprite 25, NPC 26)
  @{ off=77202; len=10; en='Carmen Berman' }   # Carmen (sprite 96, NPC 430)
)

# sanity-check every offset before writing anything
foreach($r in $renames){
    $declared=[BitConverter]::ToInt32($b,$r.off)
    if($declared -ne $r.len){ throw ("offset {0}: declared length {1}, expected {2}" -f $r.off,$declared,$r.len) }
}
"all 4 length prefixes verified"

# apply from the highest offset down so earlier offsets stay valid
$out=$b
foreach($r in ($renames | Sort-Object off -Descending)){
    $newBytes=$e.GetBytes($r.en)
    $head=$out[0..($r.off-1)]
    $tailStart=$r.off+4+$r.len
    $tail= if($tailStart -lt $out.Length){ $out[$tailStart..($out.Length-1)] } else { @() }
    $ms=New-Object IO.MemoryStream
    $ms.Write($head,0,$head.Length)
    $ms.Write([BitConverter]::GetBytes([int]$newBytes.Length),0,4)
    $ms.Write($newBytes,0,$newBytes.Length)
    if($tail.Length){ $ms.Write($tail,0,$tail.Length) }
    $out=$ms.ToArray(); $ms.Dispose()
}
[IO.File]::WriteAllBytes($cf,$out)
"creature.inf : $($b.Length) -> $($out.Length) bytes"

# ---------------------------------------------------------------------------
# 2. NPCScript.inf - the speaker name shown inside the dialogue window
# ---------------------------------------------------------------------------
$inf=Join-Path $info 'NPCScript.inf'
$rows=Read-NPCScriptInf $inf
$ownerMap=@{}
$ownerMap[[string]([char]0xD0C0+[string][char]0xB0D0)]                     = 'Tanya'   # 타냐
$ownerMap[[string]([char]0xC790+[string][char]0xD06C)]                     = 'Zach'    # 자크
$ownerMap[[string]([char]0xCE74+[string][char]0xC774+[string][char]0xC800)]= 'Kaiser'  # 카이저
$ownerMap[[string]([char]0xCE74+[string][char]0xB974+[string][char]0xBA58)]= 'Carmen'  # 카르멘

$changed=0
foreach($r in $rows){
    if($ownerMap.ContainsKey($r.OwnerID)){ $r.OwnerID=$ownerMap[$r.OwnerID]; $changed++ }
}
Write-NPCScriptInf $inf $rows
"NPCScript.inf: $changed OwnerID fields renamed"
