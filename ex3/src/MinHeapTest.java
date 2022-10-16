package src;
import java.util.*;
import java.lang.*;
import org.testng.annotations.Test;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class MinHeapTest {
    @Test
    public void EmptyMinHeap() {
        MinHeap<Integer> empty = new MinHeap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.compareTo(o2);
            }
        });
        assertTrue(empty.isEmpty());
    }

    @Test
    public void MinHeapIsOrdered() {
        MinHeap<Integer> minheap = new MinHeap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.compareTo(o2);
            }
        });
        MinHeap<Integer> equals = minheap;
        equals.insert(0);equals.insert(10);equals.insert(54);equals.insert(11);
        equals.insert(21);equals.insert(71);equals.insert(90);equals.insert(33);
        equals.insert(43);equals.insert(87);
        minheap.insert(90);minheap.insert(10);minheap.insert(33);minheap.insert(87);
        minheap.insert(21);minheap.insert(71);minheap.insert(0);minheap.insert(54);
        minheap.insert(43);minheap.insert(11);
        assertEquals(equals,minheap);
    }

    @Test
    public void MinHeapIsOrderedEqualItems() {
        MinHeap<Integer> minheap = new MinHeap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.compareTo(o2);
            }
        });
        MinHeap<Integer> equals = minheap;
        equals.insert(0);equals.insert(0);equals.insert(0);equals.insert(0);
        equals.insert(0);equals.insert(0);equals.insert(0);equals.insert(0);
        equals.insert(0);equals.insert(0);
        minheap.insert(0);minheap.insert(0);minheap.insert(0);minheap.insert(0);
        minheap.insert(0);minheap.insert(0);minheap.insert(0);minheap.insert(0);
        minheap.insert(0);minheap.insert(0);
        assertEquals(equals,minheap);
    }

    @Test
    public void CatchExceptions() {
        boolean thrown1 = false;
        boolean thrown2 = false;
        MinHeap<Integer> minheap = new MinHeap<>(new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o1.compareTo(o2);
            }
        });
        try {
            minheap.extractMin();
        }catch (MinHeapException  e) {
            thrown1 = true;
        }
        minheap.insert(3);
        try {
            minheap.decreaseKey(3,5);
        }catch (MinHeapException  e) {
            thrown2 = true;
        }
        assertEquals(thrown1,true);
        assertEquals(thrown2,true);
    }
}
