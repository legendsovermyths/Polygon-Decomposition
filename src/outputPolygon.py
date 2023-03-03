from polygenerator import (
    random_polygon,
    random_star_shaped_polygon,
    random_convex_polygon,
)
# these two are only for demonstration
import matplotlib.pyplot as plt
polygons = []
polygon = []

plt.figure()


def plot_polygon(polygon, out_file_name, label):
    plt.gca().set_aspect("equal")
    for i, (x, y) in enumerate(polygon):
        l = ""
        if (label == 0):
            l = str((len(polygon)-i) % len(polygon))
        plt.text(x, y, l, horizontalalignment="center",
                 verticalalignment="center")

    # just so that it is plotted as closed polygon
    polygon.append(polygon[0])

    xs, ys = zip(*polygon)
    plt.plot(xs, ys, "r-", linewidth=0.4)

    plt.savefig(out_file_name, dpi=300)


with open('output.txt') as f:
    while True:
        line = f.readline()
        if not line:
            break
        if (line == "$\n"):
            polygons.append(polygon)
            polygon = []
        else:
            point = line.split(" ")
            x, y = point[0], point[1]
            x, y = float(x), float(y)
            polygon.append((x, y))
for i, polygon in enumerate(polygons):
    plot_polygon(polygon, "polygon.png", i)
plt.close()
