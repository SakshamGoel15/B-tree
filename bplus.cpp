#include <bits/stdc++.h>
using namespace std;
#define swap(i, j) tie(i, j) = make_tuple(j, i)
#define in 0x3f3f3f3f

/*
  creating  a Tree Structure
*/

struct Node {
    /*
        establish connection between nodes
	    PrtNode is a parent node
    */

	Node *prtNode;
	int elmt;

	/*
	    ChildrenNode is the Child Node
	*/

	Node *childrenNode[1000];

	/*
	     values of node
	*/

	int value[1000];

    /*
	     construct a Node
	*/

	Node() {
		prtNode = NULL;
		elmt = 0;
		int a;
		for(a=0; a<1000; a++){
            value[a] = in;
            childrenNode[a] = NULL;
        	}
	}
};

/*
   Define a rootNode node
*/

Node *rootNode = new Node();

/*
  child contain Num of child nodes
*/

int child;

/*
 function Which define splitting of a leaf nodes
*/
void Leaf_Node_Split(Node *crtNode) {
    int i;
    int a,b;

    if(child % 2) {
        i = (child + 1) / 2;
    }
    else {
    	i = child / 2;
    }

    crtNode->elmt = i;

    Node *rightChildNode = new Node();
    rightChildNode->elmt = child - i;
    rightChildNode->prtNode = crtNode->prtNode;

    for(a=i, b=0; a < child; a++, b++) {
        rightChildNode->value[b] = crtNode->value[a];
        crtNode->value[a] = 0x3f3f3f3f;
    }

    int val = rightChildNode->value[0];

    if(crtNode->prtNode == NULL) {
        Node *prtNode = new Node();
        prtNode->prtNode = NULL;
        prtNode->elmt=1;
        prtNode->value[0] = val;
        prtNode->childrenNode[0] = crtNode;
        prtNode->childrenNode[1] = rightChildNode;
        crtNode->prtNode = rightChildNode->prtNode = prtNode;
        rootNode = prtNode;
        return;
    }
    else {
        Node *newNode = rightChildNode;
        crtNode = crtNode->prtNode;

        for(a=0; a <= crtNode->elmt; a++){
            if(val < crtNode->value[a]) {
                swap(crtNode->value[a], val);
            }
        }

        crtNode->elmt++;

        int a = 0;

        while(a < crtNode->elmt) {
            if(newNode->value[0] < crtNode->childrenNode[a]->value[0]) {
                swap(crtNode->childrenNode[a], newNode);
            }
            i++;
        }

        crtNode->childrenNode[a] = newNode;

        for(a=0; crtNode->childrenNode[a] != NULL; a++) {
            crtNode->childrenNode[a]->prtNode = crtNode;
        }
    }
}
/*
 function Which define splitting of a non leaf nodes
*/
void Non_Leaf_Split(Node *crtNode){
    	int i = (child/2);
    	int a,b;
    	/*
    	  crtNode is a current Node
    	  CrtNode is used for left child
    	*/
	    crtNode->elmt = i;

	    /*
	       Declaration of Right child Node
	    */
        Node *rightChildNode = new Node();
    	rightChildNode->elmt = child - i - 1;
    	/*
    	   for both left and right node their is same parent
    	*/
    	rightChildNode->prtNode = crtNode->prtNode;


   	for(a = i, b=0; a <= child; a++, b++){
    	rightChildNode->value[b] = crtNode->value[a];
	    rightChildNode->childrenNode[b] = crtNode->childrenNode[a];
        crtNode->value[a] = 0x3f3f3f3f;
	if(a != i) {
		crtNode->childrenNode[a] = NULL;
        }
    }
    /*
      storing the value of right node (first element)
    */

    	int val = rightChildNode->value[0];

   	memcpy(&rightChildNode->value, &rightChildNode->value[1], sizeof(int)*(rightChildNode->elmt + 1));
    	memcpy(&rightChildNode->childrenNode, &rightChildNode->childrenNode[1], sizeof(rootNode)*(rightChildNode->elmt + 1));

	for(a=0; crtNode->childrenNode[a] != NULL; a++) {
	crtNode->childrenNode[a]->prtNode = crtNode;
    }

    for(int a=0; rightChildNode->childrenNode[a] != NULL; a++) {
        rightChildNode->childrenNode[a]->prtNode = rightChildNode;
    }

    if(crtNode->prtNode == NULL) {
        Node *prtNode = new Node();
        prtNode->prtNode = NULL;
        prtNode->elmt = 1;
        prtNode->value[0] = val;
        prtNode->childrenNode[0] = crtNode;
        prtNode->childrenNode[1] = rightChildNode;
        crtNode->prtNode = rightChildNode->prtNode = prtNode;
        rootNode = prtNode;
        return;
    }
    else {
    	crtNode = crtNode->prtNode;

    	for(a=0; a <= crtNode->elmt; a++) {
            if(val < crtNode->value[a]) {
                swap(crtNode->value[a], val);
            }
        }

        crtNode->elmt++;

        int a = 0;
    	Node *newNode = rightChildNode;
        while(a < crtNode->elmt) {
            if(newNode->value[0] < crtNode->childrenNode[a]->value[0]) {
                swap(crtNode->childrenNode[a], newNode);
            }
            a++;
        }
        crtNode->childrenNode[a] = newNode;

        for(a=0; crtNode->childrenNode[a] != NULL; a++) {
            crtNode->childrenNode[a]->prtNode = crtNode;
        }
    }
}

