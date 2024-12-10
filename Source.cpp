#include <iostream>
#include <string>

using namespace std;

class Customer {
private:
    int CNIC;
    string name;
    string contactNumber;
    int noOfUses;

public:
    Customer(int cnic=-1, string custName="usname", string contact="usname", int uses=-1) {
        CNIC = cnic;
        name = custName;
        contactNumber = contact;
        noOfUses = uses;
    }
    friend ostream& operator<<(ostream& os, const Customer& customer); //can cout string or int on console

    int getNoOfUses() {
        return noOfUses; 
    }
    void print() {
        cout << "CNIC: " << CNIC << ", Name: " << name << ", Contact: " << contactNumber << ", Uses: " << noOfUses<<endl;
    }
    bool operator<(const Customer& other) const {
        return CNIC < other.CNIC;
    }

    bool operator==(const Customer& other) const {
        return CNIC == other.CNIC;
    }

    bool operator>(const Customer& other) const {
        return CNIC > other.CNIC;
    }
};
ostream& operator<<(ostream& os, const Customer& customer) { //ostream class handles output ,data sent on console
    os << "CNIC: " << customer.CNIC << ", Name: " << customer.name << ", Contact: " << customer.contactNumber << ", Uses: " << customer.noOfUses << endl;
    return os;
}
class BinarySearchTreeNode {
private:
    Customer data; //node
    BinarySearchTreeNode* LChild = nullptr;
    BinarySearchTreeNode* RChild = nullptr;

public:
    BinarySearchTreeNode(Customer inputData, BinarySearchTreeNode* LC = nullptr, BinarySearchTreeNode* RC = nullptr) {
        data = inputData;
        LChild = LC;
        RChild = RC;
    }

    void print(void) {
        cout << data << endl; 
        cout << LChild << endl;
        cout << RChild << endl;
    }

    friend class BinarySearchTree;
};

class BinarySearchTree {
private:
    BinarySearchTreeNode* root;

    void DeleteSubTree(BinarySearchTreeNode* rt);
    bool insert(Customer inputData, BinarySearchTreeNode* rt);
    void printSorted(BinarySearchTreeNode* rt);
    BinarySearchTreeNode* search(Customer inputData, BinarySearchTreeNode* rt);

public:
    BinarySearchTree() {
        root = nullptr;
    }

    BinarySearchTree(BinarySearchTreeNode* rt) {
        root = rt;
    }

    ~BinarySearchTree(void) {
        DeleteSubTree(root);
    }

    void printSorted(void);
    bool insert(Customer inputData);
    BinarySearchTreeNode* search(Customer inputData);
};

bool BinarySearchTree::insert(Customer inputData) {
    if (root == nullptr) {
        BinarySearchTreeNode* nodeToAdd = new BinarySearchTreeNode(inputData);
        root = nodeToAdd;
        return true;
    }
    return insert(inputData, this->root);
}

bool BinarySearchTree::insert(Customer inputData, BinarySearchTreeNode* rt) {
    if (rt->data == inputData)
        return false;//no same cnic
    else {
        if (rt->data > inputData) {
            if (rt->LChild == nullptr) {
                BinarySearchTreeNode* node = new BinarySearchTreeNode(inputData);
                rt->LChild = node;
                return true;
            }
            else
                return insert(inputData, rt->LChild);
        }
        else {
            if (rt->RChild == nullptr) {
                BinarySearchTreeNode* node = new BinarySearchTreeNode(inputData);
                rt->RChild = node;
                return true;
            }
            else
                return insert(inputData, rt->RChild);
        }
    }
}

void BinarySearchTree::DeleteSubTree(BinarySearchTreeNode* rt) {
    if (rt != nullptr) {
        DeleteSubTree(rt->LChild);  //post order lrv
        DeleteSubTree(rt->RChild);
        delete rt;
        rt = nullptr; // Set the pointer to null after deletion
    }
}


void BinarySearchTree::printSorted(BinarySearchTreeNode* rt) {
    if (rt == nullptr)
        return;     //lvr
    else {
        printSorted(rt->LChild);
        cout << rt->data << endl;
        printSorted(rt->RChild);
    }
}

