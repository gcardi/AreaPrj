@echo off
call "C:\Program Files (x86)\Embarcadero\Studio\37.0\bin\rsvars.bat" || exit /b 1
msbuild Area.cbproj /t:%1 /p:Config=Release /p:Platform=Win64x
