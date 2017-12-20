Basic drawing of a TSP using OpenGL
===================

The Traveling Salesman Problem is a famous problem in Computer Science where given `k` cities to travel, a "salesman" starting out from his home (or place of business), making his appointed rounds to show off the goods he is selling, and then returning to his starting point. To do that, salesman wants to visit all cities once, and the path to travel must be shortest.

In this code, cities are represents using points, and the path using lines between cities. An initial setup is created in sequential order, *i.e. 1, 2, 3, ..., n*. After that, the euclidean distance of points (x,y) from `1` to `n` are computed. Next, a 10000 iterations are performed in order to found a different order of cities to travel. This is made using **simples swaps between 2 cities**, and checking its distance: *if the new distances is less than previous one, then is replaced, otherwise continue with the next iteration*. It means, a random approach :-)

Pressing the key `s`, two cities are selected (randomly) and are swapped. If reached distance is less than current one, then is replaced otherwise is reverted. A distance is the distance to travel for the salesman (from a starting city to the last one). If the key `a` is pressing, the same process is performed but for all cities. This can be applied several times.

The last time, this code was tested on Visual Studio 2017.

###### Do you want to contribute? Great!