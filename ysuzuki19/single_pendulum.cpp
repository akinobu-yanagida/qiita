#include <cmath>
#include <fstream>
#include <vector>

inline constexpr auto deg2rad(double deg) { return deg / 180.0 * M_PI; }
inline constexpr auto rad2deg(double rad) { return rad / M_PI * 180.0; }

int main() {
  // In SI units
  constexpr auto delta_time                 = 0.01;
  constexpr auto start_time                 = 0.0;
  constexpr auto end_time                   = 100.0;
  constexpr auto initial_angle              = deg2rad(12.0);
  constexpr auto gravitational_acceleration = 9.80665;
  constexpr auto pendulum_length            = 10.0;
  constexpr auto pendulum_mass              = 2.0;
  constexpr auto drag_coeff                 = 0.02;

  const auto dt = delta_time;
  const auto x0 = initial_angle;
  const auto g  = gravitational_acceleration;
  const auto l  = pendulum_length;
  const auto m  = pendulum_mass;
  const auto k  = drag_coeff;

  const auto ndata = ceil((end_time - start_time) / dt);

  std::vector<double> time_series;
  std::vector<double> angle_series;
  time_series.reserve(ndata);
  angle_series.reserve(ndata);

  auto t = start_time;
  auto x = x0;
  auto v = 0.0;

  while (t < end_time) {
    // Equation of motion for a single pendulum with a drag force
    const auto a = -g / l * sin(x) - k / m * v;
    v += a * dt;
    x += v * dt;
    angle_series.push_back(x);
    time_series.push_back(t);
    t += dt;
  };

  std::ofstream fo("single_pendulum.txt");
  fo << "time [s],angle [deg]" << std::endl;
  for (size_t i = 0; i < time_series.size(); ++i)
    fo << time_series[i] << "," << rad2deg(angle_series[i]) << std::endl;
}
