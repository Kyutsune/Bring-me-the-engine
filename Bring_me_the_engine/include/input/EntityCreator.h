#pragma once

#include "Globals.h"

/**
 * @brief Classe responsable de la création d'entités de différents types.
 * 
 * Permet de créer des entités (cube, sphère, plan) positionnées dans l'espace 3D,
 * en gardant le compte du nombre d'entités créées par type.
 */
class EntityCreator {
public:
    /**
     * @brief Constructeur par défaut.
     */
    EntityCreator();

    /**
     * @brief Crée une entité du type spécifié à la position donnée.
     * 
     * @param type Type de l'entité à créer.
     * @param x Position X.
     * @param y Position Y.
     * @param z Position Z.
     * @return Un pointeur partagé vers l'entité créée.
     */
    std::shared_ptr<Entity> createEntity(TypeEntityCreated type, const double & x, const double & y, const double & z);

    /**
     * @brief Retourne le nom de l'entité correspondant au type donné.
     * 
     * @param type Type de l'entité.
     * @return Nom en chaîne de caractères.
     */
    std::string getNameOfEntityCreated(TypeEntityCreated type);

private:
    static unsigned int m_nb_cube_created;   ///< Nombre de cubes créés.
    static unsigned int m_nb_sphere_created; ///< Nombre de sphères créées.
    static unsigned int m_nb_plane_created;  ///< Nombre de plans créés.

    /**
     * @brief Crée un cube et le place à la position donnée.
     * 
     * @param x Position X.
     * @param y Position Y.
     * @param z Position Z.
     * @return Un pointeur partagé vers le cube créé.
     */
    std::shared_ptr<Entity> createCubeAndPlace(const double & x, const double & y, const double & z);

    /**
     * @brief Crée une sphère et la place à la position donnée.
     * 
     * @param x Position X.
     * @param y Position Y.
     * @param z Position Z.
     * @return Un pointeur partagé vers la sphère créée.
     */
    std::shared_ptr<Entity> createSphereAndPlace(const double & x, const double & y, const double & z);
};
