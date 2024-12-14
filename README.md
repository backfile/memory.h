# Clase Memory 

## **Constructor**
Memory(char* nombre);
*  char* nombre ➜ Nombre del proceso 

## **Escribir en la memoria**
template typename T  
void Write(uintptr_t address, T& data);
* uintptr_t address ➜ Dirección en donde se desea escribir
* T& data ➜ Valor que deseamos escribir

## **Leer en la memoria**
template typename T  
void Read(uintptr_t address, T& data);
* uintptr_t address ➜ Dirección en donde se desea leer
* T& data ➜ Variable en donde queremos guardar el valor leido
  
## **Obtener base address de un módulo del proceso**
uintptr_t GetModuleAddress(char* nombre);
* char* nombre ➜ Nombre del modulo buscado

## **Obtener ID del proceso**
uintptr_t GetProcessID();
