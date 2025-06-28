@echo off
echo Compilando Music Player com Suporte MP3 - VERSAO FINAL...

REM Adicionar MinGW ao PATH temporariamente
set PATH=%PATH%;C:\MinGW\bin

REM Compilar a versao final com busca automatica na pasta musicas/
gcc -o music_player.exe main.c biblioteca_fila_historico.c player_funcoes.c interface.c audio_player.c -lwinmm

if %errorlevel% equ 0 (
    echo.
    echo ========================================
    echo   COMPILACAO BEM-SUCEDIDA! ^_^            
    echo.
    echo ========================================
    echo.
    echo Executando o programa...
    echo.
    music_player.exe
) else (
    echo Erro na compilacao!
    echo Verifique se o MinGW esta instalado em C:\MinGW\bin
    pause
)
