echo LIBRARY HavokScript_FinalRelease > HavokScript_FinalRelease.def
echo EXPORTS >> HavokScript_FinalRelease.def
for /f "skip=19 tokens=4" %%A in ('dumpbin /exports HavokScript_FinalRelease.dll') do echo %%A >> HavokScript_FinalRelease.def
lib /def:HavokScript_FinalRelease.def /out:HavokScript_FinalRelease.lib /machine:x64
