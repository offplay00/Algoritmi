package Graph;

import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.List;
import static org.junit.jupiter.api.Assertions.*;
public class GraphTesting {
    @Test
    public void EmptyGraphZeroEl() {
        Graph<String,Arch<String,Double>> graph = new Graph<String,Arch<String, Double>>(true);
        assertEquals(graph.get_n_arch(),0);
        assertEquals(graph.get_n_vertex(),0);
    }
    @Test
    public void EmptyGraphOneEl() throws Exception {
        Graph<String,Double> graph = new Graph<String,Double>(true);
        graph.addArch("start","end",6.0);
        assertNotEquals(graph.get_n_arch(),0);
        assertNotEquals(graph.get_n_vertex(),0);
    }
    @Test
    public void GraphCorrectAdd() throws Exception{
        Graph<String,Double> graph = new Graph<String,Double>(true);
        graph.addArch("start","end",(double) 6);
        assertTrue(graph.hasVertex("start"));
        assertTrue(graph.hasVertex("end"));
        assertTrue(graph.hasArch("start","end"));
        assertEquals(graph.getEdgeLabel("start","end"), 6);
    }
    @Test
    public void GraphCorrectAdjVertex() throws Exception{
        Graph<String,Double> graph = new Graph<String,Double>(true);
        graph.addArch("start","way1",6.0);
        graph.addArch("start","way2",8.0);
        graph.addArch("start","way3",10.0);
        List<Arch<String,Double>> check = new ArrayList<>();
        check.add(new Arch<>("way1",6.0));
        check.add(new Arch<>("way2",8.0));
        check.add(new Arch<>("way3",10.0));
        assertEquals(graph.getAdjacentVertex("start"),check);
    }
    @Test
    public void CorrectArchOperation() throws Exception {
        Arch<String,Double> arch1 = new Arch<>("way1",10.0);
        Arch<String,Double> arch2 = new Arch<>("way2",15.5);
        assertEquals(Arch.add(arch1.getWeight(),arch2.getWeight()),25.5);
    }
 }
