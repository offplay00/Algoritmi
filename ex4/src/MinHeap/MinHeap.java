package MinHeap;
import java.util.*;

public class MinHeap <T> {
    private final ArrayList<T> heap_array; //generic array
    private final Comparator<T> comp;
    private final Map<T,Integer> map;
    public MinHeap(Comparator<T> comp) {
        this.heap_array = new ArrayList<>();
        this.map = new HashMap<>();
        this.comp = comp;
    }
    private int parent(int pos) { return (pos % 2 == 1) ? pos/2 : (pos-1)/2; }
    private int right(int pos) { return pos * 2 + 2 ; }
    private int left(int pos) { return pos * 2 + 1; }
    public boolean isEmpty() { return heap_array.size() == 0; }
    public int getPosition(T elem) { return map.get(elem); }
    public Set<T> getKey() { return map.keySet(); }
    private void swap(int pos,int pos2) {
        map.replace(heap_array.get(pos),pos2);
        map.replace(heap_array.get(pos2),pos);
        Collections.swap(heap_array,pos,pos2);
    }
    public void insert(T item) {
        heap_array.add(item);
        map.put(item,heap_array.size()-1);
        int size = heap_array.size()-1;
        while(parent(size) != size && comp.compare(heap_array.get(size),heap_array.get(parent(size))) < 0) {
            swap(size,parent(size));
            size = parent(size);
        }
    }
    public T extractMin() throws Exception{
        if(heap_array.size() == 0) throw new Exception("Min heap is EMPTY!");
        else if(heap_array.size() == 1)
            return heap_array.remove(0);
        Collections.swap(heap_array,heap_array.size()-1,0);
        T item = heap_array.remove(heap_array.size()-1);
        map.replace(heap_array.get(0),0);
        minHeapify(0);
        return item;
    }

    public void decreaseKey(T item,T dcr) throws Exception{
        if(comp.compare(item,dcr)<0) throw new Exception("Previous item was smaller than this!");
        int size = getPosition(item);
        heap_array.set(size,dcr);
        map.replace(dcr,size);
        while(size > 0 && comp.compare(heap_array.get(parent(size)),heap_array.get(size)) > 0) {
            swap(size,parent(size));
            size = parent(size);
        }
    }

    private void minHeapify(int i) {
        int left = left(i);
        int right = right(i);
        int smallest;
        if (left <= heap_array.size() - 1 && comp.compare(heap_array.get(left),heap_array.get(i)) < 0)
            smallest = left;
        else  smallest = i;
        if (right <= heap_array.size() - 1 && comp.compare(heap_array.get(right),heap_array.get(smallest)) < 0)
            smallest = right;
        if (smallest != i) {
            swap(i, smallest);
            minHeapify(smallest);
        }
    }

    @Override
    public String toString() {
        return heap_array.toString();
    }

    public boolean contains(T k) { return map.get(k) != null; }
}
