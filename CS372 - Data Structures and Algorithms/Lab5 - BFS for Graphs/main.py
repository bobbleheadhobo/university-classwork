# Joey Troyer
# 04/17/23
# Lab5
# program creates graph and tests how long it takes to run BFS

from graph import Graph
from time import time
from collections import deque


visit = 1 # global counting variable previsit and postvisit in dfs

def main():

    d = Graph("directed.txt")

    print("DIRECTED GRAPH")
    sourceNode = d.getNode(0)
    directed = testBFS(sourceNode, d)
    print(f"directed graph of {d.num_nodes()} nodes and {d.num_edges()} edges    TIME: {directed * 1e6:.2f} micro seconds\n\n")



    # second argument FALSE to create an undirected graph
    u = Graph("undirected.txt", False)

    print("UNDIRECTED GRAPH")
    sourceNode = u.getNode(5)
    undirected = testBFS(sourceNode, u)
    print(f"directed graph of {u.num_nodes()} nodes and {u.num_edges()} edges     TIME: {undirected * 1e6:.2f} micro seconds\n\n")



    c = Graph("cyclic.txt")

    print("CYCLIC GRAPH")
    sourceNode = c.getNode(0)
    cyclic = testBFS(sourceNode, c)
    print(f"cyclic graph of {c.num_nodes()} nodes and {c.num_edges()} edges     TIME: {cyclic * 1e6:.2f} micro seconds\n\n")



    a = Graph("acyclic.txt")

    print("ACYCLIC GRAPH")
    sourceNode = a.getNode(0)
    acyclic = testBFS(sourceNode, a)
    print(f"Acyclic graph of {a.num_nodes()} nodes and {a.num_edges()} edges    TIME: {acyclic * 1e6:.2f} micro seconds\n\n")



    e = Graph("large.txt")

    print("LARGE GRAPH")
    sourceNode = e.getNode(0)
    disconnected = testBFS(sourceNode, e)
    print(f"Graph of {e.num_nodes()} nodes and {e.num_edges()} edges    TIME: {disconnected * 1e6:.2f} micro seconds\n\n")




    







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



#* breadth first search algorithm
def bfs(node, g):

    # Set the distance of the source node to 0
    node.setDist(0)

    # Create a queue and add the source node. Using deque because its more efficent
    queue = deque([node])

    # while queue not empty
    while queue:

        # Get the next node in the queue
        current = queue.popleft()

        # Iterate through the adjacent nodes of the current node
        for adj in g.getAdjNodes(current):

            # If adj node hasnt been discovered yet
            if adj.getDist() == -1:  

                # Update the distance of the adj node
                adj.setDist(current.getDist() + 1) 
                
                # Add the adj node to the queue
                queue.append(adj) 

    #return node name and distance from source node for all nodes
    return [(node.name(), node.getDist()) for node in g.m_nodes]




#* helper function to run bfs and time it
def testBFS(sourceNode, g):

    #prints graph and its edges
    g.printGraph()

    start_time = time()

    BFS_Distance = bfs(sourceNode, g)

    end_time = time()

    #get the time it takes to run bfs
    runTime = (end_time - start_time)

    print("\nBFS Distances:")
    #prints the returned list from BFS so it doesnt look ugly
    for name, distance in BFS_Distance:
        print(f"{name}: {distance}")


    return runTime


main()