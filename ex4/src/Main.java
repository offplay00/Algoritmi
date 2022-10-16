import java.util.*;
import java.io.*;
import java.lang.*;
import Dijkstra.*;
import Graph.*;

public class Main {

    public static void main(String[] args) throws Exception {
        String path = "C:\\Users\\simon\\Desktop\\laboratorio-algoritmi-2021-2022\\ex4\\src\\italian_dist_graph.csv";
        Graph<String,Double> graph = csvReader(path, false);
        String start = (args[0]);
        Map<String,Double> result;
        if (graph.hasVertex(start))
            result = new Dijkstra<String,Double>().dijkstra(graph,start,new WeightCompareDouble(),0.0,Double.POSITIVE_INFINITY);
        else
            throw new Exception("Starting point doesn't exist");
        System.out.println("la distanza minore tra:"+start+" e:"+args[1]+" e' di:"+result.get(args[1])/1000 + " km");
    }

    private static Graph<String,Double> csvReader(String pathname,boolean digraph) throws Exception{
        Graph<String,Double> tmp = new Graph<String,Double>(digraph);
        String Nodes = "";
        Scanner sc = new Scanner(new File(pathname));
        sc.useDelimiter("[,\r\n]+");
        while(sc.hasNext()){
            Nodes += sc.next();
            if(!tmp.hasVertex(Nodes))
                tmp.addVertex(Nodes);
            tmp.addArch(Nodes,sc.next(),Double.parseDouble(sc.next()));
            Nodes = "";
        }
        sc.close();
        return tmp;
    }
}
