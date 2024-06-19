import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Doc du lieu tu data.out
def read_data_from_file(filename):
    with open(filename, 'r') as file:
        lines = file.readlines()

    d, N = map(int, lines[0].strip().split())
    data = []
    labels = []

    for line in lines[1:N+1]:
        parts = list(map(float, line.strip().split()))
        data.append(parts[:-1])
        labels.append(parts[-1])

    W = list(map(float, lines[N+1].strip().split()))
    b = W[-1]
    W = W[:-1]

    return np.array(data), np.array(labels), np.array(W), b

def plot_svm_2d(data, labels, W, b):
    plt.figure(figsize=(10, 6))

    # Ve diem du lieu
    for i in range(len(labels)):
        if labels[i] == 1:
            plt.scatter(data[i, 0], data[i, 1], color='blue', marker='o')
        else:
            plt.scatter(data[i, 0], data[i, 1], color='red', marker='x')
    
    # ve do thi
    x_min, x_max = min(data[:, 0]) - 1, max(data[:, 0]) + 1
    y_min, y_max = min(data[:, 1]) - 1, max(data[:, 1]) + 1
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100))
    Z = W[0] * xx + W[1] * yy + b
    plt.contour(xx, yy, Z, levels=[0], colors='green')
    
    # Bat luoi do thi
    plt.grid(True)
    
    plt.xlabel('X1')
    plt.ylabel('X2')
    plt.title('ĐỒ THỊ BIỂU DIỄN CÁC ĐIỂM VÀ MẶT PHẲNG')
    plt.show()

def plot_svm_3d(data, labels, W, b):
    fig = plt.figure(figsize=(10, 6))
    ax = fig.add_subplot(111, projection='3d')

    # Ve diem du lieu
    for i in range(len(labels)):
        if labels[i] == 1:
            ax.scatter(data[i, 0], data[i, 1], data[i, 2], color='blue', marker='o')
        else:
            ax.scatter(data[i, 0], data[i, 1], data[i, 2], color='red', marker='x')

    # Ve do thi
    x_min, x_max = min(data[:, 0]) - 1, max(data[:, 0]) + 1
    y_min, y_max = min(data[:, 1]) - 1, max(data[:, 1]) + 1
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 100), np.linspace(y_min, y_max, 100))
    zz = (-W[0] * xx - W[1] * yy - b) / W[2]
    
    ax.plot_surface(xx, yy, zz, color='green', alpha=0.5)

    # Them luoi
    ax.grid(True)

    ax.set_xlabel('X1')
    ax.set_ylabel('X2')
    ax.set_zlabel('X3')
    ax.set_title('ĐỒ THỊ BIỂU DIỄN CÁC ĐIỂM VÀ MẶT PHẲNG')
    plt.show()

# Giong nhu main()
filename = 'data.out'
data, labels, W, b = read_data_from_file(filename)

if data.shape[1] == 2:
    plot_svm_2d(data, labels, W, b)
elif data.shape[1] == 3:
    plot_svm_3d(data, labels, W, b)
else:
    print("So chieu khong phu hop de ve do thi")