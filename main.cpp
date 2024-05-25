#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

void printFinalSpanningTree(std::vector<char> spanningTree);
void checkSearchingCondition(std::vector<char> stack, bool& searching);
bool checkLowestExist(char lowest);
std::vector<char> getvertices();
std::unordered_map<char,std::vector<char>> getNeighbouring (std::vector<char> vertices);
char FindLowest(std::unordered_map<char,std::vector<char>> map,char mainVertex, std::vector<char>& UsedVertices);

int main()
{
    bool searching = true;
    char mainVertex, lowest;
    std::vector <char> stack, V_vertices, UsedVertices, SpanningTree;
    std::unordered_map<char,std::vector<char>> M_neighbouring;


    V_vertices = getvertices();
    M_neighbouring = getNeighbouring(V_vertices);

    std::cout << "What is the main vertex: ";
    std::cin >> mainVertex;

    SpanningTree.push_back(mainVertex);
    stack.push_back(mainVertex);

    lowest = FindLowest(M_neighbouring,mainVertex,UsedVertices);
    SpanningTree.push_back(lowest);
    stack.push_back(lowest);

    while(searching)
    {
        mainVertex = stack[stack.size()-1]; //last member of stack is the main
        lowest = FindLowest(M_neighbouring,mainVertex,UsedVertices);
        if(checkLowestExist(lowest))
        {
            stack.push_back(lowest);
            SpanningTree.push_back(mainVertex);
            SpanningTree.push_back(lowest);
        } else {
            stack.pop_back();
        }
        checkSearchingCondition(stack,searching);
    }


    std::cout << "The spanning tree for Depth-first search is -> ";
    printFinalSpanningTree(SpanningTree);
}

void printFinalSpanningTree(std::vector<char> spanningTree)
{
    for(int i = 0; i < spanningTree.size(); i++)
    {
        std::cout << spanningTree[i];
        if(i % 2 != 0)
            std::cout << ',';
    }
}

void checkSearchingCondition(std::vector<char> stack, bool& searching)
{
    if (stack.empty()){
        searching = false;
    }
}

bool checkLowestExist(char lowest)
{
    if (lowest == 'z')
        return false;
    else
        return true;
}

std::vector<char> getvertices() //get vertices
{
    std::vector<char> F_vertices;
    int numOfVertices;
    char tempvertex;
    std::cout << "Number of vertices:";
    std::cin >> numOfVertices;
    std::cout << "Char of those " << numOfVertices << " Vertices: ";
    for (int i = 0; i < numOfVertices; i++){
        std::cin >> tempvertex;
        F_vertices.push_back(tempvertex);
    }

    return F_vertices;
}

std::unordered_map<char,std::vector<char>> getNeighbouring (std::vector<char> vertices)
{
    int numOfNeighbourVertex;
    char tempvertex;
    std::unordered_map<char,std::vector<char>> F_neighbour;
    std::vector<char> F_NeighVertices;

    for(int i = 0; i < vertices.size(); i++) // loop all vertices get all neighbouring
    {
        std::cout << "How Many Neighbouring vertices for " << vertices[i] << std::endl;
        std::cin >> numOfNeighbourVertex;
        std::cout << "Enter Neighbouring vertices for " << vertices[i] << std::endl;

        for (int i = 0; i < numOfNeighbourVertex;i++){
            std::cin >> tempvertex;
            F_NeighVertices.push_back(tempvertex);
        }
        F_neighbour.emplace(vertices[i],F_NeighVertices);
        F_NeighVertices.clear();
    }

    return F_neighbour;
}

char FindLowest(std::unordered_map<char,std::vector<char>> map,char mainVertex, std::vector<char>& UsedVertices)
{
    char lowest = 'z';
    bool VertexHaventUsed = true;
    std::vector<char> VertexNeighbouring;
    auto it = map.find(mainVertex);
    VertexNeighbouring = it->second;

    UsedVertices.push_back(mainVertex);

    for(char c:VertexNeighbouring) {
        VertexHaventUsed = true;

        for(char UsedVertex:UsedVertices){
            if (c == UsedVertex) {
                VertexHaventUsed = false;
            }
        }

        if(VertexHaventUsed) {
            if(c < lowest)
                lowest = c;
        }
    }

    return lowest;
}