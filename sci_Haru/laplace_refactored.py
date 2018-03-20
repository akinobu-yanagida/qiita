import numpy as np
from scipy.sparse import csc_matrix
import matplotlib.pyplot as plt
from matplotlib import cm
import time

class CartesianGrid:
    """
        Simple class to generate a computational grid and apply boundary conditions
    """

    def __init__(self, nx=10, ny=10, xmin=0.0, xmax=1.0, ymin=0.0, ymax=0.0):
        self.nx, self.ny = nx, ny
        self.ntotal = nx*ny

        self.xmin, self.xmax = xmin, xmax
        self.ymin, self.ymax = ymin, ymax

        self.dx = (xmax - xmin)/(nx - 1)
        self.dy = (ymax - ymin)/(ny - 1)

        self.x = np.arange(xmin, xmax + 0.5*self.dx, self.dx)
        self.y = np.arange(ymin, ymax + 0.5*self.dy, self.dy)

    def create_field(self):
        return np.zeros((self.nx, self.ny), dtype=np.float)

    def create_meshgrid(self):
        return np.meshgrid(self.x, self.y, indexing='ij')

    def set_boundary_condition(self, u, side='top', boundary_condition_function=lambda x,y: 0.0):
        if side == 'top':
            u[:,-1] = boundary_condition_function(self.x, self.ymax)
        elif side == 'bottom':
            u[:,0] = boundary_condition_function(self.x, self.ymin)
        elif side == 'left':
            u[0,:] = boundary_condition_function(self.xmin, self.y)
        elif side == 'right':
            u[-1,:] = boundary_condition_function(self.xmax, self.y)
        else:
            print("side must be top, bottom, left, or right")

    def convert_to_1d_array(self, x):
        return x.reshape(self.ntotal, 1)

    def convert_to_2d_array(self, x):
        return x.reshape(self.nx, self.ny)

    def index(self, i, j):
        return i*self.nx + j

    def is_boundary(self, i, j):
        if i == 0 or i == self.nx - 1 or j == 0 or j == self.ny - 1:
            return True
        else:
            return False

def calc_jacobi_matrix(mesh):
    """
        Create sparse matrix for Jacobi method
    """

    row_index = []
    col_index = []
    value = []

    for i in range(mesh.nx):
        for j in range(mesh.ny):
            k = mesh.index(i, j)
            if mesh.is_boundary(i, j):
                row_index.append(k)
                col_index.append(k)
                value.append(1.0)
            else:
                row_index.append(k)
                col_index.append(mesh.index(i - 1, j))
                value.append(0.25)

                row_index.append(k)
                col_index.append(mesh.index(i + 1, j))
                value.append(0.25)

                row_index.append(k)
                col_index.append(mesh.index(i, j - 1))
                value.append(0.25)

                row_index.append(k)
                col_index.append(mesh.index(i, j + 1))
                value.append(0.25)

    s = (mesh.ntotal, mesh.ntotal)
    return csc_matrix((value, (row_index, col_index)), s)

class IterationControl:
    """
        Class to control iteration loop
    """

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

    mesh = CartesianGrid(100, 100, 0.0, 10.0, 0.0, 10.0)

    phi = mesh.create_field()

    # set boundary condition for y = 0
    mesh.set_boundary_condition(phi, side='bottom', boundary_condition_function=lambda x,y:5.0)
    phi = mesh.convert_to_1d_array(phi)

    A = calc_jacobi_matrix(mesh)

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
    x, y = mesh.create_meshgrid()

    fig, ax = plt.subplots()
    surf = ax.contourf(x, y, phi, cmap=cm.coolwarm)
    ax.set_xlabel('x')
    ax.set_ylabel('y')

    # add a color bar
    fig.colorbar(surf, shrink=0.5, aspect=5)

    fig.savefig("phi.png")

if __name__=='__main__':
    solve_laplace_eq()