/*
merging of right sub-trees and left sub-trees
*/
void node_merge(Node *leftchildNode, Node *rightChildNode, bool is_leaf, int Right_position) {

    if(!is_leaf) {
        leftchildNode->value[leftchildNode->elmt] = leftchildNode->prtNode->value[Right_position - 1];
        leftchildNode->elmt++;
    }

    memcpy(&leftchildNode->value[leftchildNode->elmt], &rightChildNode->value[0], sizeof(int)*(rightChildNode->elmt + 1));
    memcpy(&leftchildNode->childrenNode[leftchildNode->elmt], &rightChildNode->childrenNode[0], sizeof(rootNode)*(rightChildNode->elmt + 1));

	leftchildNode->elmt += rightChildNode->elmt;
    memcpy(&leftchildNode->prtNode->value[Right_position - 1], &leftchildNode->prtNode->value[Right_position], sizeof(int)*(leftchildNode->prtNode->elmt + 1));
    memcpy(&leftchildNode->prtNode->childrenNode[Right_position], &leftchildNode->prtNode->childrenNode[Right_position + 1], sizeof(rootNode)*(leftchildNode->prtNode->elmt + 1));
    leftchildNode->prtNode->elmt--;

    for(int i=0; leftchildNode->childrenNode[i] != NULL; i++) {
		leftchildNode->childrenNode[i]->prtNode = leftchildNode;
	}
}


/*
 after insertion or deletion Rearranging the Nodes to get Bplus Tree
*/
void Node_rearrange(Node *leftchildNode, Node *rightChildNode, bool is_leaf, int left_position, int iscrtNode){
	int prev_Rightvalue1 = rightChildNode->value[0];

   if(!is_leaf) {
    	memcpy(&rightChildNode->value[1], &rightChildNode->value[0], sizeof(int)*(rightChildNode->elmt + 1));
        memcpy(&rightChildNode->childrenNode[1], &rightChildNode->childrenNode[0], sizeof(rootNode)*(rightChildNode->elmt + 1));

        rightChildNode->value[0] = leftchildNode->prtNode->value[left_position];
        rightChildNode->childrenNode[0] = leftchildNode->childrenNode[leftchildNode->elmt];
        rightChildNode->elmt++;

        leftchildNode->prtNode->value[left_position] = leftchildNode->value[leftchildNode->elmt - 1];
        leftchildNode->value[leftchildNode->elmt - 1] = 0x3f3f3f3f;
        leftchildNode->childrenNode[leftchildNode->elmt] = NULL;
        leftchildNode->elmt--;
    }
    else if(iscrtNode == 0) {
        if(!is_leaf){
        	leftchildNode->value[leftchildNode->elmt] = leftchildNode->prtNode->value[left_position];
            leftchildNode->childrenNode[leftchildNode->elmt + 1] = rightChildNode->childrenNode[0];
            leftchildNode->elmt++;
            leftchildNode->prtNode->value[left_position] = rightChildNode->value[0];
            memcpy(&rightChildNode->value[0], &rightChildNode->value[1], sizeof(int)*(rightChildNode->elmt + 1));
            memcpy(&rightChildNode->childrenNode[0], &rightChildNode->childrenNode[1], sizeof(rootNode)*(rightChildNode->elmt + 1));
            rightChildNode->elmt--;
        }
        else {
            leftchildNode->value[leftchildNode->elmt] = rightChildNode->value[0];
            leftchildNode->elmt++;
            memcpy(&rightChildNode->value[0], &rightChildNode->value[1], sizeof(int)*(rightChildNode->elmt + 1));
            rightChildNode->elmt--;
            leftchildNode->prtNode->value[left_position] = rightChildNode->value[0];
        }
    }
    else {
    	memcpy(&rightChildNode->value[1], &rightChildNode->value[0], sizeof(int)*(rightChildNode->elmt + 1));
        rightChildNode->value[0] = leftchildNode->value[leftchildNode->elmt - 1];
        rightChildNode->elmt++;
        leftchildNode->value[leftchildNode->elmt - 1] = 0x3f3f3f3f;
        leftchildNode->elmt--;
        leftchildNode->prtNode->value[left_position] = rightChildNode->value[0];
    }
}


