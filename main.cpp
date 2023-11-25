
//=================================================================================
// Name         : DS Assignment#2 
// Author       : 
// Version      : 1.0
// Date Created : 07-11-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include <regex>
#include "myvector.h"
#include "contact.h"
#include "contactbst.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"remove <key>       :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markFav <key>      :Mark as favourite"<<endl
		<<"unmarkFav <key>    :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printFav           :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================

// to be completed with ALL the necessary method definitions

//==========================================================
int main(void)
{


	ContactBST cms;
	listCommands();
	string user_input;
	string command;
	string key;

	while(true)
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,key);

		Node* root = cms.getRoot();	//get the root of the tree
		if( user_input =="add")	//command for the add method
		{
		 string fname; string lname; string email; string primaryPhone; string city; string country; bool isFav;string bFav;
		 cout<<"Please enter the details of the contact: "<<endl; //collects user input
         cout<<"First Name: ";
         getline(cin,fname);
		 const regex fsample("[a-zA-Z]+");
		 while (!regex_match(fname,fsample))
		 {
			cout<<"Please enter a valid first name again: ";
			getline(cin,fname);
		 }
         cout<<"Last Name: ";
         getline(cin,lname);
		 const regex lsample("[a-zA-Z]+");
		 while (!regex_match(lname,lsample))
		 {
			cout<<"Please enter a valid last name again: ";
			getline(cin,lname);
		 }
         cout<<"Email: ";
         getline(cin,email);
		 const regex esample("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		 while (!regex_match(email,esample))
		 {
			cout<<"Please enter a valid email adress again: ";
			getline(cin,email);
		 }
         cout<<"Phone#: ";
         getline(cin,primaryPhone);
         for(int i=0;i<primaryPhone.size();i++)
		 {
            if (i<2)
			 {
				while (primaryPhone[0]!='+'&&(primaryPhone[0]!='0'||primaryPhone[i]!='0'))
			 {
                 cout<<"Please enter a valid phone number again: ";
				 getline(cin,primaryPhone);
			 }
			 }
			else
			{ while (!isdigit(primaryPhone[i]))
			 {
				cout<<"Please enter a valid phone number again: ";
				getline(cin,primaryPhone);
			 }
			}
		 }
         cout<<"city: ";
         getline(cin,city);
		 const regex csample("[a-zA-Z]+");
		 while (!regex_match(city,csample))
		 {
			cout<<"Please enter a valid city again: ";
			getline(cin,city);
		 }
         cout<<"country: ";
         getline(cin,country);
		 const regex cosample("[a-zA-Z]+");
		 while (!regex_match(country,cosample))
		 {
			cout<<"Please enter a valid country again: ";
			getline(cin,country);
		 }
		 string y;string n;
		 cout<<"Do you want to add the contact in your favourite(y/n): ";
		 getline(cin,bFav);
		 while (bFav!="y"&&bFav!="n")
		 {
			cout<<"You are only allowed to enter either y or n!"<<endl;
			cout<<"Do you want to add the contact in your favourite(y/n): ";
		    getline(cin,bFav);
		 }

		 if (bFav=="y")//changes user input to boolean
		 {
			isFav=true;
		 }
		 else if(bFav=="n")
		 {
			isFav=false;
		 }
		 Contact* data=new Contact(fname, lname, email,  primaryPhone, city,  country,  isFav);
		 key=fname +' '+lname;
		 cms.add(root,key,data);
		 cout<<"Contact "<<key<<" has been successfully added"<<endl;
		 
		}
		else if( command =="searchFor")	//comand for searchFor method
		{
			Node* found= cms.searchFor(root, key);
			if(found!=nullptr)
			{found->print();}
			else{
				cout<<"The contact you have asked is not found!"<<endl;
				
			}
		}
		else if( command =="edit")	//command for the update method
		{
			
			cms.update(root, key);
			cout<<endl;

		}
		else if( command =="remove" or command =="r")//command for the remove method	
		{
			cms.remove(root,key);
			fflush(stdin);
		}
		
		else if( command =="markFav" or command =="m")	//command for the markFav method
		{
			cms.markFav(key);
			cout<<endl;
		}
		else if( command =="unmarkFav" or command =="um")//command for the unmarkFav method
		{
			cms.unmarkFav(key);
			cout<<endl;
		}
		else if( command =="printASC" or command=="pa")	{ cms.printASC(root);} //command for the printASC method
		else if( command =="printDES" or command=="pd")	{ cms.printDES(root);}//command for the printDES method
		else if( command =="printFav" or command=="pv")	{ cms.printFav(root);} 
		else if( command =="export" or command=="ex")	//command to export
		{   
			int m;
			m=cms.exportCSV(root,key);
			cout<<m<<endl;
		} 
		else if( command =="import" or command=="im")//comand to import
		
		{ 
			int l;
			l=cms.importCSV(key);
			cout<<l<<endl;
			
		}
	 
			
	
		else if( command == "help") listCommands();//comman for displaying list of commands
		else if( command =="exit" or command =="quit" or command =="q") break;
		else cout<<"Invalid command !!!"<<endl;
        
	}
	return 0;
	
}