void BinarySearchTree::printSorted(void) {
    printSorted(root);
}

BinarySearchTreeNode* BinarySearchTree::search(Customer inputData) {
    return search(inputData, root);
}

BinarySearchTreeNode* BinarySearchTree::search(Customer inputData, BinarySearchTreeNode* rt) {
    if (rt != nullptr && rt->data == inputData)
        return rt;
    else {
        if (rt == nullptr)
            return nullptr;

        if (rt->data > inputData)
            return search(inputData, rt->LChild);
        else
            return search(inputData, rt->RChild);
    }
}
class Graph
{

private:
    int V = 40;
    int graph[40][40] = {
{0 ,71 ,70 ,50 ,70 ,37 ,25 ,50 ,85 ,82 ,16 ,19 ,58 ,30 ,21 ,87 ,77 ,93 ,43 ,73 ,94 ,76 ,4 ,67 ,61 ,88 ,55 ,30 ,49 ,31 ,2 ,36 ,60 ,82 ,20 ,92 ,22 ,22 ,98 ,4},//40
{71 ,0 ,89 ,3 ,97 ,83 ,91 ,74 ,96 ,43 ,19 ,50 ,90 ,68 ,76 ,61 ,23 ,16 ,68 ,70 ,48 ,39 ,22 ,68 ,12 ,24 ,80 ,46 ,57 ,15 ,3 ,74 ,21 ,50 ,42 ,94 ,41 ,70 ,27 ,58},//39
{70 ,89 ,0 ,71 ,10 ,93 ,62 ,4 ,49 ,17 ,32 ,62 ,41 ,29 ,94 ,50 ,2 ,11 ,33 ,66 ,99 ,30 ,45 ,98 ,18 ,24 ,68 ,19 ,10 ,9 ,89 ,30 ,8 ,66 ,93 ,2 ,80 ,2 ,57 ,26},//38
{50 ,3 ,71 ,0 ,34 ,57 ,26 ,95 ,19 ,77 ,17 ,78 ,3 ,28 ,97 ,18 ,10 ,72 ,37 ,81 ,72 ,57 ,86 ,98 ,6 ,1 ,30 ,98 ,3 ,79 ,41 ,79 ,55 ,88 ,63 ,11 ,8 ,44 ,79 ,59},//37
{70 ,97 ,10 ,34 ,0 ,36 ,42 ,19 ,42 ,28 ,32 ,14 ,59 ,66 ,23 ,99 ,61 ,36 ,1 ,60 ,86 ,67 ,66 ,41 ,42 ,28 ,13 ,97 ,27 ,85 ,33 ,81 ,38 ,8 ,42 ,90 ,67 ,86 ,9 ,46},//36
{37 ,83 ,93 ,57 ,36 ,0 ,94 ,99 ,52 ,25 ,18 ,83 ,54 ,88 ,19 ,80 ,74 ,75 ,49 ,36 ,90 ,96 ,77 ,5 ,2 ,10 ,70 ,14 ,12 ,58 ,73 ,2 ,72 ,62 ,92 ,8 ,7 ,12 ,62 ,40},//35
{25 ,91 ,62 ,26 ,42 ,94 ,0 ,7 ,79 ,49 ,93 ,40 ,27 ,8 ,10 ,99 ,33 ,58 ,65 ,47 ,26 ,23 ,31 ,49 ,90 ,97 ,24 ,72 ,70 ,82 ,60 ,36 ,33 ,11 ,4 ,96 ,61 ,72 ,7 ,55},//34
{50 ,74 ,4 ,95 ,19 ,99 ,7 ,0 ,86 ,11 ,99 ,54 ,13 ,69 ,60 ,77 ,1 ,14 ,75 ,82 ,30 ,22 ,91 ,86 ,12 ,96 ,52 ,20 ,88 ,79 ,53 ,4 ,6 ,30 ,71 ,94 ,38 ,53 ,53 ,90},//33
{85 ,96 ,49 ,19 ,42 ,52 ,79 ,86 ,0 ,95 ,8 ,53 ,13 ,57 ,42 ,12 ,86 ,5 ,13 ,91 ,25 ,34 ,75 ,50 ,54 ,31 ,36 ,7 ,61 ,67 ,81 ,7 ,32 ,49 ,56 ,84 ,17 ,11 ,76 ,79},//32
{82 ,43 ,17 ,77 ,28 ,25 ,49 ,11 ,95 ,0 ,24 ,87 ,33 ,27 ,30 ,68 ,6 ,89 ,92 ,61 ,62 ,64 ,56 ,70 ,63 ,65 ,5 ,48 ,71 ,84 ,77 ,87 ,84 ,50 ,41 ,53 ,32 ,74 ,96 ,77},//31
{16 ,19 ,32 ,17 ,32 ,18 ,93 ,99 ,8 ,24 ,0 ,74 ,35 ,18 ,41 ,32 ,94 ,77 ,46 ,80 ,57 ,38 ,34 ,87 ,40 ,29 ,41 ,14 ,14 ,75 ,94 ,63 ,46 ,43 ,24 ,48 ,54 ,50 ,34 ,5},//30
{19 ,50 ,62 ,78 ,14 ,83 ,40 ,54 ,53 ,87 ,74 ,0 ,11 ,48 ,59 ,17 ,46 ,84 ,89 ,24 ,69 ,58 ,15 ,98 ,6 ,79 ,84 ,33 ,66 ,15 ,9 ,13 ,43 ,27 ,14 ,62 ,27 ,10 ,51 ,67},//29
{58 ,90 ,41 ,3 ,59 ,54 ,27 ,13 ,13 ,33 ,35 ,11 ,0 ,35 ,34 ,7 ,39 ,45 ,96 ,83 ,4 ,52 ,86 ,50 ,8 ,94 ,50 ,12 ,75 ,59 ,64 ,45 ,64 ,72 ,25 ,89 ,63 ,49 ,5 ,36},//28
{30 ,68 ,29 ,28 ,66 ,88 ,8 ,69 ,57 ,27 ,18 ,48 ,35 ,0 ,26 ,53 ,2 ,39 ,43 ,65 ,2 ,78 ,99 ,43 ,76 ,7 ,8 ,60 ,73 ,84 ,56 ,91 ,75 ,18 ,30 ,25 ,28 ,35 ,48 ,82},//27
{21 ,76 ,94 ,97 ,23 ,19 ,10 ,60 ,42 ,30 ,41 ,59 ,34 ,26 ,0 ,2 ,94 ,54 ,22 ,28 ,77 ,61 ,11 ,76 ,5 ,63 ,64 ,59 ,39 ,72 ,77 ,42 ,88 ,67 ,65 ,55 ,58 ,95 ,3 ,42},//26
{87 ,61 ,50 ,18 ,99 ,80 ,99 ,77 ,12 ,68 ,32 ,17 ,7 ,53 ,2 ,0 ,56 ,68 ,12 ,99 ,74 ,43 ,47 ,18 ,90 ,25 ,72 ,26 ,70 ,63 ,85 ,45 ,24 ,46 ,98 ,69 ,15 ,52 ,69 ,10},//25
{77 ,23 ,2 ,10 ,61 ,74 ,33 ,1 ,86 ,6 ,94 ,46 ,39 ,2 ,94 ,56 ,0 ,45 ,69 ,45 ,40 ,3 ,13 ,23 ,54 ,88 ,4 ,2 ,77 ,32 ,3 ,24 ,63 ,88 ,32 ,94 ,39 ,85 ,15 ,55},//24
{93 ,16 ,11 ,72 ,36 ,75 ,58 ,14 ,5 ,89 ,77 ,84 ,45 ,39 ,54 ,68 ,45 ,0 ,67 ,37 ,5 ,68 ,23 ,46 ,57 ,18 ,38 ,9 ,62 ,28 ,73 ,20 ,18 ,21 ,87 ,70 ,88 ,14 ,63 ,57},//23
{43 ,68 ,33 ,37 ,1 ,49 ,65 ,75 ,13 ,92 ,46 ,89 ,96 ,43 ,22 ,12 ,69 ,67 ,0 ,70 ,63 ,81 ,92 ,65 ,11 ,19 ,17 ,39 ,26 ,26 ,63 ,18 ,49 ,46 ,56 ,45 ,35 ,66 ,62 ,47},//22
{73 ,70 ,66 ,81 ,60 ,36 ,47 ,82 ,91 ,61 ,80 ,24 ,83 ,65 ,28 ,99 ,45 ,37 ,70 ,0 ,29 ,12 ,10 ,41 ,66 ,52 ,92 ,76 ,85 ,68 ,45 ,83 ,77 ,56 ,46 ,65 ,24 ,95 ,37 ,60},//21
{94 ,48 ,99 ,72 ,86 ,90 ,26 ,30 ,25 ,62 ,57 ,69 ,4 ,2 ,77 ,74 ,40 ,5 ,63 ,29 ,0 ,88 ,88 ,66 ,93 ,22 ,41 ,33 ,8 ,81 ,30 ,75 ,11 ,61 ,19 ,95 ,70 ,49 ,48 ,85},//20
{76 ,39 ,30 ,57 ,67 ,96 ,23 ,22 ,34 ,64 ,38 ,58 ,52 ,78 ,61 ,43 ,3 ,68 ,81 ,12 ,88 ,0 ,19 ,81 ,98 ,92 ,87 ,94 ,9 ,94 ,44 ,88 ,32 ,90 ,73 ,26 ,9 ,88 ,67 ,21},//19
{4 ,22 ,45 ,86 ,66 ,77 ,31 ,91 ,75 ,56 ,34 ,15 ,86 ,99 ,11 ,47 ,13 ,23 ,92 ,10 ,88 ,19 ,0 ,83 ,8 ,61 ,48 ,79 ,8 ,70 ,2 ,69 ,76 ,72 ,97 ,76 ,15 ,62 ,46 ,2},//18
{67 ,68 ,98 ,98 ,41 ,5 ,49 ,86 ,50 ,70 ,87 ,98 ,50 ,43 ,76 ,18 ,23 ,46 ,65 ,41 ,66 ,81 ,83 ,0 ,6 ,95 ,28 ,63 ,98 ,49 ,93 ,64 ,95 ,12 ,21 ,74 ,12 ,24 ,56 ,73},//17
{61 ,12 ,18 ,6 ,42 ,2 ,90 ,12 ,54 ,63 ,40 ,6 ,8 ,76 ,5 ,90 ,54 ,57 ,11 ,66 ,93 ,98 ,8 ,6 ,0 ,41 ,24 ,82 ,39 ,43 ,73 ,98 ,39 ,83 ,98 ,69 ,49 ,75 ,86 ,23},//16
{88 ,24 ,24 ,1 ,28 ,10 ,97 ,96 ,31 ,65 ,29 ,79 ,94 ,7 ,63 ,25 ,88 ,18 ,19 ,52 ,22 ,92 ,61 ,95 ,41 ,0 ,25 ,88 ,19 ,9 ,97 ,22 ,3 ,77 ,30 ,97 ,41 ,3 ,53 ,22},//15
{55 ,80 ,68 ,30 ,13 ,70 ,24 ,52 ,36 ,5 ,41 ,84 ,50 ,8 ,64 ,72 ,4 ,38 ,17 ,92 ,41 ,87 ,48 ,28 ,24 ,25 ,0 ,57 ,16 ,30 ,5 ,22 ,20 ,38 ,11 ,9 ,36 ,10 ,41 ,80},//14
{30 ,46 ,19 ,98 ,97 ,14 ,72 ,20 ,7 ,48 ,14 ,33 ,12 ,60 ,59 ,26 ,2 ,9 ,39 ,76 ,33 ,94 ,79 ,63 ,82 ,88 ,57 ,0 ,62 ,84 ,55 ,77 ,8 ,71 ,42 ,39 ,68 ,20 ,37 ,4},//13
{49 ,57 ,10 ,3 ,27 ,12 ,70 ,88 ,61 ,71 ,14 ,66 ,75 ,73 ,39 ,70 ,77 ,62 ,26 ,85 ,8 ,9 ,8 ,98 ,39 ,19 ,16 ,62 ,0 ,14 ,14 ,92 ,66 ,58 ,15 ,91 ,20 ,56 ,7 ,3},//12
{31 ,15 ,9 ,79 ,85 ,58 ,82 ,79 ,67 ,84 ,75 ,15 ,59 ,84 ,72 ,63 ,32 ,28 ,26 ,68 ,81 ,94 ,70 ,49 ,43 ,9 ,30 ,84 ,14 ,0 ,96 ,33 ,27 ,17 ,18 ,42 ,15 ,24 ,76 ,35},//11
{2 ,3 ,89 ,41 ,33 ,73 ,60 ,53 ,81 ,77 ,94 ,9 ,64 ,56 ,77 ,85 ,3 ,73 ,63 ,45 ,30 ,44 ,2 ,93 ,73 ,97 ,5 ,55 ,14 ,96 ,0 ,75 ,9 ,91 ,99 ,6 ,3 ,38 ,70 ,18},//10
{36 ,74 ,30 ,79 ,81 ,2 ,36 ,4 ,7 ,87 ,63 ,13 ,45 ,91 ,42 ,45 ,24 ,20 ,18 ,83 ,75 ,88 ,69 ,64 ,98 ,22 ,22 ,77 ,92 ,33 ,75 ,0 ,69 ,64 ,85 ,70 ,10 ,7 ,46 ,73},//9
{60 ,21 ,8 ,55 ,38 ,72 ,33 ,6 ,32 ,84 ,46 ,43 ,64 ,75 ,88 ,24 ,63 ,18 ,49 ,77 ,11 ,32 ,76 ,95 ,39 ,3 ,20 ,8 ,66 ,27 ,9 ,69 ,0 ,66 ,29 ,54 ,80 ,2 ,77 ,50},//8
{82 ,50 ,66 ,88 ,8 ,62 ,11 ,30 ,49 ,50 ,43 ,27 ,72 ,18 ,67 ,46 ,88 ,21 ,46 ,56 ,61 ,90 ,72 ,12 ,83 ,77 ,38 ,71 ,58 ,17 ,91 ,64 ,66 ,0 ,90 ,77 ,84 ,35 ,56 ,42},//7
{20 ,42 ,93 ,63 ,42 ,92 ,4 ,71 ,56 ,41 ,24 ,14 ,25 ,30 ,65 ,98 ,32 ,87 ,56 ,46 ,19 ,73 ,97 ,21 ,98 ,30 ,11 ,42 ,15 ,18 ,99 ,85 ,29 ,90 ,0 ,95 ,74 ,30 ,71 ,29},//6
{92 ,94 ,2 ,11 ,90 ,8 ,96 ,94 ,84 ,53 ,48 ,62 ,89 ,25 ,55 ,69 ,94 ,70 ,45 ,65 ,95 ,26 ,76 ,74 ,69 ,97 ,9 ,39 ,91 ,42 ,6 ,70 ,54 ,77 ,95 ,0 ,43 ,23 ,24 ,35},//5
{22 ,41 ,80 ,8 ,67 ,7 ,61 ,38 ,17 ,32 ,54 ,27 ,63 ,28 ,58 ,15 ,39 ,88 ,35 ,24 ,70 ,9 ,15 ,12 ,49 ,41 ,36 ,68 ,20 ,15 ,3 ,10 ,80 ,84 ,74 ,43 ,0 ,75 ,90 ,40},//4
{22 ,70 ,2 ,44 ,86 ,12 ,72 ,53 ,11 ,74 ,50 ,10 ,49 ,35 ,95 ,52 ,85 ,14 ,66 ,95 ,49 ,88 ,62 ,24 ,75 ,3 ,10 ,20 ,56 ,24 ,38 ,7 ,2 ,35 ,30 ,23 ,75 ,0 ,71 ,18},//3
{98 ,27 ,57 ,79 ,9 ,62 ,7 ,53 ,76 ,96 ,34 ,51 ,5 ,48 ,3 ,69 ,15 ,63 ,62 ,37 ,48 ,67 ,46 ,56 ,86 ,53 ,41 ,37 ,7 ,76 ,70 ,46 ,77 ,56 ,71 ,24 ,90 ,71 ,0 ,88},//2
{4 ,58 ,26 ,59 ,46 ,40 ,55 ,90 ,79 ,77 ,5 ,67 ,36 ,82 ,42 ,10 ,55 ,57 ,47 ,60 ,85 ,21 ,2 ,73 ,23 ,22 ,80 ,4 ,3 ,35 ,18 ,73 ,50 ,42 ,29 ,35 ,40 ,18 ,88 ,0 }//1
    };

public:
    Graph() {
    }
     

