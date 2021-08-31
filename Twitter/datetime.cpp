
#include <iostream>
#include <sstream>
#include "datetime.h"
#include <ctime>


/**
 * Models a timestamp in format YYYY-MM-DD HH:MM:SS 
 */

  /**
   * Default constructor for current system time/date
   */
  DateTime::DateTime(){
  time_t rawtime;
  struct tm * timeinfo;
  
  time (&rawtime);
  timeinfo = localtime(&rawtime);
   // Use timeinfo pointer to access fields of the tm struct
   // set vairables to what this pointer gives us
   // then call already made function for correct format

   sec = timeinfo->tm_sec;
   hour =timeinfo->tm_hour;
   min =timeinfo-> tm_min;
   this->year = 1900 + timeinfo->tm_year;
   this-> month = 1 + timeinfo->tm_mon;
   this ->day = timeinfo->tm_mday;



  }

  /**
   * Alternative constructor 
   */
  DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day){
      hour = hh;
      min = mm;
      sec = ss;
      this->year = year;
      this-> month = month;
      this ->day = day;

  }

  /**
   * Return true if the timestamp is less-than other's
   *
   * @return result of less-than comparison of timestamp
   */
  bool DateTime::operator<(const DateTime& other) const{
      if(this->year < other.year){
          return true;
      }
      else if(this->year == other.year){
          if(this->month < other.month){
              return true;
          }
          else if(this->month == other.month){
              if(this->day < other.day){
                  return true;
              }
              else if(this->day == other.day){
                  if(this->hour < other.hour){
                      return true;
                  }
                  else if(this->hour == other.hour){
                      if(this->min < other.min){
                          return true;
                      }
                      else if(this->min == other.min){
                          if(this->sec < other.sec){
                              return true;
                          }
                      }
                  }
              }
          }
      }
      return false;

  }

  /**
   * Outputs the timestamp to the given ostream in format:
   *   YYYY-MM-DD HH:MM:SS
   *
   * @return the ostream passed in as an argument
   */
  std::ostream& operator<<(std::ostream& os, const DateTime& other){
    os << other.year << '-' ;
    if(other.month < 10){
        os << "0";
        }
    os << other.month << '-';
    if(other.day < 10){
        os << "0";
    }
    os << other.day << ' ';
    if(other.hour < 10){
        os << "0";
    }
    os  << other.hour << ':';
    if(other.min < 10){
        os << "0";
    }
    os << other.min << ':';
    if(other.sec < 10){
        os << "0";
    }
    os << other.sec;
    
    return os;

  }

  /**
   * Inputs the timestamp from the given istream expecting the format:
   *   YYYY-MM-DD HH:MM:SS
   *  Returns if an error is found in the format but sets the DateTime 
   *   to the current system time/date
   *   
   *
   * @return the istream passed in as an argument
   */
// string stream --> stream of strings
/*
can add stringstream 
acts like a file of texts, can 
getline, delimiter 
put into integer see if fails
*/
  // makes sure date/time format is correct
  //error if not correct + sets time to current time
  // create a timestamp with this info 
  // 
  std::istream& operator>>(std::istream& is, DateTime& dt){
    //bool correct_form = true;
    std::stringstream sstemp_date;
    std::stringstream sstemp_time;
    std::string date;
    std::string time;
    is >> date;
    is >> time;
    sstemp_date.str(date);
    sstemp_time.str(time);
    int hh,  mm,  ss,  year,  month,  day;

    for(int i = 0; i < 3; i++){
    std::string temp;
    getline(sstemp_date, temp, '-');
    int num_temp;
    std::stringstream global_ss;
    global_ss.str(temp);
    global_ss >> num_temp;
    if(global_ss.fail()){
        DateTime tmp;
        dt = tmp;

        return is;
    }
    if(i == 0){
        year = num_temp;
    }
    else if(i == 1){
        month = num_temp;
    }
    else{
        day = num_temp;


    }
    }
    
    for(int i = 0; i < 3; i++){
    std::string temp;
    getline(sstemp_time, temp, ':');
    int num_temp;
    std::stringstream global_ss;
    global_ss.str(temp);
    global_ss >> num_temp;
    if(global_ss.fail()){
        DateTime tmp;
        dt = tmp;

        return is;
    }
    if(i == 0){
        hh = num_temp;
    }
    else if(i == 1){
        mm = num_temp;
    }
    else{
        ss = num_temp;

    }

    }

  std::string date_time = date + " " + time;
  std::stringstream final;
  final.str(date_time);

  DateTime current( hh,  mm,  ss,  year,  month,  day);
  dt = current;

  }


 

  
  


