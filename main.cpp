#include <iostream>
#include <dirent.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <cctype>
#include <cstdio>
#include <conio.h>

using namespace std;

fstream file;

string toLower(string s) { // FUNCTION TO CONVERT STRING TO LOWERCASE
    transform(s.begin(), s.end(), s.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return s;
};

void swap(string* a, string* b) 
{ 
    string t = *a; 
    *a = *b; 
    *b = t; 
} 

struct node{ // CREATING NODE STRUCTURE
    node *ptr;
    char name[25];
    char number[25];
    char email[50];
    char address[100];
    char note[100];
    char tag[25];
    string data;
};

// USER CLASS
class User{
    protected:
        string username, password, un, pw;
        char choice;
    public:
    
    char LoginMenu(){ // LOGIN MENU
        cout << "0. Exit\n1. Login\n\n Enter Your Choice: "; cin >> choice;
        return choice;
    }

    // LOGIN/REGISTER START
   
    void Register(){    // REGISTER()
        char ch;
        bool f=true;
        do{
            try{
                cout << "Select a Username: "; cin >> username;
                for (int i = 0; i <= username.length()-1; i++)
                {
                    if (!isalpha(username[i]))
                    {
                        throw username[i];
                    }else{
                        f=true;
                    }
                }
                
                if(username.length()-1 > 25 || username.length()-1 < 3){
                    throw username;
                }
                char ch;
                    cout << "Select a Password: "; 
                    ch = _getch();
                    while(ch != 13){//character 13 is enter
                        password.push_back(ch);
                        cout << '*';
                        ch = _getch();
                    } 
               
                if ( password.length()-1 > 25 || password.length()-1 < 3)
                {   
                    throw password;
                }
            
        }
            catch(char u){
                cout<<"\nUsername can only be alphabets\n\n ";
                f = false;
            }
            catch(string u){

                cout<<"\nUsername/Password length can only be between 4-25 charachters. \n\n ";
            }
            
        } while (username.length()-1 > 25 || username.length()-1 < 3 || password.length()-1 > 25 || password.length()-1 < 3 || f==false);
        ofstream file;
        file.open("data\\" + username + ".bin", ios::binary | ios::out);
        
        file << username << endl << password;
        file.close();
        
    }
    
    bool IsLoggedIn(){ // LOGIN()
        
        do{
        cout << "Enter Username: "; cin >> username;
        ifstream file;
        file.open("data\\" + username + ".bin", ios::binary | ios::in);
        getline(file, un);
        if (un == username){
            char ch;
            password = "\0";
            pass:
            cout << "Enter Password: "; 
            ch = _getch();
            while(ch != 13){//character 13 is enter
                password.push_back(ch);
                cout << '*';
                ch = _getch();
            }
            getline(file, pw);
             if (un == username && pw == password){
                     return true;
            }else{
                cout<<"\n\n***********Invalid Password!***********\n\n";
                password = "\0";
                goto pass;
            }
            
        }else{
            cout<<"\n\n***********Invalid Username!***********\n\n";
        }}while(un != username);

     }
   
    // LOGIN/REGISTER END

};


// PHONEBOOKC CLASS START
class PhoneBook:User{
    private:
        char choice; node *s, *n, *c,*n2, *top;
        string filename;
        DIR *directory;   // creating pointer of type dirent
        struct dirent *x;
        
    public:
    PhoneBook(){
        s=c=n=top=n2=NULL;
    }

    bool nameExist(string name){    // CHECK IF CONTACT NAME ALREADY EXISTS
        
            bool f=false;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
                while ((x = readdir (directory)) != NULL)
                {   
                    
                    if (toLower(name) == toLower(x->d_name))
                    {
                        f=true;
                    }
                
                }
            }
            closedir (directory);
            return f;
    }
    
    bool numberExist(string number){    // CHECK IF CONTACT NUMBER ALREADY EXISTS
         
            bool f=false;
            string data;
            int count = 0;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
               while ((x = readdir (directory)) != NULL)
                {           
                        if (count > 1)
                        {
                            file.open("contacts\\" + string(x->d_name), ios::binary | ios::in);
                                while(!file.eof()){
                                    getline(file,data);
                                }
                                size_t found = data.find(number);
                                if (found != string::npos)
                                { f=true;  }
                            file.close();
                        }else {
                            count ++;
                        }
                }
                
            }
            closedir (directory);
            return f;
    }
    
    void AddRecord(){   // ADD CONTACT
        if (s==NULL)
        {
            s = new node;
            NAME1:
            try{
                cout << "\nEnter Name: "; cin >> s->name;
                for (int i = 0; i <= string(s->name).length()-1; i++)
                {
                    if (!isalpha(s->name[i]))
                    {
                        throw s->name[i];
                    }
                }
            }
            catch(char x){
            cout <<"\n\n*********Only Alphabets Allowed!*******\n\n";
            goto NAME1;
            }
            if(!nameExist(string(s->name) + ".txt")){
                NUMBER1:
                try{
                    cout << "\nEnter Phone Number: ";cin >> s->number;
                    for (int i = 0; i <= string(s->number).length()-1; i++)
                    {
                        if (!isdigit(s->number[i]))
                        {
                            throw s->number[i];
                        }
                    }
                }catch(char x){
                    cout <<"\n\n*********Only Digits Allowed!*******\n\n";
                    goto NUMBER1;
                }
                if(!numberExist(string(s->number))){
                    cin.ignore();
                    cout << "\nEnter Email: ";cin >> s->email;
                    cout << "\nEnter Address: ";cin >> s->address;
                    cout << "\nAdd Personal Note: ";cin >> s->note;
                    cout << "\nAdd a Tag: ";cin >> s->tag;
                }else{
                    cout<<"\n***********Contact Already Exists!***********\n";
                    goto NUMBER1;
                }
                }
            else
            {
                cout<<"\n***********Contact Name Already Exists! Try a Different Name***********\n";
                goto NAME1;
            }
            
            string filename = s->name;
            file.open("contacts\\" + filename + ".txt", ios::binary | ios::out);
            file << "\t"<<s->name <<"\t\t"<<s->number<<"\t"<< s->email
            << "\t\t"<<s->address<<"\t\t"<< s->note<<"\t\t"<< s->tag;
            file.close();
            s->ptr = NULL;
            c=s;
            cout<<"\n---------------------------------\n";
            cout<<"           CONTACT ADDED\n";
            cout<<"---------------------------------\n";
        }else{
            n=new node;
            string s;
            NAME:
            cout << "\nEnter Name: "; cin >> n->name;
            if(!nameExist(string(n->name) + ".txt")){
                NUMBER:
                cout << "\nEnter Phone Number: ";cin >> n->number;
                if(!numberExist(n->number)){
                    cin.ignore();
                    cout << "\nEnter Email: ";cin >> n->email;
                    cout << "\nEnter Address: ";cin >> n->address;
                    cout << "\nAdd Personal Note: ";cin >> n->note;
                    cout << "\nAdd a Tag: ";cin >> n->tag;
                }else{
                    cout<<"\n***********Contact Already Exists!***********\n";
                    goto NUMBER;
                }
                }
            else
            {
                cout<<"\n***********Contact Name Already Exists! Try a Different Name***********\n";
                goto NAME;
            }
            filename = n->name;
            file.open("contacts\\" + filename + ".txt", ios::binary | ios::out);
            file <<"\t" << n->name <<"\t\t" << n->number<< "\t" << n->email
            << "\t\t\t" << n->address<< "\t\t" << n->note<< "\t\t" << n->tag;
            file.close();
            n->ptr = NULL;
            c->ptr = n;
            c=n;
            cout<<"\n---------------------------------\n";
            cout<<"           CONTACT ADDED\n";
            cout<<"---------------------------------\n";
        }
    }

    void search_by_name(string name){   // SEARCH BY NAME
            ifstream file;
            string data;
            bool f=false;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                cout << "\tNAME\t\tPHONE\t\tEMAIL\t\t\tADDRESS\t\tNOTE\t\t\tTAG\n";
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                while ((x = readdir (directory)) != NULL)
                {   
                    if (toLower(name) == toLower(x->d_name))
                    {
                        file.open("contacts\\" +  string(x->d_name), ios::binary | ios::in);
                        while(!file.eof()){
                            getline(file,data);
                            cout<<data<<endl<<endl;
                        }
                        file.close();
                        f=true;
                    }
                
                }
            }
            closedir (directory);
            if (!f)
            {
                cout <<"\n\t\t\t\tNO RECORD FOUND\n\n";
            }
    }
    
    void search_by_number(string number){ // SEARCH BY NUMBER/TAG
            ifstream file;
            string data;
            bool f=false;
            int count = 0;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                cout << "\tNAME\t\tPHONE\t\tEMAIL\t\t\tADDRESS\t\tNOTE\t\t\tTAG\n";
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                while ((x = readdir (directory)) != NULL)
                {   
                    
                        if (count > 1)
                        {
                            file.open("contacts\\" + string(x->d_name), ios::binary | ios::in);
                                while(!file.eof()){
                                    getline(file,data);
                                }
                                size_t found = toLower(data).find(toLower(number));
                                if (found != string::npos)
                                {
                                    cout << data <<endl << endl;
                                    f=true;  
                                }
                            file.close();
                        }else {
                            count ++;
                        }
                    }
                
                }
                closedir (directory);
                if (!f)
                {
                    cout <<"\n\t\t\t\tNO RECORD FOUND\n\n";
                }
            }
    
    void displayAll(){  // DISPLAY ALL CONTACTS
            ifstream file;
            string data;
            int count = 0;
            bool f=false;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                cout << "\tNAME\t\tPHONE\t\tEMAIL\t\t\tADDRESS\t\tNOTE\t\t\tTAG\n";
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                while ((x = readdir (directory)) != NULL)
                {   
                    if (strcmp(x->d_name, ".") != 0 && strcmp(x->d_name, "..") != 0)
                    {
                        file.open("contacts\\" + string(x->d_name), ios::binary | ios::in);
                        while(!file.eof()){
                            getline(file,data);
                            cout<<data<<endl<<endl;
                        }
                        file.close();
                        count ++;
                        f=true;
                    }
                }
            }
            closedir (directory);
            if (!f)
            {
                cout <<"\n\t\t\t\tNO RECORD FOUND\n\n";
            }else{
                cout <<"--------------------------------------------------------------------------------------------------------------------\n\tTOTAL CONTACTS: "<<count<<"\n\n";
            }
    }
    
    int MainMenu(){ // MAIN MENU
        cout << "..................................................\n";
        cout << "           W H A T  Y O U  W A N T  T O  D O ?          \n";
        cout << "..................................................\n\n\n";
        cout << "0. Exit\n1. Add Contact\n2. Search Contact\n3. Display All Contacts\n4. Delete Contact\n5. Edit Contact\n6. Reverse Sort\n7. Logout\n\n Enter Your Choice: "; cin >> choice;
        return choice;
    }

    void delete_specific(string name, char check){   // SEARCH BY NAME
            ifstream file;
            string data;
            bool f=false;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
                while ((x = readdir (directory)) != NULL)
                {   
                    if (toLower(name) == toLower(x->d_name))
                    {
                                     char result[100];   // array to hold the result.
                                    const char *one = "D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts\\";
                                    const char *two = x->d_name;
                                    strcpy(result,one); // copy string one into the result.
                                    strcat(result,two);
                                    
                                    remove(result);
                                    if (check=='y')
                                    {
                                     cout<<"\n---------------------------------\n";
                                     cout<<"           CONTACT DELETED\n";
                                     cout<<"---------------------------------\n";
                                    }
                                    f=true;  
                                
                        
                    }
                
                }
            }
            closedir (directory);
            if (!f)
            {
                cout <<"\n\t\t\t\tNO CONTACT EXISTS\n\n";
            }
    }

    void update(string name){
        ifstream file;
            string data;
            bool f=false;
            string newname, newnumber, newaddress, newtag, newemail, newnote;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
               while ((x = readdir (directory)) != NULL)
                {   
                    if (toLower(name) == toLower(x->d_name))
                    {
                            delete_specific(x->d_name, 'n');
                            cout << "\n\n*************ENTER NEW DETAILS*************\n\n";
                            AddRecord();
                            
                        f=true;
                    }

                }
                directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts");
            }
            closedir (directory);
            if (!f)
            {
                cout <<"\n\t\t\t\tNO RECORD FOUND\n\n";
            }
    }
    
    // STACK FUNCTIONS

    void push(string val){
		n2=new node;
		n2->data=val;
		n2->ptr=top;
		top=n2;
	}
	string pop(){
        string data;
	if(top==NULL)
	{
       cout<<"Stack is empty"<<endl;
    }
   else {
       data = top->data;
      top = top->ptr;
   }
   return data;
}
	void display_stack(){
		node *rep;
		if(top==NULL){
			cout<<"stack is empty"<<endl;
		}
		else{
			rep=top;
			while(rep!=NULL){
				cout<<rep->data<<"\n";
				rep=rep->ptr;
			}
		}
	}
    
    // SORTING
    int partition(int arr[], int start, int end)
    {
    
        int pivot = arr[start];
    
        int count = 0;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] <= pivot)
                count++;
        }
    
        int pivotIndex = start + count;
        swap(arr[pivotIndex], arr[start]);
    
        int i = start, j = end;
    
        while (i < pivotIndex && j > pivotIndex) {
    
            while (arr[i] <= pivot) {
                i++;
            }
    
            while (arr[j] > pivot) {
                j--;
            }
    
            if (i < pivotIndex && j > pivotIndex) {
                swap(arr[i++], arr[j--]);
            }
        }
    
        return pivotIndex;
    }
    void quickSort(int arr[], int start, int end)
    {
    
        if (start >= end)
            return;
    
        int p = partition(arr, start, end);
    
        quickSort(arr, start, p - 1);
    
        quickSort(arr, p + 1, end);
    }
    
    void sort_dec(){
        ifstream file;
            string data;
            
            int count = 0;
            bool f=false;
            if (( directory= opendir ("D:\\UOG\\UOGSemester3\\DSA\\Project\\contacts")) !=NULL)
            {
                while ((x = readdir (directory)) != NULL)
                {   
                    
                    push(string(x->d_name));
                    count ++;
                    f = true;

                }
            }
            closedir (directory);
            if (!f)
            {
                cout <<"\n\t\t\t\tNO RECORD FOUND\n\n";
            }else{
                string check;
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                cout << "\tNAME\t\tPHONE\t\tEMAIL\t\t\tADDRESS\t\tNOTE\t\t\tTAG\n";
                cout << "--------------------------------------------------------------------------------------------------------------------\n";
                for (int i = count; i > 0; i--)
                {
                    check = pop();
                    
                    if (check != ".." && check != ".")
                    {
                        file.open("contacts\\" +  check, ios::binary | ios::in);
                        while(!file.eof()){
                            getline(file,data);
                            cout<<data<<endl<<endl;
                        }
                        file.close();;
                    }
                    
                    
                }
                
            }

    }
    
};


