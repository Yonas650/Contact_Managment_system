#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include "contactbst.h"
ContactBST::ContactBST()
{
    root=NULL;
}
ContactBST::~ContactBST()
{
while(root!=NULL)
{
	remove(root,root->getKey());
}
}
Node* ContactBST::getRoot()//returns the root
{
    return root;
}

void ContactBST::add(Node* ptr,string key, Contact *data)
{
	
	if (ptr==nullptr)//if the tree is empty it will create a new root node
	{
         root=new Node(key,data);
		
	}
    else if (key<ptr->key) //if the key is smaller than the ptr key it will recurse to the left
	{
		if(ptr->left==NULL)//it creates a new left child if the arguement pointer doesn't have a left child
		{
			ptr->left=new Node(key,data);
            ptr->left->left=NULL;
		    ptr->left->right=NULL;
		    ptr->left->parent=ptr;
			
		}
		else if (ptr->left!=NULL)//if the left child not null we recurse until we reach the end where we can add the node
		{
			add(ptr->left,key, data);
		}
	
	}
    else if (key>ptr->key)//if the key is greater than the ptr key it will recurse to the right
	{
	
		if (ptr->right==NULL)//it creates a new right child if the arguement pointer doesn't have a left child
		{
			ptr->right=new Node(key,data);
			ptr->right->right=NULL;
			ptr->right->left=NULL;
		    ptr->right->parent=ptr;
			
			
		}
		else if (ptr->right!=NULL)
		{
			add(ptr->right,key,data);
		}
	
	}
	else if (key==ptr->key)
	{
		Node* eqq=searchFor(ptr,key);
		eqq->contactVector.push_back(data);
	}

    
}
void ContactBST::update(Node* ptr, string key) //update attributes of contacts
{
	Node* e=searchFor(root,key);
	if(e==nullptr) //if the tree is empty the message inside will be printed
	{
		cout<<"No record found";
	}
	else
	{
	e->print();
	cout<<"Please select the record you want to edit: ";
	string vecindex;
	getline(cin,vecindex);
	if (stoi(vecindex)-1>e->contactVector.size() or stoi(vecindex)-1<0)
	{cout<<"Index out of range!";}
	else{
	Contact* cv=e->contactVector.at(stoi(vecindex)-1);
	cout<<"which field do you want to edit? 1) First Name, 2) Last Name, 3) Email, 4)Phone#, 5) City, or 6) Country: ";
	string attr;
	getline(cin,attr);
	
	string nattr;
	
	if (attr=="1")//if there are two the same keys when updated they have to rearrange themselves calling add?????????
	{
		cout<<"Please enter the new "<<"First Name"<<": ";
		getline(cin,nattr);
		cv->fname=nattr;
		Contact* tmp=cv;
		if (e->contactVector.size()==1)
		{e->key=nattr+' '+cv->lname;
		e->contactVector.erase(stoi(vecindex)-1);
		add(ptr,e->key,tmp);}
		else{
			string newk=nattr+' '+cv->lname;
			e->contactVector.erase(stoi(vecindex)-1);
			add(ptr,newk,tmp);
		}
		

	}
	if (attr=="2")//updates last name
	{
		cout<<"Please enter the new "<<"Last Name"<<": ";
		getline(cin,nattr);
		cv->lname=nattr;
		Contact* tmp=cv;
      if (e->contactVector.size()==1)
		{e->key=cv->fname+' '+nattr;
		e->contactVector.erase(stoi(vecindex)-1);
		add(ptr,e->key,tmp);}
		else{
			string newk=cv->fname+' '+nattr;
			e->contactVector.erase(stoi(vecindex)-1);
			add(ptr,newk,tmp);
		}
		//e->contactVector.erase(stoi(vecindex)-1);
		//add(ptr,e->key,tmp);
	}
	if (attr=="3")//updates email
	{
		cout<<"Please enter the new "<<"Email"<<": ";
		getline(cin,nattr);
		cv->email=nattr;
	}
	if (attr=="4")//updates phone number
	{
		cout<<"Please enter the new "<<"Phone#"<<": ";
		getline(cin,nattr);
		cv->primaryPhone=nattr;
	}
	if (attr=="5")//updates city
	{
		cout<<"Please enter the new "<<"City"<<": ";
		getline(cin,nattr);
		cv->city=nattr;
	}
	if (attr=="6")//updates country
	{
		cout<<"Please enter the new "<<"country"<<": ";
		getline(cin,nattr);
		cv->country=nattr;
	}
	if (stoi(attr)>6 or stoi(attr)<1)
	{
		cout<<"Index out of range";
	}
	else{
	
	cout<<"Do you want to edit another field(line/n)?";
	string ch;
	getline(cin,ch);
	if (ch=="line")
	{
		
		update(ptr,e->getKey());
	}
	cout<<"The contact record has been successfully updated!";
	}
	}
	}
	

}
void ContactBST::remove(Node* ptr,string key)
{
	
if (ptr==NULL)
{cout<<"Empty tree";}
	else if (key<ptr->key)
	{
		remove(ptr->left,key);
	}
	else if (key>ptr->key)
	{
		remove(ptr->right,key);
	}
	else if(key==ptr->key)
	{
		if (ptr->left==NULL &&ptr->right==NULL)
		{
			if (ptr->parent==NULL)
			{
			if (ptr->contactVector.size()>1)
				{
					string vecindex;
					ptr->print();
					cout<<"Please select the record you want to delete: ";
					cin>>vecindex;
					ptr->contactVector.erase(stoi(vecindex)-1);
				}
	        else{
		    delete ptr;
			root=NULL;
		        }
			
			
			}
			else{
				if(ptr==ptr->parent->right)//if the node is a right child
				{
					if (ptr->contactVector.size()>1)//if it has more than one contact 
				    {
					string vecindex;
					ptr->print();
					cout<<"Please select the record you want to delete: ";
					cin>>vecindex;
					ptr->contactVector.erase(stoi(vecindex)-1);
				    }
	                else{
		                 ptr->parent->right=NULL;
						 delete ptr;
		                 }
				
				}
				else if(ptr==ptr->parent->left)//if the node is a left child
				{
					if (ptr->contactVector.size()>1)//if it has more than on contact
				    {
					string vecindex;
					ptr->print();
					cout<<"Please select the record you want to delete: ";
					cin>>vecindex;
					ptr->contactVector.erase(stoi(vecindex)-1);
				    }
	                else{
		                 ptr->parent->left=NULL;
						 delete ptr;
		                 }
				}
			   }
			
		}
		else if (ptr->left==NULL&&ptr->right!=NULL)//if the node has only a right child
		{
			
			
			if (ptr==ptr->parent->right)//if the node is a right child
			{
				if (ptr->contactVector.size()>1)//if it has more than one contact
				    {
					string vecindex;
					ptr->print();
					cout<<"Please select the record you want to delete: ";
					cin>>vecindex;
					ptr->contactVector.erase(stoi(vecindex)-1);
				    }
	                else{
		                 ptr->parent->right=ptr->right;
				         ptr->right->parent=ptr->parent;
				         delete ptr;
		                 }
				
				
				
			}
			else if (ptr==ptr->parent->left)//if the node is a left child
			{
				if (ptr->contactVector.size()>1) //if it has more than one contact
				    {
					string vecindex;
					ptr->print();
					cout<<"Please select the record you want to delete: ";
					cin>>vecindex;
					ptr->contactVector.erase(stoi(vecindex)-1);
				    }
	                else{
		                 ptr->parent->left=ptr->right;
                         ptr->right->parent=ptr->parent;
				         delete ptr;
		                 }
			}

		}
		else if (ptr->right==NULL&&ptr->left!=NULL)//if the node has only a left child
		{
			if (ptr==ptr->parent->right)//if the node is right child
			{
				if (ptr->contactVector.size()>1)//if it has more than contact
				    {
					string vecindex;
					ptr->print();
					cout<<"Please select the record you want to delete: ";
					cin>>vecindex;
					ptr->contactVector.erase(stoi(vecindex)-1);
				    }
	                else{
		                ptr->parent->right=ptr->left;
						ptr->left->parent=ptr->parent;
						delete ptr;
		                 }	
			}
			if (ptr==ptr->parent->left)//if the node is a left child
			{
				if (ptr->contactVector.size()>1)//if it has more than one contact
				    {
					string vecindex;
					ptr->print();
					cout<<"Please select the record you want to delete: ";
					cin>>vecindex;
					ptr->contactVector.erase(stoi(vecindex)-1);
				    }
	                else{
		                ptr->parent->left=ptr->left;
						ptr->left->parent=ptr->parent;
						delete ptr;
		                 }
			}
			

		}
		else if (ptr->left!=NULL&&ptr->right!=NULL){//if the node has two children
			
			for (int i=0;i<ptr->contactVector.size();i++ )
			{
			ptr->contactVector.erase(i);
			}
			for (int j=0;j<ptr->contactVector.size();j++ )
			{
			ptr->contactVector.push_back(findMin(ptr->right)->contactVector.at(j));
			}
			ptr->key=findMin(ptr->right)->key;
			remove(findMin(ptr->right),findMin(ptr->right)->key);
			cout<<"The contact record "<<key<<" has successfully been removed"<<endl; 
		}
		
	}
		
}
Node* ContactBST::searchFor(Node* ptr,string key)
{

if (ptr==NULL) {return NULL;}//if the tree is empty it will return a null pointer
	
if (ptr->key==key) //if the key of the node is equal to the key being searched the node will be returned
	{
		return ptr;
	}
	
	
 if (key>ptr->key)//if the key passed is greater than the key of the node we will recurse to the right
    {
		return searchFor(ptr->right, key);
	}
if (key<ptr->key)//if the key passed is smaller than the key of the node we will recurse to the left
  {
	return searchFor(ptr->left, key);
   }
	return ptr;
}
bool ContactBST::markFav(string key)// searches for the node with the provided key and change the mark
{
Node* x=searchFor(root, key);// searches for the node with the provided key
if (key==""||x==NULL)//prints the message below if no key is provided
{
	cout<<"No key provided or the key doesn't found!";
	return false;
}
else 
{ 
 x->print();
 cout<<"Please select the record you want to mark as favorite: ";
 string vecindex;
 getline(cin,vecindex);
 Contact* cv=x->contactVector.at(stoi(vecindex)-1);
 if(cv->isFav==0) //if the the contact is not in the favorite list it will add it to the list
 {
	cv->isFav=1;
	cout<<key<<"("<<cv->email<<")"<<" has been added successfully marked as favorite!";
 }
 else //if the the contact is already in the favorite list it will do nothing and print the message below
		{
		cout<<key<<"("<<cv->email<<")"<<" is already a in the favorite list!";
		}
 return true;
}

}
bool ContactBST::unmarkFav(string key)// searches for the node with the provided key and change the mark
{
 
 Node* x=searchFor(root, key); // searches for the node with the provided key
 if (key==""||x==NULL )//prints the message below if no key is provided
{
	cout<<"No key provided or the key doesn't found!";
	return false;
}
else {
 x->print();
 cout<<"Please select the record you want to mark as favorite: ";
 string vecindex;
 getline(cin,vecindex);
 Contact* cv=x->contactVector.at(stoi(vecindex)-1);
 if(cv->isFav==1)//if the the contact is in the favorite list it will unmark it
 {
	cv->isFav=0;
	cout<<key<<"("<<cv->email<<")"<<" has been added successfully unmarked as favorite!";
 }
 else//if the the contact is in the unfavorite it will do nothing and print the message below
		{
		cout<<key<<"("<<cv->email<<")"<<" is already a in the unfavorite list!";
		}
 return true;
}
		
}
void ContactBST::printASC(Node* ptr)//prints the contacts as a comma separated list in ascending order
{
if(ptr==NULL)
{
	cout<<"Nothing to print!"<<endl;
}
else{
if (ptr->left!=NULL) //recurses on the left side of the bst
	{
		printASC(ptr->left);

	}
		
		for (int i=0;i<ptr->contactVector.size();i++) //does the printing
		{
			Contact* ct=ptr->contactVector.at(i);
			cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
		}
	if (ptr->right!=NULL)	//recurses on the right side of the bst
	{
		printASC(ptr->right);
	}
}
}
void ContactBST::printDES(Node* ptr)//prints the contacts as a comma separated list in descending order
{
if(ptr==NULL)
{
	cout<<"Nothing to print!"<<endl;
}
else
{
if (ptr->right!=NULL)	//recurses on the right side of the bst
	{
		printDES(ptr->right);
	}
    for (int i=0;i<ptr->contactVector.size();i++) //does the printing
		{
			Contact* ct=ptr->contactVector.at(i);
			cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
		}
if (ptr->left!=NULL)//recurses on the left side of the bst
	{
		printDES(ptr->left);
	}
}
}
void ContactBST::printFav(Node* ptr) //prints favorite contacts as a comma separated list in ascending order
{
 if(ptr==NULL)
{
	cout<<"Nothing to print!"<<endl;
}
 else{
 if (ptr->left!=NULL)//recurses on the left side of the bst
	{
		printFav(ptr->left);
	}

	for (int i=0;i<ptr->contactVector.size();i++)//does the printing of the favorite lists
		{
			Contact* ct=ptr->contactVector.at(i);
			if(ct->isFav==1)
			{
				cout<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
			}
		}
if (ptr->right!=NULL)	//recurses on the right side of the bst
	{
		printFav(ptr->right);
	}
 }
}
int ContactBST::importCSV(string path)//imports contacts 
{
	int counter;
	string key;
	string fname; string lname; string email; string primaryPhone; string city; string country; bool isFav;string bFav;
	fstream myFile;
	myFile.open(path,ios::in);
	if(myFile.is_open())
	{
		string line;
		while(getline(myFile,line))
		{
		  
		  string coattr[7];  // string array to save the attributes
          stringstream linesav(line);  // string stream object
   
            int z=0;            // declaring i and assign  to 0
   
			while(linesav.good())   // if there is no error our while continues
		     {
			
			
			string a;       
			getline( linesav, a, ',' );   
			coattr[z]=a;
			z++;
     
           }
         fname=coattr[0];
		 lname=coattr[1];
		 email=coattr[2];
		 primaryPhone=coattr[3];
		 city=coattr[4];
		 country=coattr[5];
		 if (coattr[6]=="1")
		 {
			isFav=1;
		 }
		 else
		 {
			isFav=0;
		 }
        Contact* data=new Contact(fname, lname, email,  primaryPhone, city,  country,  isFav); //creating a new contact object for each line
		key=fname +' '+lname;
		add(root,key,data); //adding the created object to the binary search tree
		counter++;
		}
		myFile.close();
	    return counter;
	}
else{
	return -1;
}
}
int ContactBST::exportCSV(Node* ptr, string path)
{
int counter;
fstream myFile;
myFile.open(path,ios::out);
if (myFile.is_open())
{
	Node* cur; Node*bef;
	if (ptr==NULL)
	{
		cout<<"Nothing to export!";
	}
	cur=ptr;
	while(cur!=NULL) //the whole code block inside this while loop is basically an inorder traversal using an iterative approach
	{
		
		if(cur->left==NULL)
		{
		
        for (int i=0;i<cur->contactVector.size();i++) //does the printing
		{
			Contact* ct=cur->contactVector.at(i);
			myFile<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
            counter++;
		}
		cur=cur->right;
		}
		
	    else 
		{
			bef=cur->left;
			while(bef->right!=NULL&&bef->right!=cur)
			{
				bef=bef->right;
			}
			if (bef->right==NULL)
			{
				bef->right=cur;
				cur=cur->left;
			}
			else
			{
			
             bef->right=NULL;
			 for (int i=0;i<cur->contactVector.size();i++) //does the printing
		    {
			Contact* ct=cur->contactVector.at(i);
			myFile<<ct->fname<<","<<ct->lname<<","<<ct->email<<","<<ct->primaryPhone<<","<<ct->city<<","<<ct->country<<","<<ct->isFav<<endl;
			counter++;
		    }
			 cur=cur->right;
			}
		}
	
	}  
return counter; //returning the number of contacts exported
}
else{
	return -1;//if the file can't be opened the function returns -1
}

}

Node* ContactBST::findMin(Node* ptr)//finds a node with a minimum key
{
    if (ptr==NULL)
	{
		cout<<"Error: The tree is empty\n";
	
	}
	while(ptr->left!=NULL)
	{
		ptr=ptr->left;
	}
	return ptr;
}