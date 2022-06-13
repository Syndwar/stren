call "c:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\vcvars32.bat" 

CHOICE /M "Press O to Open Project. B to Build or R to Rebuild. C to Clean:" /C OBRC

IF %ERRORLEVEL% EQU 1 (
    GOTO :OPEN
)
IF %ERRORLEVEL% EQU 2 (
    SET PARAM1=Build
)
IF %ERRORLEVEL% EQU 3 (
    SET PARAM1=Rebuild
)
IF %ERRORLEVEL% EQU 4 (
    SET PARAM1=Clean
)

CHOICE /M "Press R for Release or D for Debug:" /C RD

IF %ERRORLEVEL% EQU 1 (
    SET PARAM2=Release
)
IF %ERRORLEVEL% EQU 2 (
    SET PARAM2=Debug
)
GOTO :BUILD

:OPEN
devenv stren.sln
GOTO :END

:BUILD
devenv stren.sln /%PARAM1% %PARAM2%

:END
pause