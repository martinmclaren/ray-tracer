//main.cpp

#include <fstream>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "light.h"
#include "material.h"
#include "colour.h"
#include "sphere.h"

int numRays = 0;

/*
 * The main driver class for the raytracing program.
 */
bool sceneIntersection(const Ray &ray,
                       Vector &intersection,
                       Vector &normal,
                       const std::vector<Sphere> &spheres,
                       Material &material) {

    //Set initial intersect distance to be far
    float objDistance = 5.0e+20;
    float sceneDistance = 5.0e+20;

    //Loop through each object in scene, determine intersections
    for (int i=0; i<spheres.size(); i++) {
        float sphereDistance = 0;
        if (spheres[i].sphereIntersection(ray, sphereDistance)) {
            //Intersect distance set to sphere's position
            objDistance = sphereDistance;
            intersection = ray.getOrigin() + ray.getDirection()*sphereDistance;
            normal = (intersection - spheres[i].getCenter()).normalize();
            //If intersection occurs, update material at point
            material = spheres[i].getMaterial();
        }
    }

    //Define plane primitive (static)
    if (std::abs(ray.getDirection().getY()) > 0.0)  {
        //Plane at y=-4
        float t = -(ray.getOrigin().getY() + 4)/ray.getDirection().getY();
        Vector vec = ray.getOrigin() + ray.getDirection()*t;

        //Check if point intersects plane and there's no object in the way
        if ( 0 < t && t < objDistance) {
            sceneDistance = 1;  // t
            intersection = vec;
            normal = Vector(0,1,0);
            //Create checkerboard pattern
            //Vector v = Vector(0.2, 0.2, 0.2);
            Vector v = (int(.9*intersection.getX()+1000)
                     + int(.9*intersection.getZ())) & 1
                     ? Vector(.4, .4, .4) : Vector(.0, .0, .0);
            //Set colour appropriately
            material.colour.set(v.getX(), v.getY(), v.getZ());
            //material.reflectivity = 0.3; //make surface reflective
        }
    }
    return std::min(objDistance, sceneDistance)<1000;
}

Colour rayCast(Ray &ray,
               const std::vector<Sphere> &spheres,
               const std::vector<Light> &lights,
               Colour background) {
    numRays++;
    //Define temporary vector, material for shadow rays
    Vector point, normal, tempV;
    Material material, tempM;
    //Diffuse and specular components of light
    float ld = 0;
    float ls = 0;

    //If no intersection with scene, assign background colour
    if (!sceneIntersection(ray, point, normal, spheres, material)) {
        return background;
    }

    //Determine reflections, and cast new rays to get colours
    Vector reflectedRayDirection = Vector::reflect(ray.getDirection(), normal);
    Ray reflectedRay = Ray(point, reflectedRayDirection);
    Colour reflectedColour = rayCast(reflectedRay, spheres, lights, background);

    //Compute shadows
    for (int i=0; i<lights.size(); i++) {
        //Determine normalized position of light
        Vector lightD = (lights[i].position - point).normalize();
        Vector shadowOrigin = point + normal*0.0001;
        //Get shadow ray
        Ray shadowRay = Ray(shadowOrigin, lightD);

        //Check for intersections with scene
        if (sceneIntersection(shadowRay, tempV, tempV, spheres, tempM)) {
            continue;
        }

        //Components for illumination calculation
        float d = (lightD.dot(normal) > 0) ? lightD.dot(normal) : 0;
        float r = Vector::reflect(lightD, normal).dot(ray.getDirection());
        //Clamp value to zero if negative
        r = (r > 0) ? r : 0;
        //Update diffuse/specular components
        ld += lights[i].brightness * d;
        ls += powf(r, material.specularity) * lights[i].brightness;
    }

    //Calculate final colour using Phong formula
    return material.colour * (ld * material.saturation)
           + Vector(1.0, 1.0, 1.0) * (ls * material.shine)
           + reflectedColour * material.reflectivity;
}

void renderImage(std::vector<Sphere> &spheres,
                 std::vector<Light> &lights,
                 Colour background,
                 int aa) {

    int width = 2000;  //2000 3000
    int height = 1000; //1500 2250
    int aadepth = aa;

    //Output file
    std::ofstream output;
    output.open("./image.ppm");
    output << "P6\n" << width << ' ' << height << "\n255\n";

    //Rendering loop
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            Colour pixelColour = Colour(0,0,0);
            //Anti-alias loop
            for (int k=0; k<aadepth; k++) {
                //Generate random value
                float rand = (aadepth > 1) ? (float) std::rand()/RAND_MAX : 0;
                //Create vector through pixel, padded w/ random value
                Vector direction = Vector((j+rand)-width/2.0,
                                         -(i+rand)+height/2.0,
                                         -height/1.3).normalize();
                //Camera position
                Vector origin = Vector(0,1,0);
                Ray ray = Ray(origin, direction);
                pixelColour += rayCast(ray, spheres, lights, background);
            }

            //Find average colour
            pixelColour = pixelColour*(1.0/(float) aadepth);
            //Ensure colour components are in [0,255]
            pixelColour.bound();
            output << (char)pixelColour.getR()
                   << (char)pixelColour.getG()
                   << (char)pixelColour.getB();
        }
    }
}

int main() {
    //Vectors to store scene objects
    std::vector<Sphere> spheres;
    std::vector<Light> lights;

    //Materials
    Material black(Colour(0.15, 0.16, 0.16), 0.9, 0.0, 0.0, 200.0);
    Material blue1(Colour(0.0, 0.0, 0.1), 0.9,  0.9, 0.9, 1000.0);
    Material blue(Colour(0.1, 0.1, 0.5), 0.9, 0.9, 0.9, 1000.0);

    spheres.push_back(Sphere(4, Vector(0, 0, -18), blue));
    //spheres.push_back(Sphere(4, Vector(0, 0, -18), purple));
    spheres.push_back(Sphere(0.5, Vector(0, -3.5, -10), black));
    lights.push_back(Light(Vector(-30, 20,  20), 4.5));

    int aadepth = 200;
    std::cout << "Scene: aadepth = " << aadepth << ", background = tan" << "\nRendering..." << std::endl;

    //Parameters: spheres, lights, backgroundColour, aadepth
    renderImage(spheres, lights, Colour(0.0, 0.0, 0.0), aadepth);

    std::cout << "Number of rays: " << numRays << std::endl;

    return 0;
}