// --------MAIN FUNCTION-------

int main(){
   
   system("color f1");
   char choice;
   PhoneBook P1;
   User U;
   AGAIN:
   cout << "..................................................\n";
   cout << "           P H O N E   D I R E C T O R Y          \n";
   cout << "..................................................\n\n\n";

    // LOGIN

   choice = U.LoginMenu();
//    if(choice=='1'){
//        U.Register();
//        system("cls");
//        cout << "\n\nUSER REGISTERED\n\n";
//        system("pause");
//        system("cls");
//        goto AGAIN;

//    }else

    if (choice== '1')
   {
       if(U.IsLoggedIn()){

           // IF LOGIN SCUCCESSFUL 

           system("cls");
           cout << "\n\nLOGIN SUCCESSFUL\n\n";
           system("pause");
           system("cls");

            // MAIN MENU

           MENU:
           choice=P1.MainMenu();
           if (choice == '1')
           {

               // ADD CONTACT

               P1.AddRecord();
                system("pause");
                system("cls");
                goto MENU;
           }else if (choice == '0')
           {
               system("exit");
               
           }else if (choice == '2')
           {

               // SEARCH CONTACT

               SEARCH:
               cout << "\n0. Back\n1. Search by Name\n2. Search by Phone Number or Tag\n"; cin >> choice;
               if (choice == '1')
               {

                   // SEARCH BY NAME

                    string name;
                    cout<<"\n\nEnter a Name to search: ";
                    cin >> name;
                    P1.search_by_name(name+".txt");
                    system("pause");
                    system("cls");
               }else if (choice == '2')
               {

                   // SEARCH BY NUMBER/TAG

                    string number;
                    cout<<"\n\nEnter a Phone Number or Tag to search: ";
                    cin >> number;
                    P1.search_by_number(number);
                    system("pause");
                    system("cls");
               }else if (choice = '0')
               {
                   system("cls");
                   goto MENU;
               }
               else{
                   cout << "\n\n************Invalid Choice************\n";
                   system("pause");
                   goto SEARCH;
               }
               goto MENU;
           }else if (choice == '3')
           {

               // DISPLAY ALL CONTACTS

               P1.displayAll();
               system("pause");
               system("cls");
               goto MENU;
           }
           else if (choice == '4')
           {

               // DELETE CONTACT
               string name;
                cout << "Enter Name of Contact: ";
                cin >> name;
               P1.delete_specific(name+".txt", 'y');
               system("pause");
               system("cls");
               goto MENU;
           }else if (choice=='5')
           {
                string name;
                cout << "Enter Name of Contact: ";
                cin >> name;
               P1.update(name+".txt");
               system("pause");
               system("cls");
               goto MENU;
           }else if (choice == '6')
           {
               P1.sort_dec();
               system("pause");
               system("cls");
               goto MENU;
           }
           else if (choice == '7')
           {
               
               system("pause");
               system("cls");
               
               goto AGAIN;
           }
           
            else{
               cout << "\n\n***********Invalid Choice!***********\n\n";
                system("pause");
                system("cls");
                goto MENU;
           }
           

       }else{

           // IF LOGIN UNSUCCESSFUL

           cout << "\n\n***********Invalid Password!***********\n\n";
           system("pause");
           system("cls");
           goto AGAIN;
       }
       
   }
   else if (choice=='0')
   {
       system("exit");
   }
   
   else{
       cout << "\nInvalid Choice\n\n";
       system("pause");
       system("cls");
       goto AGAIN;
   }
    return 0;
}