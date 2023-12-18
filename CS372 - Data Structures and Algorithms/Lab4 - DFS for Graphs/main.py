# Joey Troyer
# 04/03/23
# Lab4
# program creates graph and tests how long it takes to run DFS

from graph import Graph
from time import time

visit = 1 # global counting variable previsit and postvisit in dfs

def main():

    d = Graph("directed.txt")

    print("DIRECTED GRAPH WITH DISCONNECTED NODE")
    directed = testDFS(d)
    print(f"directed graph of size: {d.num_nodes()}     TIME: {directed * 1e6:.2f} micro seconds\n\n")
    d.save("DirectedGraph.txt")


    # second argument FALSE to create an undirected graph
    u = Graph("undirected.txt", False)

    print("UNDIRECTED GRAPH WITH DISCONNECTED NODE")
    undirected = testDFS(u)
    print(f"directed graph of size: {u.num_nodes()}     TIME: {undirected * 1e6:.2f} micro seconds\n\n")
    u.save("UndirectedGraph.txt")



    c = Graph("cyclic.txt")

    print("CYCLIC GRAPH")
    cyclic = testDFS(c)
    print(f"cyclic graph of size: {c.num_nodes()}     TIME: {cyclic * 1e6:.2f} micro seconds\n\n")
    c.save("CyclicGraph.txt")



    a = Graph("acyclic.txt")

    print("ACYCLIC GRAPH")
    acyclic = testDFS(a)
    print(f"Acyclic graph of size: {a.num_nodes()}    TIME: {acyclic * 1e6:.2f} micro seconds\n\n")
    a.save("AcyclicGraph.txt")



    e = Graph("disconnected.txt")

    print("GRAPH WITH THREE SETS OF DISCONNECTED NODES")
    disconnected = testDFS(e)
    print(f"Disconnected graph of size: {e.num_nodes()}    TIME: {disconnected * 1e6:.2f} micro seconds\n\n")
    e.save("disconnectedGraph.txt")

    







#* depth first search algorithm
#! saves the pre visit and post visit in each node
def dfs(node, g):
    global visit

    #set the previst value of node to the int visit
    node.setPre(visit)
    visit += 1
    
    #recur through all the adjecent nodes of that node
    #keeping track of pre and post visits
    for adj in g.m_adjList[node.id()]:
        if(adj.getPre() == -1):
            dfs(adj, g)

    #after we have already visited and there is no more adjecent nodes to explore set the postvist value of the node
    node.setPost(visit)
    visit += 1




#* helper function to run dfs on all nodes and time it
def testDFS(g):
    global visit
    #reset the visit to keep track of pre and postvists
    visit = 1

    g.printGraph()

    start_time = time()

    # Perform DFS on all nodes in the graph that haven't been visited, handling disconnected nodes
    for node in g.m_nodes:
        if node.getPre() == -1:
            dfs(node, g)

    end_time = time()

    #get the time it takes to run dfs
    runTime = (end_time - start_time)
    

    printVisits(g)


    return runTime



#* prints pre and post values in each node
def printVisits(g):
    for node in g.m_nodes:
        print(f"{node.name()} Pre: {node.getPre()}  Post: {node.getPost()}")


main()