    void addEdge(int src, int dest, int weight) {
        graph[src][dest] = weight;
        graph[dest][src] = weight; // the graph is undirected
    }

    int minDistance(const int* dist, const bool* sptSet) {
        int min = INT_MAX, min_index;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && dist[v] < min) {//unvisited nodes which have min distance from root
                min = dist[v]; //current min distance cal
                min_index = v;  //save the minimun distance node from root
            }

        return min_index;
    }

    void dijkstra(int src, int result[]) { //all visited array ,visited nodes ki unvisited neighbours ka root se distance m se sbse shortest distance wali node ko visited mark krna or result in roots shortest distance in array and marked visited 
        int* dist = new int[V];
        bool* sptSet = new bool[V];

        for (int i = 0; i < V; i++) {
            dist[i] = INT_MAX;
            sptSet[i] = false;
        }

        dist[src] = 0;

        for (int count = 0; count < V ; count++) {
            int u = minDistance(dist, sptSet);

            sptSet[u] = true;

            for (int v = 0; v < V; v++) {
                if (!sptSet[v] && graph[u][v]/*C->B(EXISTS)*/ && dist[u] != INT_MAX /* A->C!=INF*/ && dist[u] + graph[u][v] < dist[v])//(A->B) > (A->C->B)
                    //A(src),C(current shortest),B(loop node)
                    dist[v] = dist[u] + graph[u][v];
            }
        }

        for (int i = 0; i < V; i++)
            result[i] = dist[i];

        delete[] dist;
        delete[] sptSet;
    }

    double getFare(int distance, int timesUsed) {
        int travelCost = distance * 500;
      
        if (timesUsed > 5) {
            cout <<"discount" << travelCost - (travelCost * 0.7) << endl;
            return (travelCost * 0.7); // Apply 30% discount
        }

        return travelCost;
    }
    
};

