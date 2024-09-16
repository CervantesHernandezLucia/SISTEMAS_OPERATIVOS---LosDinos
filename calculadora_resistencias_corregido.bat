@echo off
color 0A

:inicio
cls
echo.
echo ===================================================
echo            Calculadora de Resistencias
echo ===================================================
echo.
echo 4. Calcular resistencia de 4 bandas
echo 5. Calcular resistencia de 5 bandas
echo 6. Calcular resistencia de 6 bandas
echo 1. Salir
echo.
set /p opcion=Ingrese una opcion: 

if %opcion% equ 4 goto cuatroBandas
if %opcion% equ 5 goto cincoBandas
if %opcion% equ 6 goto seisBandas
if %opcion% equ 1 goto fin
goto inicio

:cuatroBandas
cls
echo.
echo Calculadora de Resistencias de 4 Bandas
echo.
echo Ingrese los colores de las bandas separados por espacios.
echo.
echo.
echo.
echo.
echo Ejemplo: 1 2 100 5 (Marron, Rojo, Rojo como multiplicador, Oro como tolerancia)
echo.
echo 1. Marron, 2. Rojo, 3. Naranja, 4. Amarillo, 5. Verde, 6. Azul, 7. Morado, 8. Gris, 9. Blanco
echo.
echo Multiplicador: Negro=1, Marron=10, Rojo=100, Naranja=1000, Amarillo=10000, Verde=100000, Azul=1000000, Morado=10000000
echo.
echo Tolerancia: Marron=1%%, Rojo=2%%, Oro=5%%, Plata=10%%
echo.
echo.
echo.
echo.

set /p valores="Ingrese las bandas 1, 2, multiplicador y tolerancia: "

for /f "tokens=1,2,3,4" %%a in ("%valores%") do (
    set banda1=%%a
    set banda2=%%b
    set multiplicador=%%c
    set tolerancia=%%d
)

set /a resistencia=%banda1%%banda2%*%multiplicador%
set /a toleranciaInferior=%resistencia%-(%resistencia%*%tolerancia%/100)
set /a toleranciaSuperior=%resistencia%+(%resistencia%*%tolerancia%/100)

echo.
echo La resistencia es de %resistencia% ohms.
echo La tolerancia es de +/- %tolerancia%%.
echo El rango de valores es de %toleranciaInferior% ohms a %toleranciaSuperior% ohms.
echo.
echo 1. Volver al menu principal
set /p volver=Presione cualquier tecla para regresar.
goto inicio

:cincoBandas
cls
echo.
echo Calculadora de Resistencias de 5 Bandas
echo.
echo Ingrese los colores de las bandas separados por espacios.
echo.
echo.
echo.
echo.
echo Ejemplo: 1 2 3 100 5 (Marron, Rojo, Naranja, Naranja como multiplicador, Oro como tolerancia)
echo.
echo 1. Marron, 2. Rojo, 3. Naranja, 4. Amarillo, 5. Verde, 6. Azul, 7. Morado, 8. Gris, 9. Blanco
echo.
echo Multiplicador: Negro=1, Marron=10, Rojo=100, Naranja=1000, Amarillo=10000, Verde=100000, Azul=1000000, Morado=10000000
echo.
echo Tolerancia: Marron=1%%, Rojo=2%%, Oro=5%%, Plata=10%%
echo.
echo.
echo.
echo.

set /p valores="Ingrese las bandas 1, 2, 3, multiplicador y tolerancia: "

for /f "tokens=1,2,3,4,5" %%a in ("%valores%") do (
    set banda1=%%a
    set banda2=%%b
    set banda3=%%c
    set multiplicador=%%d
    set tolerancia=%%e
)

set /a resistencia=%banda1%%banda2%%banda3%*%multiplicador%
set /a toleranciaInferior=%resistencia%-(%resistencia%*%tolerancia%/100)
set /a toleranciaSuperior=%resistencia%+(%resistencia%*%tolerancia%/100)

echo.
echo La resistencia es de %resistencia% ohms.
echo La tolerancia es de +/- %tolerancia%%.
echo El rango de valores es de %toleranciaInferior% ohms a %toleranciaSuperior% ohms.
echo.
echo 1. Volver al menu principal
set /p volver=Presione cualquier tecla para regresar.
goto inicio

:seisBandas
cls
echo.
echo Calculadora de Resistencias de 6 Bandas
echo.
echo Ingrese los colores de las bandas separados por espacios.
echo.
echo.
echo.
echo.
echo Ejemplo: 1 2 3 100 5 10 (Marron, Rojo, Naranja, Naranja como multiplicador, Oro como tolerancia, Azul como TCR)
echo.
echo 1. Marron, 2. Rojo, 3. Naranja, 4. Amarillo, 5. Verde, 6. Azul, 7. Morado, 8. Gris, 9. Blanco
echo.
echo Multiplicador: Negro=1, Marron=10, Rojo=100, Naranja=1000, Amarillo=10000, Verde=100000, Azul=1000000, Morado=10000000
echo.
echo Tolerancia: Marron=1%%, Rojo=2%%, Oro=5%%, Plata=10%%
echo.
echo TCR: Negro=250ppm/C, Marron=100ppm/C, Rojo=50ppm/C, Naranja=15ppm/C, Amarillo=25ppm/C, Verde=20ppm/C, Azul=10ppm/C, Morado=5ppm/C, Gris=1ppm/C
echo.
echo.
echo.
echo.

set /p valores="Ingrese las bandas 1, 2, 3, multiplicador, tolerancia y TCR: "

for /f "tokens=1,2,3,4,5,6" %%a in ("%valores%") do (
    set banda1=%%a
    set banda2=%%b
    set banda3=%%c
    set multiplicador=%%d
    set tolerancia=%%e
    set tcr=%%f
)

set /a resistencia=%banda1%%banda2%%banda3%*%multiplicador%
set /a toleranciaInferior=%resistencia%-(%resistencia%*%tolerancia%/100)
set /a toleranciaSuperior=%resistencia%+(%resistencia%*%tolerancia%/100)

echo.
echo La resistencia es de %resistencia% ohms.
echo La tolerancia es de +/- %tolerancia%%.
echo El rango de valores es de %toleranciaInferior% ohms a %toleranciaSuperior% ohms.
echo El coeficiente de temperatura es de %tcr% ppm/C.
echo.
echo 1. Volver al menu principal
set /p volver=Presione cualquier tecla para regresar.
goto inicio

:fin
cls
echo.
echo Gracias por usar la calculadora de resistencias.
pause
exit
