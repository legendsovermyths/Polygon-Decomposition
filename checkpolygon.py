import math
import csv
import sys


def get_angle(a, b, c):
    angle = math.degrees(math.atan2(
        c[1]-b[1], c[0]-b[0]) - math.atan2(a[1]-b[1], a[0]-b[0]))
    return angle + 360 if angle < 0 else angle


def solve(points):
    n = len(points)
    for i in range(len(points)):
        p1 = points[i-2]
        p2 = points[i-1]
        p3 = points[i]
        if get_angle(p1, p2, p3) > 180:
            return False
    return True


polygons = []
polygon = []
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
flag = 1
t = ""

for i, polygon in enumerate(polygons):
    if (i > 0):
        if solve(polygon) == False:
            flag = 0
if flag == 1:
    print("Accepted")
else:
    print("Rejected")

with open('time.txt') as f:
    t = f.readline()
args = len(sys.argv)
filename = "Result.csv"
verdict = ""
if flag == 1:
    verdict = "Accepted"
else:
    verdict = "Rejected"
# if args > 1:
#     with open(filename, 'a') as csvfile:
#         csvwriter = csv.writer(csvfile)
#         csvwriter.writerow(["Polygon #"+str(sys.argv[1]), t, verdict])
#         csvfile.close()
