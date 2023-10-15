# RayTracing
Projekt wykorzystujący RayTracing do renderowania scen wykonany w ramach pracy licencjackiej

# Jak używać
Projekt do działania wymaga dwóch bibliotek: glm, ASSIMP.
Zalecane jest skorzystanie z vcpkg, jakoże plik cMake połączy je z projektem w momencie budowania.

Zbudować poprzez cMake do katalogu build.

Projekt był testowany na plikach .Obj z ustawionymi opcjami triangulacji oraz "Pbr extension" wyeksportowanych z Blender 3.5
Aby był poprawnie odczytany może być konieczne ręczne usunięcie parametrów "aniso" oraz "anisor" z pliku .mtl

W pliku pch.h są edytowalne parametry rozdzielczości, ilości próbek, odbić, oraz wartość korekcji Gamma.

![image](https://github.com/MaciejWodnicki/RayTracing/assets/101054402/1ac8d11b-0a54-4c56-a948-dc6eae232792)
