package Dijkstra;

import Graph.*;
import MinHeap.*;
import java.util.*;

public class Dijkstra<T,G extends Number> {
    public Map<T, G> dijkstra(Graph<T, G> graph, T start, Comparator<Arch<T, G>> comparator, G startValue,G inf) throws Exception {
        Map<T,G> distances = new HashMap<>();   //Distances from nodes
        MinHeap<Arch<T,G>> pq = new MinHeap<>(comparator); //Priority Queue
        ArrayList<T> keys = graph.getVertexes();    //All the nodes names from the graph
        Arch<T, G> u;
        for (T i : keys) {  //O(n)
            if (i.equals(start)) {
                distances.put(start, startValue);
                pq.insert(new Arch<>(start, startValue));
            } else {
                distances.put(i, inf);
                pq.insert(new Arch<>(i, inf));
            }
        }
        while (!pq.isEmpty()) { //O(n)
            u = pq.extractMin();    //O(log n)
            for(Arch<T,G> i : graph.getAdjacentVertex(u.getEnd())) {    //O(m) for dense graph O(1)
                //if v is present in min heap and dist[v] > dist[u] + dist(u+v)
                if(pq.contains(new Arch<>(i.getEnd(),distances.get(i.getEnd()))) &&
                        Arch.compare(distances.get(i.getEnd()),Arch.add(u.getWeight(),graph.getEdgeLabel(u.getEnd(),i.getEnd()))) > 0) {
                    //decrease the actual value in min heap for newer value O(log n)
                    pq.decreaseKey(new Arch<>(i.getEnd(),distances.get(i.getEnd())),
                            new Arch<>(i.getEnd(),Arch.add(u.getWeight(),graph.getEdgeLabel(u.getEnd(),i.getEnd()))));
                    //update the value of the arc O(1)
                    distances.replace(i.getEnd(),Arch.add(u.getWeight(),graph.getEdgeLabel(u.getEnd(),i.getEnd())));
                }
            }
        }
        return distances;
    }
}

/*total time complexity for dense graph:
  build min heap and hashmap: O(n)
  extract min: O(n log(n)) (counting the while condition)
  decrease key: O(n log(n)) (counting the while condition)
  replace the value in hashmap: O(n) (counting the while condition)
  total: O(n log(n))
 */


