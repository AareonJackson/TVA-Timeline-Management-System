/*
    file: main.cpp
    Description: This program outputs the timeline of the Nexus events
    Input: None
    Output: The timeline of the Nexus events
*/

#include<iostream>
using namespace std;

class node{
  public:
    //3 vars: integers for year and branches, and next pointer of node type
    int year, branches;
    node *next;
 
    //Default Constructor
    node() : year(0), branches(0), next(nullptr){}
    //Constructor with year as arg
    node(int year) : year(year), branches(0), next(nullptr){}
}; 
class Timeline{
  public:
    //Constructor with start year and size. default param are 0 for both.
    Timeline(int start = 0, int size = 0) : size(size), head(nullptr){
      for(int i = 0; i < size; i++){
        node *temp = new node(start+i); //create new node
        if(!head)                       //if head is null, set head to temp
          head = temp;                  //else, traverse to end of list and add temp to end
        else{
          node *temp2 = head;           //temp2 is a temp pointer to traverse list
          while(temp2->next){           //while temp2 is not null, traverse to end of list
            temp2 = temp2->next;        //temp2 is now the last node in the list
          }
          temp2->next = temp;           //set last node in list to temp
        }
      }
    }
    int createNexusEvent(int amount = 1){
      if(!head) return 0; //Can't create nexus event if timeline is empty!
      for(int i=0; i< amount; i++){
        int year = (rand() % size) + head->year;
        //branchsize is MaxSize minus years left give us how big branch can be before end of time 
        int branchSize = rand() % (head->year+size-year)/4; //divide by 4 to keep them smaller for visual reasons

        // For createNexusEvent
        node *currentNode = head;
        // while the current node is not null and the year is not equal to the current node's year
        while(currentNode && currentNode->year != year){
          // traverse the list
          currentNode = currentNode->next;
        } 
        // if the current node is not null
        if(currentNode){
          //dynamically allocate a 1-Dimensional array of node type of size 2
          node** branchArr = new node*[2];
          // copy over the next node of the next year into the first instance
          branchArr[0] = currentNode->next;
          // put the branching timeline into the second instance
          branchArr[1] = new node(year + branchSize);   // create a new node
          // set the branches of currentNode to 1
          currentNode->branches = 1;
          currentNode->next = (node*)branchArr;        // set the next node to the branch array
          // delete the new node
          delete branchArr[1];
        }
        cout << "Created Nexus at " << year << ", Size: " << branchSize+1 << endl;
      }
      return amount;
    }

    void print(){
      cout << "The Sacred Timeline" << endl;
      // Should match the output in wtf function exactly.
      cout << "s->";
      // create a temp node to traverse the list
      node *currentNode = head;
      // while the current node is not null
      while(currentNode){
        // output to the console the year
        cout << currentNode->year;
        // if the current node has branches
        if(currentNode->branches > 0){
          // initialize a new branch
          node** branchArr = (node**)currentNode->next;
          // output to the console the branches
          cout << "->(";
          // loop through the branches
          for(int i = 0; i < currentNode->branches; ++i){
            cout << "*" << branchArr[i]->year << "." << i + 1;
            if(i < currentNode->branches - 1){
              cout << "->";
            }
          }
          cout << ")~>";    // output to the console the branches
        } else {
          cout << "->";
        }
        // initialize current node to the next node
        currentNode = currentNode->next;
      }
      cout << "x\n" << endl;
    }

