# Shell
## Integrantes
- Renzo Andree Espíritu Cueva
- Sebastian Aaron Guevara Dominguez
## Índice
- [Shell](#Shell)
	- [Integrantes](#Integrantes)
	- [Índice](#Índice)
	- [Descripción](#Descripción)
 	- [Características](#Características)
  	- [Lexer & Parser](#Lexer&Parser)
	- [Requisitos](#Requisitos)
 	- [Uso](#Uso)
## Descripción
Un shell es una interfaz de línea de comandos que sirve de intermediario entre el usuario y el sistema operativo, permitiendo a los usuarios interactuar con el sistema mediante la ejecución de comandos. Proporciona una forma de lanzar programas, gestionar archivos y realizar diversas tareas interpretando la entrada del usuario. Los shells pueden ofrecer capacidades de scripting, personalización mediante archivos de configuración y acceso a una amplia gama de utilidades del sistema, lo que los convierte en un componente fundamental de los sistemas operativos tanto para usuarios principiantes como avanzados.
## Características
Ejecute el programa principal y podrá acceder a las funcionalidades del shell. Por ejemplo, puedes moverte entre carpetas, listar documentos, crear carpetas, ficheros, etc. Además, introduciendo el comando <block> puedes ejecutar bucles, funciones, estructuras condicionales, etc. Por último, puedes definir las variables con las que vas a trabajar.
## Lexer&Parser
Para el desarrollo del analizador léxico y sintactico empleamos la herramienta de ANTLR4.

![image](https://github.com/Raichi1/Shell/assets/114627641/8b310c01-179a-41cd-9fbd-a8b2401e8d82)

![image](https://github.com/Raichi1/Shell/assets/114627641/02fed3a3-3f09-49da-9429-9d33c46e5857)

![image](https://github.com/Raichi1/Shell/assets/114627641/f10fbc2b-3417-4894-b157-3fdf4bb2ba7d)

![image](https://github.com/Raichi1/Shell/assets/114627641/06c83639-bd98-4eac-bf6f-edd9d9842f26)

## Visitors
Para hacer funcionales nuestras reglas gramaticales a partir de la construcción del AST generado por ANTLR4, empleamos el lenguaje de C++ para realizar dichas funciones que nos permiten ofrecer un sistema completo.

![image](https://github.com/Raichi1/Shell/assets/114627641/5267f980-3250-465a-a6b8-bb5a15f71430)

![image](https://github.com/Raichi1/Shell/assets/114627641/25f25229-cf9a-46a7-99a5-525bbef5101a)

## Requisitos
Para ejecutar el programa necesitas tener cmake, llvm 17, cplusplus y antlr4.
## Uso
En primer lugar, debe ir a la carpeta que contiene el archivo .g4. A continuación, ejecute el archivo antlr4 (.g4) con el siguiente comando:

	antlr4 -no-listener -visitor -o libs -Dlanguage=Cpp *.g4

En segundo lugar, en el directorio principal debe ejecutar el siguiente comando para tener la carpeta cmake (build):

	cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=1
 
Por último, para obtener el archivo de programa es necesario ejecutar
	cmake --build build -j8
 Luego,
 
 	build/prog
  
 y ejecuta.

  
