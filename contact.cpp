#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cctype>
#include "contact.h"
//a constructor for the contact class
Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav) {
    this->fname=fname;
    this->lname=lname;
    this->email=email;
    this->primaryPhone=primaryPhone;
    this->city=city;
    this->country=country;
    this->isFav=isFav;
}

