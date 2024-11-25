#include "rtweekend.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

int main() {
  //set up a sphere into world
  hittable_list world;
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  //create camera
  camera cam;

  //image aspects ratio
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1000;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  //render the scene
  cam.render(world);

  return 0;
}