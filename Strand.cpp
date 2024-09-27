#include "Strand.h"

// Name: Strand() - Default Constructor
  // Desc: Used to build a new empty strand (m_head, m_tail = nullptr and size = 0)
  // Preconditions: None
  // Postconditions: Creates a new strand with a default name
  Strand::Strand(){
    //create all variables in strand
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
    m_name = "Test";
  }
  // Name: Strand(string) - Overloaded Constructor
  // Desc: Used to build a new empty strand with the name passed
  //       with m_head, m_tail = nullptr; size = 0;
  // Preconditions: None
  // Postconditions: Creates a new strand with passed name
  Strand::Strand(string name){
    //name is passed and set
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
    m_name = name;

  }
  // Name: ~Strand() - Destructor
  // Desc: Used to destruct a strand
  // Preconditions: There is an existing strand with at least one node
  // Postconditions: Strand is deallocated (including all dynamically allocated nodes)
  //                 to have no memory leaks!
  Strand::~Strand(){
    //iterate through nodes and delete the first node untill you delete the last 
    Node *curr = m_head;
    while(curr != nullptr){
      m_head = curr;
      curr = curr ->m_next;
      delete m_head;
    }
    // cleanup
    m_head = NULL;
    m_tail = NULL;
    m_size = 0;
    m_name = '\0';
  }
  // Name: InsertEnd
  // Desc: Takes in a char. Creates a new node.
  //       Inserts node at the end of the strand. Increases size.
  // Preconditions: Requires a strand
  // Postconditions: Strand is larger.
  void Strand::InsertEnd(char data){
    // dynamiclly create a node and a pointer to the node called temp
    Node *temp = new Node();
    //this temp node carries the new data and will be inserted at the end
    temp->m_next = nullptr;
    temp->m_data = data;
    // iterate to the end
    if (m_head == nullptr){
      // first node being inserted
      m_head = temp;
      m_tail = temp;
    }
    else{
      // start at the beginning and iterate to the end
      m_tail = m_head;
      while(m_tail->m_next != nullptr){
        //gets m_tail to the end
        m_tail = m_tail->m_next;

      }
      // set the orginal last node to point to the new last node 
      m_tail->m_next = temp;
      m_tail = temp;
      m_tail->m_next = nullptr;
    }
    //increase node size variable
    m_size++;
  }
  // Name: GetName()
  // Preconditions: Requires a strand
  // Postconditions: Returns m_name;
  string Strand::GetName(){
    // getter
    return m_name; 
  }
  // Name: GetSize()
  // Preconditions: Requires a strand
  // Postconditions: Returns m_size;
  int Strand::GetSize(){
    // getter
    return m_size;
  }
  // Name: ReverseSequence
  // Preconditions: Reverses the strand
  // Postconditions: Strand sequence is reversed in place; nothing returned
  void Strand::ReverseSequence(){
    // creade a dode and point it to m_head
    Node *curr = m_head;
    // creade previous and next nodes to traverse the linked list
    Node *prev = nullptr;
    Node *next = nullptr;
    // iterate throught the linked list
    while(curr != nullptr){ 
      // next points to the node after current
        next = curr->m_next;
        // current points to node before it
        curr->m_next = prev;
        // the new previous points to current node
        prev = curr;
        // current node moves to the next node 
        curr = next;
    }
    m_head = prev; 

  }
  // Name: GetData
  // Desc: Returns the data at a specific location in the strand.
  //       Iterates to node and returns char.
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns a single char from a node
  char Strand::GetData(int nodeNum){
    Node *temp = m_head;
    int count = 0;
    // iterate throuh the linked list and count everytime you go to the next node
    while (temp != nullptr){
        // when that number equals to requested node get that data;
        if (count == nodeNum){
            return temp->m_data;
        }
        //keep iterating through if the if statemnt doesnt go off
        temp = temp->m_next;
        count++;
    }
    return '\n';
  }
  // Name: operator<<
  // Desc: Overloaded << operator to return ostream from strand
  //       Iterates over the entire strand and builds an output stream
  //       (Called like cout << *m_DNA.at(i); in Sequencer)
  // Preconditions: Requires a strand
  // Postconditions: Returns an output stream (does not cout the output)
  ostream &operator<< (ostream &output, Strand &myStrand){
    //special case where there is no strand
    if (myStrand.m_size == 0){
      output << "There is no strand" << endl;
      return output;
    } // case where there is only onw node in a strand
    else if (myStrand.m_size == 1){
      cout << myStrand.m_head << endl;
      cout << "The strand is of size 1" << endl;
      return output;
    } //normal cases
    else{
      //iterate through strand and output the data
      Node* curr = myStrand.m_head;
      while(curr != nullptr){
        cout << curr->m_data << "->";
        curr = curr->m_next;
      }
      cout << "END" << endl;
      return output;
    }
    return output;
  } 