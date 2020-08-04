// constants used in the solution
class HighResolutionConstants {
public:
  HighResolutionConstants(int nx, int ny, int nt) :
    nx(nx),
    ny(ny),
    nt(nt),
    x0((nx - 1) / 2),
    y0((ny - 1) / 2),
    k(0.04),
    dx(2.0 / (std::max(nx, ny) - 1)),
    dy(2.0 / (std::max(nx, ny) - 1)),
    dt(0.5 * (dx * dx + dy * dy) / (8 * k)),
    tfinal(nt ? nt * dt : 1.0),
    pi(3.14159265358979323846)
  {}

  int nx;        // grid points in x
  int ny;        // grid points in y
  int nt;        // number of time steps (0 for default)
  int x0;        // x location of heat source
  int y0;        // y location of heat source
  long double k;      // diffusion constant
  long double dx;     // grid spacing in x
  long double dy;     // grid spacing in y
  long double dt;     // time step
  long double tfinal; // minimum time to run solution to
  long double pi;     // 3.141...
};


void time_step_indexed(long double* u, const HighResolutionConstants& c) {

  long double* du = (long double *) malloc(c.nx * c.ny * sizeof(long double));

  for (int y = 1; y < c.ny - 1; y++) {
    for (int x = 1; x < c.nx - 1; x++) {
      long double uxx = (u[x - 1 + y * c.nx] - 2 * u[x + y * c.nx] + u[x + 1 + y * c.nx]) / (c.dx * c.dx);
      long double uyy = (u[x + (y - 1) * c.nx] - 2 * u[x + y * c.nx] + u[x + (y + 1) *c.nx]) / (c.dy * c.dy);
      du[x + y * c.nx] = c.dt * c.k * (uxx + uyy);
    }
  }
  // take forward Euler step
  for (int i = 0; i < c.nx * c.ny; i++)
    u[i] += du[i];
}

void HighResolution_Solver(long double* u, const HighResolutionConstants& c) {

  u[c.x0+ c.y0 * c.ny] = 1;
  double t;

  for (t = 0; t < c.tfinal; t += c.dt) {
    time_step_indexed(u, c);
  }
}