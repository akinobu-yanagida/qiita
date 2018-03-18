import numpy as np
from scipy.sparse import csc_matrix
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import time

class SquareCartesianMesh:

    def __init__(self, length, n):
        self.length_x = length
        self.length_y = length
        self.nx = n
        self.ny = n
        self.ntotal = self.nx*self.ny

    def meshgrid(self):
        self.xgv = np.linspace(0.0, self.length_x, self.nx)
        self.ygv = np.linspace(0.0, self.length_y, self.ny)
        return np.meshgrid(self.xgv, self.ygv)

    def create_field(self):
        s = (self.ny, self.nx)
        return np.zeros(s)

    def convert_to_1d_array(self, x):
        return x.reshape(self.ntotal, 1)

    def convert_to_2d_array(self, x):
        return x.reshape(self.ny, self.nx)

def calc_jacobi_matrix(nx, ny):

    row_index = []
    col_index = []
    value = []

    def is_boundary(i, j):
        if i == 0 or i == ny - 1 or j == 0 or j == nx - 1:
            return True
        else:
            return False

    for i in range(ny):
        for j in range(nx):
            k = i*nx + j
            if is_boundary(i, j):
                row_index.append(k)
                col_index.append(k)
                value.append(1.0)
            else:
                row_index.append(k)
                col_index.append(k - nx)
                value.append(0.25)

                row_index.append(k)
                col_index.append(k - 1)
                value.append(0.25)

                row_index.append(k)
                col_index.append(k + 1)
                value.append(0.25)

                row_index.append(k)
                col_index.append(k + nx)
                value.append(0.25)

    ntotal = nx*ny
    s = (ntotal, ntotal)
    return csc_matrix((value, (row_index, col_index)), s)

class IterationControl:

    def __init__(self, max_iter, info_interval, tolerance):
        self.max_iter = max_iter
        self.info_interval = info_interval
        self.tolerance = tolerance
        self.eps = 1.0
        self.iter = 0

    def loop(self):
        self.iter += 1
        self.output_info()

        if self.eps < self.tolerance:
            return False
        elif self.iter > self.max_iter:
            print("max iteration reached")
            return False
        else:
            return True

    def calc_epsilon(self, dx):
        self.eps = np.max(abs(dx))

    def output_info(self):
        if self.iter % self.info_interval == 0:
            print("iter = %d, eps = %.3e" % (self.iter, self.eps))

def solve_laplace_eq():

    mesh = SquareCartesianMesh(10.0, 100)

    phi = mesh.create_field()

    # set boundary condition for y = 0
    # phi is always 0 for other boundaries
    phi[0,:] = 5.0
    phi = mesh.convert_to_1d_array(phi)

    A = calc_jacobi_matrix(mesh.nx, mesh.ny)

    iter_control = IterationControl(1500, 100, 1e-3)

    start_time = time.time()

    while iter_control.loop():
        # update field using Jacobi method
        phi_new = A.dot(phi)
        iter_control.calc_epsilon(phi_new - phi)
        phi, phi_new = phi_new, phi

    end_time = time.time()
    elapsed_time = end_time - start_time

    print("iter = %d, eps = %.3e, elapsed time = %.3f sec" \
            % (iter_control.iter, iter_control.eps, elapsed_time))

    # reshape for surface plotting
    phi = mesh.convert_to_2d_array(phi)
    # create mesh grid for surface plot
    x, y = mesh.meshgrid()

    fig = plt.figure()
    ax = fig.gca(projection='3d')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('$\phi$')

    # plot the surface
    surf = ax.plot_surface(x, y, phi, cmap=cm.coolwarm, linewidth=0)

    # add a color bar
    fig.colorbar(surf, shrink=0.5, aspect=5)

    plt.show()

if __name__=='__main__':
    solve_laplace_eq()
