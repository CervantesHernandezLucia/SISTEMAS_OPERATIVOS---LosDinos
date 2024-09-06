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
echo.
echo ==================================================================
echo            Ingrese el numero correspondiente al color de la banda 1
echo ==================================================================
echo.
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.

set /p banda1=Ingrese el valor de la primera banda: 


echo.
echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 2
echo ==========================================================
echo.
echo 0. Negro
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.

set /p banda2=Ingrese el valor de la segunda banda: 


echo.
echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 3
echo ==========================================================
echo.
echo 1. Negro
echo 10. Marron 
echo 100. Rojo
echo 1000. Naranja
echo 10000. Amarillo
echo 100000. Verde
echo 1000000. Azul
echo 10000000. Morado
echo.
echo.
echo.

set /p multiplicador=Ingrese el valor del multiplicador: 




echo.
echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 4
echo ==========================================================
echo.
echo 1. Marron 
echo 2. Rojo
echo 5. Oro
echo 10. Plata
echo.
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
echo.
echo ==================================================================
echo            Ingrese el numero correspondiente al color de la banda 1
echo ==================================================================
echo.
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.

set /p banda1=Ingrese el valor de la primera banda: 


echo.
echo.
echo ==================================================================
echo            Ingrese el numero correspondiente al color de la banda 2
echo ==================================================================
echo.
echo 0. Negro
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.

set /p banda2=Ingrese el valor de la segunda banda: 

echo.
echo.
echo ==================================================================
echo            Ingrese el numero correspondiente al color de la banda 3
echo ==================================================================
echo.
echo 0. Negro
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.

set /p banda3=Ingrese el valor de la tercera banda: 

echo.
echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 4
echo ==========================================================
echo.
echo 1. Negro
echo 10. Marron 
echo 100. Rojo
echo 1000. Naranja
echo 10000. Amarillo
echo 100000. Verde
echo 1000000. Azul
echo 10000000. Morado
echo.
echo.
echo.

set /p multiplicador=Ingrese el valor del multiplicador: 


echo.
echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 5
echo ==========================================================
echo.
echo 1. Marron 
echo 2. Rojo
echo 5. Oro
echo 10. Plata
echo.
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



echo.
echo.
echo ==================================================================
echo            Ingrese el numero correspondiente al color de la banda 1
echo ==================================================================
echo.
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.

set /p banda1=Ingrese el valor de la primera banda: 


echo.
echo.
echo ==================================================================
echo            Ingrese el numero correspondiente al color de la banda 2
echo ==================================================================
echo.
echo 0. Negro
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.
set /p banda2=Ingrese el valor de la segunda banda: 


echo.
echo.
echo ==================================================================
echo            Ingrese el numero correspondiente al color de la banda 3
echo ==================================================================
echo.
echo 0. Negro
echo 1. Marron 
echo 2. Rojo
echo 3. Naranja
echo 4. Amarillo
echo 5. Verde
echo 6. Azul
echo 7. Morado
echo 8. Gris
echo 9. Blanco
echo.
set /p banda3=Ingrese el valor de la tercera banda: 

echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 4
echo ==========================================================
echo.
echo 1. Negro
echo 10. Marron 
echo 100. Rojo
echo 1000. Naranja
echo 10000. Amarillo
echo 100000. Verde
echo 1000000. Azul
echo 10000000. Morado
echo.
echo.
echo.
set /p multiplicador=Ingrese el valor del multiplicador: 


echo.
echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 5
echo ==========================================================
echo.
echo 1. Marron 
echo 2. Rojo
echo 5. Oro
echo 10. Plata
echo.
set /p tolerancia=Ingrese el valor de la tolerancia: 



echo.
echo ==========================================================
echo            Ingrese el numero correspondiente al color de la banda 6 en ppm/C.
echo ==========================================================
echo.
echo 250. Negro 
echo 100. Marron 
echo 50. Rojo
echo 15. Naranja
echo 25. Amarillo
echo 20. Verde
echo 10. Azul
echo 5. Morado
echo 1. Gris
echo.
set /p tcr=Ingrese el coeficiente de temperatura: 

set /a resistencia=%banda1%%banda2%%banda3%*%multiplicador%
set /a toleranciaInferior=%resistencia%-(%resistencia%*%tolerancia%/100)
set /a toleranciaSuperior=%resistencia%+(%resistencia%*%tolerancia%/100)

echo.
echo La resistencia es de %resistencia% ohms.
echo La tolerancia es de +/- %tolerancia%%.
echo El rango de valores es de %toleranciaInferior% ohms a %toleranciaSuperior% ohms.
echo El coeficiente de temperatura es de %tcr% ppm/C.
pause
goto inicio

:fin
cls
echo.
echo Gracias por usar la calculadora de resistencias.
pause
exit