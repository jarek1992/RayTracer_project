#include "color.hpp"
#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"
#include <iostream>
#include <limits>

class camera {
public:
  double aspect_ratio = 1.0;  //ratio of image width over height
  int image_width = 100;      //rendered image width in pixel count
  int samples_per_pixel = 10; //count of random smaples for each pixel
  int max_depth = 50;         //max recursion depth

  // render
  void render(const hittable &world) {
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
      std::clog << "\rScanlines remaining: " << (image_height - j) << ' '
                << std::flush;
      for (int i = 0; i < image_width; i++) {
        color pixel_color(0, 0, 0);
        for (int sample = 0; sample < samples_per_pixel; sample++) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, world, max_depth);
        }
        write_color(std::cout, pixel_samples_scale * pixel_color);
      }
    }

    std::clog << "\rDone.                 \n";
  }

private:
  int image_height;           //rendered image height
  double pixel_samples_scale; //color scale factor for a sum of pixel samples
  point3 center;              //camera center
  point3 pixel00_loc;         //location of pixel 0, 0
  vec3 pixel_delta_u;         //offset to pixel to the right
  vec3 pixel_delta_v;         //offset to pixel below

  constexpr static double t_min = 0.001; //min distance (avoid selfcovering)
  constexpr static double t_max = std::numeric_limits<double>::infinity(); //max distance

  void initialize() {
     //calculate the image height , and ensure that it's at least 1
    image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = point3(0, 0, 0);

    //determine viewport dimensions
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width) / image_height);

    //calculate the vectors across the horizontal and down the vertical viewport edges
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    //calculate the horizontal and vertical delta vectors from pixel to pixel
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    //calculate the location of the upper left pixel
    auto viewport_upper_left = center 
                            - vec3(0, 0, focal_length) 
                            - viewport_u / 2 - viewport_v / 2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  // construct a camera ray originating from the origin and directed at randomly sampled
  //point around the pixel location i, j
  ray get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc 
                      + ((i + offset.x()) * pixel_delta_u) 
                      + ((j + offset.y()) * pixel_delta_v);

    auto ray_origin = center;
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
  }

  vec3 sample_square() const {
    //returns the vector to a random point in the [-.5, -.5]-[+.5,+.5] unit square
    return vec3(random_double() - 0.5, random_double() - 0.5, 0);
  }

  //intersection radius with sphere
  color ray_color(const ray &r, const hittable &world, int depth) const {
    if (depth <= 0) {
      return color(0, 0, 0); //black color, when reached max depth
    }

    hit_record rec;

    if (world.hit(r, interval(t_min, t_max), rec)) {
      vec3 direction = random_on_hemisphere(rec.normal);
      return 0.5 * ray_color(ray(rec.p, direction), world, depth - 1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    //background gradient
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0); 
  }
};