/*
  checking for element found
*/
bool foundValue;

/*
searching the element(Single element)
*/

void element_Search(Node *crtNode, int val, int crtposition) {
    int a;

    for(a=0; foundValue == false &&  a <= crtNode->elmt; a++) {
        if(val < crtNode->value[a] && crtNode->childrenNode[a] != NULL) {
            element_Search(crtNode->childrenNode[a], val, a);
        }
        else if(val == crtNode->value[a] && crtNode->childrenNode[a] == NULL) {
            foundValue = true;
            break;
        }
    }
}

/*
To store the Value of the element found we creating array
*/

vector <int> elmtFound;

/*
searching the range of an element
*/
void element_search_range(Node *crtNode, int val1, int val2, int crtposition) {
    int a;

    for(a=0; a<= crtNode->elmt; a++) {
        int val = crtNode->value[a];
        if(crtNode->childrenNode[a] != NULL) {
            element_search_range(crtNode->childrenNode[a], val1, val2, a);
        }
        else if(val1 <= val && val <= val2) {
            elmtFound.emplace_back(val);
        }
    }
}

/*
insertion of new node In the Tree
*/
void element_Insert(Node *crtNode, int val) {
    int a;
    for(int a=0; a <= crtNode->elmt; a++) {
            if(val < crtNode->value[a] && crtNode->childrenNode[a] == NULL) {
            swap(crtNode->value[a], val);
            if(a == crtNode->elmt) {
                crtNode->elmt++;
                break;
            }
        }
       else if(val < crtNode->value[a] && crtNode->childrenNode[a] != NULL) {
            element_Insert(crtNode->childrenNode[a], val);
            if(crtNode->elmt == child)
                Non_Leaf_Split(crtNode);
            return;
        }

    }

    if(crtNode->elmt == child) {
            Leaf_Node_Split(crtNode);
    }
}


/*
Deleting the node
*/
void element_Delete(Node *crtNode, int val, int crtposition) {

/*
Checking, the node is leaf or a non leaf
*/
    bool is_leaf;
    if(crtNode->childrenNode[0] == NULL) {
        is_leaf = true;
    }
    else{
    	is_leaf = false;
    }

    int prev_left_value1 = crtNode->value[0];
    int a;

    for(a=0; foundValue == false &&  a <= crtNode->elmt; a++) {

        if(val == crtNode->value[a] && crtNode->childrenNode[a] == NULL) {
        	memcpy(&crtNode->value[a], &crtNode->value[a + 1], sizeof(int)*(crtNode->elmt + 1));
            crtNode->elmt--;
            foundValue = true;
            break;
        }
          else if(val < crtNode->value[a] && crtNode->childrenNode[a] != NULL) {
            element_Delete(crtNode->childrenNode[a], val, a);
        }
    }


    if(crtNode->prtNode==NULL && crtNode->childrenNode[0] != NULL && crtNode->elmt == 0) {
        rootNode = crtNode->childrenNode[0];
        rootNode->prtNode = NULL;
        return;
    }
    else if(crtNode->prtNode == NULL && crtNode->childrenNode[0] == NULL) {
        return;
    }
    else if(!is_leaf && crtNode->prtNode != NULL) {
        if(crtposition == 0) {
        Node *rightChildNode = crtNode->prtNode->childrenNode[1];
        if(rightChildNode != NULL && crtNode->elmt + rightChildNode->elmt < child - 1) {
                node_merge(crtNode, rightChildNode, is_leaf, 1);
            }

        else if(rightChildNode != NULL && rightChildNode->elmt - 1 >= ceil((child - 1) / 2)) {
                Node_rearrange(crtNode, rightChildNode, is_leaf, 0, 0);
            }

        }
        else {
        	Node *leftchildNode = crtNode->prtNode->childrenNode[crtposition-1];
            Node *rightChildNode = crtNode->prtNode->childrenNode[crtposition+1];

            if(leftchildNode != NULL && crtNode->elmt + leftchildNode->elmt < child - 1) {
                node_merge(leftchildNode, crtNode, is_leaf, crtposition);
            }
            else if(rightChildNode != NULL && crtNode->elmt + rightChildNode->elmt < child - 1) {
               node_merge(crtNode, rightChildNode, is_leaf, crtposition+1);
            }
            else if(leftchildNode != NULL && leftchildNode->elmt - 1 >= ceil((child - 1) / 2)) {
                 Node_rearrange(leftchildNode, crtNode, is_leaf, crtposition - 1, 1);
            }
            else if(rightChildNode != NULL && rightChildNode->elmt - 1 >=  ceil((child - 1) / 2)) {
                Node_rearrange(crtNode, rightChildNode, is_leaf, crtposition, 0);
            }

        }
    }

    else if(is_leaf && crtNode->prtNode != NULL) {
        if(crtposition == 0) {
            Node *rightChildNode = new Node();
            rightChildNode = crtNode->prtNode->childrenNode[1];
            if(rightChildNode != NULL && crtNode->elmt + rightChildNode->elmt < child) {
                    node_merge(crtNode, rightChildNode, is_leaf, 1);
            }
			else if(rightChildNode != NULL && rightChildNode->elmt > (child + 1) / 2) {
                    Node_rearrange(crtNode, rightChildNode, is_leaf, 0, 0);
            }

        }
        else {
            Node *leftchildNode = crtNode->prtNode->childrenNode[crtposition-1];
            Node *rightChildNode = crtNode->prtNode->childrenNode[crtposition+1];
            if (leftchildNode != NULL && crtNode->elmt + leftchildNode->elmt < child) {
                node_merge(leftchildNode, crtNode, is_leaf, crtposition);
            }

            else if(leftchildNode != NULL && leftchildNode->elmt > (child + 1) / 2) {
                 Node_rearrange(leftchildNode, crtNode, is_leaf, crtposition - 1, 1);
            }
            else if (rightChildNode != NULL && crtNode->elmt + rightChildNode->elmt < child) {
               node_merge(crtNode, rightChildNode, is_leaf, crtposition + 1);
            }
            else if(rightChildNode != NULL && rightChildNode->elmt > (child + 1) / 2) {
                Node_rearrange(crtNode, rightChildNode, is_leaf, crtposition, 0);
            }

        }
    }

    /*
     Deleting duplicate pairs
    */

	Node *tmpNode = crtNode->prtNode;
    while(tmpNode != NULL){
        for(int i=0; i < tmpNode->elmt; i++) {
            if(tmpNode->value[i] == prev_left_value1) {
                tmpNode->value[i] = crtNode->value[0];
                break;
            }
    	}
        tmpNode = tmpNode->prtNode;
    }
}

