package MinHeap;
import java.util.Comparator;

public class DoubleComparator implements Comparator<prova> {
    @Override
    public int compare(prova a,prova b) {
        return Double.compare(a.casa,b.casa);
    }
}
