#include "Sequencer.h"


// Name: Sequencer (constructor)
  // Desc: Creates a new sequencer to hold one or more DNA/mRNA strands make of
  //       multiples of three nucleotides
  // Preconditions:  Populates m_fileName from passed information from call
  //                 For example: ./proj3 proj3_data1.txt
  // Postconditions: A sequencer created to populate DNA/mRNA strands
  Sequencer::Sequencer(string fileName){
    m_fileName = fileName;
  }
  // Name:  Sequencer (destructor)
  // Desc: Deallocates all dynamic aspects of a Sequencer
  // Preconditions: There are an existing DNA/mRNA strand(s) (linked list)
  // Postconditions: All vectors are cleared of DNA and mRNA strands
  //                 Indicates that the strands have been deallocated
  Sequencer::~Sequencer(){
    // automatically made by compiler and runs at the end
  }
  // Name: StartSequencing
  // Desc: Calls ReadFile and continually calls mainmenu until the user exits
  // Preconditions: m_fileName has been populated
  // Postconditions: m_DNA has been populated (after ReadFile concludes)
  void Sequencer::StartSequencing(){
    ReadFile();
    //keeps game running until user presses 5
    while(MainMenu() != 5){
      MainMenu(); 
    }
  }
  // Name: DisplayStrands
  // Desc: Displays each strand in both mDNA and mRNA
  //       Displays numbered type (For example, DNA 1) then the name of the strand.
  //       Finally displays the strand with arrows between each nucleotide
  // Preconditions: At least one linked list is in mDNA (may have mRNA)
  // Postconditions: Displays DNA strand from one of the vectors
  void Sequencer::DisplayStrands(){
    // for every strand in the vector output the name and call overloaded operator in strand.cpp
    for (unsigned int i = 0; i < m_DNA.size(); i++){
      cout << "DNA " << i+1 << endl;
      cout << "***" << m_DNA.at(i)->GetName() << "***" << endl;
      cout << *m_DNA.at(i);
    }
    for (unsigned int i = 0; i < m_mRNA.size(); i++){
      cout << "mRNA " << i+1 << endl;
      cout << "***" << m_mRNA.at(i)->GetName() << "***" << endl;
      cout << *m_mRNA.at(i);
    }

  }
  // Name: ReadFile
  // Desc: Reads in a file of DNA strands that has the name on one line then
  //       the sequence on the next
  //       All sequences will be an indeterminate length (always evenly divisible by three though).
  //       There are an indeterminate number of sequences in a file.
  //       Hint: Read in the entire sequence into a string then go char
  //       by char until you hit a new line break. Then insert to the m_DNA vector
  // Preconditions: Valid file name of characters (Filled with a name and then A, T, G, or C)
  // Postconditions: Populates each DNA strand and puts in m_DNA
  void Sequencer::ReadFile(){
    char strandData;
    int count = 0;
    string line;
    string name;
    string strand;
    ifstream inputStream;
    inputStream.open(m_fileName);
    while(getline(inputStream, name, ',')){//get the name
      getline(inputStream, strand, '\n');// get the entire sequence as a string
      Strand* strandPtr = new Strand(name);
      for (unsigned int i = 0; i < strand.size(); i++){
        if (strand.at(i) != ',' && strand.at(i) != '\0'){ //when theres a letter add it to end of the strand
          strandData = strand.at(i);
          strandPtr->InsertEnd(strandData);
        }
      }
      m_DNA.push_back(strandPtr); // add the strands ptr into a vector
      count++; 
    }
    inputStream.close();
    cout << "Opened File" << endl;
    cout << count << " strands loaded." << endl;


  }
  // Name:  MainMenu
  // Desc: Displays the main menu and manages exiting.
  //       Returns 5 if the user chooses to quit, else returns 0
  // Preconditions: m_DNA populated
  // Postconditions: Indicates the user has quit the program
  int Sequencer::MainMenu(){
    int choice = 0;

    while (choice != 5){

      cout << "What would you like to do?:" << endl;
      cout << "1. Display Strands" << endl;
      cout << "2. Reverse Strand" << endl;
      cout << "3. Transcribe DNA to mRNA" << endl;
      cout << "4. Translate mRNA to Amino Acids" << endl;
      cout << "5. Exit" << endl;
      cin >> choice;

      if (choice == 1){
        DisplayStrands();
      }
      else if (choice == 2){
        ReverseSequence();
      }
      else if (choice == 3){
        Transcribe();
      }
      else if (choice == 4){
        Translate();
      }
      else if (choice == 5){
        // ends the program
        cout << "Exiting program" << endl;
        cout << "Deleting DNA Strands" << endl;
        if ((int)m_mRNA.size() > 0){
          cout << "Deleting mRNA Strands" << endl;
        }
        return 5;
      }
      else{ cout << "Invalid choice please pick an integer 1-5" <<endl;} //validate user input
    }
    return 5;
  }
  // Name: ChooseDNA
  // Desc: Asks the user to choose one strand to use from loaded DNA strands
  // Preconditions: Populated m_DNA
  // Postconditions: Returns index of chosen strand
  int Sequencer::ChooseDNA(){
    int strandChoice = 0;
    cout << "Which strand to work with?" << endl;
    cout << "Choose 1 - " << m_DNA.size() << endl;
    cin >> strandChoice;
    //validate strandChoice
    while (strandChoice < 1 || strandChoice > int(m_DNA.size())){
      cout << "Invalid number please pick a number between 1 - " << m_DNA.size() << endl;
      cin >> strandChoice;
    }
    return strandChoice - 1; //makes sure you dont go out of bounds and picks correct one
  }
  // Name: ChooseMRNA
  // Desc: Asks the user to choose one strand to use from translated mRNA strands
  // Preconditions: Populated m_mRNA
  // Postconditions: Returns index of chosen strand
  int Sequencer::ChooseMRNA(){
    int strandChoice = 0;
    cout << "Which strand to work with?" << endl;
    cout << "Choose 1 - " << m_mRNA.size() << endl;
    cin >> strandChoice;
    //validate strandChoice
    while (strandChoice < 1 || strandChoice > int(m_mRNA.size())){
      cout << "Invalid number please pick a number between 1 - " << m_mRNA.size() << endl;
      cin >> strandChoice;
    }
    return strandChoice - 1; //makes sure you dont go out of bounds and picks correct one
  }
  // Name: ReverseSequence
  // Desc: User chooses to reverse either DNA or mRNA to reverse
  //       Then calls either ChooseDNA or ChooseMRNA which returns index of strand
  //       Calls ReverseStrand on chosen location
  // Preconditions: Populated m_DNA or m_mRNA
  // Postconditions: Reverses a specific strand replacing in place
  void Sequencer::ReverseSequence(){
    int reverseChoice = 0;
    int choiceIndex = 0;
    int count = 0;
    while (count < 1){
    cout << "Which type of strand to reverse?" << endl;
    cout << "1. DNA \n2. mRNA" << endl;
    cin >> reverseChoice;
      if(reverseChoice == 1){
        choiceIndex = ChooseDNA();
        //reverse DNA
        m_DNA.at(choiceIndex);
        m_DNA.at(choiceIndex)->ReverseSequence();
        cout << "Done reversing DNA " << choiceIndex +1 << "'s strand." << endl;
        count++;
      }
      else if(reverseChoice == 2 && (int) m_mRNA.size() == 0){
        //validate to make sure that there even are eny mRNA
        cout << "No mRNA to reverse; transcribe first" << endl;
        count++;
      }
      else if (reverseChoice == 2){
        choiceIndex = ChooseMRNA();
        //reverse mRNA
        m_mRNA.at(choiceIndex)->ReverseSequence();
        cout << "Done reversing mRNA " << choiceIndex + 1 << "'s strand." << endl;
        count++;
      }
      else{
        cout << "Invalid input please input 1 or 2" << endl;
      }
    }
  }
  // Name: Transcribe
  // Desc: Iterates through each DNA strand in m_DNA to transcribe to m_mRNA
  // A->U, T->A, C->G, G->C (DNA to mRNA)
  // Can be called multiple times (will result in multiple mRNA strands)
  // Puts the transcribed mRNA strand into m_mRNA
  // Note: if this function is called more than once on the same strands of DNA,
  // it will add duplicate strands into m_mRNA!
  // Preconditions: Populated m_DNA
  // Postconditions: Transcribes each strand of m_DNA to m_mRNA
  void Sequencer::Transcribe(){
    char letter = '\n';
    char adenine = 'A';
    char guanine = 'G';
    char cytonsine = 'C';
    char uracil = 'U';
    string name;
    // iterate through vector
    for (unsigned int i = 0; i < m_DNA.size(); i++){ 
      name = m_DNA.at(i)->GetName();
      Strand* mRNAPtr = new Strand(name); // create nodes for a new linked list for mrna 
      for (int j = 0; j < m_DNA.at(i)->GetSize(); j++){
        letter = m_DNA.at(i)->GetData(j);
        // letter is the data in a node from dna and it will be transcribed with its corresponding nucleotide and creates a new linked list for mRNA
        if (letter == 'T'){
          mRNAPtr->InsertEnd(adenine);
        }
        else if(letter == 'A'){
          mRNAPtr->InsertEnd(uracil);
        }
        else if(letter == 'C'){
          mRNAPtr->InsertEnd(guanine);
        }
        else if(letter == 'G'){
          mRNAPtr->InsertEnd(cytonsine);
        }
        else{// simple test
          cout << "There is something wrong if this statement appears" << endl;
        }
        
      }
      m_mRNA.push_back(mRNAPtr); // add the ptr that pts to the mRNA linked list to the vector
    }
    cout << (int)m_DNA.size() << " Strand(s) of DNA successfully transcribed into new mRNA strands" << endl;
  }
  // Name: Translate
  // Desc: Iterates through a chosen mRNA strand and converts to amino acids
  // For every three nucleotides in strand, passes them three at a time to Convert
  // Displays each amino acid but does not store the amino acids in the class
  // Preconditions: Populated m_mRNA
  // Postconditions: Translates a specific strand of mRNA to amino acids
  void Sequencer::Translate(){
    if ((int)m_mRNA.size() < 1){
      cout << "No mRNA to reverse; transcribe first" << endl; //makes sure you have done transcribe first
      return;
    }
    int mRNAChoice = 0;
    int aminoSize = 3;
    int min = 1;
    int m_RNASize = 0;
    int count = 0;
    string trinuc;
    string aminoA;
    do {
      cout << "Which strand to work with?" << endl;
      cout << "choose 1 - " << (int) m_mRNA.size() << endl;
      cin >> mRNAChoice;
    }while(mRNAChoice < min || mRNAChoice > (int) m_mRNA.size());// validate user input

    m_RNASize = (int) m_mRNA.at(mRNAChoice-1)->GetSize(); // used int the for loop to get to every node

    cout << "***" << m_mRNA.at(mRNAChoice -1 )->GetName() << "***" << endl; //output name of the strand
    for (int i = 0; i < m_RNASize + 1; i++){
      
      
      if (count == aminoSize){ // every three letters this will be true
        aminoA = Convert(trinuc); // set aminoA to the string that correspondeds with the trinucleotide
        cout << trinuc << "->" << aminoA << endl; 
        count = 0; // reset int
        trinuc = ""; //reset string
      }

      trinuc += m_mRNA.at(mRNAChoice-1)->GetData(i); // makes a string by putting together the letters from each node
      count ++; // keeps track of the letters
      
    }
    cout << "Done translating mRNA " << mRNAChoice << "'s strand." << endl;
    
  }
  // Name: Convert (Provided)
  // Desc: Converts codon (three nodes) into an amino acid
  // Preconditions: Passed exactly three U, A, G, or C
  // Postconditions: Returns the string name of each amino acid
  string Sequencer::Convert(const string trinucleotide){
    // given to us
  if((trinucleotide=="AUU")||(trinucleotide=="AUC")||(trinucleotide=="AUA"))
    return ("Isoleucine");
  else if((trinucleotide=="CUU")||(trinucleotide=="CUC")||(trinucleotide=="CUA")||
	  (trinucleotide=="CUG")|| (trinucleotide=="UUA")||(trinucleotide=="UUG"))
    return ("Leucine");
  else if((trinucleotide=="GUU")||(trinucleotide=="GUC")||
	  (trinucleotide=="GUA")||(trinucleotide=="GUG"))
    return ("Valine");
  else if((trinucleotide=="UUU")||(trinucleotide=="UUC"))
    return ("Phenylalanine");
  else if((trinucleotide=="AUG"))
    return ("Methionine (START)");
  else if((trinucleotide=="UGU")||(trinucleotide=="UGC"))
    return ("Cysteine");
  else if((trinucleotide=="GCU")||(trinucleotide=="GCC")||
	  (trinucleotide=="GCA")||(trinucleotide=="GCG"))
    return ("Alanine");
  else if((trinucleotide=="GGU")||(trinucleotide=="GGC")||
	  (trinucleotide=="GGA")||(trinucleotide=="GGG"))
    return ("Glycine");
  else if((trinucleotide=="CCU")||(trinucleotide=="CCC")||
	  (trinucleotide=="CCA")||(trinucleotide=="CCG"))
    return ("Proline");
  else if((trinucleotide=="ACU")||(trinucleotide=="ACC")||
	  (trinucleotide=="ACA")||(trinucleotide=="ACG"))
    return ("Threonine");
  else if((trinucleotide=="UCU")||(trinucleotide=="UCC")||
	  (trinucleotide=="UCA")||(trinucleotide=="UCG")||
	  (trinucleotide=="AGU")||(trinucleotide=="AGC"))
    return ("Serine");
  else if((trinucleotide=="UAU")||(trinucleotide=="UAC"))
    return ("Tyrosine");
  else if((trinucleotide=="UGG"))
    return ("Tryptophan");
  else if((trinucleotide=="CAA")||(trinucleotide=="CAG"))
    return ("Glutamine");
  else if((trinucleotide=="AAU")||(trinucleotide=="AAC"))
    return ("Asparagine");
  else if((trinucleotide=="CAU")||(trinucleotide=="CAC"))
    return ("Histidine");
  else if((trinucleotide=="GAA")||(trinucleotide=="GAG"))
    return ("Glutamic acid");
  else if((trinucleotide=="GAU")||(trinucleotide=="GAC"))
    return ("Aspartic acid");
  else if((trinucleotide=="AAA")||(trinucleotide=="AAG"))
    return ("Lysine");
  else if((trinucleotide=="CGU")||(trinucleotide=="CGC")||(trinucleotide=="CGA")||
	  (trinucleotide=="CGG")||(trinucleotide=="AGA")||(trinucleotide=="AGG"))
    return ("Arginine");
  else if((trinucleotide=="UAA")||(trinucleotide=="UAG")||(trinucleotide=="UGA"))
    return ("Stop");
  else
    cout << "returning unknown" << endl;
  return ("Unknown");
}