    //Visual Print Mode
    void vprint(){
      //Best thing to do is to create a 2D array of chars. generate the proper drawing,
      //and then print out the array in a loop at the end. do 11 by 70.
      //branches alternate, first up, then down, then up, then down, and so on.
      //they always have two slashes in appropriate direction and then ~ where each ~ represents a branched node.
      //in the sacred timeline each - represents 1 year. If 2 branches happen to overap it's ok don't worry about it.
      //same thing if the map is too wide (bigger than 70) don't worry about it just stop printing and cut it off so
      //it does not segfault

      // declare variables
      int height = 11;    // height of the visual print
      int length = 70;    // length of the visual print
      char visualPrint[height][length];   // declare the visual print
      // output to the console the top of the visual print
      for(int i = 0; i <= length; i++){
        cout << "#";
      }
      /// initialize the visual print to empty spaces
      for(int i = 0; i < height; ++i){
        for(int j = 0; j < length; ++j){
          visualPrint[i][j] = ' ';
        }
      }
  
      // declare a node pointer to traverse the list
      node *currentNode = head;
      // location of the current node
      int location = 0;
      // alternate direction of the branches
      bool direction = true;
      // while the current node is not null
      while(currentNode && location < length){
        visualPrint[height / 2][location] = '-';    // output to the console the year
        // if the current node has branches
        if(currentNode->branches > 0){
          // initialize a new branch
          // node** branchArr = (node**)currentNode->next;
          // output to the console the branches
          for(int i = 0; i < currentNode->branches && location + i * 2 < length; ++i){
            // location of the branch
            int branchLocation = location + i * 2;
              // if direction is up 
              if(direction){
                if(branchLocation < length - 1){
                  visualPrint[height / 2 - 1][branchLocation] = '/';
                  visualPrint[height / 2 - 2][branchLocation + 1] = '~';
                }
              } else {  // if direction is down
                  if(branchLocation < length - 1){
                    // output to the console the branches
                    visualPrint[height / 2 + 1][branchLocation] = '\\';
                    // output to the console the branches
                    visualPrint[height / 2 + 2][branchLocation + 1] = '~';
                  }
                }
          }
          // alternate the direction
          direction = !direction;
        }
        // move to the next position in the timeline
        location += 2;
        // initialize current node to the next node
        currentNode = currentNode->next;
      }
      // output the visual print
      for(int i = 0; i < height; ++i){
        for(int j = 0; j < length; ++j){    
          cout << visualPrint[i][j];  
        }
        cout << endl;
      }
      // output the bottom border
      for(int i = 0; i <= length; i++){
        cout << "#";
      }
      cout << endl;
    }
    int prune(){ //prunes a branch and returns location it pruned. For all time. always.
      int yearWithBranch = -1;
      int branchSize = 1;
      // declare a node pointer to traverse the list
      node *currentNode = head;
      //node *previousNode = nullptr;
      // while the current node is not null
      while(currentNode){
        if(currentNode->branches > 0){    // if the current node has branches
          yearWithBranch = currentNode->year;   // set the year with branch
          node** branchArr = (node**)currentNode->next;    // initialize a new branch

          // node for the year of the following branch
          node* branchNode = new node(branchArr[0]->year);
          branchNode->next = branchArr[0]->next;

         // deallocate all branched nodes and the array
         for(int i = 0; i < currentNode->branches; ++i){
          delete branchArr[i];    // deallocate the branched node
          branchSize++;
         }
          delete[] branchArr;    // deallocate the array
          // relink the nodes
          currentNode->next = branchNode;
          currentNode->branches = 0;    // set the branches to 0
        }
        // place the previous node to the current node
        //previousNode = currentNode;
        // initialize current node to the next node
        currentNode = currentNode->next;
      }
      if(yearWithBranch != -1)
        cout << "Pruned Brach at: " << yearWithBranch << " of size " << branchSize << endl;
      return yearWithBranch;
    }

    ~Timeline(){
      // For de-allocating. if a branch that was not pruned is found just cout that it was not pruned.
      //cout << "Branch was not pruned!" << endl;
      node* currentNode = head;   // declare a node pointer to traverse the list
      // while the current node is not null
      while(currentNode){
        // if the current node has branches
        if(currentNode->branches > 0){
          cout << "Branch was not pruned!" << endl;
          // skip the branche nodes as they should be handled by the prune function
          node** branchArr = (node**)currentNode->next;
          // move the node after the branch nodes
          currentNode = branchArr[0]->next;
        } else {
          // deallocate the current node
          node* temp = currentNode;
          currentNode = currentNode->next;   // move to the next node
          delete temp;    // deallocate the current node
        }
      } 
    }

