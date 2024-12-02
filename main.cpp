#include "rtweekend.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "sphere.hpp"

int main() {
  //set up a sphere into world
  hittable_list world;

  //base material and plane
  auto material_ground = make_shared<metal>(color(0.5, 0.5, 0.5), 0.3);
  world.add(make_shared<sphere>(point3(0.0, -1000.0, 0.0), 1000.0, material_ground));

  //glass sphere into scene
  auto material_glass = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0.0, 1.0, 0.0), 1.0, material_glass));

  //bubble sphere into scene
  auto material_bubble = make_shared<dielectric>(1.0 / 1.5);
  world.add(make_shared<sphere>(point3(0.0, 1.0, 0.0), 0.9, material_bubble));

  //diffuse material sphere into scene
  auto material_diffuse = make_shared<lambertian>(color(0.5, 0.9, 0.1));
  world.add(make_shared<sphere>(point3(4.0, 1.0, 2.0), 1.0, material_diffuse));

  //metal material sphere into scene
  auto material_metal = make_shared<metal>(color(0.2, 0.2, 0.2), 0.2);
  world.add(make_shared<sphere>(point3(6.0, 1.0, -2.0), 1.0, material_metal));

  //randomize location of small spheres
  for (int a = -20; a < 20; a++) {
    for (int b = -20; b < 20; b++) { //create the grid a(-20, 20) / b(-20, 20)
      auto choose_material = random_double(); //randomize material for each sphere in range(0, 1)
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double()); //point3(x,(y = const),z)

      if ((center - point3(5.0, 1.0, 0.0)).length() > 0.9) { //condition to create sphere
        shared_ptr<material> sphere_material;

        if (choose_material < 0.8) {
          //diffuse material
          auto albedo = color::random() * color::random(); //random sphere color
          sphere_material = make_shared<lambertian>(albedo);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else if (choose_material < 0.95) {
          //metal material
          auto albedo = color::random(0.5, 1); //range (0.5, 1) allows to select amongst brighter range
          auto fuzz = random_double(0, 0.5); //higher value more diffused reflections
          sphere_material = make_shared<metal>(albedo, fuzz);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          //glass material
          sphere_material = make_shared<dielectric>(1.5);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  //create camera
  camera cam;

  //image aspects ratio
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1200;
  cam.samples_per_pixel = 500;
  cam.max_depth = 50;

  //camera settings
  cam.vfov = 30; //vertical field of the view
  cam.lookfrom = point3(10, 2, 0); //cords for camera source
  cam.lookat = point3(0, 0, 0); //cords for camera target
  cam.vup = vec3(0, 1, 0); //up vector set to Y

  //defocus blur settings
  cam.defocus_angle = 1.0; //higher values more blur on objects outside defocus point
  cam.focus_dist = 8; //higher values defocus point more far from camera

  //render the scene
  cam.render(world);

  return 0;
}