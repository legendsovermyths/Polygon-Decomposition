from polygenerator import random_polygon
# these two are only for demonstration
import matplotlib.pyplot as plt


def plot_polygon(polygon, out_file_name):
    plt.figure()
    plt.gca().set_aspect("equal")

    for i, (x, y) in enumerate(polygon):
        plt.text(x, y, str(i), horizontalalignment="center",
                 verticalalignment="center")

    # just so that it is plotted as closed polygon
    polygon.append(polygon[0])

    xs, ys = zip(*polygon)
    plt.plot(xs, ys, "r-", linewidth=0.4)

    plt.savefig(out_file_name, dpi=300)
    plt.close()


polygon = random_polygon(num_points=20)
polygon.reverse()
f = open("polygon.txt", "w")
for (x, y) in polygon:
    x *= 100
    y *= 100
    f.write(str(x) + " " + str(y)+"\n")

f.close()
print(polygon)
# [(0.752691110661913, 0.948158571633034), (0.7790276993942304, 0.05437135270534656), ..., (0.633385213909564, 0.7365967958574935)]

plot_polygon(polygon, "random_polygon.png")
