/// L'idée d'un callback est de pouvoir imposer la signature d'une fonction à un événement,
/// Son nom n'importe pas mais la signature si
/// L'utilisation dans l'exemple ci-dessous paraît simpliste, mais très utile dans des cas ou on développe
/// des bibliothèques ou des frameworks, car on peut laisser le choix à l'utilisateur de l'implémentation de la fonction callbackée.
/// Voir exemple dans main.cpp avec la fonction key_callback qui est appelée à chaque fois qu'une touche du clavier est pressée.

/// Exemple quelconque ici:
#include <iostream>

// Type de fonction callback : prend un int, ne renvoie rien
using Callback = void(*)(int);

void doWork(int value, Callback cb) {
    std::cout << "Travail en cours avec la valeur " << value << std::endl;
    
    // Fin du travail, on appelle le callback avec un résultat
    cb(value * 2);
}

// Callback utilisateur
void onDone(int result) {
    std::cout << "Callback appelé avec le résultat : " << result << std::endl;
}

int main() {
    doWork(5, onDone);
    return 0;
}
