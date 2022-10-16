package Dijkstra;

import Graph.Arch;
import java.util.Comparator;

public class WeightCompareDouble implements Comparator<Arch<String,Double>> {
    @Override
    public int compare(Arch<String,Double> a, Arch<String,Double> b) {
        return Double.compare(a.getWeight(),b.getWeight());
    }
}
