#ifndef FACTORYMETHOD_H
 #define FACTORYMETHOD_H
 
 #include "IBestiole.h"
 
 class FactoryMethod {
 public:
     // Destructeur virtuel
     virtual ~FactoryMethod() = default;
 
     // Méthode pour créer une IBestiole
     virtual IBestiole* creerIBestiole() = 0;  
 };
 
 #endif // FACTORYMETHOD_H