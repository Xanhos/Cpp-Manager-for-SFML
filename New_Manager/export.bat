copy /Y ..\lib\SFML_ENGINE.lib ..\DLL\lib\SFML_ENGINE.lib
copy /Y ..\lib\SFML_ENGINE-d.lib ..\DLL\lib\SFML_ENGINE-d.lib
Robocopy ..\include\SFML_ENGINE ..\DLL\SFML_ENGINE /E
Robocopy ..\DLL_ENGINE\Debug ..\DLL\Debug /E
Robocopy ..\DLL_ENGINE\Release ..\DLL\Release /E
pause