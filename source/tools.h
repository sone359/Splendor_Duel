#ifndef TOOLS_H
#define TOOLS_H

#include <stdexcept>

enum Jeton
{
    Nul,
    Bleu,
    Vert,
    Blanc,
    Rouge,
    Noir,
    Perle,
    Or,
};

class SplendorException : public std::exception
{
public:
    // Constructeur prenant un message d'erreur en paramètre
    explicit SplendorException(const std::string& msg) : message(msg) {}

    // Redéfinition de la fonction what() pour obtenir le message d'erreur. message est converti en chaîne c pour conserver le type de retour de what() tel qu'hérité de exception
    const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};

#endif
