#include "math/intersect/IntersectUtils.h"

namespace IntersectUtils {

    bool intersect(const Vec3 & o, const Vec3 & d, const float tmax, const Vec3 & a, const Vec3 & b, const Vec3 & c,
                   Vec3 & intersection, Vec3 & normale_intersection, float & t) {
        // On commence par calculer la normale du triangle, c'est-à-dire son orientation, ab x ac
        Vec3 n = (a - b).cross(a - c);

        // Intersection du plan (a, n) avec le rayon (o, d)
        t = n.dot(a - o) / n.dot(d);
        if (t < 0 || t > tmax)
            return false; // L'intersection n'est pas valide, soit derrière la caméra soit trop loin

        // Point d'intersection avec le plan
        intersection = o + t * d;
        // Vérifier si l'intersection contient des NaN
        if (std::isnan(intersection.x) || std::isnan(intersection.y) || std::isnan(intersection.z)) {
            return false; // L'intersection n'est pas valide
        }

        // Tester le triangle abp / orientation des arêtes ab et ap
        Vec3 abp = (a - b).cross(a - intersection);
        if (n.dot(abp) < 0)
            return false; // p est à l'extérieur de l'arête ab

        // Tester le triangle bcp / orientation des arêtes bc et bp
        Vec3 bcp = (b - c).cross(b - intersection);
        if (n.dot(bcp) < 0)
            return false; // p est à l'extérieur de l'arête bc

        // Tester le triangle cap / orientation des arêtes ca et cp
        Vec3 cap = (c - a).cross(c - intersection);
        if (n.dot(cap) < 0)
            return false; // p est à l'extérieur de l'arête ca

        normale_intersection = normalize(n);

        // std::cout << "Le point d'intersection avec le rayon:" << intersection << std::endl;
        // std::cout << "La normale à ce point:" << normale_intersection << std::endl;

        // Le point est du bon côté des 3 arêtes, il est donc à l'intérieur du triangle !
        return true;
    }

    bool intersectEntity(const Ray & ray, const Entity & entity, IntersectionInfo & outInfo, float tmax) {
        const std::shared_ptr<Mesh> mesh = entity.getMesh();
        if (!mesh)
            return false;

        const std::vector<Vertex> & vertices = mesh->getVertices();
        const std::vector<unsigned int> & indices = mesh->getIndices();
        Mat4 transform = entity.getTransform();

        bool hit = false;

        for (size_t i = 0; i < indices.size(); i += 3) {
            Vec3 a = transform * vertices[indices[i]].m_position;
            Vec3 b = transform * vertices[indices[i + 1]].m_position;
            Vec3 c = transform * vertices[indices[i + 2]].m_position;

            Vec3 intersection;
            Vec3 normal;
            float t;

            if (intersect(ray.origin, ray.direction, tmax, a, b, c, intersection, normal, t)) {
                if (t < outInfo.t) {
                    outInfo.hit = true;
                    outInfo.t = t;
                    outInfo.position = intersection;
                    outInfo.normal = normal;
                    outInfo.entity = std::const_pointer_cast<Entity>(std::static_pointer_cast<const Entity>(entity.shared_from_this())); // nécessite que Entity hérite de `std::enable_shared_from_this<Entity>`
                    hit = true;
                }
            }
        }

        return hit;
    }

}