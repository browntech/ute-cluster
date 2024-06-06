import numpy as np
import matplotlib.pyplot as plt

# Input data
x_data = np.array([5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160])
y_data = np.array([120000, 60000, 41000, 30250, 24400, 20600, 17800, 15750, 14250, 13050, 11900, 11000, 10150, 9450, 8775, 8175, 7675, 7250, 6875, 6500, 6200, 5945, 5700, 5460, 5240, 5035, 4840, 4670, 4510, 4360, 4220, 4090])

# Fit a polynomial curve of degree 3 (you can adjust the degree as needed)
coefficients = np.polyfit(x_data, y_data, 28)
polynomial = np.poly1d(coefficients)

# Generate y values for the curve
x_curve = np.linspace(min(x_data), max(x_data), 100)
y_curve = polynomial(x_curve)

# Plot the original data points and the curve
plt.scatter(x_data, y_data, label='Data Points')
plt.plot(x_curve, y_curve, color='red', label='Curve Fit')
needed_x_points = [k for k in range(1,160)]
modelPredictions = np.polyval(coefficients, needed_x_points)

scat = plt.scatter(needed_x_points,modelPredictions)
y = 1000000
for x in scat.get_offsets():
    if x[1] > y:
        print("{}, // {} - error".format(round(x[1]),round(x[0])))
    else:
        print("{}, // {}".format(round(x[1]),round(x[0])))
    y = x[1]
# plt.show()
# plt.xlabel('X Axis')
# plt.ylabel('Y Axis')
# plt.title('Curve Fitting')
# plt.legend()
# plt.grid(True)
# plt.show()
