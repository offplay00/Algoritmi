package Dijkstra;
import Graph.Arch;
import java.util.Comparator;

public class NameCompare implements Comparator<Arch<String,Float>> {
    @Override
    public int compare(Arch<String,Float> a, Arch<String,Float> b) {
        return a.getEnd().compareTo(b.getEnd());
    }
}

