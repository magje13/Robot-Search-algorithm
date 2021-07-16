# Search-algorithm

The map (see images/Map.png) shows some rooms with red dots. The robot has to find all dots, but has no information about the position of red dots and can't look through walls. The robot must move around the map until every red dot has been visisted.

The approach is to use Brushfire and Voronoi to find nodes (See images/Voronoi.png and images/Nodes.png) that will later be used as input to an A* algorithm.
