#include "IIntersectable.h"

#include <tuple>
#include <Eigen/Core>

class Sphere : public IIntersectable
{
public:
    Sphere(const Eigen::Vector3f& center, float radius);

    std::tuple<bool, float> Intersect(const Eigen::Vector3f& origin, const Eigen::Vector3f& direction) const;
    
private:
    float _radius;
    float _radius2;
    Eigen::Vector3f _center;
};