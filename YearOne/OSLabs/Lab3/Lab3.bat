@echo off
cls
setlocal enableDelayedExpansion

:: Начало цикла

:loop

:: Выбор пользователя

echo 1-Rock, 2-Scissors, 3-Paper, 4-Stop 
set /p input= Type any input  

cls
if %input%==4 (GOTO end)  

GOTO printer


GOTO loop

:printer

:: Вывод на экран

if %input%==1 type Rock.txt
if %input%==2 type Scissors.txt
if %input%==3 type Paper.txt

type VS.txt

:: Выбор случайной опции для противника

SET /A rnd=%RANDOM% * 3 / 32768 + 1

if %rnd%==1 type Rock.txt
if %rnd%==2 type Scissors.txt
if %rnd%==3 type Paper.txt

if %input%==1 GOTO Rock
if %input%==2 GOTO Scissors
if %input%==3 GOTO Paper

GOTO loop

:: Вычисление и вывод результата

:Rock
if %rnd%==1 type Draw.txt
if %rnd%==2 type Win.txt
if %rnd%==3 type Loose.txt
GOTO loop

:Scissors
if %rnd%==1 type Loose.txt
if %rnd%==2 type Draw.txt
if %rnd%==3 type Win.txt
GOTO loop

:Paper
if %rnd%==1 type Win.txt
if %rnd%==2 type Loose.txt
if %rnd%==3 type Draw.txt
GOTO loop

endlocal

:end