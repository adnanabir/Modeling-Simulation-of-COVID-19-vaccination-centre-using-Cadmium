#ifndef BOOST_SIMULATION_MESSAGE_HPP
#define BOOST_SIMULATION_MESSAGE_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

/*******************************************/
/**************** MESSAGE_t ****************/
/*******************************************/
struct message_t{
  message_t(){}
  message_t(int i_message)
   :ID(){}

  	int   ID;
};

istream& operator>> (istream& is, message_t& msg);

ostream& operator<<(ostream& os, const message_t& msg);


#endif // BOOST_SIMULATION_MESSAGE_HPP