int main() {
    BinarySearchTree* BST = new BinarySearchTree();

    Customer customer1(4, "Alice", "1234567890", 5);
    Customer customer2(12, "Bob", "9876543210", 7);
    Customer customer3(9, "Charlie", "1234567890", 4);
    Customer customer4(8, "Taha", "1234567890", 8);
    Customer customer5(23, "Mobeen", "1234567890", 0);
    Customer customer6(11, "Shobeen", "1234567890", 2);
    Customer customer7(17, "Kobeen", "1234567890", 15);
   

    BST->insert(customer1);
    BST->insert(customer2);
    BST->insert(customer3);
    BST->insert(customer4);
    BST->insert(customer5);
    BST->insert(customer6);
    BST->insert(customer7);
    

    BST->printSorted();
    const int numOfNodes = 40;
    Graph g ;

    // Add edges and weights to the graph (use g.addEdge(src, dest, weight);)

    int* result = new int[numOfNodes];

    g.dijkstra(0, result);

    cout << "Enter the destination node (0-" << numOfNodes - 1 << "): ";
    int destination;
    cin >> destination;

    

    int timesUsed = customer7.getNoOfUses();

    int totalCost = g.getFare(result[destination], timesUsed);

    cout << "Total cost for traveling to node " << destination << ": $" << totalCost << endl;

    delete[] result;


    delete BST;
    return 0;
}
