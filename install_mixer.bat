
@ECHO OFF
setlocal
ECHO This will install DoomNukem mixer dependencies.
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