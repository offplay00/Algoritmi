package src;
import java.util.*;
//Class MinHeap created for sort elements given by these 3 rules:
//Rule 1: children cannot have more than one parent and one sibling (binary condition)
//Rule 2: the parent element need to be less than or equal among the children
//Rule 3: the root need to be the minimum element among all the elements in the min heap
public class MinHeap <T> {
    private final ArrayList<T> heap_array;  //generic array based on min heap rules, the actual size of this array is controlled by .size() function
    private final Comparator<T> comp;   //comparator function for compare different types of objects
    private final Map<T,Integer> map;   //This HashMap take the object as a key and the position of the object in the array as a value
    //Empty MinHeap Constructor user doesn't need to write the right size of the object at time of compilation
    public MinHeap(Comparator<T> comp) {
        this.heap_array = new ArrayList<>();
        this.map = new HashMap<>();
        this.comp = comp;
    }
    public boolean isEmpty() { return heap_array.size() == 0; }
    private int parent(int pos) { return (pos % 2 == 1) ? pos/2 : (pos-1)/2; }  //return the parent position based on the specified element position time comp:O(1)
    private int right(int pos) { return pos * 2 + 2 ; } //return the right child position based on the specified element position time comp:O(1)
    private int left(int pos) { return pos * 2 + 1; }   //return the left child position based on the specified element position time comp:O(1)
    public int getPosition(T elem) { return map.get(elem); }    //take in input the object and return the position in the array time comp:O(1) (thanks the HashMap)

    public Set<T> getKey() { return map.keySet(); } //return all the key set in the hashmap (another way to obtain all the object currently stored in the min heap)
    private void swap(int pos,int pos2) {
        map.replace(heap_array.get(pos),pos2);
        map.replace(heap_array.get(pos2),pos);
        Collections.swap(heap_array,pos,pos2);
    }
    public void insert(T item) {    //insert an element by the rules of min heap time comp: O(log n)
        heap_array.add(item);
        map.put(item,heap_array.size()-1);
        int size = heap_array.size()-1;
        while(parent(size) != size && comp.compare(heap_array.get(size),heap_array.get(parent(size))) < 0) {
            swap(size,parent(size));
            size = parent(size);
        }
    }
    public T extractMin() throws MinHeapException {    //remove the first element in the heap and adjust the heap by his rules time comp: O(log n)
        if(heap_array.size() == 0) throw new MinHeapException("Min heap is EMPTY!");
        else if(heap_array.size() == 1)
            return heap_array.remove(0);
        Collections.swap(heap_array,heap_array.size()-1,0);
        T item = heap_array.remove(heap_array.size()-1);
        map.replace(heap_array.get(0),0);
        minHeapify(0);
        return item;
    }

    public void decreaseKey(T item,T dcr) throws MinHeapException {    //decrease the value based on comparator function of a determinate element in the min heap time comp: O(log n)
        if(comp.compare(item,dcr)<0) throw new MinHeapException("Previous item was smaller than this!");
        if(!map.containsKey(item)) throw new MinHeapException("Min Heap does not contain current value!");
        int size = getPosition(item);
        heap_array.set(size,dcr);
        map.replace(dcr,size);
        while(size > 0 && comp.compare(heap_array.get(parent(size)),heap_array.get(size)) > 0) {
            swap(size,parent(size));
            size = parent(size);
        }
    }

    private void minHeapify(int i) {    //adjust every element by the rules of min heap time comp: O(log n)
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
        StringBuilder s = new StringBuilder();
        for(T i : heap_array)
            s.append(i).append(",");
        return s.toString();
    }

    public boolean contains(T k) { return map.get(k) != null; }
}
