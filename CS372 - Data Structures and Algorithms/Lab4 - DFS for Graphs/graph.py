# Joey Troyer
# 04/03/23
# Lab4
# program thats creates a graph with adj list full of nodes

from typing import List

class Node:
    
    #* constructor for node
    def __init__(self, name, id):
        self.m_name = name
        self.m_id = id
        self.m_post = -1
        self.m_pre = -1


    #* getter for id
    def id(self):
        return self.m_id
    

    #* getter for name
    def name(self):
        return self.m_name
    

    #* getter for pre
    def getPre(self):
        return self.m_pre
    

    #* getter for post
    def getPost(self):
        return self.m_post
    

    #* setter for pre
    def setPre(self, num:int):
        self.m_pre = num
        return self.m_pre
    

    #* setter for post
    def setPost(self, num:int):
        self.m_post = num
        return self.m_post
    



class Graph:
    
    #* constructor for graph
    #! By default the graph will be directed
    def __init__(self, file:str, is_directed: bool = True):

        # list of nodes
        self.m_nodes: List[Node] = []

        # 2d list that stores all the edges for each node
        self.m_adjList: List[List[Node]] = []

        # check if its a directed graph
        self.is_directed = is_directed

        # read in the nodes and add them to the graph from the file
        self.scan(file)



    #* Insert a edge (a, b) to m_adjList
    def addEdge(self, a:Node, b:Node):
       # prevents adding the same edge multiple times
       if b not in self.m_adjList[a.id()]:
        self.m_adjList[a.id()].append(b)

       # checks if graph is directed or not
       if not self.is_directed:
           if a not in self.m_adjList[b.id()]:
               self.m_adjList[b.id()].append(a)



    #* Insert a node a to m_nodes
    def addNode(self, a:Node):

        # Make sure m_nodes and m_adjList have enough space for node with id a.id().
        # If the list is too short, append None to m_nodes and an empty list to m_adjList
        # until the list is long enough to accommodate the new node.
        while len(self.m_nodes) <= a.id():
            self.m_nodes.append(None)
            self.m_adjList.append([])

        # add node to the list
        self.m_nodes[a.id()] = a




    #* Return node with id equal to i
    def getNode(self, i:int):
        return self.m_nodes[i]
    



    #* Return reference of the adjacency list of node a
    def getAdjNodes(self, a:Node):
        return self.m_adjList[a.id()]
    

    

    #* Return the total number of nodes in the graph
    def num_nodes(self):
        return len(self.m_nodes)
    

    

    #* Create a graph from a tab-separated text edge list file to adjacency lists
    def scan(self, file:str):
        
        # dictionary to keep track of nodes only inside the scan function
        self.node_dict = {}

        with open(file, 'r') as f:

            #read in file line by line
            for line in f:
                #get the data line by line and split at the tab and remove leading or trailing white space
                data = line.strip().split('\t')
                
                # check both nodes read in
                for i in range(len(data)):

                    #check if the node already exist
                    if(not self.nodeExists(data[i])):
                        self.node_dict[data[i]] = self.num_nodes(); #add the nodes name and id to a dictionary
                        newNode = Node(data[i], self.num_nodes())   #create the node
                        self.addNode(newNode)                       #add the node to m_nodes array
                    
               
                #get the id of both nodes from the dict then get the actual nodes and put them in a variable
                node1 = self.getNode(self.node_dict[data[0]])
                node2 = self.getNode(self.node_dict[data[1]])

                #add the edges to the node1
                self.addEdge(node1, node2)
    #end scan function




    #* check if node name of node already exsits by name
    def nodeExists(self, name:str) -> bool:
        for node in self.m_nodes:
            if node.name() == name:
                return True
        return False
    




    #* prints the graph and the adjecent nodes
    def printGraph(self):

        print("GRAPH AND THEIR ADJ NODES")
        for node in self.m_nodes:
            print(f"{node.name()} -> ", end="")
            for adj in self.m_adjList[node.id()]:
                print(f"{adj.name()} ", end="")
            print()


    #* prints number of edges in graph
    def num_edges(self):
        count = 0
        for adj_list in self.m_adjList:
            count += len(adj_list)

        if not self.is_directed:
            count //= 2

        return count


                
        


    #* Save a graph from adjacency lists to a tab-separated text edge list file
    def save(self, file:str):

        with open(file, 'w') as f:

            for node in self.m_nodes:
                for adj in self.m_adjList[node.id()]:
                    f.write(f"{node.name()}\t{adj.name()}\n")
