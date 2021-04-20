@ECHO OFF
setlocal
ECHO This will install Wolf3d project dependencies.
ECHO Before install, you have to install MingW gcc compiler for Windows.
ECHO Download the installer from https://sourceforge.net/projects/mingw/files/Installer/
ECHO Project assumes that it is installed to C:\MinGW
:PROMPT
SET /P AREYOUSURE= Are you sure you want to proceed (Y/[N])
IF /I "%AREYOUSURE%" NEQ "Y" GOTO END
IF NOT EXIST C:\MinGW (
    GOTO END
)
SETX PATH "%path%;c:\MinGW\bin"
IF NOT EXIST SDL2-devel-2.0.14-mingw.tar.gz (
    CURL https://www.libsdl.org/release/SDL2-devel-2.0.14-mingw.tar.gz --output SDL2-devel-2.0.14-mingw.tar.gz
) ELSE (
    ECHO SDL2-devel-2.0.14-mingw.tar.gz already exists, proceeding..
)
IF NOT EXIST SDL2-2.0.14 (
    tar -xzf SDL2-devel-2.0.14-mingw.tar.gz
) ELSE (
    ECHO SDL2-2.0.14 already exists, proceeding..
)
IF NOT EXIST SDL2_mixer-devel-2.0.4-mingw.tar.gz (
    CURL https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-devel-2.0.4-mingw.tar.gz --output SDL2_mixer-devel-2.0.4-mingw.tar.gz
) ELSE (
    ECHO SDL2_mixer-devel-2.0.4-mingw.tar.gz already exists, proceeding..
)
IF NOT EXIST SDL2_mixer-2.0.4 (
    tar -xzf SDL2_mixer-devel-2.0.4-mingw.tar.gz
) ELSE (
    ECHO SDL2-2.0.4-mixer already exists, proceeding..
)
:END
endlocal