  private:
    int size;
    node *head;
  public:
    void wtf(){ //This code should print the sacred timeline identical to the print function
      {int o_384d4468adeab2d9aed6871 = 121934831;};typedef node o_384d4468adeab2d9aed6871e0fa;
      cout<<"\x54""h\145 \x53""a\143r\x65""d\040T\x69""m\145l\x69""n\145"<<endl;
      o_384d4468adeab2d9aed6871e0fa* o_384d4468adeab2d9aed6871e0fa887d6=head;cout<<"\x73""-\076";
      while (o_384d4468adeab2d9aed6871e0fa887d6){cout<<o_384d4468adeab2d9aed6871e0fa887d6->year
      <<"\x2D"">";if ((o_384d4468adeab2d9aed6871e0fa887d6->branches > (0x0000000000000000 + 
      0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00)) & !!(o_384d4468adeab2d9aed6871e0fa887d6->
      branches > (0x0000000000000000 + 0x0000000000000200 + 0x0000000000000800 - 0x0000000000000A00)))
      {cout<<"\x28""";for (int o_8aec06cef502177edb2e9beb8e48618e=(0x0000000000000000 + 0x0000000000000200 + 
      0x0000000000000800 - 0x0000000000000A00);(o_8aec06cef502177edb2e9beb8e48618e < o_384d4468adeab2d9aed6871e0fa887d6->
      branches) & !!(o_8aec06cef502177edb2e9beb8e48618e < o_384d4468adeab2d9aed6871e0fa887d6->branches);
      o_8aec06cef502177edb2e9beb8e48618e++){cout<<"\x2A"""<<o_384d4468adeab2d9aed6871e0fa887d6->
      next[o_8aec06cef502177edb2e9beb8e48618e + (0x0000000000000002 + 0x0000000000000201 + 0x0000000000000801 - 
      0x0000000000000A03)].year<<"\x2E"""<<o_8aec06cef502177edb2e9beb8e48618e + (0x0000000000000002 + 
      0x0000000000000201 + 0x0000000000000801 - 0x0000000000000A03);o_384d4468adeab2d9aed6871e0fa* 
      o_c4e691df50ffe930c3969e01258ea6a1=o_384d4468adeab2d9aed6871e0fa887d6->next[o_8aec06cef502177edb2e9beb8e48618e + 
      (0x0000000000000002 + 0x0000000000000201 + 0x0000000000000801 - 0x0000000000000A03)].next;
      while (o_c4e691df50ffe930c3969e01258ea6a1){cout<<"\x2D"">\052"<<o_c4e691df50ffe930c3969e01258ea6a1->
      year<<"\x2E"""<<o_8aec06cef502177edb2e9beb8e48618e + (0x0000000000000002 + 0x0000000000000201 + 
      0x0000000000000801 - 0x0000000000000A03);o_c4e691df50ffe930c3969e01258ea6a1 = o_c4e691df50ffe930c3969e01258ea6a1->
      next;};};cout<<"\x29""~\076";};o_384d4468adeab2d9aed6871e0fa887d6 = o_384d4468adeab2d9aed6871e0fa887d6->next;};
      cout<<"\x78""\x0A"<<endl;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    }
};

//FOR ALL TIME. ALWAYS
int main(int argc, char *argv[]) { // ./a.out 40 4 1970 50 (40 is seed, 4 is number of nexus events to 
  //create 1970 is starting year of the sacred timeline, and 50 is the length of the sacred timeline).
  int seed = 40;                //for testing with no cmd args
  int nexusEventsToCreate = 4;  //for testing with no cmd args
  int startYear = 1970;         //for testing with no cmd args
  int timelineLength = 50;      //for testing with no cmd args
  if(argc == 5){ //for codegrading
    seed = atoi(argv[1]);
    nexusEventsToCreate = atoi(argv[2]);
    startYear = atoi(argv[3]);
    timelineLength = atoi(argv[4]);
  }
  srand(seed);
  Timeline sacredTimeline(startYear, timelineLength);
  sacredTimeline.print();
  sacredTimeline.createNexusEvent(nexusEventsToCreate);
  //sacredTimeline.print();
  sacredTimeline.wtf();
  sacredTimeline.vprint();
  cout << "Nexus Event Detected! Sending Minute Men to Prune the Branches!\n" << endl;
  //on behalf of the time variance authority, I hereby arrest you for crimes against the sacred timeline
  while(sacredTimeline.prune()!=-1){
    sacredTimeline.print();
  }
  cout << "\nSacred Timeline Restored :)" << endl;
  sacredTimeline.print();
  sacredTimeline.vprint();

  cout << "___________   ____\n| /|    \\  \\ /  / \\\n|/ |    |\\  Y \\/   \\\n   "
       <<   "|    | \\   /\\    \\\n   |____|  \\_/_/\\____\\\n FOR ALL TIME.  ALWAYS.\n"<< endl;
  return 0;
}