/*
 Main class
*/


int main() {

    /*
    Reading the given Input file "input.txt"
    Create a output file "output_file.txt"
    */
    ifstream fin;
    fin.open("input.txt");

    ofstream fout;
    fout.open("output_file.txt");

    string ln, tmp;

    int child, len;

    while(true) {
        getline(fin, ln);
        if (ln == "") {
            continue;
        }
        /*
        from input file, read for Initialize
        */
        if (ln.substr(0, 10) == "Initialize") {
            len = ln.length();
            tmp = ln.substr(11, len - 12);
            child = stoi(tmp);
            break;
        }
    }

    map <int, float> Mapping;

    int sum = 0;
    int position,key;
    float val;

    while(fin) {
        getline(fin, ln);
        if (ln == "") {
            continue;
        }
        tmp = ln.substr(0, 6);
        len = ln.length();
        /*
        from input file, Read for Searching
        */

         if (tmp == "Search") {
            tmp = ln.substr(7, len - 8);
            position = tmp.find(',');
            key = stoi(tmp.substr(0, position));
            if (position != string::npos) {
                elmtFound = {};
                int key_a = key, key_b = stoi(tmp.substr(position + 1));
                element_search_range(rootNode, min(key_a, key_b), max(key_a, key_b), 0);
                if (elmtFound.empty()) {
                    fout << "NULL" << '\n';
                }
                else {
                    len = elmtFound.size();
                    for(int a=0; a < len; a++) {
                        fout << Mapping.at(elmtFound[a]) << (a != (len - 1) ? "," : "");
                    }
                    fout << '\n';
                }
            }
            else {
                foundValue = false;
                element_Search(rootNode, key, 0);
                if (foundValue) {
                    fout << Mapping.at(key) << '\n';
                }
                else {
                    fout << "NULL" << '\n';
                }
            }

        }
        /*
        From input file, Read for Insert
	    */
        if (tmp == "Insert") {
            tmp = ln.substr(7, len - 8);
            position = tmp.find(',');
            key = stoi(tmp.substr(0, position));
            val = stof(tmp.substr(position + 1));
            element_Insert(rootNode, key);
            Mapping.insert(pair <int, float> (key, val));
            sum++;
        }
        /*
        from input file, Read for Deletion
        */

        else if (tmp == "Delete") {
            tmp = ln.substr(7, len - 8);
            key = stoi(tmp);
            if (sum!=0) {
                foundValue = false;
                element_Delete(rootNode, key, 0);
                if (foundValue == true) {
                    /*
                    key value pair Destroyed
                    */
                    Mapping.erase(key);
                }
                sum--;
            }
        }

    }
    /*
    Input and output file closed
    */
    fin.close();
    fout.close();
}
