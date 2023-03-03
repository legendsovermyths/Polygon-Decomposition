from polygenerator import (
    random_polygon,
    random_star_shaped_polygon,
    random_convex_polygon,
)
import shutil
import sys
# this is only for demonstration
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


num_points = 10
polygon_ = random_polygon(num_points=10)
polygon_.reverse()
polygon = []
for (x, y) in polygon_:
    x *= 100
    y *= 100
    polygon.append((x, y))
i = 0
f = open("input.txt", "w")
f.write(str(num_points)+"\n")
for (x, y) in polygon:
    f.write(str(x) + " " + str(y)+"\n")
    i += 1

f.close()
# args = len(sys.argv)
# if args > 1:
#     shutil.copy("input.txt", "./Test/test"+str(sys.argv[1])+".txt")
# [(0.752691110661913, 0.948158571633034), (0.7790276993942304, 0.05437135270534656), ..., (0.633385213909564, 0.7365967958574935)]

plot_polygon(polygon, "random_polygon.png")
