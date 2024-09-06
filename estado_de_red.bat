@echo off
:: Nota, este codigo no funciona con la red de la escuela debido a que esta protegida.
:: Escaneo de red - Verificación de velocidad
echo Verificando velocidad de la red...
:: Ping a un servidor para determinar el tiempo de respuesta promedio
ping -n 4 8.8.8.8 > ping_result.txt

:: Leer el archivo de resultados y extraer el tiempo de respuesta promedio
setlocal enabledelayedexpansion
set PingMs=

for /f "tokens=1,2,3,4,5 delims= " %%a in ('findstr /i "media promedio" ping_result.txt') do (
    set PingMs=%%d
)

:: Verificar si se ha encontrado el tiempo de respuesta promedio
if not defined PingMs (
    echo No se pudo determinar el tiempo de respuesta promedio.
    goto :fin
)

:: Determinar el estado de la red basado en el tiempo de respuesta
set EstadoRed=Mala
if !PingMs! LSS 100 set EstadoRed=Buena
if !PingMs! GEQ 100 if !PingMs! LSS 200 set EstadoRed=Aceptable

echo Tiempo de respuesta promedio: !PingMs!
echo Estado de la red: %EstadoRed%

:: Escaneo de procesos activos
echo Listando los 5 procesos que mas recursos consumen...
powershell "Get-Process | Sort-Object CPU -Descending | Select-Object -First 5 | Format-Table -AutoSize" > procesos_top5.txt

:: Mostrar resultados al usuario
echo.
echo * Estado de la Red: %EstadoRed% * 
type procesos_top5.txt
echo.
:: Mantener la ventana abierta al finalizar
echo Presiona cualquier tecla para salir...
pause >nul

:fin
endlocal
