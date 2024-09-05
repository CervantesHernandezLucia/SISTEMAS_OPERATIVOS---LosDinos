@echo off
color 0A

:inicio
cls
echo.
echo ===================================================
echo            Calculadora de Resistencias
echo ===================================================
echo.
echo 1. Calcular resistencia de 4 bandas
echo 2. Calcular resistencia de 5 bandas
echo 3. Calcular resistencia de 6 bandas
echo 4. Salir
echo.
set /p opcion=Ingrese una opcion: 

if %opcion% equ 1 goto cuatroBandas
if %opcion% equ 2 goto cincoBandas
if %opcion% equ 3 goto seisBandas
if %opcion% equ 4 goto fin
goto inicio

:cuatroBandas
cls
echo.
echo Calculadora de Resistencias de 4 Bandas
echo.
set /p banda1=Ingrese el valor de la primera banda: 
set /p banda2=Ingrese el valor de la segunda banda: 
set /p multiplicador=Ingrese el valor del multiplicador: 
set /p tolerancia=Ingrese el valor de la tolerancia: 

set /a resistencia=%banda1%%banda2%*%multiplicador%
set /a toleranciaInferior=%resistencia%-(%resistencia%*%tolerancia%/100)
set /a toleranciaSuperior=%resistencia%+(%resistencia%*%tolerancia%/100)

echo.
echo La resistencia es de %resistencia% ohms.
echo La tolerancia es de +/- %tolerancia%%.
echo El rango de valores es de %toleranciaInferior% ohms a %toleranciaSuperior% ohms.
pause
goto inicio

:cincoBandas
cls
echo.
echo Calculadora de Resistencias de 5 Bandas
echo.
set /p banda1=Ingrese el valor de la primera banda: 
set /p banda2=Ingrese el valor de la segunda banda: 
set /p banda3=Ingrese el valor de la tercera banda: 
set /p multiplicador=Ingrese el valor del multiplicador: 
set /p tolerancia=Ingrese el valor de la tolerancia: 

set /a resistencia=%banda1%%banda2%%banda3%*%multiplicador%
set /a toleranciaInferior=%resistencia%-(%resistencia%*%tolerancia%/100)
set /a toleranciaSuperior=%resistencia%+(%resistencia%*%tolerancia%/100)

echo.
echo La resistencia es de %resistencia% ohms.
echo La tolerancia es de +/- %tolerancia%%.
echo El rango de valores es de %toleranciaInferior% ohms a %toleranciaSuperior% ohms.
pause
goto inicio

:seisBandas
cls
echo.
echo Calculadora de Resistencias de 6 Bandas
echo.
set /p banda1=Ingrese el valor de la primera banda: 
set /p banda2=Ingrese el valor de la segunda banda: 
set /p banda3=Ingrese el valor de la tercera banda: 
set /p multiplicador=Ingrese el valor del multiplicador: 
set /p tolerancia=Ingrese el valor de la tolerancia: 
set /p tcr=Ingrese el coeficiente de temperatura: 

set /a resistencia=%banda1%%banda2%%banda3%*%multiplicador%
set /a toleranciaInferior=%resistencia%-(%resistencia%*%tolerancia%/100)
set /a toleranciaSuperior=%resistencia%+(%resistencia%*%tolerancia%/100)

echo.
echo La resistencia es de %resistencia% ohms.
echo La tolerancia es de +/- %tolerancia%%.
echo El rango de valores es de %toleranciaInferior% ohms a %toleranciaSuperior% ohms.
echo El coeficiente de temperatura es de %tcr% ppm/°C.
pause
goto inicio

:fin
cls
echo.
echo Gracias por usar la calculadora de resistencias.
pause
exit