package Graph;

import Exception.*;
import java.util.*;

public class Graph<T,G> {
    private final Map<T,List<Arch<T,G>>> map;   // Hashmap key = from vertex,value = Arch attached at from vertex
    private final boolean digraph;
    public Graph(boolean digraph) { //Empty graph constructor O(1)
        map = new HashMap<>();
        this.digraph = digraph;
    }
    public boolean isDigraph() { return this.digraph; } //check if it's direct O(1)
    public void addVertex(T newValue) throws GraphException{    //check if the vertex is already present in the hashmap, otherwise add it O(1)
        if (newValue == null)
            throw new GraphException("add vertex: Null vertex cannot be added in the Graph");

        if (hasVertex(newValue))
            throw new GraphException("add vertex: Vertex already exists in this Graph");

        map.put(newValue, new LinkedList<>()); //O(1)
    }
    public void addArch(T src, T dest, G w) throws GraphException { // This function adds the edge between source to destination node O(1)
        if (src == null || dest == null || w == null)
            throw new GraphException("you can't insert arches with null sources,destinations or weight");

        if (!map.containsKey(src))
            addVertex(src);

        if (!map.containsKey(dest))
            addVertex(dest);

        map.get(src).add(new Arch<>(dest, w));  //O(1)

        if (isDigraph()) { map.get(dest).add(new Arch<>(src, w)); } //O(1)
    }
    public boolean hasVertex(T s) throws GraphException {   //check if the key is present in the hashmap O(1)
        if (s == null) throw new GraphException("has vertex: vertex cannot be NULL");
        return map.containsKey(s); //O(1)
    }
    public boolean hasArch(T src, T dest) throws GraphException {    //check if the arch is present in the graph O(m) for dense graph: O(1)
        if (src == null || dest == null) throw new GraphException("has arch: source or destination cannot be NULL");
        List<Arch<T,G>> tmp = getAdjacentVertex(src);
        for(Arch<T,G> i : tmp)
            if(i.getEnd().equals(dest))
                return true;
        if(!isDigraph()) {
            List<Arch<T,G>> tmp2 = getAdjacentVertex(dest);
            for(Arch<T,G> i : tmp2)
                if(i.getEnd().equals(src))
                    return true;
        }
        return false;
    }
    public void removeVertex(T val) throws GraphException {  //used to remove Node O(m) for dense graph: O(1)
        if (val == null) throw new GraphException("remove vertex: a null vertex cannot be removed");
        if (map.containsKey(val)) {
            for (T k : map.keySet()) { //O(m)
                if (hasArch(k, val)) {
                    removeArch(val, k);
                }
            }
            map.remove(val);
        } else throw new GraphException("remove vertex: vertex not found. Can't remove this vertex: " + val);
    }
    public void removeArch(T src, T dest) throws GraphException {   //used to remove Edge from source to destination
        if (src == null || dest == null) throw new GraphException("remove arch: a null arch cannot be removed");
        if (!map.containsKey(src) || !map.containsKey(dest)) throw new GraphException("remove arch: cannot remove an arch with a undefined key");
        if (hasArch(src, dest))
            map.get(src).remove(new Arch<>(dest));  //O(1) //dest
        if (isDigraph())
            map.get(dest).remove(new Arch<>(src));  //O(1) //src
    }
    public int get_n_vertex() { return map.keySet().size(); }   //O(1)
    public int get_n_arch() {   //O(m) for dense graph: O(1)
        int count = 0;
        for (T v : map.keySet()) {
            count += map.get(v).size();
        }
        if (!digraph) { count = count / 2; }
        return count;
    }
    public ArrayList<T> getVertexes() { return  new ArrayList<>(map.keySet()); }    //O(1)
    public List<Arch<T,G>> getArch(){  //O(n)
        List<Arch<T, G>> list = new ArrayList<>();
        for (T k : map.keySet())
            list.addAll(map.get(k));
        return list;
    }
    public List<Arch<T,G>> getAdjacentVertex(T vertex) throws GraphException {  //O(1)
        if (vertex == null) throw new GraphException("get adjacent vertex: vertex null. Adjacent list cannot be printed");
        if (!hasVertex(vertex)) throw new GraphException("get adjacent vertex: vertex does not exist. Adjacent list cannot be printed");
        return map.get(vertex);
    }
    public G getEdgeLabel(T v1, T v2) throws GraphException {   //O(m) for dense graph: O(1) for indirect non dense graph: O(m^2)
        if (v1 == null || v2 == null) throw new GraphException("get edge label: Parameters cannot be null");
        if (hasArch(v1,v2)) {
            List<Arch<T,G>> tmp = map.get(v1);
            for(Arch<T,G> i : tmp) //O(m) O(1) for dense graph
                if(v2.equals(i.getEnd()))
                    return i.getWeight();
        }else if(hasArch(v2,v1) && !isDigraph()) {
            List<Arch<T,G>> tmp = map.get(v2);
            for(Arch<T,G> i : tmp) //O(m) O(1) for dense graph
                if(v1.equals(i.getEnd()))
                    return i.getWeight();
        }
        throw new GraphException("get edge label: arch (" + v1 + ", " + v2 + ") doesn't exist");
    }

    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();
        for (T v : map.keySet()) {
            builder.append("Vertex: " + v + "\n\tAdj_list:");
            for (int i = 0; i < map.get(v).size(); i++) {
                builder.append("\n\t\t\t" + map.get(v).get(i));
            }
            builder.append("\n");
        }
        return (builder.toString());
    }
}
